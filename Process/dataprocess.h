#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include <QObject>

#include <QThread>

class DataProcess : public QObject
{
    Q_OBJECT
public:
    explicit DataProcess(QObject *parent = nullptr);
    ~DataProcess();

    virtual bool checkData();

    virtual bool ProcessPackage(QByteArray &byteArray);



    QThread thread;

signals:

public slots:
};

#endif // DATAPROCESS_H
