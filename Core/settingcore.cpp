#include "settingcore.h"
#include <QDebug>

#include <QCoreApplication>
#include <QNetworkInterface>

#include <QQmlListProperty>

//.h里面定义的成员变量必须在.cpp内实例化才不会报错
QMutex SettingCore::m_Mutex;
QSharedPointer<SettingCore> SettingCore::m_pInstance;

SettingCore::SettingCore(QObject *parent) : QObject(parent)
{
    //初始化QList

    qDebug()<<"Init SettingCore";

    settings = new QSettings(QCoreApplication::applicationDirPath()+"/info.ini",QSettings::IniFormat);

    qDebug() << settings << QCoreApplication::applicationDirPath()+"/info.ini";

    //这里需要更改 改成如果没有数值 那么才初始化...
    settings->setValue("udp/port",QVariant(5556));
    settings->setValue("udp/ipAddress",QVariant("172.16.0.1"));//文字fitter
    settings->setValue("master/isRing",QVariant(true));
    settings->setValue("master/isCrossRoad",QVariant(true));
    settings->setValue("data/isHex",QVariant(true));
    settings->setValue("graph/ch1_name",QVariant("kk"));
    settings->setValue("graph/ch2_name",QVariant("tt"));

//    qDebug() << settings->value("udp/port").isNull();
//    qDebug() << settings->value("udp/port").toInt();
//    qDebug() << settings;

//    qDebug() << settings->allKeys();


    //测试QQmlListProperty

//    _ipList.append(new QString("ip"));

//    for(auto ip : QNetworkInterface::allAddresses())
//    {
//        _ipList.append(new QVariant(ip.toString()));
//    }

//    for(auto ip : _ipList)
//    {
//        qDebug() << *ip;
//    }


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
//    // 如果没有找到，则以本地IP地址为IP
//    if (strIpAddress.isEmpty())
//    {
//        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
//        //localHostAddrComboBox->addItem(strIpAddress);
//    }

    //构造IP地址

    QString strIpAddress;

    for(auto ip : QNetworkInterface::allAddresses())
    {
        if (ip != QHostAddress::LocalHost && ip.toIPv4Address()) {
            if (strIpAddress.isEmpty())
            {
                strIpAddress = ip.toString();
                //break;
            }
            //localHostAddrComboBox->addItem(strIpAddress);
            //把以下内容要改到系统日志中..
            qDebug()<<"[ip]"<<ip.toString();
            _ipList.append(ip.toString());

        }

        //_ipList.append(ip.toString());
    }

    //settings->setValue("udp/lastIpList",_ipList);

    //qDebug() << "t1" << settings->value("udp/lastIpList");
    //qDebug() << "t2" << settings->value("udp/lastIpList").toStringList();


}

SettingCore::~SettingCore()
{
    qDebug()<<"Destory SeetingCore";

    delete settings;
}

QVariant SettingCore::value(const QString name)
{
    //接口成功写好..默认的QVariant里面全部存的QString类型 所以需要注意类型转换
    return settings->value(name);
}

//QQmlListProperty<QString> SettingCore::getIpAddress()
//{
//    //return static_cast<QQmlListProperty<QString>>(_ipList);
//}



QVariantList SettingCore::getIpAddress()
{
    //return QQmlListProperty<QVariant>(this, 0, &SettingCore::appendIP);
    return _ipList;

}

QVariantList SettingCore::ipList() const
{
    return _ipList;
}

void SettingCore::setIpList(const QVariant ipLists)
{
    _ipList.append(ipLists);
    emit ipListChanged();
}




QSharedPointer<SettingCore> &SettingCore::getIns()
{
    //判断是否为空
    if (m_pInstance.isNull())
    {
        QMutexLocker mutexLocker(&m_Mutex);
        if (m_pInstance.isNull())
        {
            m_pInstance = QSharedPointer<SettingCore>(new SettingCore());
            qDebug() << m_pInstance;
        }


    }
    return m_pInstance;
}
