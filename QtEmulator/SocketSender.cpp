#include "SocketSender.h"

#include <QByteArray>
#include <QDataStream>

//############# class SocketWork #################

Emulator::SocketWork::SocketWork(QTcpSocket* sock) noexcept
{
    this->sock = sock;
}
Emulator::SocketWork::~SocketWork() noexcept
{
     sock = nullptr;
}

void Emulator::SocketWork::Send(float x, float y) {
    if ( !sock ) { return; }

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    stream << x << y;

    qint64 send      = 0;
    qint64 good_send = 0;

    do {
        send = sock->write(data.data() + good_send, data.size() - good_send);
        good_send += send;
    } while ( send > 0 );

    if ( send  < 0 || good_send != data.size() )
        emit ErrorSending(sock->socketDescriptor());
}

//############# class Client #####################

Emulator::Client::Client() {}
Emulator::Client::Client(Emulator::Client&& other)      { *this = std::move(other); }
Emulator::Client::Client(Emulator::Client const& other)
    : Client(other.swork->sock)
{}

Emulator::Client::Client(QTcpSocket* client) {
    swork  = new SocketWork(client);
    thread = new QThread();

    connect(thread, &QThread::finished, swork, &QObject::deleteLater);
    connect(this,   &Client::sending,   swork, &SocketWork::Send);

    thread->start();
}
Emulator::Client::~Client(){
    if (thread) {
       thread->quit();
       thread->wait();
       thread->exit();

       delete thread;
    }

    thread = nullptr;
    swork  = nullptr;
}


Emulator::Client&& Emulator::Client::operator=(Client&& other) {
    disconnect(this,   &Client::sending, swork,       &SocketWork::Send);
    disconnect(&other, &Client::sending, other.swork, &SocketWork::Send);

    std::swap( swork,  other.swork  );
    std::swap( thread, other.thread );

    connect(this,   &Client::sending, swork,       &SocketWork::Send);
    connect(&other, &Client::sending, other.swork, &SocketWork::Send);

    return std::move(*this);
}

void Emulator::Client::Send(float x, float y) {
    emit sending(x, y);
}
