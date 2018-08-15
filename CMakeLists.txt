cmake_minimum_required(VERSION 2.8)

project( stitch )
find_package( OpenCV REQUIRED )
add_executable( stitch stitch.cpp )
#add_executable( stitch_test stitch_two_thread_vid_works.cpp )
target_link_libraries( stitch ${OpenCV_LIBS} )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

# Locate GTest
#find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
# add_executable(runTests tests.cpp)
# target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)