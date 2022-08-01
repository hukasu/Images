cmake_minimum_required(VERSION 3.12)

project("Image")

option(ENABLE_TESTING "Enable testing?" OFF)

add_library(
    image
    src/image.cpp
    src/image_buffer.cpp
    src/bmp/bmp.cpp
    src/qoi/qoi.cpp
)
target_compile_features(
    image
    PUBLIC cxx_std_17
)

if (ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif(ENABLE_TESTING)