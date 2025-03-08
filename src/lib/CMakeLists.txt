set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Collect all .cpp files recursively
file(GLOB_RECURSE LIB_SOURCES "${LIB_DIR}/*.cpp")

# Define library
add_library(Pizzeria-simulator-lib ${LIB_SOURCES})

# Add include directories
target_include_directories(Pizzeria-simulator-lib PUBLIC ${LIB_DIR})
