#ifndef SOCKETSENDER_H
#define SOCKETSENDER_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

namespace Emulator {

class SocketWork : public QObject
{
    Q_OBJECT
public:
    SocketWork(QTcpSocket* sock = nullptr) noexcept;
    ~SocketWork() noexcept;

    void Send(float x, float y);

    QTcpSocket *sock;

signals:
    void ErrorSending(qintptr); // ошибка отправки
};

class Client : public QObject {
    Q_OBJECT

public:
    Client();
    Client(Client&& other);
    Client(Client const& other);
    Client(QTcpSocket* client);
    ~Client();

    Client&& operator=(Client&& other);
    SocketWork* SWork() { return swork; }

    void Send(float x, float y);
signals:
    void sending(float x, float y);

private:
    SocketWork * swork  { nullptr };
    QThread    * thread { nullptr };
};

}

#endif // SOCKETSENDER_H
