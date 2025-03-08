set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Collect all .cpp files in `src/` (excluding subdirectories)
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")

# Include subdirectories
add_subdirectory(lib)
add_subdirectory(tests)

# Define the executable
add_executable(Pizzeria-simulator ${SRC_FILES})

# Link against the library
target_link_libraries(Pizzeria-simulator Pizzeria-simulator-lib)

# Add include directories
target_include_directories(Pizzeria-simulator PRIVATE lib)
