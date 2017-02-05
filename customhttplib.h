#ifndef CUSTOMHTTPLIB_H
#define CUSTOMHTTPLIB_H

#include <QObject>
#include "public.h"
#include "QNetworkAccessManager"
#include "QNetworkReply"
#include "QNetworkRequest"
#include "QUrl"
#include "QTextCodec"
#include "QJsonObject"
#include "QJsonDocument"
#include <QQmlApplicationEngine>
#include <QQmlContext>

class CustomHttpLib : public QObject
{
    Q_OBJECT
public:
    explicit CustomHttpLib(QObject *parent = 0);
    void init(QQmlApplicationEngine *e);
    ~CustomHttpLib();

public slots:
    Q_INVOKABLE void startCollect();

private variable:
    QQmlApplicationEngine *engine;
    QObject *rootObject;
    QObject *usernameEdit;
    QObject *passwordEdit;

private:
    QString GBK2UNICODE(QByteArray array);

private slots:
    void handleResponse(QNetworkReply*);
};

#endif // CUSTOMHTTPLIB_H
