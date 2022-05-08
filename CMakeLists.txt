cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 11)

project(convert_image)

# public server not showing full path
set(OpenCV_DIR ../../../github/build_opencv)

find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} ./include)

add_executable(convert_image 
       src/main.cpp 
       src/commands.cpp 
       src/ConvertImage.cpp
       src/CreateAction.cpp
       src/LineAction.cpp
       )

target_link_libraries(convert_image ${OpenCV_LIBS})
