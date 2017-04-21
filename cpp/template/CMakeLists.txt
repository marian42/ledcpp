cmake_minimum_required(VERSION 3.7)
project("<AppName>")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_library(<AppName> SHARED
	../../screen/Color.cpp
	../../screen/Frame.cpp
	../../screen/Screen.cpp
	../../app/helpers.cpp
	../../app/Simplex.cpp
	../../app/App.cpp
	../../app/LoopApp.cpp
	../../app/ShaderApp.cpp
	appInterface.cpp
	<AppName>.cpp
)

get_filename_component(USERAPPS_DIR ${CMAKE_SOURCE_DIR} DIRECTORY)
get_filename_component(CPP_DIR ${USERAPPS_DIR} DIRECTORY)
TARGET_LINK_LIBRARIES(<AppName> ${CPP_DIR}/screen/rpi_ws281x/libws2811.a)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set_target_properties(<AppName> PROPERTIES PREFIX "")