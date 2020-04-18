;; Auto-generated. Do not edit!


(when (boundp 'dahua_ptzcontrol::HeatMapTemp)
  (if (not (find-package "DAHUA_PTZCONTROL"))
    (make-package "DAHUA_PTZCONTROL"))
  (shadow 'HeatMapTemp (find-package "DAHUA_PTZCONTROL")))
(unless (find-package "DAHUA_PTZCONTROL::HEATMAPTEMP")
  (make-package "DAHUA_PTZCONTROL::HEATMAPTEMP"))

(in-package "ROS")
;;//! \htmlinclude HeatMapTemp.msg.html


(defclass dahua_ptzcontrol::HeatMapTemp
  :super ros::object
  :slots (_temp _timer ))

(defmethod dahua_ptzcontrol::HeatMapTemp
  (:init
   (&key
    ((:temp __temp) 0.0)
    ((:timer __timer) 0)
    )
   (send-super :init)
   (setq _temp (float __temp))
   (setq _timer (round __timer))
   self)
  (:temp
   (&optional __temp)
   (if __temp (setq _temp __temp)) _temp)
  (:timer
   (&optional __timer)
   (if __timer (setq _timer __timer)) _timer)
  (:serialization-length
   ()
   (+
    ;; float32 _temp
    4
    ;; int32 _timer
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _temp
       (sys::poke _temp (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _timer
       (write-long _timer s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _temp
     (setq _temp (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _timer
     (setq _timer (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get dahua_ptzcontrol::HeatMapTemp :md5sum-) "5584b0e644c8f93b541882b48b5271fc")
(setf (get dahua_ptzcontrol::HeatMapTemp :datatype-) "dahua_ptzcontrol/HeatMapTemp")
(setf (get dahua_ptzcontrol::HeatMapTemp :definition-)
      "float32 temp
int32 timer

")



(provide :dahua_ptzcontrol/HeatMapTemp "5584b0e644c8f93b541882b48b5271fc")


