class lable_name():
    '''This is the lable for the phone to save the connection'''
    def __init__(self):
        self.storage = {}
        self.storage["First"] = {}
        self.storage["Middle"] = {}
        self.storage["Name"] = {}
    def lookup(self,lable,name):
        return self.storage[lable].get(name)
    def add(self,full_name):
        names = full_name.split()
        if names == 2: names[1] = ' '
        lables = 'First','Middle','Name'
        for lable,name in zip(lables,names):
            people = self.lookup(lable,name)
            if people:
                if full_name in people:
                    print(full_name,"exits!")
                    return
                else:
                    self.storage[lable][name].append(full_name)
            else:
                self.storage[lable][name] = [full_name]
    def add_mul(self,*full_names):
        for full_name in full_names:
            self.add(full_name)

test = lable_name()
print(test.storage)
test.add("James Lantian rang")
print(test.storage)
test.add("DJSNJ nfsf fsfs")
print(test.storage)
test.add("James Lantian rang")
print(test.storage)
