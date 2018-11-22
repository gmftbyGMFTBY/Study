class Temperature():
    '''http://python.jobbole.com/81967/
    目的是实现向后兼容，防止修改原来已经存在的大量的调用代码
    temperature原本是作为我们的属性，但是在添加了条件之后，我们按照上述
    的需要将temperature设定成特性和新构建的_tem属性挂钩并增加了相应的检验的代码，实现避免修改原来的关于temperature的访问和赋值操作，向后兼容'''
    def __init__(self,value = 0):
        self.temperature = value
    def to_fah(self):
        return (self.temperature * 1.8) + 32
    def get_tem(self):
        print("get_tem is running!")
        return self._tem
    def set_tem(self,value):
        print("set_tem is running!")
        if value < -273:raise ValueError("The temperature can not below -273")
        else:self._tem = value
    temperature = property(fget = get_tem,fset = set_tem,doc = "This is the test for the property!")

now = Temperature()
now.temperature = -30 #以前的这句话可以执行但是不满足我们的要求，所以我们这里进行修改后就可以了
#???print(now.temperature,now.temperature.__doc__)
