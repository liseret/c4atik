#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket=new QTcpSocket(this);
    connect(socket,&QTcpSocket::readyRead,this,&MainWindow::SlotReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);
    DataSize=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1",777);
}

void MainWindow::SendToServer(QString str){
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out<<quint16(0)<<QTime::currentTime()<<str;
    out.device()->seek(0);
    out<<qint16(Data.size() - sizeof(qint16));
    socket->write(Data);
    ui->lineEdit->clear();
}

void MainWindow::SlotReadyRead()
{
    QDataStream in(socket);
    if (in.status()==QDataStream::Ok){
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
            ui->textBrowser->append(time.toString() +" "+ str);

        }
    }
    else{
        ui->textBrowser->append("read error :(");
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    SendToServer(ui->lineEdit->text());
}


void MainWindow::on_lineEdit_returnPressed()
{
    SendToServer(ui->lineEdit->text());
}

