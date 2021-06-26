#pragma once

#include <QMutex>
#include <QObject>

#include "Common.h"
#include "Client.h"

class LIBRARY Server final : protected ServerType {
  Q_OBJECT
public:
  Server();
  virtual ~Server();
  
  void stop();
  bool start(QString address, uint16_t port);
  
public slots:
  void notifyAllClients(Packet const& pack);
  void removeConnection();
  
protected:
  void incomingConnection(qintptr handle) override;
  
private:
  QMutex _lockClients;
  QVector<Client*> _clients;
};
