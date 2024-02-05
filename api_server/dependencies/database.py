from peewee import MySQLDatabase
from decouple import config


dbase = MySQLDatabase(None)


def init_database():
    dbase.init(
        database=config('DATABASE_NAME'),
        user=config('DATABASE_USER'),
        password=config('DATABASE_PASSWORD'),
        host=config('DATABASE_HOST'),
        port=int(config('DATABASE_PORT'))
    )
    dbase.connect()


def close_database():
    if not dbase.is_closed():
        dbase.close()
