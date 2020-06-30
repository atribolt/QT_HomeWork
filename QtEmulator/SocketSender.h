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


// Объект владеет, принимаемыми извне указателями
struct Client {
    QThread    * thread { nullptr };
    SocketWork * swork  { nullptr };

    // устанавливает указатели и перемещает swork в поток thread
    // !!! перед установкой удаляет данные по указателям
    // free_mem - ваш сборщик мусора для этих двух полей
    // если free_mem == nullptr, данные не удаляются
    void Init( QThread*    _thread
             , SocketWork* _swork
             , void (*free_mem)(QThread*&, SocketWork*&) = nullptr);

    void Free();
private:
    void (*_Free)(QThread*&, SocketWork*&) { nullptr };
};

}

#endif // SOCKETSENDER_H
