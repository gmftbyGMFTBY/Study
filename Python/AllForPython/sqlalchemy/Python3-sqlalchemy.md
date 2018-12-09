### Sqlalchemy　对象关系映射器简介

对象关系映射器为我提供针对具体的数据库的接口进行相应操作，可以讲抽象的关系型操作转化成对应的对象操作

下面介绍一下简要的用法,**一个表对应一个类，一个记录对应一个元组，一个表的数据对应一个包含元组的列表**

#### 简要使用

1. 必要库加载

   ```python
   #　必要的库加载
   from sqlalchemy import Column , String , Integer , ForeignKey , create_engine , and_ , or_ , text    # text创建SQL语句文本
   from sqlalchemy.orm import sessionmaker , relationship
   from sqlalchemy.ext.declarative import declarative_base
   ```

2. 准备工作

   ```python
   Base = declarative_base()    # 创建所有ORM类的基类，所有之后的类都从此继承得到
   engine = create_engine("mysql+pymysql://root:lt970106@(IP):3306/Databasename" , echo = True , max_overflow = 5)    # 使用具体的数据库驱动建立连接引擎,"数据库+数据库驱动名://user:passw@(IP):端口/数据库名称",echo属性可以显示每一次的SQL查询语句 , max_overflow限制最大连接数
   session = sessionmaker(bind = engine)()    # 创建会话，之后的操作都是在会话上建立起来的
   ```

3. 建立类(关系)

   ```python
   #　关系必须存在一个__tablename__属性　，　至少一个主键，可以添加__repr__魔法函数实现对repr()函数的支持用来实现对一个对象数据的表达
   class User(Base):    # 继承Base类
       __tablename__ = "user"
       id = Column(Integer , primary_key = True)    # Column函数可以创建一个对应二维表额一列数据的映射
       name = Column(String(20))
       fullname = Column(String(20))    # 可以添加ForeignKey属性
       
       def __repr__(self):
           '''
           该方法除了在repr()的时候加载，还会在搜索出来的结果中自动的转成这样的形式
           '''
           return "The student named : %s,%s" % (self.fullname,self.name)
   # ...　建立了很多的二维表类之后必须要执行这一句
   Base.metadata.create_all(engine)    # 创建所有使用Base为基类的映射类的二维表
   user1 = User(id = 1 , name = 'tian' , fullname = 'lan')
   session.add(user1)     # session.add_all([...]) 可以批量加入
   session.commit()    #　上传写入数据库
   session.close()    #　关闭连接数据库的本次会话，一次数据库的操作结束
   ```

4. 数据库的查询操作

   ```python
   # .all() - [...] , .one() / .firest() - 一个对象
   for user in session.query(User).filter(User.id == 1).all():
       print(repr(user))
   # filer之后的返回对象可以使用count()方法进行计数，当然我们也可以使用SQL语句count计数方法进行计数
   # 或者使用类似pymysql中的execute('...')的方式创建SQL语句进行查询，虽然这样很有扩展价值但是不是很符合ORM的理念，如果需要这样执行建议直接使用pymysql库
   engine.execute("SQL")    #　使用engine强制执行SQL语句
   ```

5. 数据库删除操作

   ```python
   session.delete(user1)    # 利用session会话接口从数据库中删除对应的数据
   ```

6. 一对多关系映射

   sqlalchemy使用`ForeignKey`和`relationship()`函数来指明一对多的关系，比如一个用户可有多个邮件地址，而一个邮件地址只属于一个用户。那么就是典型的一对多或多对一关系。

#### 官方文档学习

