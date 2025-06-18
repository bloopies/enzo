cmake_minimum_required(VERSION 3.10)
project(node)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

qt_add_executable(test
    src/main.cpp
)

target_link_libraries(test PRIVATE Qt6::Core Qt6::Widgets)
