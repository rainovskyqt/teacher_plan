from typing import Union
from webbrowser import get

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
                                        name=first.user.name, middle_name=first.user.middle_name), posts={})
        if first.user.rang:
            user.user.rang = first.user.rang.name

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


async def get_teacher_plan(plane_id: int):
    tp = MTeacherPlan
    answer_query = (tp
                    .select(tp)
                    .where(tp.id == plane_id)
                    .order_by(tp.id))

    if answer_query:
        answer = answer_query[0]
        plan = STeacherPlan(base_id=answer.id, user_id=answer.user.id, department_id=answer.department.id,
                            post_id=answer.post.id, year_id=answer.year.id, status_id=answer.status.id,
                            rate=answer.rate,
                            protocol_number=answer.protocol_number, protocol_date=answer.protocol_date,
                            approved_date=answer.approved_date)
        approved = answer.approved_user
        if approved:
            plan.approved_user = UserInBase(base_id=approved.id, login=approved.login, surname=approved.surname,
                                            name=approved.name, middle_name=approved.middle_name,
                                            rang=approved.rang.name if approved.rang else '')
        for hour in answer.teacher_plan_total_hours:
            plan.hours.append(PlanHours(base_id=hour.id, work_type_id=hour.work_type.id,
                                        plan_id=answer.id, first_semester=hour.first_semester,
                                        second_semester=hour.second_semester, name=hour.work_type.name,
                                        order_place=hour.order_place))

    # department_boss_sign: Optional[UserInBase]   TODO добавить
    return plan


async def get_plan_hours(plan_id: int):
    query = (TeacherPlanTotalHours.select().where(TeacherPlanTotalHours.teacher_plan == plan_id))
    if query:
        return [PlanHours(base_id=row.id, plan_id=row.teacher_plan.id, work_type_id=row.work_type.id,
                          first_semester=row.first_semester, second_semester=row.second_semester,
                          order_place=row.order_place, name=row.name) for row in query]


async def update_teacher_plans(plan: InputTeacherPlan):
    print(plan)
    if plan.base_id:
        query = (MTeacherPlan.update(status=plan.status_id, approved_user=plan.approved_user_id,
                                     approved_date=plan.approved_date,
                                     rate=plan.rate, department_boss_sign=plan.department_boss_sign_id,
                                     protocol_number=plan.protocol_number, protocol_date=plan.protocol_date).
                 where(MTeacherPlan.id == plan.base_id))
        query.execute()

        for hour in plan.hours:
            query = (TeacherPlanTotalHours.update(teacher_plan=plan.base_id, work_type=hour.work_type_id,
                                                  first_semester=hour.first_semester,
                                                  second_semester=hour.second_semester,
                                                  order_place=hour.order_place).
                     where(TeacherPlanTotalHours.id == hour.base_id))
            query.execute()
        return plan.base_id
    else:
        plane = MTeacherPlan.create(user_id=plan.user_id, department_id=plan.department_id, post_id=plan.post_id,
                                    year_id=plan.year_id, status=plan.status_id, approved_user=plan.approved_user_id,
                                    approved_date=plan.approved_date,
                                    rate=plan.rate, department_boss_sign=plan.department_boss_sign_id,
                                    protocol_number=plan.protocol_number, protocol_date=plan.protocol_date)

        for hour in plan.hours:
            TeacherPlanTotalHours.create(teacher_plan=plane, work_type=hour.work_type_id,
                                         first_semester=hour.first_semester,
                                         second_semester=hour.second_semester,
                                         order_place=hour.order_place)
        print("returned create ", plane.id)
        return plane.id
