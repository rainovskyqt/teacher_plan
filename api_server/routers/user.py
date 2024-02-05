from typing import Union

from fastapi import APIRouter, HTTPException
from schemas.user import AuthUser, OutUser
from services.user import get_user
from services.auth import authenticator
from models.user import User

router = APIRouter()



@router.post('/login')
async def login(user_details: AuthUser):
    user = await get_user(user_details.login)

    if user is None:
        return HTTPException(status_code=401, detail="Пользователь с таким логином и паролем не найден")
    if not authenticator.verify_password(user_details.password, user['password']):
        return HTTPException(status_code=401, detail="Неверный пароль")

    access_token = authenticator.encode_token(base_id=user['id'], token_type='access')
    refresh_token = authenticator.encode_token(base_id=user['id'], token_type='refresh')

    return {'user_id': user['id'], 'access_token': access_token, 'refresh_token': refresh_token}