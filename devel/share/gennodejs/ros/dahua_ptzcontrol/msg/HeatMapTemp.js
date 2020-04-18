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

class HeatMapTemp {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.temp = null;
      this.timer = null;
    }
    else {
      if (initObj.hasOwnProperty('temp')) {
        this.temp = initObj.temp
      }
      else {
        this.temp = 0.0;
      }
      if (initObj.hasOwnProperty('timer')) {
        this.timer = initObj.timer
      }
      else {
        this.timer = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type HeatMapTemp
    // Serialize message field [temp]
    bufferOffset = _serializer.float32(obj.temp, buffer, bufferOffset);
    // Serialize message field [timer]
    bufferOffset = _serializer.int32(obj.timer, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type HeatMapTemp
    let len;
    let data = new HeatMapTemp(null);
    // Deserialize message field [temp]
    data.temp = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [timer]
    data.timer = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'dahua_ptzcontrol/HeatMapTemp';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5584b0e644c8f93b541882b48b5271fc';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 temp
    int32 timer
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new HeatMapTemp(null);
    if (msg.temp !== undefined) {
      resolved.temp = msg.temp;
    }
    else {
      resolved.temp = 0.0
    }

    if (msg.timer !== undefined) {
      resolved.timer = msg.timer;
    }
    else {
      resolved.timer = 0
    }

    return resolved;
    }
};

module.exports = HeatMapTemp;
