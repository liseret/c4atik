#include "server.h"

server::server() {
    if (this->listen(QHostAddress::Any,777)){
        qDebug()<<"start";
    }
    else{
        qDebug()<<"error";
    }
    DataSize=0;
}


void server::incomingConnection(qintptr SoketDescription){
    QTcpSocket* NewClient = new QTcpSocket;
    NewClient->setSocketDescriptor(SoketDescription);
    QString* clientUsername = new QString();
    NewClient->setProperty("username", QVariant::fromValue(clientUsername));
    connect(NewClient, &QTcpSocket::readyRead, this, &server::SlotReadyRead);
    connect(NewClient, &QTcpSocket::disconnected, this, [this, NewClient](){
        qDebug() << "Client disconnected";
        QString* usernamePtr = NewClient->property("username").value<QString*>();
        QString username = usernamePtr ? *usernamePtr : "Unknown";
        if (!username.isEmpty() && username != "Unknown") {
            SendToClient("SERVER", username + " disconnected");
        }
        Sockets.removeOne(NewClient);
        delete usernamePtr;
        NewClient->deleteLater();
    });

    Sockets.push_back(NewClient);
    qDebug() << "Client connected:" << SoketDescription<< "Total clients:" << Sockets.size();
}

void server::SlotReadyRead(){
    QTcpSocket* CurrClient = qobject_cast<QTcpSocket*>(sender());

    if (!CurrClient) {
        return;
    }
    QByteArray allData = CurrClient->readAll();
    qDebug() << "Received" << allData.size() << "bytes";
    QDataStream in(allData);
    in.setVersion(QDataStream::Qt_5_15);
    quint16 size;
    QString user, str;
    QTime time;
    in >> size;
    if (allData.size() >= size + sizeof(quint16)) {
        in >> user >> time >> str;
        qDebug() << "Message from" << user << ":" << str;
        QString* usernamePtr = CurrClient->property("username").value<QString*>();
        if (usernamePtr && usernamePtr->isEmpty()) {
            *usernamePtr = user;
            SendToClient("SERVER", user + " connected to the c4atik!");
        }
        SendToClient(user, str);
    } else {
        qDebug() << "Incomplete data received";
    }
}

void server::SendToClient(QString username, QString str){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);

    out << quint16(0) << username << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    qDebug() << "Sending to" << Sockets.size() << "clients";

    for (int i = 0; i < Sockets.size(); i++) {
        if (Sockets[i] && Sockets[i]->state() == QTcpSocket::ConnectedState) {
            Sockets[i]->write(block);
        }
    }
}

