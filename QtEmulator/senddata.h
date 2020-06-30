#ifndef SENDDATA_H
#define SENDDATA_H

#include <memory>

#include <QVector>
#include <QTcpServer>

#include "SocketSender.h"

namespace Emulator {

inline static const QHostAddress SERVER_ADDR { QHostAddress::LocalHost };
inline static const int          SERVER_PORT { 8888 };

class SendData final : public QObject {
    Q_OBJECT

public:
    static std::shared_ptr<SendData> Create();

    void Send(float x, float val);

    ~SendData() { if ( serv ) delete serv; }
signals:
    void ErrorCreateServer(QString msg);

private:
    SendData(QHostAddress addr, int port);

    void AddNewConnection();
    void RemoveClient(qintptr);

    QVector<Client>  socks; // подключенные клиентов
    QTcpServer     * serv;
};

} // end namespace Emulator

#endif // SENDDATA_H
