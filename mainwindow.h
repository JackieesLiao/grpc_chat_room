#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//-------------------------------------------------------------
// Copyright(c) 2023-2024  All Rights Reserved
// Name:         mainwindow.h
// Function: mainwinow
// Purpose:open source for learning
// Author: liaojunjian
// Modified by:liaojunjian
// Created:     2024-03-02 15:52
// Licence:MIT License
//-------------------------------------------------------------
#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void SlotSwitchReg();
private:
    Ui::MainWindow *ui;
    LoginDialog * loginDlg;
    RegisterDialog * registerDlg;

};
#endif // MAINWINDOW_H
