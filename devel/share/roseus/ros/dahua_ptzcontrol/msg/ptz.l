;; Auto-generated. Do not edit!


(when (boundp 'dahua_ptzcontrol::ptz)
  (if (not (find-package "DAHUA_PTZCONTROL"))
    (make-package "DAHUA_PTZCONTROL"))
  (shadow 'ptz (find-package "DAHUA_PTZCONTROL")))
(unless (find-package "DAHUA_PTZCONTROL::PTZ")
  (make-package "DAHUA_PTZCONTROL::PTZ"))

(in-package "ROS")
;;//! \htmlinclude ptz.msg.html


(defclass dahua_ptzcontrol::ptz
  :super ros::object
  :slots (_test ))

(defmethod dahua_ptzcontrol::ptz
  (:init
   (&key
    ((:test __test) 0)
    )
   (send-super :init)
   (setq _test (round __test))
   self)
  (:test
   (&optional __test)
   (if __test (setq _test __test)) _test)
  (:serialization-length
   ()
   (+
    ;; int8 _test
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _test
       (write-byte _test s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _test
     (setq _test (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _test 127) (setq _test (- _test 256)))
   ;;
   self)
  )

(setf (get dahua_ptzcontrol::ptz :md5sum-) "f1a6ca594e44b73a507295573c903a8b")
(setf (get dahua_ptzcontrol::ptz :datatype-) "dahua_ptzcontrol/ptz")
(setf (get dahua_ptzcontrol::ptz :definition-)
      "int8 test
")



(provide :dahua_ptzcontrol/ptz "f1a6ca594e44b73a507295573c903a8b")


