cmake_minimum_required(VERSION 2.6)
project(PMBP)

set(CMAKE_BUILD_TYPE "Release")

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIR})

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

find_package(X11 REQUIRED)
find_package(OpenMP)

IF(APPLE)
include_directories(/opt/X11/include)
ENDIF(APPLE)

## VC11 (Visual Studio 2012) contains variadic templates emulation macros for std::tuple, std::bind etc.
## By default, _VARIADIC_MAX sets this to max. 5 arguments. We need more.
if(MSVC AND MSVC_VERSION EQUAL 1700)
  add_definitions(/D _VARIADIC_MAX=10)
endif()


include_directories(${PMBP_SOURCE_DIR}/include ${PMBP_SOURCE_DIR}/tools/CImg)

add_executable(pmbp src/colorcode.cc src/graph_2d_flow.cc src/image_operator.cc src/graph_discrete.cc src/graph_particles.cc src/graph_pmbp.cc src/graph_stereo.cc src/image.cc src/image_reader_cimg.cc src/main.cc src/message.cc)

#SET(CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++")
#this is for c++11 support
SET(CMAKE_CXX_FLAGS "-std=c++11")
if(OPENMP_FOUND)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
#TARGET_LINK_LIBRARIES(pbmp pthread)
TARGET_LINK_LIBRARIES( pmbp pthread)
target_link_libraries(pmbp ${PNG_LIBRARY} ${X11_LIBRARIES} )
