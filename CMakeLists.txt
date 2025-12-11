cmake_minimum_required(VERSION 3.14) # Changed from 3.10 to 3.14 to support FetchContent properly
project(bcp CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Dependencies & Includes ---
include_directories(include)
include_directories(external/cadical/include)
include_directories(src)

# Point to the actual library
set(CADICAL_LIB ${CMAKE_SOURCE_DIR}/external/cadical/libcadical.a)

# --- NEW: Fetch GoogleTest Automatically ---
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# This downloads GoogleTest and adds it to your project
FetchContent_MakeAvailable(googletest)

# --- 2. Define Shared Sources ---
set(CORE_SOURCES
        src/sat_solver/SatSolver.cpp
        src/bcp_solver/utility.cpp
        src/bcp_solver/bcp_solver.cpp
)

# --- 3. Main Application Target ---
add_executable(bcp
        src/main.cpp
        ${CORE_SOURCES}
)
target_link_libraries(bcp PRIVATE ${CADICAL_LIB})

# --- 4. Test Target ---
# IMPORTANT: Use 'enable_testing()' so CTest works
enable_testing()

add_executable(bcp_tests
        test/test_bcp.cpp
        ${CORE_SOURCES}
)

# Link GoogleTest (GTest::gtest_main provides a standard main() function for you)
target_link_libraries(bcp_tests
        PRIVATE
        ${CADICAL_LIB}
        GTest::gtest_main
)

# --- 5. Automatic Test Runner ---
include(GoogleTest)
# This helps CTest find individual tests inside your executable
gtest_discover_tests(bcp_tests)

# Run tests immediately after building
add_custom_command(
        TARGET bcp_tests
        POST_BUILD
        COMMAND ctest --output-on-failure
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "------------------ RUNNING UNIT TESTS ------------------"
        VERBATIM
)