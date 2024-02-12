from typing import Union

from schemas.academy import OutStaff
from schemas.user import UserInBase
from schemas.general import Dictionary
from models.academy import Staff, Post, Department


async def get_staff_data(user_id: int) -> Union[OutStaff | None]:
    answer = (Staff
              .select(Staff, Post, Department)
              .join(Post)
              .switch(Staff)
              .join(Department)
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
