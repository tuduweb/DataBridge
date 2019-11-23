#include "socketbridge.h"

SocketBridge::SocketBridge(QObject *parent) : QObject(parent)
{
    //UDP
    udpSocket   = new QUdpSocket(this);

    connect(udpSocket,&QUdpSocket::readyRead,this,&SocketBridge::receiveUdpData);
    connect(udpSocket,&QUdpSocket::stateChanged,this,&SocketBridge::udpStateChanged);
    connect(udpSocket,static_cast<void (QUdpSocket::*)(QAbstractSocket::SocketError socketError)>
            (&QUdpSocket::error),this,&SocketBridge::udpErrorOccur);

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

