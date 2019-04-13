CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(flvlc)

SET(APP flvlc)

FILE(GLOB SOURCES "*.cxx" "*.hpp")

FIND_PACKAGE(FLTK REQUIRED)

include (FindPkgConfig)
pkg_search_module(VLC REQUIRED libvlc)

link_directories(
  ${FLTK_LIBRARY_DIRS}
  ${VLC_LIBRARY_DIRS}
)

include_directories(
  ${FLTK_INCLUDE_DIRS}
  ${VLC_INCLUDE_DIRS} 
)


#set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)


if( ${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set( CMAKE_CXX_FLAGS "-Wl,-s -Wno-write-strings -lrt -Ofast -march=native -mtune=native -std=c++11")
else()
    set( CMAKE_CXX_FLAGS "-Wno-write-strings -lrt -Wall -ggdb3 -DDEBUG -std=c++11")
endif()


ADD_EXECUTABLE(${APP} ${SOURCES} ${FLTK_INCLUDE_DIRS} ${VLC_INCLUDE_DIRS} )

TARGET_LINK_LIBRARIES(${APP} ${FLTK_LIBRARIES} ${VLC_LIBRARIES} ${VLC_LIBRARY_DIRS} -lpthread -ldl)



