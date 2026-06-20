cmake_minimum_required(VERSION 3.20)
project(cvtest VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc)

add_executable(cvtest
    cvtest/ImageProcessingClass.cpp
)
target_include_directories(cvtest PRIVATE cvtest)
target_link_libraries(cvtest PRIVATE ${OpenCV_LIBS})

add_executable(chapter_01_01
    Book/Chapter_01_01.cpp
)
target_link_libraries(chapter_01_01 PRIVATE ${OpenCV_LIBS})

option(BUILD_TESTS "Build Google Test suite" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
