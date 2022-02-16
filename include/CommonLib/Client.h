#pragma once

#include <QObject>
#include <QVector>

#include "Common.h"
#include "Packet.h"

class LIBRARY Client : public QObject
{
  Q_OBJECT
  
public:
  enum State : uint8_t {
    Closed,
    Connected,
    NotInited
  };
  
public:
  Client();
  Client(DescriptorType descriptor);
  virtual ~Client();
  
  void sendPacket(Packet const& pack);
  
  State state() const;
  void closeConnection();
  bool openConnection(DescriptorType descr);
  bool connectToServer(QString address, uint16_t port);
  
  bool operator==(Client const& other) const;
  
signals:
  void disconnected(Client*);
  void newPacket(Packet const& packet);
  
private:
  void init();
  void disconnecting();
  void readIncomeData();
  QByteArray encodeData(QByteArray const& data) const;
  QByteArray decodeData(QByteArray const& data) const;
  
  SocketType* _connection { nullptr };
};
