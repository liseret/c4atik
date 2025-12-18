#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QIcon>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":new/prefix1/icons/icon.png"));
    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        QString username = loginDialog.getUsername();
        QTcpSocket* socket = loginDialog.getSocket();

        if (socket && socket->state() == QTcpSocket::ConnectedState) {
            MainWindow w(username, socket);
            w.setWindowIcon(QIcon(":new/prefix1//icons/icon.png"));
            w.show();
            return a.exec();
        }
    }
    return 0;
}
