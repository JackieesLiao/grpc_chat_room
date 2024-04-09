#include "httpmanage.h"

HttpManage::~HttpManage()
{

}

HttpManage::HttpManage()
{
    connect(this,&HttpManage::sig_http_finish,this,&HttpManage::slot_http_finish);
}
///
/// \brief HttpManage::PostHttpRequest
/// \param url 根据某个URL进行发送数据
/// \param json 将发送的数据序列成字符串
/// \param req_id 请求ID
/// \param mod   指定某个功能模块
///
void HttpManage::PostHttpRequest(const QUrl& url, QJsonObject json, RequestID req_id, Modules mod)
{
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(data.length()));
    auto self = shared_from_this();
    QNetworkReply*reply = _manager.post(request,data);
    QObject::connect(reply,&QNetworkReply::finished,[self,reply,req_id,mod](){
        //处理错误情况
        //1.有错误
        if(reply->error() != QNetworkReply::NoError){
            qDebug() << reply->errorString();
            //发送信号通知本次http请求结果失败
            emit self->sig_http_finish(req_id,"",ErrorCodes::ERR_NETWORK,mod);
            //不用reply的时候删除掉
            reply->deleteLater();
            return;
        }
        //2.无错误
        QString res = reply->readAll();
        //发送信号通知本次http请求结果成功
        emit self->sig_http_finish(req_id,res,ErrorCodes::SUCCESS,mod);
        reply->deleteLater();
        return;
    });
}

void HttpManage::slot_http_finish(RequestID id, QString res, ErrorCodes err_code, Modules mod)
{
    if(mod == Modules::REGISTERMOD){//注册模块
        //emit sig_http_finish(id,res,err_code,mod);//发送信号通知指定模块这里是注册模块的响应已经结束
        emit sig_reg_mod_finish(id,res,err_code);
    }
}
