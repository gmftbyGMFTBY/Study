### 第一章要点摘要

１．文件读写的时候的健壮性保证

```python
try:
    f = open("file_name" , mode = 'r' , buffering = -1)
    # Other lines to execute
finally:
    if f:    # f这个文件对象的引用还存在，说明没被关闭，强制关闭
        f.close()
```

```python
with open("file_name" , mode = 'r' , buffering = -1) as f:
    # Other lines to execute
```

* 小文件读取的时候，可以采用如下的形式进行读取，其中注意小文件size可以忽略，但是大文件容易出现内存不足的情况

  这时候我们通常对文件对象进行迭代处理，当然如果是文本文件我们还可以使用readline()逐行获取

  ```python
  f.read(size)
  ```

2.os / shutil模块简单解析

* os.getcwd():获取当前脚本运行的工作目录
* os.listdir(path):根据输入的路径名称获取当前路径下的所有的文件和文件夹
* os.remove(filepath):删除文件
* os.removedirs(path):删除**空目录**
* os.path.isfile(filepath):判断制定对象是否是文件，bool返回
* os.path.isdir(filepath):判断制定对象是否是文件夹，bool返回
* os.path.isabs(path):判断是否是绝对路径,bool返回
* os.path.exists(path):检查路径是否合法，bool返回
* os.path.split(path):将路径按照路径和文件名分解成一个二元元组
* os.path.splitext(path):和上面雷同，只不过是分离成(文件路径和文件名)与扩展名,没有扩展名泽远祖的第二个元素是空字符串
* os.path.getenv(name)：由name获取对应的环境变量
* os.path.putenv(name , value):name,value都是字符串，在当前脚本环境中添加环境变量
* os.path.abspath(filename) : 补充文件的绝对路径
* os.linesep:显示当前系统的行终止符号，**是属性不是方法** - '\n - linux'
* os.name:系统的名称标识 - 'posix - linux'
* os.rename(old , name):文件或者目录重命名
* os.makedirs(''):创建一个多级目录
* os.mkdir(''):创建单个目录
* os.stat(file):获取文件属性
* os.chmod(file)
* os.path.getsize(file):获取文件大小
* os.getpid():获取当前的进程号PID
* os.getppid():获取父进程的PID


* shutil.copytree('old' , 'new')：拷贝文件树
* shutil.copyfile('old','new')：拷贝文件
* shutil.move('old','new')：移动文件
* shutil.rmtree('dir')：rm -r ...,可不空
* os.rmdir('dir'):rm -r...，必不空

3.多进程操作：

​	1.fork实现多进程：

​		首先需要声明，fork是Linux下特有的系统函数，该多进程的实现方法不适用与windows机器

​		os.fork()函数，**调用一次，返回两次**，将父进程复制一份构建新的子进程。

​		fork()函数的返回值很特殊，如果是父进程，返回子进程的PID,如果是子进程返回0

```python
import os
pid = os.fork()

if pid < 0:print("Fork error!")
elif pid == 0:print("Child processing!")
else:print("Father processing!")
```

​	2.multiprocessing模块

​		http://www.cnblogs.com/lipijin/p/3709903.html

​		我们提前需要直到，所有的产生的多进程其实都是并列同等级的，不存在谁先谁后的区分，也就是说根据不同机器，运行的结果也是不一样的

​		1.Process类：

​			模块中使用该类描述一个进程对象，创建进程需要我们传入一个执行函数和执行函数的参数元组，其中执行函数就是子进程需要执行的任务

​			1.p.start():启动进程p

​			2.p.join():进程阻塞，p进程执行的时候**父进程阻塞**直到p进程结束父进程继续

​			3.p.run():当进程没有制定target的时候，run默认执行，run可以被其他的函数对象覆盖

​			4.p.terminate():强制终止进程，有些进程太耗时，我们选择强行终止进程

```python
import multiprocessing as mp
import os
import time

def run(name):
    print("This is the processing %s (%s)" % (name , os.getpid()))
    if name != 4 : time.sleep(5)

print("Parent processing %s" % os.getpid())   # print the PID of the parent processing.
for i in range(5):
    p = mp.Process(target = run , args = (i,))    # 这里必须要写成(i,)的形式，因为要求args是可迭代的，一个值是不可以迭代的
    print("processing will start.")
    p.start()
    p.join()     #　父进程只有在当前的这个循环的子进程p结束之后才会进入下一个循环
print('End!')

###############

def run1(name):
    print(name)

def run2(name):
    print(name)
    time.sleep(10)

print("Begin")
p1 = mp.Process(target = run1 , args = (str(1)))
p2 = mp.Process(target = run2 , args = (str(2)))
p1.start()
p1.join()　　　　# p1进程结束后，父进程就可以继续运行了
p2.start()
print("End")
```

​		2.Pool类：

​			P.S. : pool的默认的数目是核数，也可以手动指定

​			我们在进程少的时候，完全可以使用Process动态的产生多个进程来运行，但是这样的话，我们就没有办法去限制同一时间内的运行着的进程的数目，这时候我们采用进程池的概念，Pool正是这样一个描述进程池的对象,**池中的每一个进程的任务函数都是一样的**

​			如果池还没满，我们就可以一直往里面添加运行的子进程，对预留队列进行阻塞。可以设置最大的运行子进程的上限，只有当池中的子进程数目小于预定的最大值的时候我们的列表中的下一个子进程才可以继续的加入pool中

​			1.pool.apply_async(run_function , args = (,)):非阻塞的添加我们的子进程进入我们的池中

​				**该方法返回一个对象，该对象的get方法可以获取run_function函数的执行返回值**,可以对该函数包装成迭代器，生成多种的子进程，之后在用迭代器取出即可

​				apply_async(func[, args[, kwds[, callback]]])与apply用法一致，但它是非阻塞的且支持结果返回后进行回调。

```python
for x in gen_list(l):
    result = pool.apply_async(pool_test, (x,))
    print 'main process'
```

   这个时候主进程循环运行过程中不等待apply_async的返回结果，在主进程结束后，即使子进程还未返回整个程序也会就退出。虽然 apply_async是非阻塞的，但其返回结果的get方法却是阻塞的，在本例中result.get()会阻塞主进程。因此可以这样来处理返回结果：
​    [x.get() for x in [pool.apply_async(pool_test, (x,)) for x in gen_list(l)]]



​			2.pool.apply(function , args = (,)):阻塞的添加子进程到池中

​			3.pool.close():停止向池中添加子进程

​			4.pool.join():进程阻塞，父进程等待池中的所有的子进程执行完毕才可以执行,**注意只有在执行了close之后才可以阻塞**

---

​                         5.pool.map(target = ,iterations) : 将迭代器的结果返回成一个列表，和内置的map函数一样，支持将之后的迭代器的中的值统一加到target函数中去处理

---

```python
import os
import multiprocessing as mp
from time import *

def run(i):
    print("processing %s is running." % os.getpid())
    sleep(i)
    print("processing %s is done." % os.getpid())

print('Current processing is %s' % os.getpid())
p = mp.Pool(4)

for i in range(5):
    p.apply(run , args=(i,))
print("Current append done.")
p.close()
p.join()
print("End")
```

​		3.Queue类 - 多进程通信：

​			既然一个父进程下有了很多的子进程，那么子进程之间的通信就是必不可少的事情了，Python的multiprocessing模块提供了很多的进程间通信的的方法，这里先讲解Queue，Queue是一个**多进程安全(跨进程,也是多线程安全的)**的队列，可以使用Queue进行多进程之间的数据传递

​			1.put(instance , blocked , timeout):instance是传递的数据，blocked是否阻塞，timeout是阻塞时长。如果不阻塞且此时队列已满会返回满异常，如果阻塞的时长超过了还没有空余，会返回满异常

​			2.get(blocked,timeout):读取删除一个元素,不阻塞，队列不空立即获取一个，为空返回一个空异常。如果阻塞，如果队列阻塞完之后还是空，返回空异常，否则就会取走一个数据并删除。

```python
import os
from multiprocessing import *
from time import *
from random import *

def write(q, urls):
    print("processing %s is writing" % os.getpid())
    for i in urls:
        q.put(i)
        print('Put the %s into the Queue' % i)
        sleep(random())

def read(q):
    print("processing %s is reading " % os.getpid())
    while True:
        url = q.get(True)
        print('Get %s from the Queue' % url)

if __name__ == "__main__":
    print("Begin...")
    q = Queue()    # the Queue tool class from the multiprocessing module
    writer1 = Process(target = write , args = (q , ['url1' , 'url2' , 'url3']))
    writer2 = Process(target = write , args = (q , ['url4' , 'url5' , 'url6']))
    reader = Process(target = read , args = (q,))
    writer1.start()
    writer2.start()
    reader.start()
    writer2.join()     # When I ignore the writer.join,the father processing will end when then writer2 is end and ignore the writer1.只有writer2阻塞了主进程
    reader.terminate()    # 读进程因为死循环所以要认为强行终止父进程才会结束，否则会一直在等待该reader子进程结束主进程才会结束
    print("End...")
```

​		4.Pipe - 两个进程的通信:

​			两个进程位于我们的管道的两端，管道建立两个进程之间的沟通渠道

​			1.Pipe(duplex):返回一个一个管道二元组(conn1 , conn2)

​				duplex = False :conn1是接收方，conn2是发送方

​				duplex = True :默认格式，全双工模式，两个都可发送和接收

​			2.conn.send(instance):通过管道发送数据

​			3.conn.recv()：通过管道接收数据，**没有消息接收的时候，recv会一直在阻塞状态**

```python
import os
from multiprocessing import Pipe , Process
import time , os , random

def send(pipe , urls):
    for url in urls:
        print("Process %s send : %s" % (os.getpid() , url))
        pipe.send(url)   # Send the url to the recv,这里如果注释掉，那么我们的recv会一直在阻塞直到我们的terminate.
        time.sleep(random.random())

def recv(pipe):
    while True:
        print("Processing %s recv : %s" % (os.getpid() , pipe.recv()))
        time.sleep(random.random())

if __name__ == "__main__":
    pipe = Pipe()
    p1 = Process(target = send , args = (pipe[0] , ['url_' + str(i) for i in range(10)]))
    p2 = Process(target = recv , args = (pipe[1] , ))
    p1.join()    # 父进程阻塞到发信子进程结束，意味着发信子进程结束后主进程马上就要执行下一条语句结束进程
    p2.terminate()    # 读进程只能强行终止
```

---

#### 多进程共享内存

* 多进程存在不同的地址空间，没有办法使用全局变量像多线程一样传递数据，但是多进程也有自己的办法

* `shared memory`

  ```python
  import multiprocessing as mp
  value = mp.Value('i', 100)    # 整数,共享内存申请
  value.value    # 进行访问
  array = mp.Array('i', [1, 2, 3])    # list,只能是一维的
  array[0]     # 让共享的数组像(字符串 / list)一样进行访问
  ```

  * i : 整数
  * d : 小数
  * f : 浮点数
  * u : unicode char

---

#### 多进程锁

* 因为对多进程引入了共享内存的概念，方便了我们的数据的交流，但是对于数据的访问需要一种控制方式，就是锁机制

* 分析

  1. 没有锁，抢夺方式

     ```python
     #!/usr/bin/python3

     import multiprocessing as mp
     import time

     def job(v, num):
         for _ in range(10):
             time.sleep(0.1)
             v.value += num
             print(v.value)

     if __name__ == "__main__":
         v = mp.Value('i', 0)
         p1 = mp.Process(target = job, args=(v, 1))
         p2 = mp.Process(target = job, args=(v, 3))
         p1.start()
         p2.start()
         p1.join()
         p2.join()
     ```

  2. 加锁

     ```python
     #!/usr/bin/python3

     import multiprocessing as mp
     import time

     def job(v, num):
         # 对于数据加锁，一次只有一个进程可以对数据进行访问和操作
         l = l.acquire()
         for _ in range(10):
             time.sleep(0.1)
             v.value += num    # 这里的value的使用必须使使用.value的形式才可以调用
             print(v.value)
         l.release()

     if __name__ == "__main__":
         l = mp.Lock()
         v = mp.Value('i', 0)
         p1 = mp.Process(target = job, args=(v, 1))
         p2 = mp.Process(target = job, args=(v, 3))
         p1.start()
         p2.start()
         p1.join()
         p2.join()
     ```

     ​
