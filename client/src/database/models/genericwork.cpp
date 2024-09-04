#include "genericwork.h"

GenericWork::GenericWork(WorkType work, int planId, QObject *parent)
    : TeacherWork(planId, parent)
{
    m_type = work;



    `work_form_id` INT NULL DEFAULT NULL,
    `semester` INT NOT NULL,
    `complite` TEXT NULL DEFAULT NULL COLLATE 'utf8mb4_0900_ai_ci',
    `order_place` INT NULL DEFAULT NULL,
    `plan_hours` INT NULL DEFAULT NULL,
    `fact_hours` INT NULL DEFAULT NULL,
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
