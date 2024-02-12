from pydantic import BaseModel


class Dictionary(BaseModel):
    base_id: int
    name: str
