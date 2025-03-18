#include "printdata.h"

PrintData::PrintData(QObject *parent)
    : QObject{parent}
{}

QString PrintData::studyRector() const
{
    return m_studyRector;
}

void PrintData::setStudyRector(const QString &newStudyRector)
{
    m_studyRector = newStudyRector;
}

int PrintData::startYear() const
{
    return m_startYear;
}

void PrintData::setStartYear(int newStartYear)
{
    m_startYear = newStartYear;
}

int PrintData::endYear() const
{
    return m_endYear;
}

void PrintData::setEndYear(int newEndYear)
{
    m_endYear = newEndYear;
}

PrintTitleData::PrintTitleData(QObject *parent)
    : PrintData(parent)
{
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
