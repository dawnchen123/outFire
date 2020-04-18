// Generated by gencpp from file dahua_ptzcontrol/HeatMapTemp.msg
// DO NOT EDIT!


#ifndef DAHUA_PTZCONTROL_MESSAGE_HEATMAPTEMP_H
#define DAHUA_PTZCONTROL_MESSAGE_HEATMAPTEMP_H


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
struct HeatMapTemp_
{
  typedef HeatMapTemp_<ContainerAllocator> Type;

  HeatMapTemp_()
    : temp(0.0)
    , timer(0)  {
    }
  HeatMapTemp_(const ContainerAllocator& _alloc)
    : temp(0.0)
    , timer(0)  {
  (void)_alloc;
    }



   typedef float _temp_type;
  _temp_type temp;

   typedef int32_t _timer_type;
  _timer_type timer;





  typedef boost::shared_ptr< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> const> ConstPtr;

}; // struct HeatMapTemp_

typedef ::dahua_ptzcontrol::HeatMapTemp_<std::allocator<void> > HeatMapTemp;

typedef boost::shared_ptr< ::dahua_ptzcontrol::HeatMapTemp > HeatMapTempPtr;
typedef boost::shared_ptr< ::dahua_ptzcontrol::HeatMapTemp const> HeatMapTempConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> >
{
  static const char* value()
  {
    return "5584b0e644c8f93b541882b48b5271fc";
  }

  static const char* value(const ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x5584b0e644c8f93bULL;
  static const uint64_t static_value2 = 0x541882b48b5271fcULL;
};

template<class ContainerAllocator>
struct DataType< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dahua_ptzcontrol/HeatMapTemp";
  }

  static const char* value(const ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32 temp\n\
int32 timer\n\
";
  }

  static const char* value(const ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.temp);
      stream.next(m.timer);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct HeatMapTemp_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::dahua_ptzcontrol::HeatMapTemp_<ContainerAllocator>& v)
  {
    s << indent << "temp: ";
    Printer<float>::stream(s, indent + "  ", v.temp);
    s << indent << "timer: ";
    Printer<int32_t>::stream(s, indent + "  ", v.timer);
  }
};

} // namespace message_operations
} // namespace ros

#endif // DAHUA_PTZCONTROL_MESSAGE_HEATMAPTEMP_H
