#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQuickView>

#include <QSharedPointer>
#include <QQmlContext>


#include <Core/settingcore.h>

#include <Bridge/socketbridge.h>

#include <datacenter.h>
#include <QThread>

static DataCenter* dataCenter;
static QThread dataCenterThread;


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //初始化配置类 static_cast<int>
    QSharedPointer<SettingCore> settingCore = SettingCore::getIns();

    //SocketBridge* socketBridge = new SocketBridge(&app);


    dataCenter = new DataCenter(&app);

//    dataCenter->moveToThread(&dataCenterThread);
//    dataCenterThread.start();

    //此后 通信得用其他类了...



    //qmlRegisterType<BackEnd>("io.qt.examples.backend", 1, 0, "BackEnd");//注册类

    QQmlApplicationEngine engine;


    engine.rootContext()->setContextProperty("dataCenter", dataCenter);
    engine.rootContext()->setContextProperty("settings", settingCore.data());

    //注意setContextProperty函数的调用要在load qml之前
    //注意需要在.h中加上宏定义



    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    if (engine.rootObjects().isEmpty())
        return -1;

    //  信号的链接
    //  QObject::connect(item, SIGNAL(qmlSignal(QString)),&myClass, SLOT(cppSlot(QString)));

    //QObject* object = ;
    QObject* object = engine.rootObjects().first();//需要学习一下 通过QQuickView 和 现有方法 QQmlApplicationEngine 创建的区别

    //信号的链接 从QML信号链接到 c++另外一个进程中的信号
    QObject::connect(object, SIGNAL(bindUdp(QString,int)),dataCenter->socketBridge, SLOT(bindUdpSlot(QString,int)));



    return app.exec();
}
