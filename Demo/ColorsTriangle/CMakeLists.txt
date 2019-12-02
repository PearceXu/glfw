
cmake_minimum_required(VERSION 3.1)
#link_libraries(glfw3)




set(GLFW_SOURCE_DIR /home/xubaipei/workspace/glfw)
#${PROJECT_SOURCE_DIR}
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

project (Texture)
add_custom_target(copy
  COMMAND cp -r ${CMAKE_SOURCE_DIR}/imgs ${CMAKE_SOURCE_DIR}/shaders  ${EXECUTABLE_OUTPUT_PATH}
  )

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

add_executable(Texture ${DIR_SRCS} ${GLAD_GL} ${GLAD_VULKAN})

target_link_libraries(Texture glfw3 dl  pthread rt X11)
