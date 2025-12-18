#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const QString &username,QTcpSocket *existingSocket,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,socket(existingSocket)
    ,username(username)

{
    ui->setupUi(this);
    setWindowTitle("c4atik");
    connect(socket,&QTcpSocket::readyRead,this,&MainWindow::SlotReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);
    DataSize=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SendToServer(QString str){
    if (str.isEmpty()){
        return;
    }
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out<<quint16(0)<<username<<QTime::currentTime()<<str;
    out.device()->seek(0);
    out<<qint16(Data.size() - sizeof(qint16));
    socket->write(Data);
    ui->lineEdit->clear();
}

void MainWindow::SlotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
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
            QString user;
            QTime time;
            in>>user>>time>>str;
            DataSize=0;
            if (user == "SERVER") {
                ui->textBrowser->append("=== " + str + " ===");
            }
            else{
                ui->textBrowser->append("["+user +"]"+ " "+time.toString() +" "+ str);
            }

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

