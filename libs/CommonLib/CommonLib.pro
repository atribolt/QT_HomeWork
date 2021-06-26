QT += core network
CONFIG += c++17
CONFIG -= console

TARGET = CommonLib
TEMPLATE = lib

DEFINES += COMMON_LIBRARY

SOURCES += \
  Client.cpp \
  CoordinatePacket.cpp \
  Packet.cpp \
  Server.cpp

HEADERS +=  \
  include/Client.h \
  include/Common.h \
  include/CoordinatePacket.h \
  include/Packet.h \
  include/Server.h
