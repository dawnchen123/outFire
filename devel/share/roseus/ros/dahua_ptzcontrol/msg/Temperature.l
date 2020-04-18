;; Auto-generated. Do not edit!


(when (boundp 'dahua_ptzcontrol::Temperature)
  (if (not (find-package "DAHUA_PTZCONTROL"))
    (make-package "DAHUA_PTZCONTROL"))
  (shadow 'Temperature (find-package "DAHUA_PTZCONTROL")))
(unless (find-package "DAHUA_PTZCONTROL::TEMPERATURE")
  (make-package "DAHUA_PTZCONTROL::TEMPERATURE"))

(in-package "ROS")
;;//! \htmlinclude Temperature.msg.html


(defclass dahua_ptzcontrol::Temperature
  :super ros::object
  :slots (_max_temperature _min_temperature _timer ))

(defmethod dahua_ptzcontrol::Temperature
  (:init
   (&key
    ((:max_temperature __max_temperature) 0.0)
    ((:min_temperature __min_temperature) 0.0)
    ((:timer __timer) 0)
    )
   (send-super :init)
   (setq _max_temperature (float __max_temperature))
   (setq _min_temperature (float __min_temperature))
   (setq _timer (round __timer))
   self)
  (:max_temperature
   (&optional __max_temperature)
   (if __max_temperature (setq _max_temperature __max_temperature)) _max_temperature)
  (:min_temperature
   (&optional __min_temperature)
   (if __min_temperature (setq _min_temperature __min_temperature)) _min_temperature)
  (:timer
   (&optional __timer)
   (if __timer (setq _timer __timer)) _timer)
  (:serialization-length
   ()
   (+
    ;; float32 _max_temperature
    4
    ;; float32 _min_temperature
    4
    ;; int32 _timer
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _max_temperature
       (sys::poke _max_temperature (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _min_temperature
       (sys::poke _min_temperature (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _timer
       (write-long _timer s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _max_temperature
     (setq _max_temperature (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _min_temperature
     (setq _min_temperature (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _timer
     (setq _timer (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get dahua_ptzcontrol::Temperature :md5sum-) "efdfa2e0b9ac13acef941502135a514f")
(setf (get dahua_ptzcontrol::Temperature :datatype-) "dahua_ptzcontrol/Temperature")
(setf (get dahua_ptzcontrol::Temperature :definition-)
      "float32 max_temperature
float32 min_temperature
int32 timer
")



(provide :dahua_ptzcontrol/Temperature "efdfa2e0b9ac13acef941502135a514f")


