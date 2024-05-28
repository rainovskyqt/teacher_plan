from peewee import CharField, ForeignKeyField, DecimalField, DateField, IntegerField
from models.academy import Department, Post
from models.basemodel import BaseModel
from models.general import EducationalYears
from models.user import User


class TeacherPlanStatus(BaseModel):
    name = CharField(unique=True, null=False)

    class Meta:
        table_name = 'teacher_plan_status'


class TeacherPlan(BaseModel):
    user = ForeignKeyField(User, backref="teacher_plan")
    department = ForeignKeyField(Department, backref="teacher_plan")
    post = ForeignKeyField(Post, backref="teacher_plan")
    year = ForeignKeyField(EducationalYears, backref="teacher_plan")
    status = ForeignKeyField(TeacherPlanStatus, backref="teacher_plan")
    approved_user = ForeignKeyField(User, backref="teacher_plan", null=True)
    approved_date = DateField(null=True)
    rate = DecimalField(max_digits=3, decimal_places=2, default=1.00)
    department_boss_sign = ForeignKeyField(User, backref="teacher_plan", null=True)
    protocol_number = CharField(null=True)
    protocol_date = DateField(null=True)

    class Meta:
        table_name = 'teacher_plan'


class TeacherPlanWorksType(BaseModel):
    name = CharField(unique=True, null=False)
    order = IntegerField()

    class Meta:
        table_name = 'teacher_plan_works_type'


class TeacherPlanTotalHours(BaseModel):
    teacher_plan = ForeignKeyField(TeacherPlan, backref="teacher_plan_total_hours")
    work_type = ForeignKeyField(TeacherPlanWorksType)
    first_semester = IntegerField()
    second_semester = IntegerField()
    order_place = IntegerField()

    class Meta:
        table_name = 'teacher_plan_total_hours'
