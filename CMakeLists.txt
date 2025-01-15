cmake_minimum_required(VERSION 3.16)

project(Pisnoop_Clone VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Pisnoop_Clone
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        newchanneldialog.h newchanneldialog.cpp newchanneldialog.ui
        ecudevice.h ecudevice.cpp
        devicemanager.h devicemanager.cpp
        newdevicedialog.h newdevicedialog.cpp newdevicedialog.ui
        devicetable.h devicetable.cpp
        goonlinebuttondelegate.h goonlinebuttondelegate.cpp
        devicewidget.h devicewidget.cpp
        vectorinterface.h vectorinterface.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Pisnoop_Clone APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Pisnoop_Clone SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Pisnoop_Clone
            ${PROJECT_SOURCES}
        )
    endif()
endif()

include_directories("C:/Users/Public/Documents/Vector/XL Driver Library 20.30.14/bin")
link_directories("C:/Users/Public/Documents/Vector/XL Driver Library 20.30.14/bin")

target_link_libraries(Pisnoop_Clone PRIVATE Qt${QT_VERSION_MAJOR}::Widgets "C:/Users/Public/Documents/Vector/XL Driver Library 20.30.14/bin/vxlapi64.lib")


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Pisnoop_Clone)
endif()
set_target_properties(Pisnoop_Clone PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Pisnoop_Clone
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Pisnoop_Clone)
endif()
