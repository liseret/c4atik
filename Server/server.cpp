#include "server.h"

server::server() {
    if (this->listen(QHostAddress::Any,777)){
        qDebug()<<"start";
    }
    else{
        qDebug()<<"error";
    }
}
void server::incomingConnection(qintptr SoketDescription){
    socket= new QTcpSocket;
    socket->setSocketDescriptor(SoketDescription);
    connect(socket,&QTcpSocket::readyRead,this,&server::SlotReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);
    Sockets.push_back(socket);
    qDebug()<<"client connectrd"<<SoketDescription;
}

void server::SlotReadyRead(){
    socket=(QTcpSocket*)sender();
    QDataStream in(socket);
    if (in.status()==QDataStream::Ok){
        qDebug()<<"read";
        QString str;
        in>>str;
        qDebug()<<str;
        SendToClient(str);
    }
    else{
        qDebug()<<"DataStream error";
    }
}

void server::SendToClient(QString str){
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out<<str;
    for (int i=0;i<Sockets.size();i++){
        Sockets[i]->write(Data);
    }
}
