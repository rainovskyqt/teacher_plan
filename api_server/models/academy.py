from peewee import CharField, ForeignKeyField

from models.basemodel import BaseModel
from models.user import User


class Posts(BaseModel):
    name = CharField(unique=True, null=False)


class Department(BaseModel):
    name = CharField(unique=True, null=False)


class Staff(BaseModel):
    user_id = ForeignKeyField(User, backref="posts")
    department_id = ForeignKeyField(Department, backref="staff")
    post_id = ForeignKeyField(Department, backref="staff")