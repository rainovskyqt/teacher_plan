from typing import Union

from models.academy import Staff, Department, Posts

async def get_staff_data(user_id: int) -> Union[dict | None]:
    query = (Staff
             .select(Staff.id, Staff, Department, Posts)
             .join(Department)
             .switch(Staff)
             .join(Posts)
             .where(Staff.user_id == user_id))

    for staff in query:
        print(staff.__dict__)

    # return User.get_or_none(User.select(User.id).where(User.login == login)).serialize()
