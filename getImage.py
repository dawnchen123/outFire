# -*- coding: UTF-8 -*-
import cv2 
import rospy
import threading
import time
from std_msgs.msg import Float32MultiArray

rospy.init_node('ptzcontrol123', anonymous=True)

pub_firePosition = rospy.Publisher('/fire/position', Float32MultiArray, queue_size=1)

global max_T,min_T

global firePosition
firePosition = Float32MultiArray()


def callback_position(msg):
    global max_T,min_T
    min_T = msg.data[0]
    max_T = msg.data[1]
    # y = msg.pose.pose.position.y
    # z = msg.pose.pose.position.z
    # rospy.loginfo(str(x) + "," + str(y)+ "," + str(z))
    # fo.write(str(x) + "," + str(y)+ "," + str(z)+ '\n')
    

    
def listener():
 
    temperature_topic = "temperature_data"
    
    rospy.Subscriber(temperature_topic, Float32MultiArray, callback_position)
    # time.sleep(0.1)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()


def getImage():
    global max_T,min_T
    fire_T = 80
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
        hotmap = frame2[:,:,0]  #
        
        cv2.imshow("frame",frame)
        cv2.imshow("frame2",frame2)
        max_gray = hotmap[120,600]  #max gray by max temperature
        min_gray = hotmap[347,600]  #min gray by min temperature
        # print(max_gray,min_gray)
        if max_T > 80 or max_T ==80:
            multiple = (max_gray - min_gray)/(max_T - min_T)
            current_gray = (fire_T - min_T)*multiple+min_gray   #80度对应的灰度值           
            res, hotmap = cv2.threshold(hotmap,int(current_gray),255,0)
            print(current_gray)
            firePosition.data = [100,200]
            # firePosition.data.append(100) 
            # firePosition.data.append(200) 
            pub_firePosition.publish(firePosition)
            firePosition.data.pop


            

            cv2.imshow("fire_image",hotmap)

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
