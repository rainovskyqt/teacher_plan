#include "genericworkform.h"

GenericWorkForm::GenericWorkForm(int baseId, QString chapter, QString name, int maxYearCount, int maxUnitCount, QObject *parent)
    : QObject{parent}
{
    m_baseId = baseId;
    m_chapter = chapter;
    m_name = name;
    m_maxYearCount = maxYearCount;
    m_maxUnitCount = maxUnitCount;
}

int GenericWorkForm::GenericWorkForm::baseId() const
{
    return m_baseId;
}

QString GenericWorkForm::GenericWorkForm::chapter() const
{
    return m_chapter;
}

QString GenericWorkForm::GenericWorkForm::name() const
{
    return m_name;
}

QString GenericWorkForm::GenericWorkForm::fullName() const
{
    return QString("%1 %2").arg(m_chapter, m_name);
}

int GenericWorkForm::GenericWorkForm::maxYearCount() const
{
    return m_maxYearCount;
}

int GenericWorkForm::maxUnitCount() const
{
    return m_maxUnitCount;
}



