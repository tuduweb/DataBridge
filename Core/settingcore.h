#ifndef SETTINGCORE_H
#define SETTINGCORE_H

#include <QObject>
#include <QMutex>
#include <QSharedPointer>
#include <QSettings>



/**
 * @brief 设置类 应该设计为单例模式
 * 设置类 是为了实现设置参数保存、读取的功能
 * 在第二次开启软件的时候就可以重新使用了
 * 这样的操作感应该非常不错!
 * 造轮子时间：2019-11-24
 * 上一次更新时间：
 */

//其中的List为以下构造


class SettingCore : public QObject
{
    Q_OBJECT
public:
    //QSharedPointer提供了对引用计数的共享指针实现. 相当于 shared_ptr
    static QSharedPointer<SettingCore>& getIns(void);
    QList<QMap<QString,QList<QVariant>>> list;
    static QMutex m_Mutex;
    static QSharedPointer<SettingCore> m_pInstance;
    QSettings *settings;

    ~SettingCore();

    qint16 ReadSettings();


private:
    explicit SettingCore(QObject *parent = nullptr);//防止被new; explicit 限制为显示调用
    SettingCore(const SettingCore&);
    SettingCore& operator==(const SettingCore&);


signals:

public slots:
};


#endif // SETTINGCORE_H
