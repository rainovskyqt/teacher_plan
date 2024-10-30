#include "dictionarymanager.h"

Q_GLOBAL_STATIC(DictionaryManager, globalInst)

DictionaryManager::DictionaryManager(QObject *parent)
    : QObject{parent}
{
    m_courses = new ModelCourses(this);
    m_departments = new ModelDepartment(this);
    m_disciplines = new ModelDiscipline(this);
    m_posts = new ModelPost(this);
    m_workForm = new ModelWorkForm(this);
    m_years = new ModelYear(this);
    m_genericWorkForm = new ModelGenericWorkForm(this);
}

DictionaryManager *DictionaryManager::get()
{
    return globalInst;
}

ModelCourses *DictionaryManager::courses() const
{
    return m_courses;
}

ModelDepartment *DictionaryManager::departments() const
{
    return m_departments;
}

ModelDiscipline *DictionaryManager::disciplines() const
{
    return m_disciplines;
}

ModelPost *DictionaryManager::posts() const
{
    return m_posts;
}

ModelWorkForm *DictionaryManager::workForm() const
{
    return m_workForm;
}

ModelYear *DictionaryManager::years() const
{
    return m_years;
}

ModelGenericWorkForm *DictionaryManager::genericWorkForm() const
{
    return m_genericWorkForm;
}
