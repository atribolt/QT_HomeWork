#ifndef SOCKETSENDER_H
#define SOCKETSENDER_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

#include <functional>

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



// Объект владеет, принимаемыми извне указателями
struct Client {
    QThread    * thread { nullptr };
    SocketWork * swork  { nullptr };

    // устанавливает указатели и перемещает swork в поток thread
    // !!! перед установкой удаляет данные по указателям
    // функтор - ваш сборщик мусора для этих двух полей
    void Init( QThread*    _thread
             , SocketWork* _swork
             , std::function<void(QThread*&, SocketWork*&)> free_memory);

    void Free();
private:
    std::function<void(QThread*&, SocketWork*&)> _Free;
};

}

#endif // SOCKETSENDER_H
