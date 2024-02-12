from peewee import *

# Создание подключения к базе данных
db = SqliteDatabase('example.db')

# Определение модели пользователя (предположим, что она уже определена)
class User(Model):
    # поля модели User
    name = CharField(unique=True, null=False)

    class Meta:
        database = db

# Определение модели Posts
class Posts(Model):
    name = CharField(unique=True, null=False)

    class Meta:
        database = db

# Определение модели Department
class Department(Model):
    name = CharField(unique=True, null=False)

    class Meta:
        database = db

# Определение модели Staff с использованием ForeignKeyField для связи с другими таблицами
class Staff(Model):
    user_id = ForeignKeyField(User, backref="posts")
    department_id = ForeignKeyField(Department, backref="staff")
    post_id = ForeignKeyField(Posts, backref="staff")

    class Meta:
        database = db

# Создание таблиц в базе данных (если они не существуют)
db.connect()
# db.create_tables([User, Posts, Department, Staff])

# Запрос на выборку данных из связанных таблиц для пользователя с user_id = 2
user_id = 2

query = (Staff
         .select(Staff, Department, Posts)
         .join(Department)
         .switch(Staff)
         .join(Posts)
         .where(Staff.user_id == 2))

for staff_member in query:
    print("Staff ID:", staff_member.id)
    print("User ID:", staff_member.user_id)
    print("Department:", staff_member.department_id.name)  # Получаем доступ к имени отдела через department_id
    print("Post:", staff_member.post_id.name)