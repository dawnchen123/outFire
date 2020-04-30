# -*- coding: UTF-8 -*-
import cv2 
import rospy
import threading
import time
from std_msgs.msg import Float32MultiArray

rospy.init_node('ptzcontrol123', anonymous=True)
pub_firePosition = rospy.Publisher('/fire/position', Float32MultiArray, queue_size=1)   #定义火源坐标发布话题

global max_T,min_T
global firePosition
firePosition = Float32MultiArray() #火源坐标初始化


def callback_position(msg):
    global max_T,min_T
    min_T = msg.data[0]
    max_T = msg.data[1]
    # y = msg.pose.pose.position.y
    # z = msg.pose.pose.position.z
    # rospy.loginfo(str(x) + "," + str(y)+ "," + str(z))
    # fo.write(str(x) + "," + str(y)+ "," + str(z)+ '\n')

def getCenter(image):
    contours,hierarchy = cv2.findContours(image,1,2)
    cv2.drawContours(image,contours[0],(0,255,0),3)
    cnt = contours[0]
    M = cv2.moments(cnt)
    print M
    cx = int(M['m10']/M['m00'])
    cy = int(M['m01']/M['m00'])

    

    
def listener():
 
    temperature_topic = "temperature_data"
    
    rospy.Subscriber(temperature_topic, Float32MultiArray, callback_position)
    # time.sleep(0.1)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()


def getImage():
    global max_T,min_T
    cx = 0
    cy = 0
    fire_T = 80         #定义火源最低温度
    cap = cv2.VideoCapture("rtsp://admin:admin123@192.168.1.108/cam/realmonitor?channel=1&subtype=0")  #RGB
    cap2 = cv2.VideoCapture("rtsp://admin:admin123@192.168.1.108/cam/realmonitor?channel=2&subtype=0")  #hotmap

    ret,frame = cap.read()
    ret2,frame2 = cap2.read()
    while ret:
        # print(max_T,min_T)
        ret,frame = cap.read()
        ret2,frame2 = cap2.read()
        frame = cv2.resize(frame,(640,480))
        frame2 = cv2.resize(frame2,(640,480))
        max_gray = frame2[120,600,0]  #max gray by max temperature
        min_gray = frame2[347,600,0]  #min gray by min temperature
        frame2=cv2.rectangle(frame2,(592,116),(610,350),(0,0,0),-1) #这里将温度指示框删除
        hotmap = frame2[:,:,0]  #获取热图
        # print(max_gray,min_gray)
        if max_T > 80 or max_T == 80:
            multiple = (max_gray - min_gray)/(max_T - min_T)
            current_gray = (fire_T - min_T)*multiple+min_gray   #100度对应的灰度值           
            res, hotmap = cv2.threshold(hotmap,int(current_gray),255,0)
            print(current_gray)

            hotmap,contours,hierarchy = cv2.findContours(hotmap,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
            # cv2.drawContours(hotmap,contours,(0,255,0),3)
            for i in range(len(contours)):
                if cv2.contourArea(contours[i])> 200:
                    cnt = contours[i]
                    M = cv2.moments(cnt)
                    cx = int(M['m10']/M['m00'])
                    cy = int(M['m01']/M['m00'])
                    print(str(cx)+','+str(cy))
            if cx > 0 and cy > 0:
                firePosition.data = [cx-320,cy-240] #将火源坐标用ROS 话题发布
            else:
                firePosition.data = [0,0]
            pub_firePosition.publish(firePosition)

            cv2.imshow("fire_image",hotmap)
        cv2.imshow("frame",frame)
        cv2.imshow("frame2",frame2)
        if cv2.waitKey(10) & 0xFF == ord('q'):
            break
        time.sleep(0.01)

    cv2.destroyAllWindows()
    cap.release()

if __name__ == '__main__':
    t1 = threading.Thread(target=listener)
    t2 = threading.Thread(target=getImage)
    t1.start()
    t2.start()
