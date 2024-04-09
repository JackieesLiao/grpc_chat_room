#ifndef GLOBAL_H
#define GLOBAL_H
//-------------------------------------------------------------
// Copyright(c) 2023-2024  All Rights Reserved
// Name:         global.h
// Function:
// Purpose:open source for learning
// Author: liaojunjian
// Modified by:
// Created:     2024-04-07 10:09
// Licence:MIT License
//-------------------------------------------------------------
#include <QWidget>
#include <QRegularExpression>
#include <functional>
#include <QNetworkReply>
#include "QStyle"

///
/// \brief repolishErrorQSS
/// 刷新QSS
///
extern std::function<void(QWidget*)> repolishErrorQSS;

enum RequestID{
    ID_GET_VERIFY_CODE = 1001,   //获取验证码
    ID_REG_USER = 1002           //注册用户
};
enum Modules{
    REGISTERMOD = 0
};
enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1,               //json解析失败
    ERR_NETWORK = 2             //网络错误
};
extern QString gate_url_prefix;
#endif // GLOBAL_H
