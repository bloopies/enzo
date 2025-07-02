cmake_minimum_required(VERSION 3.10)

# set vars
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
# set exec names
set(AppExec enzoGui)
set(TestExec tests)
set(CMAKE_AUTORCC ON)

# setup project
project(enzo_project)


# qt
find_package(Qt6 REQUIRED COMPONENTS Core Widgets SvgWidgets OpenGLWidgets)
qt_standard_project_setup()

# glm
find_package(glm REQUIRED)

# eigen (math)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)



qt_add_executable(${AppExec}
    static/resources.qrc
    src/gui/main.cpp
    src/gui/Interface.cpp
    src/gui/UtilWidgets/Splitter.cpp
    src/gui/viewport/Viewport.cpp
    src/gui/viewport/ViewportGLWidget.cpp
    src/gui/viewport/GLCamera.cpp
    src/gui/viewport/GLMesh.cpp
    src/gui/viewport/GLGrid.cpp
    src/gui/network/NetworkGraphicsView.cpp
    src/gui/network/NetworkGraphicsScene.cpp
    src/gui/network/Network.cpp
    src/gui/network/NodeGraphic.cpp
    src/gui/network/SocketGraphic.cpp
    src/gui/network/NodeEdgeGraphic.cpp
    src/gui/network/FloatingEdgeGraphic.cpp
    src/gui/network/DisplayFlagButton.cpp
    src/gui/network/NodeIconGraphic.cpp

    src/Engine/Operator/Attribute.cpp
    src/Engine/Operator/Geometry.cpp
)

target_link_libraries(${AppExec} PRIVATE Qt6::Core Qt6::Widgets Qt6::SvgWidgets Qt6::OpenGLWidgets glm::glm Eigen3::Eigen)
target_include_directories(${AppExec} PUBLIC src)

# tests
add_executable(${TestExec}
    tests/main-tests.cpp
    tests/OperatorTests.cpp
    src/Engine/Operator/Attribute.cpp
    src/Engine/Operator/Geometry.cpp
)
find_package(Catch2 3 REQUIRED)
target_link_libraries(${TestExec} PRIVATE Catch2::Catch2WithMain Eigen3::Eigen)
target_include_directories(${TestExec} PUBLIC src)
