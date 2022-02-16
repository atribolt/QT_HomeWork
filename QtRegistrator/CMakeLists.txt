add_executable(QtRegistrator
  signalmanipulateelement.h
  signalmanipulateelement.cpp
  mainwindow.h
  mainwindow.cpp
  main.cpp
)

target_link_libraries(QtRegistrator PRIVATE
  Qt5::Gui
  Qt5::Core
  Qt5::Network
  Qt5::Widgets
  CommonLib
)
