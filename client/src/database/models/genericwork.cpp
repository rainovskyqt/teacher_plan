#include "genericwork.h"

GenericWork::GenericWork(WorkType work, QObject *parent)
    : QObject{parent}
{
    m_type = work;
    m_baseId = 0;
}

int GenericWork::baseId() const
{
    return m_baseId;
}

void GenericWork::setBaseId(int newBaseId)
{
    m_baseId = newBaseId;
}

WorkType GenericWork::type() const
{
    return m_type;
}
