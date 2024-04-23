from dependencies.database import dbase, init_database, close_database
from models.user import User, Rang
from models.academy import Post, Department, Staff
from models.general import EducationalYears
from models.teacher_plan import TeacherPlan
from services.auth import authenticator


async def fill_test_data():
    init_database()

    Rang.create(name='К.п.н.')
    Rang.create(name='Д.м.н.')

    Post.create(name='Преподаватель')
    Post.create(name='Доцент')
    Post.create(name='Профессор')

    User.create(login='admin', password=await authenticator.encode_password("admin"), surname="Администратор",
                name='', middle_name='')
    User.create(login='teacher', password=await authenticator.encode_password("teacher"), surname="Никонов",
                name='Михаил', middle_name='Дмитриевич', rang=1)
    User.create(login='teacher2', password= await authenticator.encode_password("teacher2"), surname="Михайленко",
                name='Сергей', middle_name='Анатольевич')

    Staff.create(user_id=2, department_id=1,post_id=2)
    Staff.create(user_id=2, department_id=2, post_id=1)
    Staff.create(user_id=3, department_id=3, post_id=3)

    EducationalYears.create(begin_year='2024', end_year='2025')

    TeacherPlan.create(user=2, department=2, post=1, year=1, status=1, rate=1.0)

    close_database()