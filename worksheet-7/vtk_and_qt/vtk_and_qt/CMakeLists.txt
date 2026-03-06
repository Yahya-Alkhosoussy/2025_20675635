
cmake_minimum_required(VERSION 3.12)
project(first_QT_project LANGUAGES CXX)

set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "")
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO")
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO")

set(CMAKE_AUTOMOC ON)




set(CMAKE_PREFIX_PATH "/Users/khosoussy/Qt/6.10.2/macos" ${CMAKE_PREFIX_PATH})
set(Qt6_DIR "/Users/khosoussy/Qt/6.10.2/macos/lib/cmake/Qt6")
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
set(VTK_DIR "/Users/khosoussy/VTK-install/lib/cmake/vtk-9.6")
find_package(VTK REQUIRED)

qt_standard_project_setup()

qt_add_executable(first_QT_project
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ModelPart.cpp
    ModelPart.h
    ModelPartList.cpp
    ModelPartList.h
    icons.qrc
    dialog.h dialog.cpp dialog.ui
)


include(GNUInstallDirs)

install(TARGETS first_QT_project
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET first_QT_project
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

include(${VTK_USE_FILE})
set(OPENVR_ROOT_DIR "~/Downloads/openvr")

include_directories(${OPENVR_ROOT_DIR}/headers)

target_link_libraries(first_QT_project PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    ${VTK_LIBRARIES}
    ${OPENVR_ROOT_DIR}/lib/osx32/libopenvr_api.dylib
)

add_custom_target(VRBindings)
add_custom_command(TARGET VRBindings PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    copy_directory ${CMAKE_SOURCE_DIR}/vrbindings ${CMAKE_BINARY_DIR}/)
