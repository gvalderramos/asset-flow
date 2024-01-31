#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[]) {
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url (u"qrc:/qml/main.qml"_qs);
    engine.load(url);
//    engine.load(QUrl(QStringLiteral("qml:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

    return app.exec();
}
