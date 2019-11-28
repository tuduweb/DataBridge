#ifndef DATACENTER_H
#define DATACENTER_H

#include <QObject>


class DataCenter : public QObject
{
    Q_OBJECT
public:
    explicit DataCenter(QObject *parent = nullptr);
    void timerEvent(QTimerEvent *e);


private:
    intmax_t TotalRecSize;//接收大小
    intmax_t recPackCnt;//接收包数量
    intmax_t intervalRecSize[5];//时间间隔内接收的大小

signals:
    void imgDataSignal(QByteArray b,quint8 type);

public slots:
};

#endif // DATACENTER_H
