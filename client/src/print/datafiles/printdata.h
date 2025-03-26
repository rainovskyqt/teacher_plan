#ifndef PRINTDATA_H
#define PRINTDATA_H

#include <QObject>

class PrintData : public QObject
{
    Q_OBJECT
public:
    explicit PrintData(QObject *parent = nullptr);

private:

};

#endif // PRINTDATA_H
