#pragma once

#include "Common.h"
#include "Packet.h"

class LIBRARY CoordinatePacket
{
public:
  CoordinatePacket(Packet const& pack = {});
  
  void setPacket(Packet const& packet);
  Packet getPacket() const;
  
  double x;
  double y;
};
