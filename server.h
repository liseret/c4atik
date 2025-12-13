#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include<QTcpSocket>
#include<QVector>

class server: public QTcpServer
{
    Q_OBJECT
private:
    QVector<QTcpSocket*> Sockets;
    QByteArray Data;
    void SendToClient(QString str);

public:
    server();
    QTcpSocket *socket;
public slots:
    void Connection(qintptr SoketDescription);
    void SlotReadyRead();

};

#endif // SERVER_H
