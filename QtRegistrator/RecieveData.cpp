#include "RecieveData.h"

#include <QHostAddress>
#include <QDataStream>

RecieveData::RecieveData(QObject *parent) : QObject(parent) {

}

RecieveData::RecieveData(QHostAddress addr, int port) {
    sock.connectToHost(addr, port);

    connect(&sock, &QTcpSocket::readyRead, this, &RecieveData::NewDataRead);
}

void RecieveData::NewDataRead() {
    QByteArray data = sock.readAll();

    QDataStream stream(&data, QIODevice::OpenModeFlag::ReadOnly);

    float x, val;

    stream >> x >> val;

    emit NewData(x, val);
}
