#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include<QTcpSocket>
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    QTcpSocket* getSocket() const{
        return socket;
    };
    QString getUsername() const{
        return username;
    };

private slots:

    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::LoginDialog *ui;
    QString username;
    QTcpSocket *socket;
};

#endif // LOGINDIALOG_H
