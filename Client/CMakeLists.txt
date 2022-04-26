cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME Client)
project(${PROJECT_NAME})

set(BUILD_SHARED_LIBS OFF)

include_directories(external/SFML-2.5.1/include)
include_directories(external/FLTK-1.3.8)
	
set(SOURCES
		source/main.cpp
		source/ClientNetwork.cpp
	)

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(external/SFML-2.5.1)
target_link_libraries(
 ${PROJECT_NAME}
 sfml-graphics
 sfml-window
 sfml-system
 sfml-audio
 sfml-network
)

add_subdirectory(external/FLTK-1.3.8)
target_link_libraries(
 ${PROJECT_NAME}
 fltk
 uuid
 ole32
 comctl32
 comdlg32
 gdi32
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}../../bin/)