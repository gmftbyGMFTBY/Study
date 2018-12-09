### JavaScript

JS是一种轻量级脚本语言，和python类似只不过是在浏览器内解释执行的，可以插入到HTML页面中，可在所有的现有的浏览器执行

下面解释JS的基本用法:

1.使用方式

* 直接插入HTML中

  ```html
  <html>
    <head>
      <script type="text/javascript">
        alert("Hello World!")
      </script>
    </head>
    <body>
      alert标签中包含的就是javascript代码，可以直接运行
    </body>
  </html>
  ```

* 额外的JS文件(更利于维护代码)

  ```html
  <html>
    <head>
      <script src="目标文档的url"></script>
    </head>
    <body>
      src直接指向外部的js文件
    </body>
  </html>
  ```

为了之后可以看懂爬虫爬过来的JS代码,下面进行简要的介绍

2.语法

* 严格区分大小写，分号结束语句
* 注释(同C语言的注释方式)
* 定义变量var即可，类型会自动转化，同python

3.数据类型和变量

* Number : 不区分整数和浮点数，科学计数法，进制，无限大，NaN等数字统一都是Number类型

* string : '' / ""

* bool : true / false

* array : 

  1.可以包括任意类型的数据，类同list，使用[]

  ​	eg : [1,2,3,4,'lantian',"nothing",NaN,null,true]

  2.var array = new Array(1,2,3)

  3.数组元素可以通过索引来访问，索引开始是０

* 对象，类似python中的字典,**无序**

  var person = {name:'lantian' , age:24,tags:[1,2,3,4,'python'],man:true}

  使用person.name获取属性的值

4.运算符和操作符号:

|   类别   |                   操作符号                   |                    示例                    |
| :----: | :--------------------------------------: | :--------------------------------------: |
|   算数   |                +,-,*,/,%                 |      1 + 2;(1 + 4) * 5 / 2;10.5%3;       |
|  字符串   |                   +,+=                   | var str1='hello';var str2="world";str1+=str2; |
| bool操作 |                !,&&,\|\|                 |    true && true;true\|\|false;!true;     |
|  一元算数  |                  ++,--,                  |             var i = 0;i ++;              |
|  关系比较  |       <,<=,>=,>,!=,==,\=\==,\!\=\=       |      \=\==是还要附带类型判断，\!\==是还要附带类型判断       |
|  按位操作  |            ~,&,\|,^,<<,>>,>>>            |               同C/Python原因                |
|  赋值操作  | =,+=,-=,*=,%=,~=,&=,\|=,^=,<<=,>>=,>>>=  |               按位复合运算和基本运算                |
|  对象操作  | .,[],new,delete,void(undefined),in,instanceof |         对象成员访问，数组访问，构造对象，删除对象...         |
|   其他   |       ?:(三元运算),\,,()(分组操作),typeof        |      typeof true; // 同Python type()      |

5.语句

```javascript
// if - else
var role = 20;
if(age >= 18)
  {
   alert("adult!") 
  }
else
  {
    alert("teenager!")
  }
// for
var x = 0;
var i;
for(i=1;i<=100;i++)
  {
    x+=i;
  }
var person=
    {
      name:'lantian';
      age:20;
      city:'beijing';
    }
for(var i in person)
  {
    alert(i)   // 对对象进行迭代 
  }
// while - 同C语言

// function 函数
/*
	函数获取的参数少了没关系，没有对应的变量收到的值是undefined,计算结果为NaN
	函数获取的参数多了没有关系，不用而已
*/
function add(x,y)
{
  return x + y;
}
```

### XPath - XML

1.XML:

本人不才，没有接触过XML，再看了很多大神在知乎上的回复，感觉XML像是一种存储数据的规范，使用特定的方式(类似JSON和HTML语言的标签一样)

来记录数据，并且内部的信息冗余很大

2.XPath:

该语言用来在XML文档中查询信息，也可以很好的搜寻HTML文档的信息，爬虫开发的时候该点至关重要

并且使用路径表示的形式来指定元素，路径表达式类似于我们的资源路径

使用要点:

* 节点:

  XPath中XML是被当成节点树对待的，有7中节点(元素(类＝类似标签),属性，文本，文档节点(根节点)...)

  5中节点关系(父，子，同胞，先辈，后代)

* 语法:

  ```xml
  <?xml version="1.0" encoding="ISO-8859-1"?>
  <classroom>
    <student>
      <id>1001</id>
      <name lang="en">marry</name>
      <age>20</age>
      <country>China</country>
    </student>
    <student>
      <id>1002</id>
      <name lang="en">jack</name>
      <age>25</age>
      <country>USA</country>
    </student>
  </classroom>
  ```

  如上是一个XML文档，XPath使用路径表达式来选取XML中的节点和节点集

  |    表达式     |             描述              |
  | :--------: | :-------------------------: |
  |  nodename  | 选取nodename下的**所有子节点**(不含本身) |
  |     /      |             层级              |
  | //nodename |       选取所有的nodename节点       |
  |   **.**    |           选取当前节点            |
  |   **..**   |            选取父节点            |
  |     ＠      |            选取属性             |

  ```xpath
  1.classroom/student
  2.classroom//student
  3.//@lang
  ```

  选择到了符合条件的节点之后，**选取特殊的节点需要谓语**,谓语嵌入在[]内

  classroom/student[1]

  classroom/student[last() - n]

  classroom/student[position()<n]

  //name[@lang="..."]

  classroom/student[age>20]/name

  特殊符号：

  * | : 一次匹配出多个
  * \* : 匹配未知的成分,可以充当全部的意思

3.XPath轴　｜　XPath运算符

P59

### JSON

**JSON是JavaScript的对象表示法**，用于存储和交换文本信息，因为JSON比XML更小更快解析，在网络中使用更广泛.

JSON使用JS的语法来描述数据对象，但是本身JSON有独立与JS,并且Python支持解析JSON文件,非常类似于Python的字典。

基本语法:

```json
// JSON对象
{
  'name':'lantian';
  'age':'20';
}

// JSON数组
{'reader':[{'name':'lantian';'age':20},{'name':'marry','age':21}]}    # 这里的readers是包含了两个对象的数组，也是一个对象
```



