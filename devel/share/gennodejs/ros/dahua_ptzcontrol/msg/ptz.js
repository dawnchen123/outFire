// Auto-generated. Do not edit!

// (in-package dahua_ptzcontrol.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class ptz {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.test = null;
    }
    else {
      if (initObj.hasOwnProperty('test')) {
        this.test = initObj.test
      }
      else {
        this.test = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ptz
    // Serialize message field [test]
    bufferOffset = _serializer.int8(obj.test, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ptz
    let len;
    let data = new ptz(null);
    // Deserialize message field [test]
    data.test = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'dahua_ptzcontrol/ptz';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f1a6ca594e44b73a507295573c903a8b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 test
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ptz(null);
    if (msg.test !== undefined) {
      resolved.test = msg.test;
    }
    else {
      resolved.test = 0
    }

    return resolved;
    }
};

module.exports = ptz;
