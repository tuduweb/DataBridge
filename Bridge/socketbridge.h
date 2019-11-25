#ifndef SOCKETBRIDGE_H
#define SOCKETBRIDGE_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>

class SocketBridge : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentRecPort READ CurrentRecPort)



    //Q_PROPERTY (LanguageType currentLanguage READ getLanguage WRITE setLanguage NOTIFY languageChanged) // 导出currentLanguage及对应的get，set接口 get为const
    //Q_ENUMS(LanguageType) // 导出枚举类型


public:
    explicit SocketBridge(QObject *parent = nullptr);
    ~SocketBridge();

    QHostAddress currentClientAddress;
    QUdpSocket  *udpSocket;//udp
    quint16 currentRecPort;
    int CurrentRecPort();



    void udpSendData(QByteArray byteArray);



signals:
    void receivedData(QByteArray byteArray);
    void warning(QString str);
    void error(QString str);
    void newMassage(QString str);

public slots:

private slots:
    void receiveUdpData();
    void udpStateChanged(QAbstractSocket::SocketState socketState);
    void udpErrorOccur(QAbstractSocket::SocketError socketError);
};

#endif // SOCKETBRIDGE_H
