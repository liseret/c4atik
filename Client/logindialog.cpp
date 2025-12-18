#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    socket(new QTcpSocket(this))
{
    ui->setupUi(this);
    setWindowTitle("c4atik");
    username = "";
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::on_pushButton_clicked()
{

    username = ui->lineEdit->text().trimmed();
    if (username.isEmpty()) {
        return;
    }
    socket->connectToHost("127.0.0.1",777);
    if (socket->waitForConnected(3000)) {
        accept();
    }
}


void LoginDialog::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}


