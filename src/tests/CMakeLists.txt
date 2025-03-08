set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Collect all test files
file(GLOB TEST_SOURCES "${TEST_DIR}/*.cpp")

# Define the test executable
add_executable(Pizzeria-tests ${TEST_SOURCES})

# Link against the main project library
target_link_libraries(Pizzeria-tests Pizzeria-simulator-lib)
