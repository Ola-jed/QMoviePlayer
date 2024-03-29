cmake_minimum_required(VERSION 3.17)
project(QMoviePlayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets)
if( NOT Qt6_FOUND )
    set(QT_VERSION 5)
else()
    set(QT_VERSION 6)
endif()

set(REQUIRED_LIBS Core Gui Widgets Multimedia MultimediaWidgets)
set(REQUIRED_LIBS_QUALIFIED Qt${QT_VERSION}::Core Qt${QT_VERSION}::Gui Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Multimedia Qt${QT_VERSION}::MultimediaWidgets)
add_executable(${PROJECT_NAME} main.cpp resources.qrc src/videowidget.cpp include/videowidget.hpp src/window.cpp include/window.hpp include/Window.ui src/aboutdialog.cpp include/aboutdialog.hpp include/AboutDialog.ui src/settings.cpp include/settings.hpp include/Settings.ui src/info.cpp include/info.hpp include/Info.ui src/recentfilesmanager.cpp include/recentfilesmanager.hpp)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wunused")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif()

include_directories(${QMoviePlayer_SOURCE_DIR}/include)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
