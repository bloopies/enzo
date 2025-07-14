cmake_minimum_required(VERSION 3.30)

# set vars
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
# set exec names
set(AppExec enzoGui)
set(TestExec tests)
set(BenchExec bench)
set(CMAKE_AUTORCC ON)

# setup project
project(enzo_project)

set(ENGINE_SOURCES
    src/Engine/Operator/Attribute.cpp
    src/Engine/Operator/Geometry.cpp
    src/Engine/Operator/GeometryOperator.cpp
    src/Engine/Operator/GeometryConnection.cpp
    src/Engine/Operator/GeometryOpDef.cpp
    src/Engine/Operator/OperatorTable.cpp
    src/Engine/Operator/Context.cpp
    src/Engine/Operator/GOP_test.cpp
    src/Engine/Network/NetworkManager.cpp
)

set(GUI_SOURCES
    static/resources.qrc
    src/Gui/main.cpp
    src/Gui/Interface.cpp
    src/Gui/UtilWidgets/Splitter.cpp
    src/Gui/Viewport/Viewport.cpp
    src/Gui/Viewport/ViewportGLWidget.cpp
    src/Gui/Viewport/GLCamera.cpp
    src/Gui/Viewport/GLMesh.cpp
    src/Gui/Viewport/GLGrid.cpp
    src/Gui/Network/NetworkGraphicsView.cpp
    src/Gui/Network/NetworkGraphicsScene.cpp
    src/Gui/Network/Network.cpp
    src/Gui/Network/NodeGraphic.cpp
    src/Gui/Network/SocketGraphic.cpp
    src/Gui/Network/NodeEdgeGraphic.cpp
    src/Gui/Network/FloatingEdgeGraphic.cpp
    src/Gui/Network/DisplayFlagButton.cpp
    src/Gui/Network/NodeIconGraphic.cpp
)

# qt
find_package(Qt6 REQUIRED COMPONENTS Core Widgets SvgWidgets OpenGLWidgets)
qt_standard_project_setup()

# glm
find_package(glm REQUIRED)

# eigen (math)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# tbb
find_package(TBB REQUIRED COMPONENTS TBB::tbb)

find_package(Boost REQUIRED COMPONENTS filesystem system)



qt_add_executable(${AppExec}
    ${GUI_SOURCES}
    ${ENGINE_SOURCES}
)

target_link_libraries(${AppExec} PRIVATE Qt6::Core Qt6::Widgets Qt6::SvgWidgets Qt6::OpenGLWidgets glm::glm Eigen3::Eigen TBB::tbb Boost::filesystem Boost::system)
target_include_directories(${AppExec} PUBLIC src)

# tests
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(${TestExec}
    ${ENGINE_SOURCES}
    tests/main-tests.cpp
    tests/OperatorTests.cpp
    tests/NetworkTests.cpp
)
target_link_libraries(${TestExec} PRIVATE Catch2::Catch2WithMain Eigen3::Eigen Qt6::Core TBB::tbb Boost::filesystem Boost::system)
target_compile_definitions(${TestExec} PRIVATE UNIT_TEST)
target_include_directories(${TestExec} PUBLIC
    src
    ${BOOST_INCLUDE_DIRS}
)

# benchmarks
add_executable(${BenchExec}
    ${ENGINE_SOURCES}

    tests/Benchmarks.cpp
)
target_link_libraries(${BenchExec} PRIVATE Catch2::Catch2WithMain Eigen3::Eigen Qt6::Core  TBB::tbb)
target_compile_definitions(${BenchExec} PRIVATE UNIT_TEST)
target_include_directories(${BenchExec} PUBLIC src)

add_subdirectory(src/OpDefs)
