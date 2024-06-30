#ifndef EDUCATIONALWORK_H
#define EDUCATIONALWORK_H

#include <QObject>

class EducationalWork : public QObject
{
    Q_OBJECT
public:
    explicit EducationalWork(QObject *parent = nullptr);

signals:

private:
    int m_disciplineId;
    int workFormId;
    int courseId;

};

#endif // EDUCATIONALWORK_H
