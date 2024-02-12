from enum import Enum
from typing import Union

from models.academy import Department, Post
from schemas.general import Dictionary


class DictionaryName(Enum):
    Department = 1,
    Post = 2


dictionaries = {
    DictionaryName.Department: Department,
    DictionaryName.Post: Post
}


async def get_dictionary(name: DictionaryName) -> Union[list[Dictionary] | None]:
    table = dictionaries.get(name)
    query = table.select(table.id, table.name)
    dict_rows = query.execute()
    if dict_rows:
        return [Dictionary(base_id=row.id, name=row.name) for row in dict_rows]
    else:
        return None
