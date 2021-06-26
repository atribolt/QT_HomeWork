#include <QLoggingCategory>

#include "include/Server.h"

const QLoggingCategory server("Server");

Server::Server()
{}

Server::~Server() {
  stop();
}

void Server::stop() {
  {
    QMutexLocker lock(&_lockClients);
    for (Client* client : _clients) {
      client->closeConnection();
    }
  }
  
  ServerType::close();
}

bool Server::start(QString address, uint16_t port) {
  if (!ServerType::listen(QHostAddress(address), port)) {
    qCritical(server) << "Error start server";
    return false;
  }
  
  qDebug(server).nospace() << "Server listen: " << address << ":" << port;
  return true;
}

void Server::notifyAllClients(const Packet& pack) {
  QMutexLocker lock(&_lockClients);
  
  for (Client* client : _clients) {
    client->sendPacket(pack);
  }
}

void Server::removeConnection(Client* client) {
  {
    QMutexLocker lock(&_lockClients);
    
    int index = _clients.indexOf(client);
    _clients.remove(index);
  }
  
  QObject::disconnect(client, nullptr, nullptr, nullptr);
  delete client;
}

void Server::incomingConnection(qintptr handle) {
  Client* client = new (std::nothrow) Client(handle);
  
  if (client != nullptr && client->state() == Client::Connected) {
    QMutexLocker lock(&_lockClients);
    
    _clients.append(client);
    QObject::connect(_clients.back(), &Client::disconnected,
                     [&](Client* c){ this->removeConnection(c); });
  }
  else {
    qCritical(server) << "Client didn't connect";
  }
}
