from typing import Union

from models.user import User


async def get_user(login: str) -> Union[dict | None]:
    return User.get_or_none(User.select(User.id).where(User.login == login)).serialize()
