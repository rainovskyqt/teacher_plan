#ifndef PRINTCOMPLITE_H
#define PRINTCOMPLITE_H

#include "printdata.h"

class PrintComplite : public PrintData
{
    Q_OBJECT
public:
    explicit PrintComplite(QObject *parent = nullptr);

    QString comments() const;
    void setComments(const QString &newComments);

    void setValue(int month, int work, QString value);


    QMultiMap<int, QPair<int, QString> > values() const;

private:
    QString m_comments;
    QMultiMap<int, QPair<int, QString>> m_values;  //< Месяц < Вид, Значение>>
};

#endif // PRINTCOMPLITE_H
