from peewee import Model, CharField, IdentityField
from models.basemodel import BaseModel


class User(BaseModel):
    login = CharField(unique=True)
    password = CharField()
    surname = CharField()
    name = CharField()
    middle_name = CharField(null=True)