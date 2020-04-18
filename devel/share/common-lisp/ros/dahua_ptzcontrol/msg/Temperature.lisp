; Auto-generated. Do not edit!


(cl:in-package dahua_ptzcontrol-msg)


;//! \htmlinclude Temperature.msg.html

(cl:defclass <Temperature> (roslisp-msg-protocol:ros-message)
  ((max_temperature
    :reader max_temperature
    :initarg :max_temperature
    :type cl:float
    :initform 0.0)
   (min_temperature
    :reader min_temperature
    :initarg :min_temperature
    :type cl:float
    :initform 0.0)
   (timer
    :reader timer
    :initarg :timer
    :type cl:integer
    :initform 0))
)

(cl:defclass Temperature (<Temperature>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Temperature>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Temperature)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dahua_ptzcontrol-msg:<Temperature> is deprecated: use dahua_ptzcontrol-msg:Temperature instead.")))

(cl:ensure-generic-function 'max_temperature-val :lambda-list '(m))
(cl:defmethod max_temperature-val ((m <Temperature>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dahua_ptzcontrol-msg:max_temperature-val is deprecated.  Use dahua_ptzcontrol-msg:max_temperature instead.")
  (max_temperature m))

(cl:ensure-generic-function 'min_temperature-val :lambda-list '(m))
(cl:defmethod min_temperature-val ((m <Temperature>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dahua_ptzcontrol-msg:min_temperature-val is deprecated.  Use dahua_ptzcontrol-msg:min_temperature instead.")
  (min_temperature m))

(cl:ensure-generic-function 'timer-val :lambda-list '(m))
(cl:defmethod timer-val ((m <Temperature>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dahua_ptzcontrol-msg:timer-val is deprecated.  Use dahua_ptzcontrol-msg:timer instead.")
  (timer m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Temperature>) ostream)
  "Serializes a message object of type '<Temperature>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'max_temperature))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'min_temperature))))
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Temperature>) istream)
  "Deserializes a message object of type '<Temperature>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'max_temperature) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'min_temperature) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'timer) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Temperature>)))
  "Returns string type for a message object of type '<Temperature>"
  "dahua_ptzcontrol/Temperature")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Temperature)))
  "Returns string type for a message object of type 'Temperature"
  "dahua_ptzcontrol/Temperature")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Temperature>)))
  "Returns md5sum for a message object of type '<Temperature>"
  "efdfa2e0b9ac13acef941502135a514f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Temperature)))
  "Returns md5sum for a message object of type 'Temperature"
  "efdfa2e0b9ac13acef941502135a514f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Temperature>)))
  "Returns full string definition for message of type '<Temperature>"
  (cl:format cl:nil "float32 max_temperature~%float32 min_temperature~%int32 timer~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Temperature)))
  "Returns full string definition for message of type 'Temperature"
  (cl:format cl:nil "float32 max_temperature~%float32 min_temperature~%int32 timer~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Temperature>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Temperature>))
  "Converts a ROS message object to a list"
  (cl:list 'Temperature
    (cl:cons ':max_temperature (max_temperature msg))
    (cl:cons ':min_temperature (min_temperature msg))
    (cl:cons ':timer (timer msg))
))
