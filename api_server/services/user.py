from typing import Union

from models.academy import Staff
from models.user import User
from schemas.user import AuthUser, UserInBase


async def get_user(login: str) -> Union[AuthUser | None]:
    query = User.select(User.id, User.login, User.password).where(User.login == login)
    results = query.execute()[0]
    if results:
        return AuthUser(base_id=results.id, login=results.login, password=results.password)
    else:
        return None


async def add_update_user(user: UserInBase):
    if user.base_id:
        query = (User.update(surname=user.surname, name=user.name, middle_name=user.middle_name, rang=user.rang,
                             password=user.password).where(User.id == user.base_id))
        results = query.execute()
    else:
        results = (User.create(login=user.login, surname=user.surname, name=user.name, middle_name=user.middle_name,
                               password=user.password))
    user_id = results

    if user.posts:
        for post in user.posts:
            if not post.base_id:
                Staff.create(user_id=user_id, department_id=post.department_id, post_id=post.post_id)
            elif post.delete:
                Staff.delete().where(Staff.id == post.base_id)

    print(user)