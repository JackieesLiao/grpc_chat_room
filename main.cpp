#include "mainwindow.h"
#include "global.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QSettings>
#include <QDir>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //读取目录下的QSS文件
    QFile qss(":/style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly)){
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }else{
        qDebug("Open failed");
    }
    //读取配置文件
    QString fileName = "config.ini";
    QString app_path = QCoreApplication::applicationDirPath();
    QString config_path = QDir::toNativeSeparators(app_path + QDir::separator() + fileName);
    QSettings settings(config_path,QSettings::IniFormat);//INI文件
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    qDebug() << "gate_host:" << gate_host ;
    qDebug() << "gate_port:" << gate_port ;
    //拼接url地址
    gate_url_prefix = "http://" + gate_host + ":" + gate_port;
    qDebug() << "gate_url_prefix:"<<gate_url_prefix;
    MainWindow w;
    w.show();
    return a.exec();
}
