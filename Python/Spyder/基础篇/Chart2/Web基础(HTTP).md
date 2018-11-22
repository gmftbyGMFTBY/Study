### HTTP

HTTP协议是我们将超文本标记文档从服务器传送到本地浏览器的一种协议，也是Python爬虫主要的考虑对象

* HTTP请求

  1.HTTP始终采用C-S模式，客户端发起请求，服务端进行响应，HTTP的协议是一个无状态的协议，前一次的请求和后一次的请求没有任何关系

  一个HTTP操作作为一个事务

  2.执行过程

  * C-S建立连接
  * 客户端向服务端发送请求(URL + HTTP版本 + MIME + 请求修饰 + 客户信息和可能的内容)
  * 客户端收到服务端响应
  * 客户端将响应呈现在浏览器上并且断开连接

* HTTP状态码

  HTTP状态码主要目的是现实此次HTTP请求的运行状态

  * 200 - 成功
  * 301 - 资源(网页)被永久转移到了别的URL
  * 404 - 资源不存在
  * 500 - 服务器错误

  1** - 请求接收，继续发送请求

  2** - 成功接收请求

  3** - 重定向资源

  4** - 客户端错误

  5** - 服务端错误

* HTTP头信息

  P63~66

* Cookie状态管理

  会话（Session）跟踪是Web程序中常用的技术，用来**跟踪用户的整个会话**。常用的会话跟踪技术是Cookie与Session。**Cookie通过在客户端记录信息确定用户身份**，**Session通过在服务器端记录信息确定用户身份**。

  本章将系统地讲述Cookie与Session机制。

  **1.1  Cookie机制**

  在程序中，会话跟踪是很重要的事情。理论上，**一个用户的所有请求操作都应该属于同一个会话**，而另一个用户的所有请求操作则应该属于另一个会话，二者不能混淆。例如，用户A在超市购买的任何商品都应该放在A的购物车内，不论是用户A什么时间购买的，这都是属于同一个会话的，不能放入用户B或用户C的购物车内，这不属于同一个会话。

  而Web应用程序是使用HTTP协议传输数据的。**HTTP协议是无状态的协议。一旦数据交换完毕，客户端与服务器端的连接就会关闭，再次交换数据需要建立新的连接。这就意味着服务器无法从连接上跟踪会话**。即用户A购买了一件商品放入购物车内，当再次购买商品时服务器已经无法判断该购买行为是属于用户A的会话还是用户B的会话了。要跟踪该会话，必须引入一种机制。

  Cookie就是这样的一种机制。它可以弥补HTTP协议无状态的不足。在Session出现之前，基本上所有的网站都采用Cookie来跟踪会话。

  **1.1.1  什么是Cookie**

  Cookie意为“甜饼”，是**由W3C组织提出**，最早由Netscape社区发展的一种机制。目前Cookie已经成为标准，所有的主流浏览器如IE、Netscape、Firefox、Opera等都支持Cookie。

  由于HTTP是一种无状态的协议，服务器单从网络连接上无从知道客户身份。怎么办呢？就**给客户端们颁发一个通行证吧，每人一个，无论谁访问都必须携带自己通行证。这样服务器就能从通行证上确认客户身份了。这就是Cookie的工作原理**。

  Cookie实际上是一小段的文本信息。客户端请求服务器，如果服务器需要记录该用户状态，就使用response向客户端浏览器颁发一个Cookie。客户端浏览器会把Cookie保存起来。当浏览器再请求该网站时，浏览器把请求的网址连同该Cookie一同提交给服务器。服务器检查该Cookie，以此来辨认用户状态与权限。服务器还可以根据需要修改Cookie的内容。

  查看某个网站颁发的Cookie很简单。在浏览器地址栏输入**javascript:alert (document. cookie)**就可以了（需要有网才能查看）。

  注意：Cookie功能需要浏览器的支持。如果浏览器不支持Cookie（如大部分手机中的浏览器）或者把Cookie禁用了，Cookie功能就会失效。不同的浏览器采用不同的方式保存Cookie。IE浏览器会在“C:\Documents and Settings\你的用户名\Cookies”文件夹下以文本文件形式保存，一个文本文件保存一个Cookie。

  **1.1.2 Cookie的不可跨域名性**

  很多网站都会使用Cookie。例如，Google会向客户端颁发Cookie，Baidu也会向客户端颁发Cookie。那浏览器访问Google会不会也携带上Baidu颁发的Cookie呢？或者Google能不能修改Baidu颁发的Cookie呢？

  答案是否定的。**Cookie具有不可跨域名性**。根据Cookie规范，浏览器访问Google只会携带Google的Cookie，而不会携带Baidu的Cookie。Google也只能操作Google的Cookie，而不能操作Baidu的Cookie。

  Cookie在客户端是由浏览器来管理的。浏览器能够保证Google只会操作Google的Cookie而不会操作Baidu的Cookie，从而保证用户的隐私安全。浏览器判断一个网站是否能操作另一个网站Cookie的依据是域名。Google与Baidu的域名不一样，因此Google不能操作Baidu的Cookie。

  需要注意的是，虽然网站[http://images.google.com**](http://link.zhihu.com/?target=http%3A//images.google.com)与网站[http://www.google.com**](http://link.zhihu.com/?target=http%3A//www.google.com)同属于Google，但是域名不一样，二者同样不能互相操作彼此的Cookie。

  注意：用户登录网站[http://www.google.com**](http://link.zhihu.com/?target=http%3A//www.google.com)之后会发现访问images.google.com时登录信息仍然有效，而普通的Cookie是做不到的。这是因为Google做了特殊处理。本章后面也会对Cookie做类似的处理。

* HTTP请求的几种方式(Client->Server)

  * GET

    根据URL获取资源，如果URL指向的是一个处理过程，我们GET的是处理过程的结果

    通过URL提交数据

    限制大小为1024字节

  * POST

    项目的的服务器发送请求，要求服务器接收附在请求后的实体

    通过实体文本提交数据

    大小无限制

    安全性比GET好

* 总结

  在爬虫开发的过程中我们通常处理的也是GET,POST请求