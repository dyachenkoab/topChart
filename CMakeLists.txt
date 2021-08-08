cmake_minimum_required(VERSION 3.14)

project(topChart LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

set(PROJECT_SOURCES
       src/main.cpp
       src/filemanager.cpp
       src/filemanager.h
       src/postprocessing.cpp
       src/postprocessing.h
       res/qml.qrc
)

add_executable(topChart
  ${PROJECT_SOURCES}
)

target_compile_definitions(topChart
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(topChart
  PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets)
