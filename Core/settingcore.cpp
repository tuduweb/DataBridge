#include "settingcore.h"
#include <QDebug>

#include <QCoreApplication>

//.h里面定义的成员变量必须在.cpp内实例化才不会报错
QMutex SettingCore::m_Mutex;
QSharedPointer<SettingCore> SettingCore::m_pInstance;

SettingCore::SettingCore(QObject *parent) : QObject(parent)
{
    //初始化QList

    qDebug()<<"Init SettingCore";

    settings = new QSettings(QCoreApplication::applicationDirPath()+"/info.ini",QSettings::IniFormat);

    qDebug() << settings << QCoreApplication::applicationDirPath()+"/info.ini";

    settings->setValue("aab/bbb",QVariant(0));
    settings->setValue("aab/cccc",QVariant("test"));
    settings->setValue("ff/ssss",QVariant(0));

    qDebug() << settings->value("aab/bbb").isNull();

    qDebug() << settings->allKeys();
}

SettingCore::~SettingCore()
{
    qDebug()<<"Destory SeetingCore";

    delete settings;
}


QSharedPointer<SettingCore> &SettingCore::getIns()
{
    //判断是否为空
    if (m_pInstance.isNull())
    {
        QMutexLocker mutexLocker(&m_Mutex);
        if (m_pInstance.isNull())
            m_pInstance = QSharedPointer<SettingCore>(new SettingCore());
    }
    return m_pInstance;
}
