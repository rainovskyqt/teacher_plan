from datetime import datetime, timedelta
from fastapi import HTTPException
from fastapi.security import OAuth2PasswordBearer
from passlib.context import CryptContext
from decouple import config
from jose import JWTError, jwt

oauth2_scheme = OAuth2PasswordBearer(tokenUrl="login")


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
            'expires': (datetime.now() + timedelta(days=0, minutes=180)).strftime("%Y-%m-%d %H:%M:%S"),
            'scope': token_type,
            'base_id': base_id
        }

        return jwt.encode(claims=payload, key=self.secrets, algorithm=self.algorithm)

    def decode_token(self, token):
        try:
            payload = jwt.decode(token=token, key=self.secrets, algorithms=[self.algorithm])
            if payload['scope'] == 'access':
                return payload['base_id']
            elif payload['scope'] == 'refresh':
                return self.encode_token(payload['base_id'], 'access')
            raise HTTPException(status_code=401, detail='Неверный токен')
        except JWTError:
            raise HTTPException(status_code=401, detail='Неверные учетные данные')

authenticator = Auth()