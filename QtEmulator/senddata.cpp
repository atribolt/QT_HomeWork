#include "senddata.h"

#include <QString>
#include <QDataStream>

#include <memory>

Emulator::SendData::SendData(QHostAddress addr, int port) {
    serv = new QTcpServer();
    if (!serv) emit ErrorCreateServer("Error allocate QTcpServer");

    // для добавления новых клиентов в список подключенных
    connect(serv, &QTcpServer::newConnection, this, &SendData::AddNewConnection);

    serv->listen(addr, port);
}

std::shared_ptr<Emulator::SendData> Emulator::SendData::Create() {
    using Emulator::SendData;

    // C++11 гарантирует единственное инстанцирование локальной статической переменной
    // потокобезопасное инстанцирование
    static std::shared_ptr<SendData> Singleton { new SendData(SERVER_ADDR, SERVER_PORT) };

    return Singleton;
}

void Emulator::SendData::AddNewConnection() {
    QTcpSocket* sock = serv->nextPendingConnection();

    if ( sock ) {
        socks.push_back(Client(sock));
        connect(socks.back().SWork(), &SocketWork::ErrorSending, this, &SendData::RemoveClient);
    }
}

void Emulator::SendData::RemoveClient(qintptr sock_id) {
    //using iterator = QVector<Client>::iterator;
    auto fast_remove = [](auto& vec, Client* a) {
        std::swap(*a, vec.back());
        vec.resize( vec.size() - 1 );
    };

    if ( sock_id > 0 ) {
        auto check = [&sock_id](Client& c){
           return c.SWork()->sock->socketDescriptor() == sock_id;
        };

        Client* iter = std::find_if(socks.data(), socks.data() + socks.size(), check);

        if ( iter != (socks.data() + socks.size()) ) {
            fast_remove(socks, iter);
        }
    } else {
        // подчистка пустых сокетов с id == -1 // id == 0
        auto check = [](Client& c) { return c.SWork()->sock->socketDescriptor() <= 0; };

        Client* iter = std::find_if(socks.data(), socks.data() + socks.size(), check);

        while( iter != (socks.data() + socks.size()) ) {
            fast_remove(socks, iter);
            iter = std::find_if(socks.data(), socks.data() + socks.size(), check);
        }
    }
}

void Emulator::SendData::Send(float x, float val) {
    for(int i = 0; i < socks.size(); ++i) {
        socks[i].Send(x, val);
    }
}
