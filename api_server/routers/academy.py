from fastapi import APIRouter, Depends

from services.auth import oauth2_scheme, authenticator
from services.general import get_dictionary, DictionaryName
from services.academy import get_staff_data

router = APIRouter(prefix='/academy')


@router.get("/departments")
async def get_departments():
    return await get_dictionary(DictionaryName.Department)


@router.get("/posts")
async def get_post():
    return await get_dictionary(DictionaryName.Post)


@router.get('/staff/{user_id}')
async def get_staff(user_id: int, token: str = Depends(oauth2_scheme)):
    return await get_staff_data(user_id)


@router.get('/pplan/{user_id}')
async def get_personal_plan(user_id: int, token: str = Depends(oauth2_scheme)):
    print(authenticator.decode_token(token), user_id)

