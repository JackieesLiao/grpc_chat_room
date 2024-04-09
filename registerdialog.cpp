#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmanage.h"
RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->comfirmLineEdit->setEchoMode(QLineEdit::Password);
    ui->error_tips->setProperty("state","normal");
    repolishErrorQSS(ui->error_tips);
    connect(HttpManage::GetInstance().get(),&HttpManage::sig_reg_mod_finish,this,&RegisterDialog::slot_reg_mod_finish);
    initHttpHandlers();
    connect(ui->getVerifyCodeBtn,&QPushButton::clicked,this,&RegisterDialog::SlotGetVerifyCodeBtnClicked);

}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::showTips(const QString &str,bool isOk)
{
    if(isOk){
        ui->error_tips->setProperty("state","normal");
    }else{
        ui->error_tips->setProperty("state","err");
    }
    ui->error_tips->setText(str);
    repolishErrorQSS(ui->error_tips);
    //connect(HttpManage::GetInstance().get(),&HttpManage::sig_reg_mod_finish,this,&RegisterDialog::slot_reg_mod_finish);
}

void RegisterDialog::SlotGetVerifyCodeBtnClicked()
{
    auto email = ui->emailLineEdit->text();
    // \w+ 匹配a-z,A-Z,0-9并至少有一个
    // (\.|_)? 匹配零次或一次（可选）的点号 . 或下划线 _，用来匹配用户名中可能出现的分隔符。
    // (\w*) 匹配零个或多个字母、数字或下划线，用来匹配用户名中分隔符后可能的额外字符。
    // @ 匹配电子邮件地址中的 @ 符号。
    // (\w+)  匹配一个或多个字母、数字或下划线，表示邮箱的域名部分（第一级域名）。
    // (\.(\w+))+ 匹配一个或多个点号 . 加上一个或多个字母、数字或下划线，表示匹配域名后面的子域名（第二级域名、第三级域名等）。
    static QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    auto isMacth = regex.match(email).hasMatch();
    if(isMacth){
        //发送http 验证码
        QJsonObject json_obj;
        json_obj["email"] = email;
        HttpManage::GetInstance()->PostHttpRequest(QUrl(gate_url_prefix + "/get_varifycode"),
                                               json_obj,RequestID::ID_GET_VERIFY_CODE,
                                               Modules::REGISTERMOD);


    }else{
        showTips(tr("邮箱地址不正确，请重新输入。"),false);
    }
}

void RegisterDialog::slot_reg_mod_finish(RequestID id, QString res, ErrorCodes err_code)
{
    if(err_code != ErrorCodes::SUCCESS){
        showTips(tr("网络请求错误"),false);
        return;
    }

    //parse json string
    //将给定的json数据解析为一个QJsonDocument对象
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull()){
        showTips(tr("json解析失败"),false);
        return;
    }
    if(!jsonDoc.isObject()){
        showTips(tr("json解析失败"),false);
        return;
    }
    //解析成功则传递给回调函数进行处理
    handlers[id](jsonDoc.object());
    return;
}

void RegisterDialog::initHttpHandlers()
{
    //注册获取验证码回包的逻辑
    handlers.insert(RequestID::ID_GET_VERIFY_CODE,[this](QJsonObject jsonobj){
        int error = jsonobj["error"].toInt();//将value值转为int 类型
        if(error != ErrorCodes::SUCCESS){
            showTips(tr("参数错误"),false);
            return;
        }
        auto email = jsonobj["email"].toString();
        showTips(tr("验证码已经发送到邮箱,注意查收"),true);
        qDebug() <<"email is " <<email;
    });
}
