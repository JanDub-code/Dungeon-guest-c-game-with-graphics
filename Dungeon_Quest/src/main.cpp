#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "game_engine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    if (!GameEngine::instantiate(argc, argv, context))
    {
        return -1;
    }

    GameEngine *game_engine = GameEngine::getInstance();
    context->setContextProperty("game_engine", game_engine);

    //qmlRegisterSingletonType(QUrl("qrc:///src/StackViewChanger.qml"), "SVC", 1, 0, "StackViewChanger");

    const QUrl url(u"qrc:/src/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
