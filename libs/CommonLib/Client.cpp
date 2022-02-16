#include <QRegExp>
#include <QThread>
#include <QLoggingCategory>

#include "CommonLib/Client.h"

namespace {
  const QLoggingCategory client("Client");

  enum ASCII : uint8_t {
    STX = 0x02,
    ETX = 0x03
  };
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

  if (!_connection->open(QIODevice::ReadWrite)) {
    qCritical(client) << "Socket wont be open for write";
    return;
  }

  using std::chrono::operator""s;
  using std::chrono::milliseconds;

  QByteArray data(1, STX);
  data.append(encodeData(pack.getData()));
  data.append(ETX);

  _connection->write(data);
  if (!_connection->waitForBytesWritten(milliseconds(30s).count())) {
    qCritical(client) << "Packet sent timed out. Data:" << data;
  }
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

    while (_connection->isOpen()) {
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
                   this, &Client::readIncomeData);
  QObject::connect(_connection, &SocketType::disconnected,
                   this, &Client::disconnecting, Qt::QueuedConnection);
}

void Client::disconnecting() {
  emit disconnected(this);
}

bool Client::openConnection(DescriptorType descriptor) {
  if (_connection != nullptr)
    closeConnection();

  _connection = new (std::nothrow) SocketType();
  if (_connection != nullptr) {
    init();
    return _connection->setSocketDescriptor(descriptor, SocketType::ConnectedState, SocketType::ReadWrite);
  }

  qCritical(client) << "Error connected to client";
  return false;
}

void Client::readIncomeData() {
  QByteArray data = _connection->readAll();

  int stx = data.indexOf(STX);
  int etx = data.indexOf(ETX, stx);

  while (stx != -1 && etx != -1) {
    QByteArray packetData = data.mid(stx + 1, etx - stx - 1);
    emit newPacket(decodeData(packetData));

    stx = data.indexOf(STX, etx);
    etx = data.indexOf(ETX, stx);
  }
}

QByteArray Client::encodeData(QByteArray const& data) const {
  return data.toBase64();
}

QByteArray Client::decodeData(QByteArray const& data) const {
  return QByteArray::fromBase64(data);
}
