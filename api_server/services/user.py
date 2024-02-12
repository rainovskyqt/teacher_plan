from typing import Union

from models.user import User
from schemas.user import AuthUser


async def get_user(login: str) -> Union[AuthUser | None]:
    query = User.select(User.id, User.login, User.password).where(User.login == login)
    results = query.execute()[0]
    if results:
        return AuthUser(base_id=results.id, login=results.login, password=results.password)
    else:
        return None
