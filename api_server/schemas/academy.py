from typing import Optional

from pydantic import BaseModel


class OutStaff(BaseModel):
    base_id: int
    surname: str
    name: str
    middle_name: Optional[str]

