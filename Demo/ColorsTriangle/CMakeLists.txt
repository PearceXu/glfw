
cmake_minimum_required(VERSION 3.1)
link_libraries(glfw)

if (MATH_LIBRARY)
    link_libraries("${MATH_LIBRARY}")
endif()

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

if (GLFW_USE_OSMESA)
    add_definitions(-DUSE_NATIVE_OSMESA)
endif()

if (${CMAKE_VERSION} VERSION_EQUAL "3.1.0" OR
    ${CMAKE_VERSION} VERSION_GREATER "3.1.0")
    set(CMAKE_C_STANDARD 99)
else()
    # Remove this fallback when removing support for CMake version less than 3.1
    add_compile_options("$<$<C_COMPILER_ID:AppleClang>:-std=c99>"
                        "$<$<C_COMPILER_ID:Clang>:-std=c99>"
                        "$<$<C_COMPILER_ID:GNU>:-std=c99>")

endif()

STRING( REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
set(TARGET ${CURRENT_FOLDER})

set(GLFW_SOURCE_DIR ../../../glfw)
#${PROJECT_SOURCE_DIR}
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)


if(EXISTS "(${CMAKE_CURRENT_SOURCE_DIR}/imgs)")
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/imgs DESTINATION ${EXECUTABLE_OUTPUT_PATH} FOLLOW_SYMLINK_CHAIN)
endif()
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
	file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${EXECUTABLE_OUTPUT_PATH} FOLLOW_SYMLINK_CHAIN)
endif()


aux_source_directory(. DIR_SRCS)

set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h"
            "${GLFW_SOURCE_DIR}/deps/glad_gl.c")

set(GLAD_VULKAN "${GLFW_SOURCE_DIR}/deps/glad/vulkan.h"
            "${GLFW_SOURCE_DIR}/deps/glad_vulkan.c")

set(INC_GLAD_DIR ${GLFW_SOURCE_DIR}/deps/)
set(INC_GLM ${GLFW_SOURCE_DIR}/third_part/)

IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(INC_DIR /usr/local/include/)
	set(LINK_DIR /usr/local/lib)
ENDIF()


# include
include_directories(${INC_GLAD_DIR})
include_directories(${INC_DIR})
include_directories(${INC_GLM})

link_directories(${LINK_DIR})

	

if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${WINDOWS_BINARIES} PROPERTIES
                          LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

set(CMAKE_EXE_LINKER_FLAGS"${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")


add_executable(${TARGET} ${DIR_SRCS} ${GLAD_GL} ${GLAD_VULKAN})

set_target_properties(${TARGET} PROPERTIES
                      FOLDER "GLFW3/Demos")
					  
target_link_libraries(${TARGET} "${CMAKE_THREAD_LIBS_INIT}")
if (RT_LIBRARY)
    target_link_libraries(${TARGET} "${RT_LIBRARY}")
endif()



