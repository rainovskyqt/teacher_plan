#ifndef PRINTDATA_H
#define PRINTDATA_H

#include <QObject>

class PrintData : public QObject
{
    Q_OBJECT
public:
    explicit PrintData(QObject *parent = nullptr);

    QString studyRector() const;
    void setStudyRector(const QString &newStudyRector);
    int startYear() const;
    void setStartYear(int newStartYear);
    int endYear() const;
    void setEndYear(int newEndYear);

private:
    QString m_studyRector;
    int m_startYear;
    int m_endYear;
};

class PrintTitleData : public PrintData
{
    Q_OBJECT
public:
    explicit PrintTitleData(QObject *parent = nullptr);
    QString office() const;
    void setOffice(const QString &newOffice);
    QString fio() const;
    void setFio(const QString &newFio);
    QString post() const;
    void setPost(const QString &newPost);

private:
    QString m_office;
    QString m_fio;
    QString m_post;

};

#endif // PRINTDATA_H
