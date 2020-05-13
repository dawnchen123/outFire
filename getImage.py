# -*- coding: UTF-8 -*-
import cv2 
import rospy
import threading
import time
import datetime
from time import sleep
from std_msgs.msg import Float32MultiArray

from onvif import ONVIFCamera
import zeep


rospy.init_node('ptzcontrol123', anonymous=True)
pub_firePosition = rospy.Publisher('/fire/position', Float32MultiArray, queue_size=1)   #定义火源坐标发布话题

global max_T,min_T
global firePosition
global detect_fire
detect_fire = bool(0)
firePosition = Float32MultiArray() #火源坐标初始化


def zeep_pythonvalue(self, xmlvalue):
    return xmlvalue
 
def perform_move(ptz, request, timeout):
    # Start continuous move
    ptz.ContinuousMove(request)
    print(datetime.datetime.now())
    # Wait a certain time
    sleep(timeout)
    print(datetime.datetime.now())
    # Stop continuous move
    ptz.Stop({'ProfileToken': request.ProfileToken})
 
 
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

def stop_move(ptz, request,timeout=1):
    print('stop move!') 
    request.Velocity.PanTilt.x = 0
    request.Velocity.PanTilt.y = 0
    perform_move(ptz, request, timeout)

def callback_position(msg):
    global max_T,min_T
    print("receive mgs:" + str(msg.data))
    min_T = msg.data[0]
    max_T = msg.data[1]

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
    global detect_fire
    while not detect_fire:
        move_right(ptz, request, 0.2,14)
        move_left(ptz, request, -0.2,14)
        time.sleep(0.1)
    stop_move(ptz, request)    #停止移动云台




      
def listener():
 
    temperature_topic = "temperature_data"
    
    rospy.Subscriber(temperature_topic, Float32MultiArray, callback_position)
    time.sleep(0.1)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()


def getImage():

    global max_T,min_T,detect_fire

    cx = 0
    cy = 0
    fire_T = 10         #定义与火源最高温度的差值
    cap = cv2.VideoCapture("rtsp://admin:admin123@192.168.1.108/cam/realmonitor?channel=2&subtype=1")  #hotmap

    ret,frame = cap.read()
    while ret:
        
        # print(max_T,min_T)
        ret,frame = cap.read()
        frame = cv2.resize(frame,(640,480))
        max_gray = frame[120,600,0]  #max gray by max temperature
        min_gray = frame[347,600,0]  #min gray by min temperature
        frame=cv2.rectangle(frame,(592,116),(610,350),(0,0,0),-1) #这里将温度指示框删除
        hotmap = frame[:,:,0]  #获取热图
        # print(max_gray,min_gray)
        if max_T > 100:
            multiple = (max_gray - min_gray)/(max_T - min_T)
            current_gray = (max_T-fire_T - min_T)*multiple+min_gray   #100度对应的灰度值           
            # current_gray = max_gray-10   #100度对应的灰度值           

            res, hotmap = cv2.threshold(hotmap,int(current_gray),255,0)
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
                move_left(ptz, request,0,1)

                firePosition.data = [cx-320,cy-240] #将火源坐标用ROS 话题发布
            else:
                firePosition.data = [0,0]
            pub_firePosition.publish(firePosition)

            cv2.imshow("fire_image",hotmap)
        cv2.imshow("frame",frame)
        # cv2.imshow("frame2",frame2)
        if cv2.waitKey(10) & 0xFF == ord('q'):
            break

    cv2.destroyAllWindows()
    cap.release()

#多线程执行云台控制/温度获取/热红外图像采集
class myThread (threading.Thread):
    def __init__(self,func, threadID, name):
        threading.Thread.__init__(self)
        self.func = func
        self.threadID = threadID
        self.name = name
    def run(self):
        print ("开启线程： " + self.name)
        self.func()
        # 获取锁，用于线程同步
        threadLock.acquire()
        # 释放锁，开启下一个线程
        threadLock.release()


if __name__ == '__main__':
    threadLock = threading.Lock() #创建线程锁
    threads = []

    #创建线程
    thread1 = myThread(ptzControl,1,"Thread-1: ptzControl")
    thread2 = myThread(listener,2,"Thread-2: listener")
    thread3 = myThread(getImage,3,"Thread-3: getImage")

    
    # 开启新线程
    thread1.start()
    thread2.start()
    thread3.start()

    # 添加线程到线程列表
    threads.append(thread1)
    threads.append(thread2)
    threads.append(thread3)


    # # 等待所有线程完成
    for t in threads:
        t.join()
    print ("退出主线程")

    # t1 = threading.Thread(target=ptzControl)
    # t2 = threading.Thread(target=listener)
    # t3 = threading.Thread(target=getImage)
    # t1.start()
    # t2.start()
    # t3.start()
