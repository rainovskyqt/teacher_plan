from datetime import datetime, timedelta
from fastapi import HTTPException, status, Depends, Header
from fastapi.security import OAuth2PasswordBearer
from passlib.context import CryptContext
from decouple import config
from jose import JWTError, jwt

# oauth2_scheme = OAuth2PasswordBearer(tokenUrl="login")
ACCESS_TOKEN_EXPIRE_MINUTES = 30
access_security = JWTAccessBearer

class Auth:
    hasher = CryptContext(schemes=['bcrypt'], deprecated="auto")
    secrets = config('APP_SECRET_STRING')
    token_types = ['access', 'refresh']
    algorithm = 'HS256'

    def encode_password(self, password: str):
        return self.hasher.hash(password)

    def verify_password(self, password: str, encoded_password: str):
        return self.hasher.verify(password, encoded_password)

    def encode_token(self, base_id: int, token_type: str):
        if token_type not in token_type:
            raise TypeError("Неверный тип токена, должно быть 'access' или 'refresh'")

        payload = {
            'activate': datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
            'expires': (datetime.now() + timedelta(days=0, minutes=ACCESS_TOKEN_EXPIRE_MINUTES))
            .strftime("%Y-%m-%d %H:%M:%S"),
            'scope': token_type,
            'base_id': base_id
        }

        return jwt.encode(claims=payload, key=self.secrets, algorithm=self.algorithm)

    def decode_token(self, token: str = Header(...)):
        try:
            payload = jwt.decode(token=token, key=self.secrets, algorithms=[self.algorithm])
            user_id = payload['base_id']
            if user_id is None:
                raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail='Неверные учетные данные')
        except JWTError:
            raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail='Неверные учетные данные')
        return user_id

    def refresh_token(self, user_id: int = Depends(decode_token)):
        new_access_token = self.encode_token(base_id=user_id, token_type='access')
        return {"access_token": new_access_token, "token_type": "bearer"}


authenticator = Auth()
