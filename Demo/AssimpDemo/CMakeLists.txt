
cmake_minimum_required(VERSION 3.1)
#link_libraries(glfw3)


STRING( REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
set(TARGET ${CURRENT_FOLDER})
message("project name:"${TARGET})

set(GLFW_SOURCE_DIR ../../../glfw)
#${PROJECT_SOURCE_DIR}
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

#project (${TARGET})

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
add_custom_target(copy${TARGET}
  COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/imgs ${CMAKE_CURRENT_SOURCE_DIR}/shaders  ${EXECUTABLE_OUTPUT_PATH})
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
#message("project name:"copy -r ${CMAKE_CURRENT_SOURCE_DIR}/imgs ${CMAKE_CURRENT_SOURCE_DIR}/shaders  ${EXECUTABLE_OUTPUT_PATH})
add_custom_target(copy${TARGET}
  COMMAND copy -r ${CMAKE_CURRENT_SOURCE_DIR}/imgs ${CMAKE_CURRENT_SOURCE_DIR}/shaders  ${EXECUTABLE_OUTPUT_PATH})
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

aux_source_directory(. DIR_SRCS)

set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h"
            "${GLFW_SOURCE_DIR}/deps/glad_gl.c")

set(GLAD_VULKAN "${GLFW_SOURCE_DIR}/deps/glad/vulkan.h"
            "${GLFW_SOURCE_DIR}/deps/glad_vulkan.c")

set(INC_DIR /usr/local/include/)
set(INC_GLAD_DIR ${GLFW_SOURCE_DIR}/deps/)
set(LINK_DIR /usr/local/lib)
set(INC_GLM ${GLFW_SOURCE_DIR}/third_part/)


# include
include_directories(${INC_GLAD_DIR})
include_directories(${INC_DIR})
include_directories(${INC_GLM})

link_directories(${LINK_DIR})

add_executable(${TARGET} ${DIR_SRCS} ${GLAD_GL} ${GLAD_VULKAN})

target_link_libraries(${TARGET} glfw3 dl  pthread rt X11 assimp)
