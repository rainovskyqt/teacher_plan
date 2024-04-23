from peewee import CharField, ForeignKeyField
from models.basemodel import BaseModel
from models.user import User


class Post(BaseModel):
    name = CharField(unique=True, null=False)


class Department(BaseModel):
    name = CharField(unique=True, null=False)


class Staff(BaseModel):
    user = ForeignKeyField(User, backref="staff")
    department = ForeignKeyField(Department, backref="staff")
    post = ForeignKeyField(Post, backref="staff")


