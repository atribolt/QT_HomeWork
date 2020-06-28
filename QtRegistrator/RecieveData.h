#ifndef RECIEVEDATA_H
#define RECIEVEDATA_H

#include <QObject>
#include <QTcpSocket>

class RecieveData final : public QObject
{
    Q_OBJECT
public:
    explicit RecieveData(QObject *parent = nullptr);
    RecieveData(QHostAddress addr, int port);

signals:
    void NewData(float x, float value);

private:
    void NewDataRead();

    QTcpSocket sock;
};

#endif // RECIEVEDATA_H
