from datetime import date
from typing import Optional, List

from pydantic import BaseModel
from .general import Dictionary
from .user import UserInBase


class OutStaff(BaseModel):
    user: UserInBase
    posts: Optional[dict[int, int]]


class TeacherPlan(BaseModel):
    base_id: int
    user_id: int
    department_id: int
    post_id: int
    year_id: int
    status_id: int
    approved_user: Optional[UserInBase] = None
    approved_date: Optional[date] = None
    rate: float
    department_boss_sign: Optional[UserInBase] = None
    protocol_number: Optional[str] = None
    protocol_date: Optional[date] = None
    hours: Optional[List["PlanHours"]] = []


class InputTeacherPlan(BaseModel):
    base_id: Optional[int] = None
    user_id: Optional[int] = None
    department_id: Optional[int] = None
    post_id: Optional[int] = None
    year_id: Optional[int] = None
    status_id: int
    approved_user_id: Optional[int] = None
    approved_date: Optional[date] = None
    rate: float
    department_boss_sign_id: Optional[int] = None
    protocol_number: Optional[str] = None
    protocol_date: Optional[date] = None
    hours: Optional[List["PlanHours"]] = None


class PlanHours(BaseModel):
    base_id: Optional[int] = None
    plan_id: int
    work_type_id: int
    first_semester: int
    second_semester: int
    name: str
    order_place: int
