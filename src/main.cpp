#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "postprocessing.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PostProcessing pp;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty( "postProcessing", &pp );

    engine.load(url);

    return app.exec();
}
