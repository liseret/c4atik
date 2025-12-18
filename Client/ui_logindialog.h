/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(400, 300);
        pushButton = new QPushButton(LoginDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(150, 200, 80, 24));
        lineEdit = new QLineEdit(LoginDialog);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(10, 140, 381, 24));
        label = new QLabel(LoginDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 110, 113, 16));

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("LoginDialog", "Connect", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "You`r name? dummie", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
