from typing import Optional

from pydantic import BaseModel
from .general import Dictionary
from .user import UserInBase


class OutStaff(BaseModel):
    user: UserInBase
    posts: Optional[dict[int, int]]

