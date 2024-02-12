from fastapi import APIRouter, Depends
from services.academy import get_staff_data

from services.auth import oauth2_scheme, authenticator

router = APIRouter(prefix='/academy')


@router.get('/staff/{user_id}')
async def get_staff(user_id: int, token: str = Depends(oauth2_scheme)):
    return await get_staff_data(user_id)


@router.get('/pplan/{user_id}')
async def get_personal_plan(user_id: int, token: str = Depends(oauth2_scheme)):
    print('credentials.credentials', token)
    print(authenticator.decode_token(token), user_id)

