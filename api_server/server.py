from contextlib import asynccontextmanager

from fastapi import FastAPI, Request
from fastapi.responses import JSONResponse, RedirectResponse
from fastapi.exceptions import HTTPException
import uvicorn
from starlette.middleware.cors import CORSMiddleware

from dependencies.database import init_database, close_database

from routers.user import router as user_router
from routers.academy import router as academy_router


@asynccontextmanager
async def lifespan(app: FastAPI):
    init_database()
    yield
    close_database()

app = FastAPI(lifespan=lifespan)  # docs_url=None


app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.exception_handler(404)
def not_found_exception_handler(request: Request, exc: HTTPException):
    return JSONResponse(
        status_code=404,
        content={"message": "Ой! А так просто сюда заходить нельзя, воспользуйтесь приложением."},
        )


app.include_router(user_router)
app.include_router(academy_router)

if __name__ == "__main__":
    uvicorn.run('server:app', reload=True, host='0.0.0.0', port=8010)
