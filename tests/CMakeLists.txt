include(CTest)
    
add_executable(
    image_compare
    image_compare.cpp
)
target_link_libraries(
    image_compare
    PUBLIC image
)
target_include_directories(
    image_compare
    PUBLIC ../src
)
add_custom_command(
    TARGET
        image_compare
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/images/X.bmp
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/images/X.bmp
)
add_custom_command(
    TARGET
        image_compare
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/images/X.qoi
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/images/X.qoi
)
 
# Will Fail Tests
add_test(
    NAME IncompleteArguments
    COMMAND image_compare
)
add_test(
    NAME UnknownFormat
    COMMAND image_compare -nan=images/X.bmp -qoi=images/X.qoi
)
add_test(
    NAME FileNotFound
    COMMAND image_compare -bmp=X.bmp -qoi=images/X.qoi
)

# QOI tests
add_test(
    NAME CompareX
    COMMAND image_compare -qoi=images/X.qoi -bmp=images/X.bmp
)

# WILL_FAIL property
set_tests_properties(
    IncompleteArguments
    UnknownFormat
    FileNotFound
    
    PROPERTIES
    WILL_FAIL ON
)