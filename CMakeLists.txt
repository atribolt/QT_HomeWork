cmake_minimum_required(VERSION "3.10")

set(CMAKE_AUTOMOC yes)
set(CMAKE_AUTOUIC yes)
set(CMAKE_AUTORCC yes)

find_package(Qt5 COMPONENTS Core Widgets Gui Network REQUIRED)

project(QtWave VERSION "1.0")

set(LIB_HEADERS ${PROJECT_SOURCE_DIR}/include)

include_directories(include)

add_subdirectory(QtEmulator)
add_subdirectory(QtRegistrator)
add_subdirectory(libs)
