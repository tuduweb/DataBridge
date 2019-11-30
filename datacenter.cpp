#include "datacenter.h"

//需要一个结构储存发过来的数据?
//那么产生需要存多少个数据包的问题
//那么产生如何储存这么多数据的问题


DataCenter::DataCenter(QObject *parent) : QObject(parent)
{
    //const dataType

    qDebug() << &dataStorage;
    socketBridge = new SocketBridge(dataStorage);
    socketBridge->moveToThread(&socketBridgeThread);
    socketBridgeThread.start();

//    connect(socketBridge,SocketBridge::receivedData,[=](QByteArray byteArray){
//        qDebug() << &byteArray;
//    });

    connect(socketBridge,static_cast<void (SocketBridge::*)(QByteArray*)>(&SocketBridge::receivedData),this,&DataCenter::dataSteamSlot);


}

DataCenter::~DataCenter()
{
    //没有加入内存管理的内容 object parent
    qDebug() << "DataCenter Destory begin";
    socketBridgeThread.exit(0);
    socketBridgeThread.wait();
    qDebug() << "DataCenter Destory";
    delete socketBridge;
}

void DataCenter::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);

}

void DataCenter::dataSteamSlot(QByteArray *byteArray)
{
    /***
     * &byteArray 应该是stack里面的地址
     * **/
    qDebug() << "=================================";
    qDebug() << "DataSize : " << byteArray->size();
    qDebug() << "DataAddr : " << byteArray;

}

void DataCenter::bindUdpSlot(const QString ip,const int port)
{
    qDebug() << "binUdpSlot << " << ip << "/" << port;
    //socketBridge->bindUdp(ip,port);
}
