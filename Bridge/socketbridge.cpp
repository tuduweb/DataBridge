#include "socketbridge.h"
#include <QNetworkInterface>

#include <Core/settingcore.h>


SocketBridge::SocketBridge(QObject *parent) : QObject(parent)
{
    QSharedPointer<SettingCore> settingCore = SettingCore::getIns();
    //然后构造变量?

    //暂时凑合一下
    settingCore->settings->beginGroup("udp");


    //UDP
    udpSocket   = new QUdpSocket(this);




    //获取主机地址列表 QList
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    //从中获取IPV4主机地址
    //上面获取完毕按道理应该存起来.然后用一个迭代器把数据渲染出去…
    //那端口号如何渲染呢 应该从上次默认数据..
    //那么应该存在Setting这个东西?
    //UDP只需要本机地址就可以了

    currentRecPort = (quint16)settingCore->settings->value("port",QVariant(5556)).toInt();
    //currentClientAddress = <QHostAddress> 选定一个
    qDebug()<<currentRecPort;


    //需要把以上数据渲染出去.

    //MVC模式最大的特点 View中是不带数据的 所以 <数据>不应该在UI中.





    //信号的链接
    connect(udpSocket,&QUdpSocket::readyRead,this,&SocketBridge::receiveUdpData);
    connect(udpSocket,&QUdpSocket::stateChanged,this,&SocketBridge::udpStateChanged);
    connect(udpSocket,static_cast<void (QUdpSocket::*)(QAbstractSocket::SocketError socketError)>
            (&QUdpSocket::error),this,&SocketBridge::udpErrorOccur);
}

SocketBridge::~SocketBridge()
{
    this->disconnect();
    //
}

int SocketBridge::CurrentRecPort()
{
    return currentRecPort;
}

//UDP数据接收
void SocketBridge::receiveUdpData()
{
    //QHostAddress clientAddress;
    //quint16 recPort = 0;
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;

        datagram.resize((int)udpSocket->pendingDatagramSize());

        udpSocket->readDatagram(datagram.data(),datagram.size(),&currentClientAddress,&currentRecPort);//保存到当前地址

        //QString current = QHostAddress(currentClientAddress.toIPv4Address()).toString().append(":").append(QString::number(currentRecPort));

        emit receivedData(datagram);

        qDebug()<<"invalid data size:"<<datagram.count();


        /*
        int ret = strData.compare("GetIPAddr");//这一段是判断命令的 就是返回ip地址!所以抄写的时候一定要注意这些关系
        if(0 == ret)
        {
            //qDebug()<<strData;
        }*/

        //udpSocket->writeDatagram(datagram,currentClientAddress,currentRecPort);//把数据直接发送回去

        //qDebug()<<strData;
    }
}


void SocketBridge::udpStateChanged(QAbstractSocket::SocketState socketState)
{
    switch(socketState)
    {
     case QAbstractSocket::UnconnectedState:
        //emit newMassage("Tcp网络未连接");
        break;
    case QAbstractSocket::HostLookupState:
        //emit newMassage("寻找服务主机中...");
        break;
    case QAbstractSocket::ConnectingState:
        //emit newMassage("找到服务主机");
        //emit newMassage("Tcp网络连接中...");
        break;
    case QAbstractSocket::ConnectedState:
        //emit newMassage("Tcp网络已连接！");
        break;
    case QAbstractSocket::ClosingState:
        //emit newMassage("Tcp网络准备关闭中...");
        break;
    default:
        break;
    }
}
void SocketBridge::udpErrorOccur(QAbstractSocket::SocketError socketError)
{
   emit error(udpSocket->errorString());
}

void SocketBridge::udpSendData(QByteArray byteArray)
{
    udpSocket->writeDatagram(byteArray,currentClientAddress,currentRecPort);
}

