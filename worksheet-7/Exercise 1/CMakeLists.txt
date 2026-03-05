cmake_minimum_required(VERSION 3.16)
project(CylinderExample)

set(CMAKE_CXX_STANDARD 17)

find_package(VTK REQUIRED)

add_executable(CylinderExample Cylinder.cxx)

target_link_libraries(CylinderExample PRIVATE ${VTK_LIBRARIES})

vtk_module_autoinit(
    TARGETS CylinderExample
    MODULES ${VTK_LIBRARIES}
)