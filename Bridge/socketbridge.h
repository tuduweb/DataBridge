#ifndef SOCKETBRIDGE_H
#define SOCKETBRIDGE_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>

#include <QThread>

class SocketBridge : public QObject
{
    Q_OBJECT




    //Q_PROPERTY (LanguageType currentLanguage READ getLanguage WRITE setLanguage NOTIFY languageChanged) // 导出currentLanguage及对应的get，set接口 get为const
    //Q_ENUMS(LanguageType) // 导出枚举类型


public:
    explicit SocketBridge(QObject *parent = nullptr);
    explicit SocketBridge(QList<QByteArray *> &arrayList,QObject *parent = nullptr);


    ~SocketBridge();

    QUdpSocket  *udpSocket;//udp
    quint16 currentRecPort;
    QHostAddress currentClientAddress;

    bool isBind;


    void udpSendData(QByteArray byteArray);

    Q_INVOKABLE bool bindUdp(const QString ip,const int port);
    Q_INVOKABLE bool undindUdp();

private:


    QThread socketThread;

signals:
    void receivedData(QByteArray byteArray);
    void warning(QString str);
    void error(QString str);
    void newMassage(QString str);

public slots:
    void bindUdpSlot(const QString ip,const int port);

private slots:
    void receiveUdpData();
    void udpStateChanged(QAbstractSocket::SocketState socketState);
    void udpErrorOccur(QAbstractSocket::SocketError socketError);
};

#endif // SOCKETBRIDGE_H
