; Auto-generated. Do not edit!


(cl:in-package dahua_ptzcontrol-msg)


;//! \htmlinclude ptz.msg.html

(cl:defclass <ptz> (roslisp-msg-protocol:ros-message)
  ((test
    :reader test
    :initarg :test
    :type cl:fixnum
    :initform 0))
)

(cl:defclass ptz (<ptz>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ptz>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ptz)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dahua_ptzcontrol-msg:<ptz> is deprecated: use dahua_ptzcontrol-msg:ptz instead.")))

(cl:ensure-generic-function 'test-val :lambda-list '(m))
(cl:defmethod test-val ((m <ptz>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dahua_ptzcontrol-msg:test-val is deprecated.  Use dahua_ptzcontrol-msg:test instead.")
  (test m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ptz>) ostream)
  "Serializes a message object of type '<ptz>"
  (cl:let* ((signed (cl:slot-value msg 'test)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ptz>) istream)
  "Deserializes a message object of type '<ptz>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'test) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ptz>)))
  "Returns string type for a message object of type '<ptz>"
  "dahua_ptzcontrol/ptz")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ptz)))
  "Returns string type for a message object of type 'ptz"
  "dahua_ptzcontrol/ptz")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ptz>)))
  "Returns md5sum for a message object of type '<ptz>"
  "f1a6ca594e44b73a507295573c903a8b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ptz)))
  "Returns md5sum for a message object of type 'ptz"
  "f1a6ca594e44b73a507295573c903a8b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ptz>)))
  "Returns full string definition for message of type '<ptz>"
  (cl:format cl:nil "int8 test~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ptz)))
  "Returns full string definition for message of type 'ptz"
  (cl:format cl:nil "int8 test~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ptz>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ptz>))
  "Converts a ROS message object to a list"
  (cl:list 'ptz
    (cl:cons ':test (test msg))
))
