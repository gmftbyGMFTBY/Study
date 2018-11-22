import sqlite3 as tool

def convert(data):
    if data.startswith('~'):return data.strip('~')
    if not data:data = '0'
    return float(data)

conn = tool.connect("food.db")
cur = conn.cursor()

cur.execute('''
    create table food(
        id TEXT primary key,
        desc TEXT,
        water FLOAT,
        kcal FLOAT,
        protein FLOAT,
        fat FLOAT,
        ash FLOAT,
        carbs FLOAT,
        fiber FLOAT,
        suger FLOAT
        )'''
)

query = 'insert into food values(?,?,?,?,?,?,?,?,?,?)'
k = []
for i in open("./ABBREV.txt"):
    data = i.split('^')
    k.append([convert(j) for j in data[:10]])
#    cur.execute(query , values)

cur.executemany(query,k)

conn.commit()
conn.close()
