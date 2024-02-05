from dependencies.database import dbase
from peewee import Model


class BaseModel(Model):

    class Meta:
        database = dbase

    def serialize(self):
        return self.__dict__['__data__']
