include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(test_histogram
    test_histogram.cpp
)
target_include_directories(test_histogram PRIVATE ${CMAKE_SOURCE_DIR}/cvtest)
target_link_libraries(test_histogram PRIVATE ${OpenCV_LIBS} GTest::gtest_main)

add_executable(test_image_processing
    test_image_processing.cpp
)
target_include_directories(test_image_processing PRIVATE ${CMAKE_SOURCE_DIR}/cvtest)
target_link_libraries(test_image_processing PRIVATE ${OpenCV_LIBS} GTest::gtest_main)

gtest_discover_tests(test_histogram)
gtest_discover_tests(test_image_processing)
