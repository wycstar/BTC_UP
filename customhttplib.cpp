#include "customhttplib.h"

CustomHttpLib::CustomHttpLib(QObject *parent) : QObject(parent)
{

}

void CustomHttpLib::init(QQmlApplicationEngine *e)
{
    engine = e;
    rootObject = engine->rootObjects().first();
    usernameEdit = rootObject->findChild<QObject*>("username");
    passwordEdit = rootObject->findChild<QObject*>("password");
}

void CustomHttpLib::startCollect()
{
    qDebug() << "start";
    QJsonObject json;
    json.insert("username", usernameEdit->property("text").toString());
    json.insert("password", passwordEdit->property("text").toString());
    json.insert("stage", "auth");
    json.insert("start", true);
    QNetworkRequest request;
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QByteArray array = QJsonDocument(json).toJson();
    request.setUrl(QUrl("http://133.130.98.203:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/html");
    request.setHeader(QNetworkRequest::ContentLengthHeader, array.length());
    QNetworkReply *reply = manager->post(request, array);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleResponse(QNetworkReply*)));
}

void CustomHttpLib::handleResponse(QNetworkReply* reply)
{
    qDebug() << reply->readAll();
    reply->deleteLater();
    //QString header(reply->rawHeader("Content-Type"));
    //qDebug() << header.right(header.length() - header.indexOf("=") - 1).compare("UTF-8");
}

QString CustomHttpLib::GBK2UNICODE(QByteArray array)
{
    QTextCodec *gbk = QTextCodec::codecForName("GBK");
    return gbk->toUnicode(array);
}

CustomHttpLib::~CustomHttpLib()
{

}
