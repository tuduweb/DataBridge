#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <QObject>

class ImageProcess : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcess(QObject *parent = nullptr);
    ~ImageProcess();


signals:

public slots:
};

#endif // IMAGEPROCESS_H
