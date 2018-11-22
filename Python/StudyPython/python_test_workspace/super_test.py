class a():
    def __init__(self):
        print("I am A!")
    def print_something(self):
        print("here is something!")

class c():
    def __init__(self):
        print("I am C!")

class b(c,a):
    def __init__(self):
        super().__init__()
        print("I am B!")
    def pr(self):
        super().print_something()

p = b()
p.pr()
