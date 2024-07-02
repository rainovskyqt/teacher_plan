#ifndef GENERICWORK_H
#define GENERICWORK_H

#include <QObject>
#include "database/models/datamodels.h"

class GenericWork : public QObject
{
    Q_OBJECT
public:
    explicit GenericWork(WorkType work, QObject *parent = nullptr);

    int baseId() const;
    void setBaseId(int newBaseId);
    WorkType type() const;

signals:

private:
    int m_baseId;
    WorkType m_type;
};

#endif // GENERICWORK_H
