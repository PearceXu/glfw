cmake_minimum_required(VERSION 3.1)

file(GLOB SUBDIRS *)
foreach(subdir ${SUBDIRS})
	if(IS_DIRECTORY ${subdir})
		#message(${subdir})
		add_subdirectory(${subdir})
	endif()	

