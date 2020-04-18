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

class Temperature {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.max_temperature = null;
      this.min_temperature = null;
      this.timer = null;
    }
    else {
      if (initObj.hasOwnProperty('max_temperature')) {
        this.max_temperature = initObj.max_temperature
      }
      else {
        this.max_temperature = 0.0;
      }
      if (initObj.hasOwnProperty('min_temperature')) {
        this.min_temperature = initObj.min_temperature
      }
      else {
        this.min_temperature = 0.0;
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
    // Serializes a message object of type Temperature
    // Serialize message field [max_temperature]
    bufferOffset = _serializer.float32(obj.max_temperature, buffer, bufferOffset);
    // Serialize message field [min_temperature]
    bufferOffset = _serializer.float32(obj.min_temperature, buffer, bufferOffset);
    // Serialize message field [timer]
    bufferOffset = _serializer.int32(obj.timer, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Temperature
    let len;
    let data = new Temperature(null);
    // Deserialize message field [max_temperature]
    data.max_temperature = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [min_temperature]
    data.min_temperature = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [timer]
    data.timer = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'dahua_ptzcontrol/Temperature';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'efdfa2e0b9ac13acef941502135a514f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 max_temperature
    float32 min_temperature
    int32 timer
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Temperature(null);
    if (msg.max_temperature !== undefined) {
      resolved.max_temperature = msg.max_temperature;
    }
    else {
      resolved.max_temperature = 0.0
    }

    if (msg.min_temperature !== undefined) {
      resolved.min_temperature = msg.min_temperature;
    }
    else {
      resolved.min_temperature = 0.0
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

module.exports = Temperature;
