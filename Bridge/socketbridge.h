#ifndef SOCKETBRIDGE_H
#define SOCKETBRIDGE_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>

class SocketBridge : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentRecPort READ CurrentRecPort)

    Q_PROPERTY(int recPort READ recPort WRITE setRecPort NOTIFY recPortChanged)
    Q_PROPERTY(QString ipAddress READ ipAddress WRITE setIpAddress NOTIFY ipAddressChanged)



    //Q_PROPERTY (LanguageType currentLanguage READ getLanguage WRITE setLanguage NOTIFY languageChanged) // 导出currentLanguage及对应的get，set接口 get为const
    //Q_ENUMS(LanguageType) // 导出枚举类型


public:
    explicit SocketBridge(QObject *parent = nullptr);
    ~SocketBridge();

    QHostAddress currentClientAddress;
    QUdpSocket  *udpSocket;//udp
    quint16 currentRecPort;

    int CurrentRecPort() const;
    int recPort() const;
    QString ipAddress() const;
    int currentFlag() const;

    void setRecPort(int port);
    void setIpAddress(QString ip);
    void udpSendData(QByteArray byteArray);

    Q_INVOKABLE bool bindUdp(const QString ip,const int port);
    Q_INVOKABLE bool undindUdp();

private:
    int _recPort;
    QString _ipAddress;
    int _currentFlag;

signals:
    void receivedData(QByteArray byteArray);
    void warning(QString str);
    void error(QString str);
    void newMassage(QString str);

    //test for qml q_property
    void recPortChanged();
    void ipAddressChanged();

public slots:

private slots:
    void receiveUdpData();
    void udpStateChanged(QAbstractSocket::SocketState socketState);
    void udpErrorOccur(QAbstractSocket::SocketError socketError);
};

#endif // SOCKETBRIDGE_H
