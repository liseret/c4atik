#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        QString username = loginDialog.getUsername();
        QTcpSocket* socket = loginDialog.getSocket();  // ← ЗДЕСЬ ПОЛУЧАЕМ СОКЕТ

        if (socket && socket->state() == QTcpSocket::ConnectedState) {
            MainWindow w(username, socket);  // ← ПЕРЕДАЕМ СОКЕТ В MainWindow
            w.show();
            return a.exec();
        }
    }
    return 0;
}
