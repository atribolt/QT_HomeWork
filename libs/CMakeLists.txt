add_library(CommonLib
  CommonLib/CoordinatePacket.cpp
  CommonLib/Packet.cpp
  CommonLib/Client.cpp
  CommonLib/Server.cpp

  ${LIB_HEADERS}/CommonLib/CoordinatePacket.h
  ${LIB_HEADERS}/CommonLib/Packet.h
  ${LIB_HEADERS}/CommonLib/Client.h
  ${LIB_HEADERS}/CommonLib/Server.h
)

target_link_libraries(CommonLib
  PRIVATE Qt5::Core Qt5::Network
)
