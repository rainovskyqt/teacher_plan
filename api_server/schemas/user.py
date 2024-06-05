from typing import Optional, List

from pydantic import BaseModel

from schemas.general import Dictionary


class AuthUser(BaseModel):
    base_id: Optional[int] = None
    login: str
    password: str


class OutAuthUser(BaseModel):
    base_id: Optional[int] = None
    token: str
    refresh_token: str


class Staff(BaseModel):
    base_id: int
    department_id: int
    post_id: int
    delete: Optional[bool] = False


class UserInBase(BaseModel):
    base_id: Optional[int] = None
    login: str
    password: Optional[str] = None
    surname: str
    name: str
    middle_name: Optional[str] = None
    rang: Optional[str] = None
    posts: Optional[List[Staff]] = None
