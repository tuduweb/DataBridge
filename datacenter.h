#ifndef DATACENTER_H
#define DATACENTER_H

#include <QObject>

#include <Bridge/socketbridge.h>

class DataCenter : public QObject
{
    Q_OBJECT
public:
    explicit DataCenter(QObject *parent = nullptr);
    ~DataCenter();

    void timerEvent(QTimerEvent *e);

    SocketBridge* socketBridge;
    QThread socketBridgeThread;



private:
    intmax_t TotalRecSize;//接收大小
    intmax_t recPackCnt;//接收包数量
    intmax_t intervalRecSize[5];//时间间隔内接收的大小

    QList<QByteArray*> dataStorage;

signals:
    void imgDataSignal(QByteArray b,quint8 type);

public slots:
    void dataSteamSlot(QByteArray *byteArray);//引用代表一个别名
    void bindUdpSlot(QString ip,int port);
};

#endif // DATACENTER_H
