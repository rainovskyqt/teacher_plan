from fastapi import APIRouter, Depends

from schemas.academy import InputTeacherPlan
from services.auth import authenticator
from services.general import get_dictionary, DictionaryName, get_plan_years
from services.academy import get_staff_data, get_teacher_plans, update_teacher_plans, get_teacher_plan

router = APIRouter(prefix='/academy')

@router.get("/departments")
async def get_departments():
    return await get_dictionary(DictionaryName.Department)


@router.get("/posts")
async def get_post():
    return await get_dictionary(DictionaryName.Post)


@router.get("/years")
async def years():
    return await get_plan_years()


@router.get('/staff/{user_id}')
# async def get_staff(user_id: int, r_user_id: int = Depends(authenticator.login_required)):
async def staff(user_id: int):
    return await get_staff_data(user_id)  # , r_user_id)


@router.get('/pplan/teacher/{teacher_id}')
async def personal_plan(teacher_id: int):
    return await get_teacher_plans(teacher_id)


@router.get('/pplan/plan/{plan_id}')
async def plan_hours(plan_id: int):
    return await get_teacher_plan(plan_id)


@router.put('/pplan/plan')
async def update_personal_plan(plan: InputTeacherPlan):
    return await update_teacher_plans(plan)
