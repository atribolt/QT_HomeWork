#include <QList>
#include <QLoggingCategory>

#include "include/CoordinatePacket.h"

const QLoggingCategory coordPacket("CoordinatePacket");

CoordinatePacket::CoordinatePacket(const Packet& pack) {
  setPacket(pack);
}

void CoordinatePacket::setPacket(const Packet& packet) {
  QList<QByteArray> vars = packet.getData().split(' ');
  
  if (vars.size() == 2) {
    x = vars[0].toDouble();
    y = vars[1].toDouble();
  }
}

Packet CoordinatePacket::getPacket() const {
  QByteArray data = QString("%1 %2").arg(x).arg(y).toUtf8();
  return Packet(data);
}
