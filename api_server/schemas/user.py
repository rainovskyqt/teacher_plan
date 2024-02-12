from typing import Optional

from pydantic import BaseModel


class AuthUser(BaseModel):
    base_id: Optional[int] = None
    login: str
    password: str


class UserInBase(BaseModel):
    base_id: int
    token: str
    refresh_token: str
