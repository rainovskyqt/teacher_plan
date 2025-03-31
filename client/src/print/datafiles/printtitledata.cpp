#include "printtitledata.h"

PrintTitleData::PrintTitleData(QObject *parent)
    : PrintData(parent)
{
}

QString PrintTitleData::studyRector() const
{
    return m_studyRector;
}

void PrintTitleData::setStudyRector(const QString &newStudyRector)
{
    m_studyRector = newStudyRector;
}

int PrintTitleData::startYear() const
{
    return m_startYear;
}

void PrintTitleData::setStartYear(int newStartYear)
{
    m_startYear = newStartYear;
}

int PrintTitleData::endYear() const
{
    return m_endYear;
}

void PrintTitleData::setEndYear(int newEndYear)
{
    m_endYear = newEndYear;
}

QString PrintTitleData::office() const
{
    return m_office;
}

void PrintTitleData::setOffice(const QString &newOffice)
{
    m_office = newOffice;
}

QString PrintTitleData::fio() const
{
    return m_fio;
}

void PrintTitleData::setFio(const QString &newFio)
{
    m_fio = newFio;
}

QString PrintTitleData::post() const
{
    return m_post;
}

void PrintTitleData::setPost(const QString &newPost)
{
    m_post = newPost;
}
