from typing import Union

from fastapi import APIRouter, HTTPException
from schemas.user import AuthUser, UserInBase
from services.user import get_user
from services.auth import authenticator
from models.user import User

router = APIRouter()


@router.post('/login')
async def login(user_details: AuthUser):
    user = await get_user(user_details.login)

    if user is None:
        return HTTPException(status_code=401, detail="Пользователь с таким логином не найден")
    if not authenticator.verify_password(user_details.password, user.password):
        return HTTPException(status_code=401, detail="Неверный пароль")

    token = authenticator.encode_token(base_id=user.base_id, token_type='access')
    refresh_token = authenticator.encode_token(base_id=user.base_id, token_type='refresh')

    return UserInBase(base_id=user.base_id, token=token, refresh_token=refresh_token)