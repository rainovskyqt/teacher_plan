#ifndef GENERICWORKFORM_H
#define GENERICWORKFORM_H

#include <QObject>

class GenericWorkForm : public QObject
{
    Q_OBJECT
public:
    explicit GenericWorkForm(int baseId, QString chapter, QString name, int maxCount,QObject *parent = nullptr);

    int baseId() const;
    QString chapter() const;
    QString name() const;
    QString fullName() const;
    int maxCount() const;

signals:


private:
    int m_baseId;
    QString m_chapter;
    QString m_name;
    int m_maxCount;
};

#endif // GENERICWORKFORM_H
