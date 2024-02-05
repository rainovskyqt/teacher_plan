from dependencies.database import dbase, init_database, close_database
from models.user import User
from models.academy import Posts, Department, Staff
from services.auth import Auth

auth = Auth()


def create_tables():
    init_database()
    dbase.create_tables([User, Posts, Department, Staff], safe=True)
    close_database()


def fill_first_data():
    init_database()
    User.create(login='admin', password=auth.encode_password("admin"), surname="Администратор", name='',middle_name='')
    User.create(login='teacher', password=auth.encode_password("teacher"), surname="Тестов",
                name='Препод',middle_name='Академиков')

    Posts.create(name='Преподаватель')

    Department.create(name='Кафедра ТиМ ФК')

    Staff.create(user_id=2, department_id=1,post_id=1)

    close_database()


if __name__ == '__main__':
    create_tables()
    fill_first_data()