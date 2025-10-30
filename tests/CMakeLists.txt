# Add an executable for the tests
add_executable(dds_tests
    participant_factory_test.cpp
    participant_test.cpp 
    qos_test.cpp
)

# Link the test executable against the core DDS library and Google Test
target_link_libraries(dds_tests PRIVATE dds_core GTest::gtest_main)

# Discover and add tests to CTest
include(GoogleTest)
gtest_add_tests(TARGET dds_tests)

