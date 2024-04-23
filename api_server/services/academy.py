from typing import Union

from fastapi import Security

from schemas.academy import OutStaff
from schemas.user import UserInBase
from models.academy import Staff, Post, Department
from models.user import Rang
from .auth import Auth


async def get_staff_data(user_id: int, r_user_id: int) -> Union[OutStaff | None]:
    answer = (Staff
              .select(Staff, Post, Department, Rang)
              .join(Post)
              .switch(Staff)
              .switch(Department)
              .switch(Rang)
              .where(Staff.user_id == user_id)
              .execute())

    if answer:
        first = answer[0]
        user = OutStaff(user=UserInBase(base_id=first.user.id, login=first.user.login, surname=first.user.surname,
                                        name=first.user.name, middle_name=first.user.middle_name),
                        posts={})

        for row in answer:
            user.posts[row.department.id] = row.post.id
        return user
