cmake_minimum_required(VERSION 3.17)

project(ChessBot)

find_package(OpenCV REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(include)

file(GLOB HEADERS "include/*.h")
file(GLOB SOURCES "src/*.cpp")

add_executable(chess ${SOURCES} ${HEADERS})

target_link_libraries(chess ${OpenCV_LIBS})
target_link_libraries(chess Qt5::Widgets)