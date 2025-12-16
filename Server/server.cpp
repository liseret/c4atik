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
        for(;;){
            if (DataSize==0){
                if(socket->bytesAvailable()<2){
                    break;
                }
                in>>DataSize;
            }
            if (socket->bytesAvailable()<DataSize){
                break;
            }
            QString str;
            QTime time;
            in>>time>>str;
            DataSize=0;
            SendToClient(str);
            break;

        }
    }
    else{
        qDebug()<<"DataStream error";
    }
}

void server::SendToClient(QString str){
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out<<quint16(0)<<QTime::currentTime()<<str;
    out.device()->seek(0);
    out<<qint16(Data.size() - sizeof(qint16));
    for (int i=0;i<Sockets.size();i++){
        Sockets[i]->write(Data);
    }
}
