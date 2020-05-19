#!/usr/bin/env python3

################################################################################

# Example : perform live fire detection in video using FireNet CNN

# Copyright (c) 2017/18 - Andrew Dunnings / Toby Breckon, Durham University, UK

# License : https://github.com/tobybreckon/fire-detection-cnn/blob/master/LICENSE

################################################################################
import sys
import cv2
import os
import math
import rospy
import threading
import ctypes
import inspect
import time
from datetime import datetime
from time import sleep
from onvif import ONVIFCamera
import zeep

from std_msgs.msg import Float32MultiArray

################################################################################

import tflearn
from tflearn.layers.core import *
from tflearn.layers.conv import *
from tflearn.layers.normalization import *
from tflearn.layers.estimator import regression

################################################################################
rospy.init_node('ptzcontrol123',anonymous=True)
pub_cnnResult = rospy.Publisher('/fire/result',Float32MultiArray,queue_size=1)
global cnnResult
cnnResult = Float32MultiArray()


pub_firePosition = rospy.Publisher('/fire/position', Float32MultiArray, queue_size=1)   #定义火源坐标发布话题

global max_T,min_T
global firePosition
global detect_fire,cnn_fire,cnnCount
global start_t,stop_t
global thread1
detect_fire = bool(0)
cnn_fire = bool(0)
firePosition = Float32MultiArray() #火源坐标初始化
cnnCount=0
start_t = datetime.utcnow()
stop_t = datetime.utcnow()



def zeep_pythonvalue(self, xmlvalue):
    return xmlvalue
 
def perform_move(ptz, request, timeout):
    # Start continuous move
    ptz.ContinuousMove(request)
    # Wait a certain time
    sleep(timeout)
    # Stop continuous move
    ptz.Stop({'ProfileToken': request.ProfileToken})
 
def move(ptz, request,speed_horizen,speed_vertical,timeout=1):
    request.Velocity.PanTilt.x = speed_horizen
    request.Velocity.PanTilt.y = speed_vertical
    perform_move(ptz, request, timeout)

 
def move_up(ptz, request,speed, timeout=1):
    print('move up...') 
    request.Velocity.PanTilt.x = 0
    request.Velocity.PanTilt.y = speed
    perform_move(ptz, request, timeout)
 
def move_down(ptz, request,speed, timeout=1):
    print('move down...') 
    request.Velocity.PanTilt.x = 0
    request.Velocity.PanTilt.y = speed
    perform_move(ptz, request, timeout)
 
def move_right(ptz, request,speed, timeout=1):
    print('move right...') 
    request.Velocity.PanTilt.x = speed
    request.Velocity.PanTilt.y = 0
    perform_move(ptz, request, timeout)
 
def move_left(ptz, request,speed, timeout=1):
    print('move left...') 
    request.Velocity.PanTilt.x = speed
    request.Velocity.PanTilt.y = 0
    perform_move(ptz, request, timeout)

def stop_move(ptz, request,timeout=0.05):
    print('stop move!') 
    request.Velocity.PanTilt.x = 0
    request.Velocity.PanTilt.y = 0
    perform_move(ptz, request, timeout)

def callback_position(msg):
    global max_T,min_T
    # print("receive mgs:" + str(msg.data))
    min_T = msg.data[0]
    max_T = msg.data[1]

################################ Kill Thread ##############################
def _async_raise(tid, exctype):
    """raises the exception, performs cleanup if needed"""
    tid = ctypes.c_long(tid)
    if not inspect.isclass(exctype):
        exctype = type(exctype)
    res = ctypes.pythonapi.PyThreadState_SetAsyncExc(tid, ctypes.py_object(exctype))
    if res == 0:
        raise ValueError("invalid thread id")
    elif res != 1:
        # """if it returns a number greater than one, you're in trouble,
        # and you should call it again with exc=NULL to revert the effect"""
        ctypes.pythonapi.PyThreadState_SetAsyncExc(tid, None)
        raise SystemError("PyThreadState_SetAsyncExc failed")
 
def stop_thread(thread):
    _async_raise(thread.ident, SystemExit)
###########################################################################
def construct_firenet (x,y, training=False):

    # Build network as per architecture in [Dunnings/Breckon, 2018]

    network = tflearn.input_data(shape=[None, y, x, 3], dtype=tf.float32)

    network = conv_2d(network, 64, 5, strides=4, activation='relu')

    network = max_pool_2d(network, 3, strides=2)
    network = local_response_normalization(network)

    network = conv_2d(network, 128, 4, activation='relu')

    network = max_pool_2d(network, 3, strides=2)
    network = local_response_normalization(network)

    network = conv_2d(network, 256, 1, activation='relu')

    network = max_pool_2d(network, 3, strides=2)
    network = local_response_normalization(network)

    network = fully_connected(network, 4096, activation='tanh')
    if(training):
        network = dropout(network, 0.5)

    network = fully_connected(network, 4096, activation='tanh')
    if(training):
        network = dropout(network, 0.5)

    network = fully_connected(network, 2, activation='softmax')

    # if training then add training hyperparameters

    if(training):
        network = regression(network, optimizer='momentum',
                            loss='categorical_crossentropy',
                            learning_rate=0.001)

    # constuct final model

    model = tflearn.DNN(network, checkpoint_path='firenet',
                        max_checkpoints=1, tensorboard_verbose=2)

    return model


# construct and display model

model = construct_firenet (224, 224, training=False)
print("Constructed FireNet ...")

model.load(os.path.join("models/FireNet", "firenet"),weights_only=True)
print("Loaded CNN network weights ...")

################################################################################


#云台控制初始化
# def continuous_move():
mycam = ONVIFCamera('192.168.1.108', 80, 'admin', 'admin123')
# Create media service object
media = mycam.create_media_service()
# Create ptz service object
ptz = mycam.create_ptz_service()

# Get target profile
zeep.xsd.simple.AnySimpleType.pythonvalue = zeep_pythonvalue
media_profile = media.GetProfiles()[0]

# Get PTZ configuration options for getting continuous move range
request = ptz.create_type('GetConfigurationOptions')
request.ConfigurationToken = media_profile.PTZConfiguration.token
ptz_configuration_options = ptz.GetConfigurationOptions(request)

request = ptz.create_type('ContinuousMove')
request.ProfileToken = media_profile.token
ptz.Stop({'ProfileToken': media_profile.token})

if request.Velocity is None:
    request.Velocity = ptz.GetStatus({'ProfileToken': media_profile.token}).Position
    request.Velocity = ptz.GetStatus({'ProfileToken': media_profile.token}).Position
    request.Velocity.PanTilt.space = ptz_configuration_options.Spaces.ContinuousPanTiltVelocitySpace[0].URI
    request.Velocity.Zoom.space = ptz_configuration_options.Spaces.ContinuousZoomVelocitySpace[0].URI



def ptzControl():
    global detect_fire,cnn_fire
    while True:
        if not (detect_fire or cnn_fire):
            move_right(ptz, request, 0.2,14)
            move_left(ptz, request, -0.2,14)
        elif detect_fire and cnn_fire:
            if firePosition.data[0] != 0:
                if (firePosition.data[0]<-50 and firePosition.data[1]<-50): #左上
                    move(ptz, request, -0.2,0.2,0.1) 
                    print("LEFTTOP")
                elif (firePosition.data[0]<-50 and firePosition.data[1]>50): #左下
                    move(ptz, request, -0.2,-0.2,0.1) 
                    print("LEFTDOWN")
                elif (firePosition.data[0]>50 and firePosition.data[1]<-50): #右上
                    move(ptz, request, 0.2,0.2,0.1) 
                    print("RIGHTTOP")
                elif (firePosition.data[0]>50 and firePosition.data[1]>50): #右下
                    move(ptz, request, 0.2,-0.2,0.1) 
                    print("RIGHTDOWN")
                else:
                    print("stop")
                    stop_move(ptz, request)    #停止移动云台
        else:
            stop_move(ptz, request)    #停止移动云台
        time.sleep(0.1)
    # stop_move(ptz, request)    #停止移动云台


def ptzMoveToFire():
    global detect_fire,cnn_fire
    while True:
        if cnn_fire:
            print("detect CNN_fire")
        if detect_fire and cnn_fire:
            if firePosition.data[0] != 0:
                if (firePosition.data[0]<-50 and firePosition.data[1]<-50): #左上
                    move(ptz, request, -0.2,0.2,0.1) 
                    print("LEFTTOP")
                elif (firePosition.data[0]<-50 and firePosition.data[1]>50): #左下
                    move(ptz, request, -0.2,-0.2,0.1) 
                    print("LEFTDOWN")
                elif (firePosition.data[0]>50 and firePosition.data[1]<-50): #右上
                    move(ptz, request, 0.2,0.2,0.1) 
                    print("RIGHTTOP")
                elif (firePosition.data[0]>50 and firePosition.data[1]>50): #右下
                    move(ptz, request, 0.2,-0.2,0.1) 
                    print("RIGHTDOWN")
                else:
                    print("stop")
                    stop_move(ptz, request)    #停止移动云台
        time.sleep(0.1)

      
def listener():
 
    temperature_topic = "temperature_data"
    
    rospy.Subscriber(temperature_topic, Float32MultiArray, callback_position)
    time.sleep(0.1)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()


def getImage():

    global max_T,min_T,detect_fire,cnn_fire

    cx = 0
    cy = 0
    fire_T = 10         #定义与火源最高温度的差值
    cap = cv2.VideoCapture("rtsp://admin:admin123@192.168.1.108/cam/realmonitor?channel=2&subtype=1")  #hotmap
    video = cv2.VideoCapture("rtsp://admin:admin123@192.168.1.108/cam/realmonitor?channel=1&subtype=1")
    
    width = int(video.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(video.get(cv2.CAP_PROP_FRAME_HEIGHT))

    ret,frame = cap.read()

    ret2, frame2 = video.read()

    while ret:
        
        # print(max_T,min_T)
        ret,frame = cap.read()
        ret2, frame2 = video.read()

        frame = cv2.resize(frame,(640,480))
        if not cnn_fire:
            firenetDetect(frame2,width,height)
        max_gray = frame[120,600,0]  #max gray by max temperature
        min_gray = frame[347,600,0]  #min gray by min temperature
        frame=cv2.rectangle(frame,(592,116),(610,350),(0,0,0),-1) #这里将温度指示框删除
        hotmap = frame[:,:,0]  #获取热图
        # print(max_gray,min_gray)
        if max_T > 100:
            multiple = (max_gray - min_gray)/(max_T - min_T)
            current_gray = (max_T-fire_T - min_T)*multiple+min_gray   #100度对应的灰度值           
            # current_gray = max_gray-10   #100度对应的灰度值           

            res, hotmap = cv2.threshold(hotmap,int(current_gray),255,0) #提取出火
            print(current_gray)

            contours,hierarchy = cv2.findContours(hotmap,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
            # cv2.drawContours(hotmap,contours,(0,255,0),3)
            for i in range(len(contours)):
                if cv2.contourArea(contours[i])> 200:
                    cnt = contours[i]
                    M = cv2.moments(cnt)
                    cx = int(M['m10']/M['m00'])
                    cy = int(M['m01']/M['m00'])
                    print(str(cx)+','+str(cy))
            if cx > 0 and cy > 0:
                detect_fire = bool(1)
                firePosition.data = [cx-320,cy-240] #将火源坐标用ROS 话题发布
            else:
                firePosition.data = [0,0]
            # pub_firePosition.publish(firePosition)

            cv2.imshow("fire_image",hotmap)
        cv2.imshow("frame",frame)
        # cv2.imshow("frame2",frame2)
        if cv2.waitKey(10) & 0xFF == ord('q'):
            break

    cv2.destroyAllWindows()
    cap.release()


################################################################################

def firenetDetect(frame,width,height):
    global thread1
################################################################################
    global cnn_fire
    global cnnCount
    global start_t,stop_t
    # network input sizes
    rows = 224
    cols = 224
################################################################################

    # re-size image to network input size and perform prediction

    small_frame = cv2.resize(frame, (rows, cols), cv2.INTER_AREA)
    output = model.predict([small_frame])

    # label image based on prediction
    if round(output[0][0]) == 1:
        cnnCount=cnnCount+1
        if cnnCount == 1:
            start_t = datetime.utcnow()
        cv2.rectangle(frame, (0,0), (width,height), (0,0,255), 50)
        cv2.putText(frame,'FIRE',(int(width/16),int(height/4)),
            cv2.FONT_HERSHEY_SIMPLEX, 4,(255,255,255),10,cv2.LINE_AA);
        if cnnCount>20:
            stop_t = datetime.utcnow()
            dt = stop_t-start_t
            print("time: " + str(dt.seconds) + " s, " + str(dt.microseconds/1000)+ " ms")
            if dt.seconds<1:
                stop_move(ptz, request)    #停止移动云台
                # sleep(5)
                stop_thread(thread1)    #退出云台移动线程1
                cnn_fire = bool(1)
            else:
                cnnCount = 0
    else:
        cv2.rectangle(frame, (0,0), (width,height), (0,255,0), 50)
        cv2.putText(frame,'CLEAR',(int(width/16),int(height/4)),
            cv2.FONT_HERSHEY_SIMPLEX, 4,(255,255,255),10,cv2.LINE_AA);
    # pub_cnnResult.publish(cnnResult)
    # image display and key handling

    cv2.imshow("cnnResult", frame);     
    # key = cv2.waitKey(max(2, frame_time - int(math.ceil(stop_t)))) & 0xFF;
################################################################################

#多线程执行云台控制/温度获取/热红外图像采集
class myThread (threading.Thread):
    def __init__(self,func, threadID, name):
        threading.Thread.__init__(self)
        self.func = func
        self.threadID = threadID
        self.name = name
        self._stop_event = threading.Event()
    def run(self):
        print ("开启线程： " + self.name)
        self.func()
        # 获取锁，用于线程同步
        threadLock.acquire()
        # 释放锁，开启下一个线程
        threadLock.release()

if __name__ == '__main__':
    global thread1
    threadLock = threading.Lock()
    threads = []
    thread1 = myThread(ptzControl,1,"Thread-1: ptzControl")
    thread2 = myThread(listener,2,"Thread-2: listener")
    thread3 = myThread(getImage,3,"Thread-3: getImage")
    thread4 = myThread(ptzMoveToFire,4,"Thread-4: ptzMoveToFire")

    
    # 开启新线程
    thread1.start()
    thread2.start()
    thread3.start()
    thread4.start()

    threads.append(thread1)
    threads.append(thread2)
    threads.append(thread3)
    threads.append(thread4)


    # # 等待所有线程完成
    for t in threads:
        t.join()
    print ("退出主线程")