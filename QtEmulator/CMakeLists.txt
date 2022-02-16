add_executable(QtEmulator
  WaveFunction.h
  mainwindow.h
  mainwindow.cpp
  main.cpp

  mainwindow.ui
)

target_link_libraries(QtEmulator PRIVATE
  Qt5::Gui
  Qt5::Core
  Qt5::Network
  Qt5::Widgets
  CommonLib
)
