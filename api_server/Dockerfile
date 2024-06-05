FROM python:3.11.3-slim
WORKDIR .
COPY . .
RUN pip install -r requirements.txt
EXPOSE 8020
CMD ["uvicorn", "--reload", "--host",  "0.0.0.0", "--port", "8020", "server:app"]