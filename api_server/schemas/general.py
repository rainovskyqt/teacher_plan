from pydantic import BaseModel


class Dictionary(BaseModel):
    base_id: int
    name: str


class StudyYears(BaseModel):
    start: str
    end: str
    base_id: int
