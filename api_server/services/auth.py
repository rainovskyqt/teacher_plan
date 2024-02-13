from datetime import datetime, timedelta
from fastapi import HTTPException, status, Depends, Header, Security
from fastapi.security import OAuth2PasswordBearer
from passlib.context import CryptContext
from decouple import config
# from jose import JWTError, jwt
from fastapi_jwt import JwtAccessBearer, JwtAuthorizationCredentials
from schemas.user import AuthUser
from services.user import get_user

# oauth2_scheme = OAuth2PasswordBearer(tokenUrl="login")
ACCESS_TOKEN_EXPIRE_MINUTES = 30


class Auth:
    access_security = JwtAccessBearer(secret_key=config('APP_SECRET_STRING'))
    hasher = CryptContext(schemes=['bcrypt'], deprecated="auto")

    async def login_user(self, user: AuthUser) -> str:
        user_in_db = await get_user(user.login)
        if user_in_db is None:
            raise HTTPException(
                status_code=status.HTTP_401_UNAUTHORIZED,
                detail="Incorrect username or password",
                headers={"WWW-Authenticate": "Bearer"},
            )

        return await self.encode_token(user_in_db.base_id, 'access')

    async def encode_token(self, base_id: int, token_type: str):

        if token_type not in token_type:
            raise TypeError("Неверный тип токена, должно быть 'access' или 'refresh'")

        payload = {
            'activate': datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
            'expires': (datetime.now() + timedelta(days=0, minutes=ACCESS_TOKEN_EXPIRE_MINUTES))
            .strftime("%Y-%m-%d %H:%M:%S"),
            'scope': token_type,
            'base_id': base_id
        }
        return self.access_security.create_access_token(subject=payload)

    async def encode_password(self, password: str):
        return self.hasher.hash(password)

    async def verify_password(self, password: str, encoded_password: str):
        return self.hasher.verify(password, encoded_password)

    @staticmethod
    def decode_token(credentials: JwtAuthorizationCredentials = Security(access_security)):
        # try:
        payload = credentials.subject
        user_id = payload['base_id']
        if user_id is None:
            raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail='Неверные учетные данные')
        return user_id

    @staticmethod
    def login_required(user_id: int = Depends(decode_token)) -> int:
        if user_id is None:
            raise HTTPException(
                status_code=status.HTTP_401_UNAUTHORIZED,
                detail="Not authenticated",
                headers={"WWW-Authenticate": "Bearer"},
            )
        return user_id

authenticator = Auth()
