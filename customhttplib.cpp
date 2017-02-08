#include "customhttplib.h"

CustomHttpLib::CustomHttpLib(QObject *parent) : QObject(parent)
{
    isStreamStart = false;
    file.setFileName("/Users/wyc/Documents/Qt/test2/test.pdf");
    file.open(QIODevice::WriteOnly);
    connect(&progressTimer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
}

void CustomHttpLib::init(QQmlApplicationEngine *e)
{
    engine = e;
    rootObject = engine->rootObjects().first();
    usernameEdit = rootObject->findChild<QObject*>("username");
    passwordEdit = rootObject->findChild<QObject*>("password");
    tip          = rootObject->findChild<QObject*>("runTip");
    progressbar  = rootObject->findChild<QObject*>("progressbar");
}

bool CustomHttpLib::handleRequest(QJsonObject &json)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QByteArray array = QJsonDocument(json).toJson();
    request.setUrl(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/html");
    request.setHeader(QNetworkRequest::ContentLengthHeader, array.length());
    reply = manager->post(request, array);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleResponse(QNetworkReply*)));
    connect(reply, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
}

void CustomHttpLib::auth()
{
    QJsonObject json;
    json.insert("username", usernameEdit->property("text").toString());
    json.insert("password", passwordEdit->property("text").toString());
    json.insert("stage", "0");
    json.insert("start", true);
    handleRequest(json);
}

void CustomHttpLib::collect()
{
    QJsonObject json;
    json.insert("stage", "2");
    json.insert("start", true);
    handleRequest(json);
}

void CustomHttpLib::updateProgressBar()
{
    QJsonObject json;
    json.insert("stage", "1");
    json.insert("start", true);
    handleRequest(json);
}

void CustomHttpLib::handleReadyRead()
{

}

void CustomHttpLib::handleResponse(QNetworkReply* reply)
{
    QByteArray response = reply->readAll();
    if(!isStreamStart){
        QJsonParseError error;
        QJsonObject json = QJsonDocument::fromJson(response, &error).object();
        if(error.error == QJsonParseError::NoError){
            switch(json.value("stage").toInt()){
                case 0:{
                    if(json.value("result").toInt()){
                        tip->setProperty("color", "#336633");
                        tip->setProperty("text", "登录成功，已开始采集!");
                        progressTimer.start(2000);}
                    else{
                        tip->setProperty("color", "#CC3333");
                        tip->setProperty("text", "登录失败，账号或者密码错误!");}
                    break;}

                case 1:{
                    if(!json.value("finish").toInt()){
                        progressbar->setProperty("value", json.value("result"));}
                    else{
                        progressbar->setProperty("value", 1.0);
                        progressTimer.stop();
                        isStreamStart = true;
                        collect();}
                    break;}
                default:
                    qDebug() << "Error!";}}}
    else{
        file.write(response);
        file.close();
        isStreamStart = false;
        tip->setProperty("text", "采集完毕，文件已保存到桌面!");}
    reply->deleteLater();
}

QString CustomHttpLib::GBK2UNICODE(QByteArray array)
{
    QTextCodec *gbk = QTextCodec::codecForName("GBK");
    return gbk->toUnicode(array);
}

CustomHttpLib::~CustomHttpLib()
{

}
