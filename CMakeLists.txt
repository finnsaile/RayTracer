cmake_minimum_required(VERSION 3.12)

project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always -Wall")

set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

include_directories(include) 

add_subdirectory(statusbar)

find_package(OpenCV REQUIRED)

find_package(Eigen3 REQUIRED)

find_package(nlohmann_json 3.2.0 REQUIRED NO_MODULE)

file(GLOB SOURCES
    main.cc
    src/*.cc
)

add_executable(main ${SOURCES})

target_link_libraries(main ${OpenCV_LIBS} statusbar Eigen3::Eigen nlohmann_json::nlohmann_json)

set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)