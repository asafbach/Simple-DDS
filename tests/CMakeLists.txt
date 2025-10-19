# Define the test executable
add_executable(dds_tests
    participant_factory_test.cpp
)

# Link the test executable against our library and Google Test
target_link_libraries(dds_tests PRIVATE
    dds_core
    gtest_main
)

# Include the Google Test headers
target_include_directories(dds_tests PRIVATE
  "${googletest_SOURCE_DIR}/googletest/include"
)

# Add the test to CTest
include(GoogleTest)
gtest_add_tests(TARGET dds_tests)
