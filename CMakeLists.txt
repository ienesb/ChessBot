cmake_minimum_required(VERSION 3.10)

project(ChessBot)

find_package(OpenCV REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

include_directories(include)

file(GLOB HEADERS "include/*.h")
file(GLOB SOURCES "src/*.cpp")

add_executable(chess ${SOURCES} ${HEADERS})

add_compile_options("-lstdc++fs")

target_link_libraries(chess ${OpenCV_LIBS})
target_link_libraries(chess Qt5::Widgets)
target_link_libraries(chess "${TORCH_LIBRARIES}")
set_property(TARGET chess PROPERTY CXX_STANDARD 14)