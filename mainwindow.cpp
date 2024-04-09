#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginDlg = new LoginDialog(this);
    setCentralWidget(loginDlg);
    //loginDlg->show();

    connect(loginDlg,&LoginDialog::switchRegister,this,&MainWindow::SlotSwitchReg);
    registerDlg = new RegisterDialog(this);

    loginDlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    registerDlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    registerDlg->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
//    if(loginDlg)
//    {
//        delete loginDlg;
//        loginDlg = nullptr;
//    }

//    if(registerDlg)
//    {
//        delete registerDlg;
//        registerDlg = nullptr;
//    }
}

void MainWindow::SlotSwitchReg()
{
    setCentralWidget(registerDlg);
    loginDlg->hide();
    registerDlg->show();
}

