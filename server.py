import sqlite3
from user import User
from beer import Beer
from keg import Keg

connection = sqlite3.connect('database.sqlite')
db = connection.cursor()

db.execute('CREATE TABLE IF NOT EXISTS user(uid INTEGER PRIMARY KEY ASC, card TEXT, name TEXT)')
db.execute('CREATE TABLE IF NOT EXISTS beer(bid INTEGER PRIMARY KEY ASC, user INTEGER, keg INTEGER, timer INTEGER)')
db.execute('CREATE TABLE IF NOT EXISTS keg(kid INTEGER PRIMARY KEY ASC, name TEXT, brewmaster INTEGER, thermometer TEXT)')

User.db = Keg.db = Beer.db = db
User.create('test', 'test2')
