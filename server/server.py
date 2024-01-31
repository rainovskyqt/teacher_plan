from fastapi import FastAPI
import uvicorn
from settings import SERVER_HOST, SERVER_PORT

app = FastAPI()

uvicorn.run('server:app', reload=True, host=SERVER_HOST, port=SERVER_PORT)