cmake_minimum_required(VERSION 3.10)
project(enzo_project)

set(AppExec enzo_gui)
set(TestExec tests)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()


qt_add_executable(${AppExec}
    src/gui/main.cpp
)

target_link_libraries(${AppExec} PRIVATE Qt6::Core Qt6::Widgets)

# tests
add_executable(${TestExec} tests/main-tests.cpp)
find_package(Catch2 3 REQUIRED)
target_link_libraries(${TestExec} PRIVATE Catch2::Catch2WithMain)
