#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QQmlContext>
#include "lyric.h"
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<Lyric>("LyricObject", 1, 0, "LyricObject");
    qmlRegisterType<Client>("Client",1,0,"Client");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath",
            QGuiApplication::applicationDirPath());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
