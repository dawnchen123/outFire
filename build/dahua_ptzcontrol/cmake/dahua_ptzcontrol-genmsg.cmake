# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "dahua_ptzcontrol: 3 messages, 0 services")

set(MSG_I_FLAGS "-Idahua_ptzcontrol:/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(dahua_ptzcontrol_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/HeatMapTemp.msg" NAME_WE)
add_custom_target(_dahua_ptzcontrol_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "dahua_ptzcontrol" "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/HeatMapTemp.msg" ""
)

get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/Temperature.msg" NAME_WE)
add_custom_target(_dahua_ptzcontrol_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "dahua_ptzcontrol" "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/Temperature.msg" ""
)

get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/ptz.msg" NAME_WE)
add_custom_target(_dahua_ptzcontrol_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "dahua_ptzcontrol" "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/ptz.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/HeatMapTemp.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dahua_ptzcontrol
)
_generate_msg_cpp(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/Temperature.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dahua_ptzcontrol
)
_generate_msg_cpp(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/ptz.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dahua_ptzcontrol
)

### Generating Services

### Generating Module File
_generate_module_cpp(dahua_ptzcontrol
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dahua_ptzcontrol
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(dahua_ptzcontrol_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(dahua_ptzcontrol_generate_messages dahua_ptzcontrol_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/HeatMapTemp.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_cpp _dahua_ptzcontrol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/Temperature.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_cpp _dahua_ptzcontrol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/ptz.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_cpp _dahua_ptzcontrol_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(dahua_ptzcontrol_gencpp)
add_dependencies(dahua_ptzcontrol_gencpp dahua_ptzcontrol_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS dahua_ptzcontrol_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/HeatMapTemp.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dahua_ptzcontrol
)
_generate_msg_eus(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/Temperature.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dahua_ptzcontrol
)
_generate_msg_eus(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/ptz.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dahua_ptzcontrol
)

### Generating Services

### Generating Module File
_generate_module_eus(dahua_ptzcontrol
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dahua_ptzcontrol
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(dahua_ptzcontrol_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(dahua_ptzcontrol_generate_messages dahua_ptzcontrol_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/HeatMapTemp.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_eus _dahua_ptzcontrol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/Temperature.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_eus _dahua_ptzcontrol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/ptz.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_eus _dahua_ptzcontrol_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(dahua_ptzcontrol_geneus)
add_dependencies(dahua_ptzcontrol_geneus dahua_ptzcontrol_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS dahua_ptzcontrol_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/HeatMapTemp.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dahua_ptzcontrol
)
_generate_msg_lisp(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/Temperature.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dahua_ptzcontrol
)
_generate_msg_lisp(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/ptz.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dahua_ptzcontrol
)

### Generating Services

### Generating Module File
_generate_module_lisp(dahua_ptzcontrol
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dahua_ptzcontrol
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(dahua_ptzcontrol_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(dahua_ptzcontrol_generate_messages dahua_ptzcontrol_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/HeatMapTemp.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_lisp _dahua_ptzcontrol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/Temperature.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_lisp _dahua_ptzcontrol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/ptz.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_lisp _dahua_ptzcontrol_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(dahua_ptzcontrol_genlisp)
add_dependencies(dahua_ptzcontrol_genlisp dahua_ptzcontrol_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS dahua_ptzcontrol_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/HeatMapTemp.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dahua_ptzcontrol
)
_generate_msg_nodejs(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/Temperature.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dahua_ptzcontrol
)
_generate_msg_nodejs(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/ptz.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dahua_ptzcontrol
)

### Generating Services

### Generating Module File
_generate_module_nodejs(dahua_ptzcontrol
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dahua_ptzcontrol
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(dahua_ptzcontrol_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(dahua_ptzcontrol_generate_messages dahua_ptzcontrol_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/HeatMapTemp.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_nodejs _dahua_ptzcontrol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/Temperature.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_nodejs _dahua_ptzcontrol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/ptz.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_nodejs _dahua_ptzcontrol_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(dahua_ptzcontrol_gennodejs)
add_dependencies(dahua_ptzcontrol_gennodejs dahua_ptzcontrol_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS dahua_ptzcontrol_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/HeatMapTemp.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dahua_ptzcontrol
)
_generate_msg_py(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/Temperature.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dahua_ptzcontrol
)
_generate_msg_py(dahua_ptzcontrol
  "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/ptz.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dahua_ptzcontrol
)

### Generating Services

### Generating Module File
_generate_module_py(dahua_ptzcontrol
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dahua_ptzcontrol
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(dahua_ptzcontrol_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(dahua_ptzcontrol_generate_messages dahua_ptzcontrol_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/HeatMapTemp.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_py _dahua_ptzcontrol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/Temperature.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_py _dahua_ptzcontrol_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/hp-dawn/workspace/outfire/src/dahua_ptzcontrol/msg/ptz.msg" NAME_WE)
add_dependencies(dahua_ptzcontrol_generate_messages_py _dahua_ptzcontrol_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(dahua_ptzcontrol_genpy)
add_dependencies(dahua_ptzcontrol_genpy dahua_ptzcontrol_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS dahua_ptzcontrol_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dahua_ptzcontrol)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/dahua_ptzcontrol
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(dahua_ptzcontrol_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dahua_ptzcontrol)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/dahua_ptzcontrol
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(dahua_ptzcontrol_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dahua_ptzcontrol)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/dahua_ptzcontrol
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(dahua_ptzcontrol_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dahua_ptzcontrol)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/dahua_ptzcontrol
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(dahua_ptzcontrol_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dahua_ptzcontrol)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dahua_ptzcontrol\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/dahua_ptzcontrol
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(dahua_ptzcontrol_generate_messages_py std_msgs_generate_messages_py)
endif()
