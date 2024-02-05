from fastapi import APIRouter, Security, security, Depends
from fastapi.security import HTTPAuthorizationCredentials

from services.auth import oauth2_scheme, authenticator

router = APIRouter(prefix='/academy')


@router.get('/pplan/{user_id}')
async def get_personal_plan(user_id: int, token: str = Depends(oauth2_scheme)):
    print('credentials.credentials', token)
    print(authenticator.decode_token(token), user_id)

