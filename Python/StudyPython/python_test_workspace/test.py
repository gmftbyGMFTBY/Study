def first_rank(arg):
    def decorator(old_function):
        def new_function():
            print(arg)
            old_function()
        return new_function
    return decorator

@first_rank("Happy")
def return1():
    print("Today is Saturday!")

@first_rank("Sad")
def return2():
    print("TOday is Monday!")

return1()
return2()
