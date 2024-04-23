import asyncio

from dependencies.database import dbase, init_database, close_database
from models.general import EducationalYears
from models.teacher_plan import TeacherPlanStatus, TeacherPlanWorksType, TeacherPlan, TeacherPlanTotalHours
from models.user import User, Rang
from models.academy import Post, Department, Staff

from fill_test_data import fill_test_data


def create_tables():
    init_database()
    dbase.drop_tables([TeacherPlan, TeacherPlanTotalHours, TeacherPlanWorksType, TeacherPlanStatus,  User, Rang, Post,
                       Department, Staff, EducationalYears])
    dbase.create_tables([User, Rang, Post, Department, Staff, EducationalYears, TeacherPlanStatus, TeacherPlan,
                         TeacherPlanWorksType, TeacherPlanTotalHours], safe=True)
    close_database()


def fill_first_data():
    init_database()

    TeacherPlanStatus.create(name="В разработке")
    TeacherPlanStatus.create(name="На утверждении")
    TeacherPlanStatus.create(name="Утвержден")

    Department.create(name='Кафедра ТиМ ФК')
    Department.create(name='Кафедра ТиМ ЦВС')
    Department.create(name='Кафедра ТиМ СЕиТА')

    TeacherPlanWorksType.create(name="Учебная работа")
    TeacherPlanWorksType.create(name="Учебно-методическая работа")
    TeacherPlanWorksType.create(name="Научно-исследовательская работа")
    TeacherPlanWorksType.create(name="Воспитательная и спортивная работа")
    TeacherPlanWorksType.create(name="Другие виды работ")

    close_database()


if __name__ == '__main__':
    create_tables()
    fill_first_data()
    asyncio.run(fill_test_data())
