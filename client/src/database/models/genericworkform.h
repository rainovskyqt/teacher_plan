#ifndef GENERICWORKFORM_H
#define GENERICWORKFORM_H

#include <QObject>

class GenericWorkForm : public QObject
{
    Q_OBJECT
public:
    explicit GenericWorkForm(int baseId, QString chapter, QString name,
                             int maxYearCount, int maxUnitCount, QObject *parent = nullptr);

    int baseId() const;
    QString chapter() const;
    QString name() const;
    QString fullName() const;
    int maxYearCount() const;
    int maxUnitCount() const;

signals:


private:
    int m_baseId;
    QString m_chapter;
    QString m_name;
    int m_maxYearCount;
    int m_maxUnitCount;
};

#endif // GENERICWORKFORM_H
