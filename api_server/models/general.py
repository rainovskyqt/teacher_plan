from peewee import CharField
from models.basemodel import BaseModel


class EducationalYears(BaseModel):
    begin_year = CharField(unique=True)
    end_year = CharField(unique=True)

    class Meta:
        table_name = 'educational_years'
