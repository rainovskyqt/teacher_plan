from pydantic import BaseModel


class AuthUser(BaseModel):
    login: str
    password: str


class OutUser(BaseModel):
    base_id: int
    token: str
    refresh_token: str
