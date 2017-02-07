#ifndef CUSTOMHTTPLIB_H
#define CUSTOMHTTPLIB_H

#include <QObject>
#include "qtconcurrentrun.h"
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
#include <QEventLoop>
#include <QTimer>
#include <QCoreApplication>
#include <QThread>
#include <QFuture>
#include <QTimer>
#include <QIODevice>
#include <QFileInfo>

class CustomHttpLib : public QObject
{
    Q_OBJECT
public:
    explicit CustomHttpLib(QObject *parent = 0);
    void init(QQmlApplicationEngine *e);
    ~CustomHttpLib();

public slots:
    Q_INVOKABLE void collect();
    Q_INVOKABLE void auth();

private variable:
    QQmlApplicationEngine *engine;
    QObject *rootObject;
    QObject *usernameEdit;
    QObject *passwordEdit;
    QObject *tip;
    QObject *progressbar;

private function:
    QString GBK2UNICODE(QByteArray array);
    bool handleRequest(QJsonObject &json);

private slots:
    void handleResponse(QNetworkReply*);
    void updateProgressBar();
    void handleReadyRead();

private variable:
    QNetworkRequest request;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QTimer progressTimer;
    float progressValue;
    bool isStreamStart;
    QFile file;
    QFileInfo fileInfo;
};

#endif // CUSTOMHTTPLIB_H
