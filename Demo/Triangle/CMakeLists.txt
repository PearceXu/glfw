
cmake_minimum_required(VERSION 3.1)
#link_libraries(glfw3)


set(GLFW_SOURCE_DIR /home/xubaipei/workspace/glfw)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project (Triangle)

aux_source_directory(. DIR_SRCS)

set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h"
            "${GLFW_SOURCE_DIR}/deps/glad_gl.c")

set(GLAD_VULKAN "${GLFW_SOURCE_DIR}/deps/glad/vulkan.h"
            "${GLFW_SOURCE_DIR}/deps/glad_vulkan.c")

#set(GETOPT "${GLFW_SOURCE_DIR}/deps/getopt.h"
#          "${GLFW_SOURCE_DIR}/deps/getopt.c")
#set(TINYCTHREAD "${GLFW_SOURCE_DIR}/deps/tinycthread.h"
#          "${GLFW_SOURCE_DIR}/deps/tinycthread.c")

set(INC_DIR /usr/local/include/)
set(INC_GLAD_DIR ${GLFW_SOURCE_DIR}/deps/)
set(LINK_DIR /usr/local/lib)


# include
include_directories(${INC_GLAD_DIR})
include_directories(${INC_DIR})
link_directories(${LINK_DIR})

add_executable(Triangle ${DIR_SRCS} ${GLAD_GL} ${GLAD_VULKAN})

target_link_libraries(Triangle glfw3 dl  pthread rt X11)
