from dependencies.database import dbase, init_database, close_database
from models.user import User
from models.academy import Post, Department, Staff
from services.auth import Auth

auth = Auth()


def create_tables():
    init_database()
    dbase.drop_tables([User, Post, Department, Staff])
    dbase.create_tables([User, Post, Department, Staff], safe=True)
    close_database()


def fill_first_data():
    init_database()
    User.create(login='admin', password=auth.encode_password("admin"), surname="Администратор", name='',middle_name='')
    User.create(login='teacher', password=auth.encode_password("teacher"), surname="Тестов",
                name='Препод', middle_name='Академиков')

    Post.create(name='Преподаватель')
    Post.create(name='Доцент')

    Department.create(name='Кафедра ТиМ ФК')
    Department.create(name='Кафедра ТиМ ЦВС')

    Staff.create(user_id=2, department_id=1,post_id=2)
    Staff.create(user_id=2, department_id=2, post_id=1)

    close_database()


if __name__ == '__main__':
    create_tables()
    fill_first_data()