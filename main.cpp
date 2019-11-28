#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQuickView>

#include <QSharedPointer>
#include <QQmlContext>


#include <Core/settingcore.h>

#include <Bridge/socketbridge.h>

#include <datacenter.h>

static DataCenter* dc;


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //初始化配置类 static_cast<int>
    QSharedPointer<SettingCore> settingCore = SettingCore::getIns();

    SocketBridge* socketBridge = new SocketBridge(&app);


    //qmlRegisterType<BackEnd>("io.qt.examples.backend", 1, 0, "BackEnd");//注册类

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("socketBridge", socketBridge);
    engine.rootContext()->setContextProperty("settings", settingCore.data());

    //注意setContextProperty函数的调用要在load qml之前
    //注意需要在.h中加上宏定义

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;



    return app.exec();
}
