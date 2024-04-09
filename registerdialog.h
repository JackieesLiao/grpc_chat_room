#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QString>
#include <QMap>
#include "global.h"
namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();
    void showTips(const QString&str,bool isOk);
private slots:
    void SlotGetVerifyCodeBtnClicked();
    void slot_reg_mod_finish(RequestID id, QString res,ErrorCodes err_code);
private:
    void initHttpHandlers();
    //根据请求ID取出对应的回调函数
    QMap<RequestID,std::function<void(const QJsonObject&)>> handlers;
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
