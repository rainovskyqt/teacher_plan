#ifndef DICTIONARYMANAGER_H
#define DICTIONARYMANAGER_H

#include "modelcourses.h"
#include "modeldepartment.h"
#include "modeldiscipline.h"
#include "modelpost.h"
#include "modelworkform.h"
#include "modelyear.h"
#include "modelgenericworkform.h"

#include <QObject>

class DictionaryManager : public QObject
{
    Q_OBJECT
public:
    explicit DictionaryManager(QObject *parent = nullptr);

    static DictionaryManager *get();

    ModelCourses *courses() const;
    ModelDepartment *departments() const;
    ModelDiscipline *disciplines() const;
    ModelPost *posts() const;
    ModelWorkForm *workForm() const;
    ModelYear *years() const;

    ModelGenericWorkForm *genericWorkForm() const;

signals:

private:
    ModelCourses *m_courses;
    ModelDepartment *m_departments;
    ModelDiscipline *m_disciplines;
    ModelPost *m_posts;
    ModelWorkForm *m_workForm;
    ModelYear *m_years;
    ModelGenericWorkForm *m_genericWorkForm;
};

#endif // DICTIONARYMANAGER_H


