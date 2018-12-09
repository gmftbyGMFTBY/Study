months = ["January","Feburary","March","April","May","June","July","August","September"
,"October","November","December"]

endings = ["st","nd","rd"] + ["th"]*17 + ["st","nd","rd"] + ["th"]*7 + ["st"]

year = input("Year:")
month = int(input("Month:"))
day = int(input("Day:"))

print(year,months[month-1],str(day) + endings[day-1]) 
