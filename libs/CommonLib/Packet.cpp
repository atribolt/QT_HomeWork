#include <QVector>

#include "include/Packet.h"

Packet::Packet(QByteArray const& data) {
  setData(data);
}

void Packet::setData(const QByteArray& data) {
  _data = data;
}

const QByteArray& Packet::getData() const {
  return _data;
}

bool Packet::isEmpty() const {
  return _data.isEmpty();
}
