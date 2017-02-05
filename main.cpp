#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "customhttplib.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    CustomHttpLib lib;
    (engine.rootContext())->setContextProperty("httpLib", &lib);
    lib.init(&engine);
    //lib.startCollect();

    return app.exec();
}
