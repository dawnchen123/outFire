; Auto-generated. Do not edit!


(cl:in-package dahua_ptzcontrol-msg)


;//! \htmlinclude HeatMapTemp.msg.html

(cl:defclass <HeatMapTemp> (roslisp-msg-protocol:ros-message)
  ((temp
    :reader temp
    :initarg :temp
    :type cl:float
    :initform 0.0)
   (timer
    :reader timer
    :initarg :timer
    :type cl:integer
    :initform 0))
)

(cl:defclass HeatMapTemp (<HeatMapTemp>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <HeatMapTemp>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'HeatMapTemp)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dahua_ptzcontrol-msg:<HeatMapTemp> is deprecated: use dahua_ptzcontrol-msg:HeatMapTemp instead.")))

(cl:ensure-generic-function 'temp-val :lambda-list '(m))
(cl:defmethod temp-val ((m <HeatMapTemp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dahua_ptzcontrol-msg:temp-val is deprecated.  Use dahua_ptzcontrol-msg:temp instead.")
  (temp m))

(cl:ensure-generic-function 'timer-val :lambda-list '(m))
(cl:defmethod timer-val ((m <HeatMapTemp>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dahua_ptzcontrol-msg:timer-val is deprecated.  Use dahua_ptzcontrol-msg:timer instead.")
  (timer m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <HeatMapTemp>) ostream)
  "Serializes a message object of type '<HeatMapTemp>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'temp))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'timer)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <HeatMapTemp>) istream)
  "Deserializes a message object of type '<HeatMapTemp>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'temp) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'timer) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<HeatMapTemp>)))
  "Returns string type for a message object of type '<HeatMapTemp>"
  "dahua_ptzcontrol/HeatMapTemp")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'HeatMapTemp)))
  "Returns string type for a message object of type 'HeatMapTemp"
  "dahua_ptzcontrol/HeatMapTemp")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<HeatMapTemp>)))
  "Returns md5sum for a message object of type '<HeatMapTemp>"
  "5584b0e644c8f93b541882b48b5271fc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'HeatMapTemp)))
  "Returns md5sum for a message object of type 'HeatMapTemp"
  "5584b0e644c8f93b541882b48b5271fc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<HeatMapTemp>)))
  "Returns full string definition for message of type '<HeatMapTemp>"
  (cl:format cl:nil "float32 temp~%int32 timer~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'HeatMapTemp)))
  "Returns full string definition for message of type 'HeatMapTemp"
  (cl:format cl:nil "float32 temp~%int32 timer~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <HeatMapTemp>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <HeatMapTemp>))
  "Converts a ROS message object to a list"
  (cl:list 'HeatMapTemp
    (cl:cons ':temp (temp msg))
    (cl:cons ':timer (timer msg))
))
