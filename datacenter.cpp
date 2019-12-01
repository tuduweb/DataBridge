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

    totalRecSize = 0;


    //创建一个处理
    dataProcess = new DataProcess();
    dataProcess->moveToThread(&dataProcess->thread);
    dataProcess->thread.start();





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
    testData.append(*byteArray);
    qDebug() << "CopyAddr : " <<  &testData.back();

    //统计接口 最好分发出去处理..
    totalRecSize += byteArray->size();//这里还要看情况是否需要处理?
    recPackCnt++;//得到的数据包数量.

    //上述为两种方式 可以根据情况合理选择..
    //把数据发到这里 那么就需要进行数据的校验等步骤了..

    //注意 只储存一定数量的原始信息..
    //多出来的信息要么储存到日志中.要么直接扔掉.

}

void DataCenter::bindUdpSlot(const QString ip,const int port)
{
    qDebug() << "binUdpSlot << " << ip << "/" << port;
    //socketBridge->bindUdp(ip,port);
}
