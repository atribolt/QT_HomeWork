#pragma once

#include <QByteArray>

#include "Common.h"

class LIBRARY Packet
{
public:
  Packet(QByteArray const& data = "");
  
  void setData(QByteArray const& data);
  const QByteArray& getData() const;
  
  bool isEmpty() const;
  
private:
  QByteArray _data;
};
