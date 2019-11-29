#include "socketbridge.h"
#include <QNetworkInterface>

#include <Core/settingcore.h>

SocketBridge::SocketBridge(QObject *parent) : QObject(parent)
{
    QSharedPointer<SettingCore> settingCore = SettingCore::getIns();
    //然后构造变量?

    //暂时凑合一下
    //settingCore->settings->beginGroup("udp");

    //UDP
    udpSocket   = new QUdpSocket(this);
    isBind = false;

    //udpSocket->moveToThread(&socketThread);
    //socketThread.start();
    //Tips:在某线程中调用函数，这个函数一定是在这个线程中执行的!这里是一个究极大坑。如果仔细想想还是可以避免踩坑的。



    //获取主机地址列表 QList
//    QString strIpAddress;
//    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
//    // 获取第一个本主机的IPv4地址..
//    for (int i = 0,nListSize = ipAddressesList.size(); i < nListSize; ++i)
//    {
//           if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
//               if (strIpAddress.isEmpty())
//               {
//                   strIpAddress = ipAddressesList.at(i).toString();
//                   //break;
//               }
//               //localHostAddrComboBox->addItem(strIpAddress);
//               //把以下内容要改到系统日志中..
//               qDebug()<<"["<<i<<"]"<<ipAddressesList.at(i).toString();

//           }
//    }
//     //如果没有找到，则以本地IP地址为IP
//    if (strIpAddress.isEmpty())
//    {
//        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
//        //localHostAddrComboBox->addItem(strIpAddress);
//    }

//    qDebug() << strIpAddress;

//    //上面获取完毕按道理应该存起来.然后用一个迭代器把数据渲染出去…
//    //那端口号如何渲染呢 应该从上次默认数据..
//    //那么应该存在Setting这个东西?
//    //UDP只需要本机地址就可以了

//    qDebug() << ipAddressesList;

//    currentRecPort = (quint16)settingCore->settings->value("udp/port",QVariant(5556)).toInt();
//    //currentClientAddress = <QHostAddress> 选定一个
//    //qDebug()<<currentRecPort;

//    _ipAddress = QString("123.22.22.33");
//    _recPort = 5533;
//    qDebug() << _recPort;

//    connect(this,&SocketBridge::recPortChanged,this,[=](){
//        qDebug() << "changed" << _recPort;
//    });


    //需要把以上数据渲染出去.

    //MVC模式最大的特点 View中是不带数据的 所以 <数据>不应该在UI中.




    //信号的链接
    connect(udpSocket,&QUdpSocket::readyRead,this,&SocketBridge::receiveUdpData);
    connect(udpSocket,&QUdpSocket::stateChanged,this,&SocketBridge::udpStateChanged);
    connect(udpSocket,static_cast<void (QUdpSocket::*)(QAbstractSocket::SocketError socketError)>
            (&QUdpSocket::error),this,&SocketBridge::udpErrorOccur);

    connect(this,&SocketBridge::receivedData,[=](QByteArray data){
        qDebug() << &data;
    });
}

SocketBridge::SocketBridge(QList<QByteArray *> &arrayList, QObject *parent) : SocketBridge(parent)
{
    qDebug() << &arrayList;
}

SocketBridge::~SocketBridge()
{
    this->disconnect();
    //
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

        //这里的 currentRecPort 是最近一次接收到UDP数据的地址

        QString poster = QHostAddress(currentClientAddress.toIPv4Address()).toString().append("/").append(QString::number(currentRecPort));

        //在事件队列中的是QByteArray的拷贝，其中内容指针也会改变.即全拷贝?
        //为了防止内容改变.那么需要实现一定的功能..
        emit receivedData(datagram);

        qDebug()<<poster << " << " << datagram.data() << " << " <<datagram.count() << " << " << datagram.toHex();


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

bool SocketBridge::bindUdp(const QString ip, const int port)
{
    //绑定udp
    if(this->isBind)
    {
        this->undindUdp();
        this->isBind = false;
        return true;
    }
    qDebug() << "bind" << ip << "/" << port;
    this->udpSocket->bind(
                QHostAddress(ip),
                static_cast<quint16>(port),
                QUdpSocket::ShareAddress);
    this->isBind = true;
    return true;
}

bool SocketBridge::undindUdp()
{
    this->udpSocket->close();
    return true;
}

void SocketBridge::bindUdpSlot(const QString ip, const int port)
{
    this->bindUdp(ip,port);
}

