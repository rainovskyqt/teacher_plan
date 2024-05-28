from typing import Union

from fastapi import Security
from peewee import JOIN

from schemas.academy import OutStaff, TeacherPlan as STeacherPlan, InputTeacherPlan, PlanHours
from schemas.user import UserInBase
from models.academy import Staff, Post, Department
from models.user import Rang, User
from models.teacher_plan import TeacherPlan as MTeacherPlan, TeacherPlanTotalHours
from .auth import Auth


async def get_staff_data(user_id: int):  #, r_user_id: int) -> Union[OutStaff | None]:   TODO Авторизация
    answer = (Staff
              .select()
              .join(Post, JOIN.LEFT_OUTER)
              .switch(Staff)
              .join(Department, JOIN.LEFT_OUTER)
              .switch(Staff)
              .join(User, JOIN.INNER)
              .join(Rang, JOIN.LEFT_OUTER)
              .where(Staff.user == user_id))

    if answer:
        first = answer[0]
        user = OutStaff(user=UserInBase(base_id=first.user.id, login=first.user.login, surname=first.user.surname,
                                        name=first.user.name, middle_name=first.user.middle_name,
                                        rang=first.user.rang.name),
                        posts={})

        for row in answer:
            user.posts[row.department.id] = row.post.id
        return user


async def get_teacher_plans(teacher_id: int):
    TP = MTeacherPlan
    answer = (TP
              .select(TP)
              .where(TP.user == teacher_id)
              .order_by(TP.id))

    if answer:
        plans = []
        for row in answer:
            plan = STeacherPlan(base_id=row.id, user_id=row.user.id, department_id=row.department.id,
                                post_id=row.post.id, year_id=row.year.id, status_id=row.status.id, rate=row.rate,
                                protocol_number=row.protocol_number, protocol_date=row.protocol_date,
                                approved_date=row.approved_date)
            approved = row.approved_user
            if approved:
                plan.approved_user = UserInBase(base_id=approved.id, login=approved.login, surname=approved.surname,
                                                name=approved.name, middle_name=approved.middle_name,
                                                rang=approved.rang.name if approved.rang else '')
            for hour in row.teacher_plan_total_hours:
                plan.hours.append(PlanHours(base_id=hour.id, work_type_id=hour.work_type.id,
                                            plan_id=row.id, first_semester=hour.first_semester,
                                            second_semester=hour.second_semester, name=hour.work_type.name,
                                            order_place=hour.order_place))
            plans.append(plan)

        # department_boss_sign: Optional[UserInBase]   TODO добавить
        return plans


async def get_plan_hours(plan_id: int):
    query = (TeacherPlanTotalHours.select().where(TeacherPlanTotalHours.teacher_plan == plan_id))
    if query:
        return [PlanHours(base_id=row.id, plan_id=row.teacher_plan.id, work_type_id=row.work_type.id,
                          first_semester=row.first_semester, second_semester=row.second_semester) for row in query]


async def update_teacher_plans(plan: InputTeacherPlan):
    query = (MTeacherPlan.update(status=plan.status_id, approved_user=plan.approved_user_id,
                                 approved_date=plan.approved_date,
                                 rate=plan.rate, department_boss_sign=plan.department_boss_sign_id,
                                 protocol_number=plan.protocol_number, protocol_date=plan.protocol_date).
             where(MTeacherPlan.id == plan.base_id))
    query.execute()
