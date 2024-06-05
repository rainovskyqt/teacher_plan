from typing import Union

from fastapi import APIRouter, HTTPException, status
from schemas.user import AuthUser, OutAuthUser, UserInBase
from services.user import get_user, add_update_user
from services.auth import authenticator
from models.user import User

router = APIRouter()


@router.post('/login')
async def login(user_details: AuthUser):
    user = await get_user(user_details.login)

    if user is None:
        return HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="Пользователь с таким логином не найден")
    if not await authenticator.verify_password(user_details.password, user.password):
        return HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="Неверный пароль")

    token = await authenticator.encode_token(base_id=user.base_id, token_type='access')
    refresh_token = await authenticator.encode_token(base_id=user.base_id, token_type='refresh')

    return OutAuthUser(base_id=user.base_id, token=token, refresh_token=refresh_token)


@router.post('/user')
async def update_user(user: UserInBase):
    return await add_update_user(user)
