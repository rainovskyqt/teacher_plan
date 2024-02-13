from fastapi import APIRouter, Depends

from services.auth import authenticator
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
async def get_staff(user_id: int, r_user_id: int = Depends(authenticator.login_required)):
    return await get_staff_data(user_id, r_user_id)


@router.get('/pplan/{teacher_id}')
async def get_personal_plan(teacher_id: int):
    print(teacher_id)

