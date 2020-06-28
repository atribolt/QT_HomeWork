#ifndef SENDDATA_H
#define SENDDATA_H

#include <QTcpServer>
#include <QDataStream>
#include <QTcpSocket>
#include <QVector>

namespace Emulator {

// класс для абстракции работы отправки данных
class SendData final : public QObject {
    Q_OBJECT

    using Array_T  = QVector<QTcpSocket*>;
    using Server_T = QTcpServer;

public:
    SendData(QHostAddress addr, int port);
    ~SendData() { if ( serv ) delete serv; }

    //template<class ...T>
    //    void Send(T const& ...send_data) {
    //        QByteArray data;
    //        QDataStream stream(&data, QIODevice::WriteOnly);
    //
    //        ( (stream << send_data), ... ); // запись данных в буффер
    //
    //        for (auto& sock : socks) {
    //            try {
    //                sock->write(data);
    //            } catch( ... ) {
    //                emit ErrorSendToClient(sock);
    //            }
    //        }
    //    }

    void Send(float x, float val);

signals:
    void ErrorCreateServer(QString msg);
    void ErrorSendToClient(QTcpSocket* sock);

private:
    void AddNewConnection();

    Array_T      socks; // список подключенных клиентов
    Server_T   * serv;
};

} // end namespace Emulator

#endif // SENDDATA_H
