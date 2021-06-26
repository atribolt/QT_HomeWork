QT += core gui widgets network
CONFIG += c++17

LIBPATH = $${PWD}/../libs/CommonLib

INCLUDEPATH += $${LIBPATH}/include
LIBS += -L$${LIBPATH}/bin -lCommonLib

SOURCES += \
  main.cpp \
  mainwindow.cpp \
  signalmanipulateelement.cpp

HEADERS += \
  mainwindow.h \
  signalmanipulateelement.h
