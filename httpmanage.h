#ifndef HTTPMANAGE_H
#define HTTPMANAGE_H
#include "ProSingleton.h"
#include <QString>
#include <QUrl>
#include <QDebug>
#include <QObject>
#include <QNetworkAccessManager>
#include <QByteArray>
#include <QJsonObject>   //序列化
#include <QJsonDocument> //反序列化
//-------------------------------------------------------------
// Copyright(c) 2023-2024  All Rights Reserved
// Name:         httpmanage.h
// Function:    CRTP(奇异模板递归模式)+单例模式管理http类
// Purpose:open source for learning
// Author: liaojunjian
// Modified by:
// Created:     2024-04-07 11:35
// Licence:MIT License
//-------------------------------------------------------------
class HttpManage :public QObject,public Singleton<HttpManage>,
                   public std::enable_shared_from_this<HttpManage>
{
    Q_OBJECT
public:
    ~HttpManage();
    void PostHttpRequest(const QUrl& url,QJsonObject json,RequestID req_id,Modules mod);
private:
    friend class Singleton<HttpManage>;//声明为友元为了在初始化HttpManage时能访问到该构造函数
    HttpManage();

private:
    QNetworkAccessManager _manager;
private slots:
    void slot_http_finish(RequestID id, QString res,ErrorCodes err_code,Modules mod);
signals:
    void sig_http_finish(RequestID id, QString res,ErrorCodes err_code,Modules mod);//http请求信号
    void sig_reg_mod_finish(RequestID id, QString res,ErrorCodes err_code);         //注册模块信号
};

#endif // HTTPMANAGE_H
