cmake_minimum_required(VERSION 3.10)
project(bcp CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include your headers
include_directories(include)
include_directories(external/cadical/include)

# Point to the actual library
set(CADICAL_LIB ${CMAKE_SOURCE_DIR}/external/cadical/libcadical.a)

add_executable(bcp
        src/main.cpp
        src/sat_solver/SatSolver.cpp
        src/bcp_solver/utility.cpp
        src/bcp_solver/bcp_solver.cpp
)

target_link_libraries(bcp PRIVATE ${CADICAL_LIB})
