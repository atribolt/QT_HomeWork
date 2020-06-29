#include "SocketSender.h"

#include <QDataStream>
#include <QByteArray>
#include <QApplication>

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

//############# struct Client #####################

void Emulator::Client::Init( QThread    * _thread
                           , SocketWork * _swork
                           , std::function<void (QThread *&, SocketWork *&)> free_memory)
{
    Free();

    thread = _thread;
    swork  = _swork;
    swork->moveToThread(thread);

    _Free = free_memory;
}

void Emulator::Client::Free()
{
    if(_Free) _Free(thread, swork);
}

