### HTML - 超文本标记语言

```html
<html>
  <head>
    <title></title>
    <meta></meta>
  </head>
  <body></body>
</html>
```

如上就是html的基本组成

* 其中<html>标签是主标签
* <head>标签保存网页的基本信息，并且不会显示在网页上
  * <title>标签表示文档的标题信息，显示在浏览器左上角
  * <meta>标签保存文档的元信息
* <body>保存网页的主体信息，其中的内容显示在网页上

基本的标签

* <br>:强制换行
* <p> / <div>:换段落标记
* <center>:居中显示文体
* <pre>预格式化文体，常用来显示源代码等部分已经认为排版过的内容,**HTML网页的多个换行和空格都是默认成一个空格**
* <li> in <ol> / <ul>:<li>标签存放在我们的<ol> / <ul>标签中，前者是有序标签，后者是无序标签，<li>实现每个列表行
* <dl> / <dt> / <dd> : <dl>显示定义性列表,<dt>显示一个条目,<dd>显示该条目的的解释信息
* <hr>:水平分割线
* <h1>~<h6>:六级标题
* <font size = "1~7" , color = "red ~" face = "宋体"></font>:改变字体大小
* <b>:加粗文段
* <i>:斜体文段
* <sub>:下标标记文体
* <sup>:上标标记文体
* <cite>:引用文体
* <em>:强调斜体文体
* <strong>:加粗强调文体
* <small>:小写文体，可以嵌套自己和其他的标签
* <big>:大写文体，可以嵌套自己和其他的标签
* <tt>:打印机字体
* <u>:下划线文体

特殊标签

* <img>:

  图像标记，用来在网页中显示图像，特殊的**单标记标签**

  ```html
  1.src:资源路径
  2.width:图片宽度
  3.height：图片高度
  4.border:图片外套边框大小
  5.alt:图片加载失败的文体描述，搜索引擎抓取图片的方式
  <img src ="path+mode" width="" height="" border="" alt=""></img>
  ```

* <a>:

  超链接标签，爬虫经常要抽取连接，链接的使用标签是<a>

  ```html
  1.href:连接的地址，连接是网页，视频，图片音乐都可以
  2.target:定义打开超链接的方式
  	1._blank:新窗口中打开链接
  	2._self:当前窗口打开链接
  	3._parent:父窗口打开链接
  	4._top:顶层窗口打开链接
  <a href="path" target="打开方式" name="页面的锚点名称">连接的文体或者图片</a>
  ```

* 表格:

  * <table>:

    ```html
    <table 属性...></table>
    	1.width：表格宽度
    	2.height：表格高度
    	3.border：表格外框宽度
    	4.align：表格显示位置，left,center,right
    	5.cellspacing：单元格间距
    	6.cellpadding：单元格内容与边框的距离
    	7.frame
    		1.void:无边框
    		2.above:只有顶部有
    		3.below:只有下面有
    		4.hsides:顶底
    		5.lhs:左侧
    		6.rhs:右侧
    		7.vsides:左右侧
    		8.border:全部都有
    	8.rules 分割线
    		1.none：无分割线
    		2.all：全有
    		3.rows：只有行
    		4.clos：只有列
    <caption></caption>
    	用来在表格上显示表格标题，在<table>之后第一个<tr>之前
          align属性：top,bottom,left,right
    <tr></tr>
    	定义表格的行，一整行，很多的<tr>标签构成一个表格
          1.bgcolor:背景色
          2.align:
          3.valign:
    <td></td> / <th></th>
        都是单元格的标记，嵌套在<tr>标签内
        <th></th>是表头标签，都放在第一行或者第一列,文体会被加粗居中显示
          1.bgcolor:单元格背景
          2.align:单元格对齐方式
          3.valign:垂直对齐方式
          4.width:宽
          5.height:高
          6.rowspan:单元格占用行数
          7.colspan:单元格占用列数
        
    ```

### CSS - 层叠样式表

定义如何具体的现实HTML的元素，目的是为了结局内容和表现分离的问题(同一个HTML文档只要更换CSS就可以多样化显示)

1.实现方式:

* 内联样式表:直接写在HTML文档中，使用style属性设置CSS样式

* 嵌入样式表:

  将<style>标签嵌入到<head>标签内，嵌入HTML文档中

* 外部样式表:

  单独编辑成文件，.css为扩展名

  在<head>中的<link>标签的href属性中将css连接到HTML文档中

2.CSS的规则：

​	1.组成:选择器 + 声明

​		选择器:一个HTML元素

​		声明:属性和值的组合，属性是希望设置的属性，每个属性都存在一个值，冒号分开

```html
h1    #　选择器
{
  color:blue;　　　# 声明
  font-size:12px;
}
```

​	2.定义类型：

* HTML标记定义:就像上面的，使用选择器控制，一个选择器可以使用很多的声明

* ID选择器:

  ID选择器可以给HTML中任何标有特定ID的HTML元素增加制定的样式，HTML标签使用通用的ID属性设置ID选择器

  在CSS中，使用**#**特殊符号来标记ID选择器

  ```html
  #word
  {
    text-align:center;
    color:red;
  }
  可以将HTML中的所有的ID为word的元素居中红色处理
  ```

* class选择器:

  不像ID是唯一的，class选择器是可以分配给很多的不同的标签元素的，并且每个HTML也标签元素可以选多个class

  ```html
  .name
  {
    bgcolor:#FFF;
  }
  //
  p.name    # 特定对p标签的类选择器
  {
    bgcolor:#FFF;
  }
  ```

### 基本属性

* 颜色属性:

  color:green

  color:#ff6600

  color:#f60

  color:rgb(255,255,255)

  color:rgba(255,255,255,1)最后的a代表透明度0~1

* 字体属性

  font-size:14px　字体大小

  font-family:宋体，...　字体类型，不存在的时候做替换使用

  font-weight:字体的粗重程度

  ​	1.normal , bold , bolder , lighter

  ​	2.100,200,300,...,900 / normal = 400 , bold = 700

* 背景属性

  定义背景颜色，背景图片，背景位置等

  background-color:同颜色属性

  ~-image:url(...)  背景图片

  ~-repeat图片大小不够的时候的方案

  ​	repeat：整体重复

  ​	repeat-x：横向重复

  ​	repeat-y：纵向重复

  ​	no-repeat：不重复

  ~-position:left , center, right , top , bottom , center

* 文本属性

  text-align:left,center,right文本的对齐方式

  line-align:设置行高

  text-indent:首行缩进,50px...

  letter-spacing:字符间距，默认没有间距/inherit继承父亲

* 列表<ol> / <ul>

  * list-style-type:

    ```html
    将我们的ul标签包含有a类选择器的标签的无序标签设置成圆形
    ul.a   
    {
      list-style-type:circle;
    }
    ```

  * list-style-position:

    标记的位置，inside,outside(默认左侧),inherit

  * list-style-image:

    url('...'), none , inherit

  ​

  ​