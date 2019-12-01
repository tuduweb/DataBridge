#ifndef DATACENTER_H
#define DATACENTER_H

#include <QObject>

#include <Bridge/socketbridge.h>
#include <Process/dataprocess.h>


//写一个试试水
struct dataProcess_thread_typedef
{
    QThread thread;
    DataProcess obj;
    dataProcess_thread_typedef()
    {
        qDebug() << "thread Init";
    }
};



class DataCenter : public QObject
{
    Q_OBJECT
public:
    explicit DataCenter(QObject *parent = nullptr);
    ~DataCenter();

    void timerEvent(QTimerEvent *e);

    SocketBridge* socketBridge;
    QThread socketBridgeThread;

    DataProcess* dataProcess;

    QList<QByteArray> testData;

    QList<DataProcess*> dataProcList;

    //friend class DataProcess;

private:
    intmax_t totalRecSize;//接收大小
    intmax_t recPackCnt;//接收包数量
    intmax_t intervalRecSize[5];//时间间隔内接收的大小

    QList<QByteArray*> dataStorage;
    //QList<QByteArray> dataStorageTest;

signals:
    void imgDataSignal(QByteArray b,quint8 type);

public slots:
    void dataSteamSlot(QByteArray *byteArray);//引用代表一个别名
    void bindUdpSlot(QString ip,int port);
};

#endif // DATACENTER_H
