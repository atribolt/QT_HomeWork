#include <QRegExp>
#include <QThread>
#include <QLoggingCategory>

#include "include/Client.h"

namespace {
  const QRegExp PACKET_PATTERN(R"(\x02(.*?)\x03)");
  const QLoggingCategory client("Client");
  
  const char END_PACKET = '\x03';
  const char START_PACKET = '\x02';
}

Client::Client() 
  : QObject(nullptr)
{}

Client::Client(DescriptorType descriptor) 
  : QObject(nullptr)
{
  openConnection(descriptor);
}

Client::~Client() {
  closeConnection();
}

void Client::sendPacket(const Packet& pack) {
  if (_connection == nullptr) {
    qCritical(client) << "Packet wont be sent";
    return;
  }
  
  if (!_connection->isOpen() || !_connection->openMode().testFlag(QIODevice::ReadWrite)) {
    if (!_connection->open(QIODevice::ReadWrite)) {
      qCritical(client) << "Socket wont be open for write";
      return;
    }
  }
  
  using std::chrono::operator""s;
  using std::chrono::milliseconds;
  
  QByteArray data(1, START_PACKET);
  data.append(encodeData(pack.getData()));
  data.append(END_PACKET);
  
  _connection->write(data);
  if (!_connection->waitForBytesWritten(milliseconds(30s).count())) {
    qCritical(client) << "Packet sent timed out";
  }
}

Packet Client::popPacket() {
  Packet result;
  
  if (_packets.size() > 0) {
    result = _packets.back();
    _packets.resize(_packets.size() - 1);
  }
  
  return result;
}

Client::State Client::state() const {
  State result = State::NotInited;
  if (_connection != nullptr) {
    if (_connection->isOpen()) 
      result = State::Connected;
    else
      result = State::Closed;
  }
  return result;
}

void Client::closeConnection() {
  if (_connection != nullptr) {
    _connection->close();
    
    while (_connection->state() == _connection->isOpen()) {
      QThread::msleep(500);
    }
  }
  
  delete _connection;
  _connection = nullptr;
}

bool Client::connectToServer(QString address, uint16_t port) {
  if (_connection == nullptr) {
    _connection = new SocketType;
  }
  
  _connection->connectToHost(address, port, SocketType::ReadWrite);
  if (state() != State::Connected) {
    qCritical(client).nospace() << "Client wont be connect to host: " << address << ":" << port;
    return false;
  }
  
  init();
  return true;
}

bool Client::operator==(const Client& other) const {
  if (_connection != nullptr && other._connection != nullptr) {
    return _connection->peerAddress() == other._connection->peerAddress();
  }
  
  return false;
}

void Client::init() {
  QObject::connect(_connection, &SocketType::readyRead,
                   this, &Client::readIncomeData, Qt::QueuedConnection);
  QObject::connect(_connection, &SocketType::disconnected,
                   this, &Client::disconnected, Qt::QueuedConnection);
}

bool Client::openConnection(DescriptorType descriptor) {
  if (_connection != nullptr) 
    closeConnection();
  
  _connection = new (std::nothrow) SocketType();
  if (_connection != nullptr) {
    init();
    return _connection->setSocketDescriptor(descriptor, {}, SocketType::ReadWrite);
  }

  return false;
}

void Client::readIncomeData() {
  QByteArray data = _connection->readAll();
  int index = PACKET_PATTERN.indexIn(data);
  
  while (index != -1) {
    QByteArray packetData = PACKET_PATTERN.cap(1).toUtf8();
    
    _packets.append(decodeData(packetData));
  }
}

QByteArray Client::encodeData(QByteArray const& data) const {
  return data.toBase64();
}

QByteArray Client::decodeData(QByteArray const& data) const {
  return QByteArray::fromBase64(data);
}
