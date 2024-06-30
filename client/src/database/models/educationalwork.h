#ifndef EDUCATIONALWORK_H
#define EDUCATIONALWORK_H

#include <QObject>

class EducationalWork : public QObject
{
    Q_OBJECT
public:
    explicit EducationalWork(QObject *parent = nullptr);

    int baseId() const;
    void setBaseId(int newBaseId);
    int disciplineId() const;
    void setDisciplineId(int newDisciplineId);
    int workFormId() const;
    void setWorkFormId(int newWorkFormId);
    int groupId() const;
    void setGroupId(int newGroupId);
    const QString &comments() const;
    void setComments(const QString &newComments);

signals:

private:
    int m_baseId;
    int m_disciplineId;
    int m_workFormId;
    int m_groupId;
    QString m_comments;
};

#endif // EDUCATIONALWORK_H
