#ifndef PRINTTITLEDATA_H
#define PRINTTITLEDATA_H

#include "printdata.h"

class PrintTitleData : public PrintData
{
    Q_OBJECT
public:
    explicit PrintTitleData(QObject *parent = nullptr);

    QString studyRector() const;
    void setStudyRector(const QString &newStudyRector);
    int startYear() const;
    void setStartYear(int newStartYear);
    int endYear() const;
    void setEndYear(int newEndYear);
    QString office() const;
    void setOffice(const QString &newOffice);
    QString fio() const;
    void setFio(const QString &newFio);
    QString post() const;
    void setPost(const QString &newPost);

private:
    QString m_studyRector;
    int m_startYear;
    int m_endYear;
    QString m_office;
    QString m_fio;
    QString m_post;


};

#endif // PRINTTITLEDATA_H
