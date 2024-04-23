from peewee import CharField, ForeignKeyField
from models.basemodel import BaseModel


class Rang(BaseModel):
    name = CharField(unique=True)


class User(BaseModel):
    login = CharField(unique=True)
    password = CharField()
    surname = CharField()
    name = CharField()
    middle_name = CharField(null=True)
    rang = ForeignKeyField(Rang, backref="rang", null=True)
