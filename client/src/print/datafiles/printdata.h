#ifndef PRINTDATA_H
#define PRINTDATA_H

#include <QMap>
#include <QObject>

class PrintData : public QObject
{
    Q_OBJECT
public:
    explicit PrintData(QObject *parent = nullptr);

    bool isSecond() const;
    void setSecondSemester(bool newSecondSemester);

protected:
    bool m_secondSemester;
};

#endif // PRINTDATA_H
