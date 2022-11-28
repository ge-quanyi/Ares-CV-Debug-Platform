cmake_minimum_required(VERSION 3.21)
project(rm)

set(CMAKE_CXX_STANDARD 20)

find_package(Python REQUIRED COMPONENTS Development Interpreter)
find_package(OpenCV REQUIRED)
find_package(pybind11 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Python_INCLUDE_DIRS})
include_directories(${pybind11_INCLUDE_DIRS})
include_directories(UltraMultiThread/include)
include_directories(include)

FILE (GLOB ALL_SOURCES "*.cpp" "*.c" )
FILE (GLOB ALL_INCLUDES "*.hpp" "*.h" )
SET (ALL_SRCS
        ${ALL_SOURCES}
        ${ALL_INCLUDES}
        )

add_executable(rm ${ALL_SRCS})
target_link_libraries(rm pthread)
target_link_libraries(rm Python::Python pybind11::pybind11 ${OpenCV_LIBS})