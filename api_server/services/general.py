from enum import Enum
from typing import Union

from models.academy import Department, Post
from models.general import EducationalYears
from schemas.general import Dictionary, StudyYears


class DictionaryName(Enum):
    Department = 1,
    Post = 2


dictionaries = {
    DictionaryName.Department: Department,
    DictionaryName.Post: Post
}


async def get_dictionary(name: DictionaryName) -> Union[list[Dictionary] | None]:
    table = dictionaries.get(name)
    dict_rows = table.select(table).execute()
    if dict_rows:
        return [Dictionary(base_id=row.id, name=row.name) for row in dict_rows]
    else:
        return None


async def get_plan_years() -> Union[list[StudyYears] | None]:
    answer = EducationalYears.select(EducationalYears).order_by(EducationalYears.begin_year.desc()).execute()
    if answer:
        return [StudyYears(start=row.begin_year, end=row.end_year, base_id=row.id) for row in answer]
    else:
        return None
