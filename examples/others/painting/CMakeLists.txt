cmake_minimum_required(VERSION 3.3)

project(painting)
find_package(xtd.forms REQUIRED)
add_sources(src/painting.cpp)
target_type(GUI_APPLICATION)
