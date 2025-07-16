cmake_minimum_required(VERSION 3.30)

project(enzoOps1)

find_package(Boost REQUIRED)
# eigen (math)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

set(libName enzoOps1)
add_library(${libName} SHARED
    RegisterPlugin.cpp
    ../Engine/Operator/OperatorTable.cpp
    ../Engine/Operator/GeometryOpDef.cpp
    ../Engine/Operator/GeometryOperator.cpp
    ../Engine/Operator/GeometryConnection.cpp
    ../Engine/Operator/Context.cpp
    ../Engine/Operator/Geometry.cpp
    ../Engine/Operator/Attribute.cpp
    ../Engine/Network/NetworkManager.cpp
    GopTransform.cpp
    GopHouse.cpp
)
target_link_libraries(${libName} PRIVATE Qt6::Core Qt6::Widgets Qt6::SvgWidgets Qt6::OpenGLWidgets glm::glm Eigen3::Eigen TBB::tbb)


MESSAGE("CURRENT SOURCE DIR" ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${libName} PUBLIC ../)
target_include_directories(${libName} PUBLIC .)
