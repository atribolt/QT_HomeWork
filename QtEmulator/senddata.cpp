#include "senddata.h"

#include <QString>

Emulator::SendData::SendData(QHostAddress addr, int port) {
    serv = new Server_T();
    if (!serv) emit ErrorCreateServer("Error allocate QTcpServer");

    // для добавления новых клиентов в список подключенных
    serv->connect(serv, &Server_T::newConnection, this, &SendData::AddNewConnection);

    serv->listen(addr, port);
}

void Emulator::SendData::AddNewConnection() {
    auto sock = serv->nextPendingConnection();

    if ( sock ) {
        socks.push_back(sock);
    }
}

void Emulator::SendData::Send(float x, float val) {
       QByteArray data;
       QDataStream stream(&data, QIODevice::WriteOnly);

       stream << x << val;

       for (auto& sock : socks) {
           try {
               sock->write(data);
           } catch( ... ) {
               emit ErrorSendToClient(sock);
           }
       }
}
