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
        Client client;

        SocketWork *work   = new SocketWork(sock);
        QThread    *thread = new QThread();

        client.Init( thread
                   , work
                   , [] (QThread*& th, SocketWork*& sw) {
                        if (th) {
                            th->quit();
                            th->wait();
                            th->exit();
                            delete th;
                        }
                        th = nullptr;
                        sw = nullptr;
                   }
        );

        connect(thread, &QThread::finished,        work, &QObject::deleteLater);
        connect(work,   &SocketWork::ErrorSending, this, &SendData::RemoveClient);

        client.swork  = work;
        client.thread = thread;

        socks.push_back(client);
        socks.back().thread->start();
    }
}

void Emulator::SendData::RemoveClient(qintptr sock_id) {
    using iterator = QVector<Client>::iterator;
// or
// typedef QVector<Client>::iterator iterator;

    if ( sock_id > 0 ) {
        iterator iter = std::find_if(
                    socks.data(), socks.data() + socks.size(),
                    [sock_id](Client& c) {
                        return c.swork->sock->socketDescriptor() == sock_id;
                    }
        );

        if ( iter != (socks.data() + socks.size()) ) {
             iter->Free();

             std::swap(*iter, socks.back());
             socks.resize( socks.size() - 1 );
        }
    }
}

void Emulator::SendData::Send(float x, float val) {
    for(int i = 0; i < socks.size(); ++i) {
        socks[i].swork->Send(x, val);
    }
}
