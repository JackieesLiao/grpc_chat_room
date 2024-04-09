#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
//-------------------------------------------------------------
// Copyright(c) 2023-2024  All Rights Reserved
// Name:         logindialog.h
// Function:login dialog 登录对话框
// Purpose:open source for learning
// Author: liaojunjian
// Modified by:
// Created:     2024-03-02 17:03
// Licence:MIT License
//-------------------------------------------------------------
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
signals:
    void switchRegister() ;//注册信号
};

#endif // LOGINDIALOG_H
