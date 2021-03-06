// Generated by gencpp from file dahua_ptzcontrol/ptz.msg
// DO NOT EDIT!


#ifndef DAHUA_PTZCONTROL_MESSAGE_PTZ_H
#define DAHUA_PTZCONTROL_MESSAGE_PTZ_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace dahua_ptzcontrol
{
template <class ContainerAllocator>
struct ptz_
{
  typedef ptz_<ContainerAllocator> Type;

  ptz_()
    : test(0)  {
    }
  ptz_(const ContainerAllocator& _alloc)
    : test(0)  {
  (void)_alloc;
    }



   typedef int8_t _test_type;
  _test_type test;





  typedef boost::shared_ptr< ::dahua_ptzcontrol::ptz_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::dahua_ptzcontrol::ptz_<ContainerAllocator> const> ConstPtr;

}; // struct ptz_

typedef ::dahua_ptzcontrol::ptz_<std::allocator<void> > ptz;

typedef boost::shared_ptr< ::dahua_ptzcontrol::ptz > ptzPtr;
typedef boost::shared_ptr< ::dahua_ptzcontrol::ptz const> ptzConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::dahua_ptzcontrol::ptz_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::dahua_ptzcontrol::ptz_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace dahua_ptzcontrol

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'dahua_ptzcontrol': ['/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::dahua_ptzcontrol::ptz_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::dahua_ptzcontrol::ptz_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dahua_ptzcontrol::ptz_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dahua_ptzcontrol::ptz_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dahua_ptzcontrol::ptz_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dahua_ptzcontrol::ptz_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::dahua_ptzcontrol::ptz_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f1a6ca594e44b73a507295573c903a8b";
  }

  static const char* value(const ::dahua_ptzcontrol::ptz_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf1a6ca594e44b73aULL;
  static const uint64_t static_value2 = 0x507295573c903a8bULL;
};

template<class ContainerAllocator>
struct DataType< ::dahua_ptzcontrol::ptz_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dahua_ptzcontrol/ptz";
  }

  static const char* value(const ::dahua_ptzcontrol::ptz_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::dahua_ptzcontrol::ptz_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int8 test\n\
";
  }

  static const char* value(const ::dahua_ptzcontrol::ptz_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::dahua_ptzcontrol::ptz_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.test);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ptz_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::dahua_ptzcontrol::ptz_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::dahua_ptzcontrol::ptz_<ContainerAllocator>& v)
  {
    s << indent << "test: ";
    Printer<int8_t>::stream(s, indent + "  ", v.test);
  }
};

} // namespace message_operations
} // namespace ros

#endif // DAHUA_PTZCONTROL_MESSAGE_PTZ_H
