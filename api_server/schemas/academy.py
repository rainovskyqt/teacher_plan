from typing import Optional


class OutStaff:
    base_id: int
    surname: str
    name: str
    middle_name: Optional[str]
    departments: dict["OutDepartment", list["OutPost"]] 


class OutDepartment:
    base_id: int
    name: str


class OutPost:
    base_id: int
    name: str
