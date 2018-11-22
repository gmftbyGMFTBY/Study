### Scrapy框架

#### 1. Scrapy架构 

![scrapy](/home/lantian/Pictures/GMFBY/scrapy.png)

* 如上是Scrapy的基本运作框架流程示意图，下面简单的介绍一下Scrapy各各组件的特点和之间的工作联系状况

1. Scrapy Engine : 

   引擎，负责控制数据流在系统中组件的流动，并在必要的时候触发相应的事件

2. Schedule : 

   调度器，负责接收请求(URL)并维护，在引擎需要的时候将请求返还给下载器，功能类似于**URL队列管理器**

3. Item Pipeline : 

   数据处理流，其中包含多个对数据处理的方法并且按照优先级依次执行并且最终绝对数据的流向(存储或舍弃),功能类似于**数据存储器(包含数据二次加工)**

4. Downloader : 

   下载器，负责获取页面的数据产生响应并提供给引擎之后转交给Spider，功能是**数据下载器**

5. Spider : 

   是用户主要负责编写的分析响应并从中提取出数据(数据和URL)之后转交给数据处理流和调度器，每个Spider负责处理相关的网站，功能类似于**数据提取(数据一次加工)**

6. Downloader Middlewares : 

   下载器中间件，用来处理下载器的输入和输出

7. Spider Middlewares : 

   处理Spider的输入和输出

* 数据流
  1. 引擎开启特定的网站并且从目标Spider中提取出第一个种子URL
  2. 种子URL交给调度器维护并作为请求由引擎(通过下载器中间件)转交给下载器下载网页数据
  3. 下载器生成响应流经下载器中间件和Spider中间件交给Spider进行数据提取
  4. Spider生成响应和数据返还给引擎(流经中间件)
  5. 引擎将数据Item(数据)交给数据处理流，将响应(URL)交给调度器完成一次周期
  6. 当调度器中不存在更多的URL请求的时候引擎自动结束

#### 2. 项目启动

1. 创建Scrapy项目：

   ```bash
   # 在目标存储目录下开启项目文件夹
   scrapy startproject ...    # 在...文件夹下创建项目目录

   .
   ├── cnblogs
   │   ├── __init__.py    # 库根目录
   │   ├── __pycache__
   │   ├── items.py    # Item数据文件
   │   ├── middlewares.py    # 中间件
   │   ├── pipelines.py    # 数据处理流
   │   ├── settings.py    # 项目配置文件
   │   └── spiders    # Spider组件
   │       ├── __init__.py
   │       └── __pycache__
   └── scrapy.cfg    # 项目部署文件,关于项目的详细说明
   ```

2. 创建Spider模块

   1. Spider是处理单个网站或者类似网站的数据一个类，主要组成部分是

      * 种子URL
      * 处理跟进链接的，页面内容和提取数据的函数

   2. 继承scrapy.Spider类进行自定义设计

   3. 成员(类静态成员 + 方法)

      * name : 区分不同的Spider,名字必须唯一

      * start_urls : 种子URL列表

      * parse(seld , response) : 

        参数response传递并被解析，在这里response生成Item(Data)和Request(URL)对象并即将被返还给引擎

   ```python
   import scrapy 
   class cnlogs(scrapy.Spider):
       name = "cnblogs"
       allowed_domains = ['cnblogs.com']    #　网站的域名
       start_urls = [
         'http://www.cnblogs.com/qiyeboy/'
       ]    # 种子URL，目标爬作者的博客
       
       def parse(self , response):
           '''
           解析函数
           return / yield(Better)  |  Item / Request
           '''
           pass
   ```

   到目前为止，我们只建立了Spider组件，也就是说我们现在爬虫项目只是相当于是一个下载器和调度器而已，并没有任何的**存储和数据处理的功能**

3. 启动爬虫

   ```bash
   # 启动爬虫项目
   scrapy crawl cnblogs    # [cnblogs　来自于Spider的name属性，这里是启动cnblogs爬虫的工作]
   ```

4. 选择器

   我们可以使用bs4来代替我们的数据解析也可以使用Scrapy的response对象相应的css / xpath接口

   * Selector : response也有如下的接口
     * xpath()
     * css()
     * extract() : 提取节点内部的文档将其序列化
     * re(regx) : 利用这则表达式提取

   在Spider的parse方法中，其中一个参数是response，我们真正的工作中低在于如何确定自己的xpath / css　路径的正确性

   * Firebug + scrapy shell

     ```bash
     scrapy shell "URL"    # 更加令人心动的是，我们在IPython的解释其中可以详细的查看到页面的和HTTP请求的所有细节,help函数好好用
     # 之后会打开IPython的解释界面，我们在其中输入
     view(response)    #　在本地打开相应response页面
     # 之后在本地中使用Firebug查看页面元素决定我们的xpath / css 表达式，最后决定后
     response.xpath('') / response.css('')
     # 查看结果是否正确即可
     ```

   * bs4

     ```python
     # 如果觉得xpath / css 编写的国语麻烦，我们还可以绕过response
     from bs4 import BeautifulSoup
     soup = BeautifulSoup(response.body , 'lxml')    #　打开解析器使用soup.find_all方法搜索文档树也可以,response.body返还下载页面的bytes字节包
     ```

   开始解析HTML response

   ```python
   def parse(self , response):
       '''
       使用Firebug + scrapy shell的方式自动获取XPATH : .//*[@class="day"]
       time : .//*[@class='dayTitle']/a/text()
       titile  : .//*[@class="postTitle"]/a/text()
       content : .//*[@class="postCon"]/div/text()
       url : .//*[@class="postTitle"]/a/@href
       '''
       papers = response.xpath('.//*[@class="day"]')
       for paper in papers:
           url = paper.xpath('.//*[@class="postTitle"]/a/@href').extract()[0]
           title = paper.xpath('.//*[@class="postTitle"]/a/text()').extract()[0]
           time = paper.xpath('.//*[@class="dayTitle"]/a/text()').extract()[0]
           content = paper.xpath('.//*[@class="postCon"]/div/text()').extract()[0]
           print(url , title , time , content)
   ```

5. 命令行工具

   这里只讲解全局命令不考虑项目命令

   ```bash
   scrapy startproject project_name    #　建立scarpy项目
   scrapy shell "URL"    #　打开scrapy调试界面
   	view(response)    # 浏览器打开
   scrapy -v    #　version
   scrapy bench - 
   	1.crawl : scrapy crawl project_name : 启动爬虫
   	2.check : scrapy check project_name : 运行前检查
   ```

6. 定义数据Item

   爬虫的目的就是从非结构数据中获取结构数据，我们可以将Item理解成是一种简单的容器，存储爬取的数据，并且提供和字典非常相似的接口

   所有的Item代码存储在items.py中

   * 声明

     ```python
     import scrapy
     class cnblogsitem(scrapy.Item):
         # 以下是创建数据域，声明了item中的数据是什么，在之后的item构建中可以使用 域 = 值 的形式进行初始化构建
         url = scrapy.Field()
         time = scrapy.Field()
         title = scrapy.Field()
         content = scrapy.Field()
         
     # 创建
     item = cnblogsitem(title = "Python Spider" , content = "Coding Spider")
     # 获取数据
     item['title']
     item['conten']
     item.keys()
     item.items()
     item.values()
     # 修改字段
     item['title'] = 'lantian'
     # dict item　转化
     dict = dict(item)
     item = cnblogsitem({...})
     # item允许继承扩展

     # 修改Spider
     # 在这里需要详细的声明，scrapy不会为我们做任何的自动的导入的事情，我们需要手动的导入项目的库
     # from project_name.items import ....
     def parse(self , response):
         '''
         使用Firebug + scrapy shell的方式自动获取XPATH : .//*[@class="day"]
         time : .//*[@class='dayTitle']/a/text()
         titile  : .//*[@class="postTitle"]/a/text()
         content : .//*[@class="postCon"]/div/text()
         url : .//*[@class="postTitle"]/a/@href
         '''
         papers = response.xpath('.//*[@class="day"]')
         for paper in papers:
             url = paper.xpath('.//*[@class="postTitle"]/a/@href').extract()[0]
             title = paper.xpath('.//*[@class="postTitle"]/a/text()').extract()[0]
             time = paper.xpath('.//*[@class="dayTitle"]/a/text()').extract()[0]
             content = paper.xpath('.//*[@class="postCon"]/div/text()').extract()[0]
             item = cnblogsitem(url = url , title = title, time = time , content = content)
             yield item
     ```

7. 循环构建Request(URL)对象插入到调度器中

   爬虫的精髓在于我们可以根据动态的URL不断的下载对应的页面，这里就涉及到新的URL的使用的过程，也就是我们手动构造新的Request请求并由引擎交给调度器Sechdule

   ```python
   import scrapy
   request = scrapy.Request(url , callback)
   # callback参数用来设置谁(这里的谁指代的是Spider中的一个具体的解析函数)来解析该URL被下载器下载后的响应
   # 对于Spider的parse函数的返回值，可以是request , item , 也可以是二者的可迭代容器
   ```

8. 构建数据处理流

   1. 当Item被Spider手机并返还给引擎之后会被传递到数据处理流，流中的组件回一次的对Item对象进行处理

   2. 工作内容

      * 清点HTML数据
      * 检验数据的合理性已经重点字段
      * 查重数据并丢弃
      * 保存数据

   3. 定制Item Pipeline :

      * 每一个Item Pipeline都是一个独立的python类，必须实现process_item方法
      * 每个Item Pipeline对象处理Item对象并一个Item(或子类)对象或者DropItem(中断数据处理流)
      * 只要没有DropItem异常，上一个处理后的Item将会流到下一个处理流中，除非中断或者没有剩余的数据处理流处理

   4. process_item

      ```python
      process_item(self , item , spider):
          '''
          每个Item Pipeline都会执行该方法，返还新的Item / DropItem异常
          item : 被爬取收集的Item
          spider : 收集item的对应的spider
          '''
      ```

      所有的Item Pipeline类都在主目录下的pipelines.py中进行声明

      ```python
      import json    #　存储为json文件
      from scrapy.execpytions import DropItem    #　导入异常

      class cnblogsPipeline:
          def __init__(self):
              self.file = open('papers.json' , 'w')    # 初始化生成打开一个文件
          def process_item(self , item , spider):
              if item['title'] :    #　存在title,爬取到的文章有效
                  line = json.dumps(dict(item)) + '\n'    #　字典化我们的Item数据文件
                  self.file.write*(line)
                  return item
              else : 
                  raise DropItem("There are nothing in %s " % item)
      ```

      但是到这里并没有结束，我们的所有的Pipeline目前位置都是定制完成，我们想要启动就必须将类添加到settings.py中的ITEM_PIPELINES字典变量中，这个字典中更可以容纳很多的Item Pipeline组件，我们使用0-1000之内的整数约定他们的优先级(小优先)，之后就可以执行Item Pipeline 

9. 内置存储数据类型

   我们可以根据自己的洗好选择文件的类型来存储，但是scrapy内部也设置了几种文件的存储方式，我们叫这种为输出

   ```bash
   #　我们可以吧打到标准输出上的爬取内容存储到我们制定的输出文件中,并且自动采用我们制定的后缀文件格式比较方便
   scrapy crawl cnblogs -o papers.csv / papers.json / ...
   #　但是我们需要注意，一旦我们的标准输出没有了，我们的-o参数就会报错，因为这时候输入是None
   ```

10. 内置图片和文件的链接下载方式

  我们经常毁约到一种情况就是:吉祥谣爬取页面还想要爬取整个页面上的部分图片或者文件，为了应对这种情况，我们可以采用上面说过的构建新的Request的方案，但是scrapy内部提供了一套更加成熟和安全的体系去实现这个任务

  **这就涉及到两种特殊的Item Pipeline**

  * 避免重复下载
  * 制定存储位置
  * 缩略图(图片)
  * 图片格式指定(图片)
  * 检测图片的大小限制(图片)

  这两种Item Pipeline会在内部为要下载图片或者文件预留一个队列(避免了不同的Item相同内容的重复下载)

  1. FilePipeline

     * Spider处理中，把Item的文件的URL放入file_urls序列中
     * Item进入Item Pipeline
     * Item进入FilePIpeline中，file_urls中的URL被引擎抓取送给调度器和下载器(不在正规的Scrapy流程中，这意味着小调度器和下载器及其中间件是可以重复使用的)下载
     * 如果文件的下载更优先会优先执行下载(插队) 对应的Item会在文件下载中被锁住知道下载完成
     * 文件下载完成之后,Item中的files会被更新(下载后队列),如果下载失败则不会跟新到files中

  2. ImagePipeline类似处理

     但是对于图片，可以导入Pillow库使用pillow对图片处理的方式

  3. 注册：

     一样的，FilePipeline和ImagePipeline都需要在settings.py中被注册才可以使用

     ```python
     # settings.py中需要的设置
     ITEM_PIPELINES = {
       'scrapy.pipelines.files.FilesPipeline' : 1,
     }    #　处理的优先级高一些比较好，先处理这个数据处理流

     FILES_STORE = ""    #　文件存储的位置,使用绝对路径
     FILES_URLS_FIELD = "file_urls"    #　文件URL在Item中的存储的域
     FILES_RESULT_FIELD = "files"    # 文件URL下载成功后的记录信息在Item中的域

     FILES_EXPIRES = 30   #　还可以设置文件的过期时间

     # 同时在Item中也需要添加两个域
     file_urls = scrapy.Field()
     files = scrapy.Field()

     # 针对ImageFilepPipeline的特性
     #　该特性需要Pillow库的支持
     IMAGES_THUMBS = {
       "small" : (50 , 50),
       "big" : (270,270),
     }    #设置不同的图片的规模的大小，对原图生成big和small备份

     #　对Spider的重写
     def parse(self , response):
             papers = response.xpath('.//*[@class="day"]')
             for paper in papers:
                 url = paper.xpath('.//*[@class="postTitle"]/a/@href').extract()[0]
                 title = paper.xpath('.//*[@class="postTitle"]/a/text()').extract()[0]
                 time = paper.xpath('.//*[@class="dayTitle"]/a/text()').extract()[0]
                 content = paper.xpath('.//*[@class="postCon"]/div/text()').extract()[0]
                 item = CnblogsItem(url = url , title = title , time = time , content = content)
                 request = scrapy.Request(url = url , callback = self.parse_body)
                 # claaback的设置生命了这个请求的响应下一次需要有那个Spider的函数来进行解析
                 # 处理正文
                 request.meta['item'] = item    # 这里的meta的意思是，将我们处理的本次item当做下次请求的原信息，并且统一提交Item和request
                 # 需要注意的是，我们下面可以看到，该请求对应的响应也是存在这个元信息的，只需要meta调出即可，目的在于我们上次的数据信息作为下次数据提取的凭证或者条件
                 yield request
             next_page = Selector(response).re(r'<a href="(\S*)">下一页</a>')    # \S非空白字符,只有选扎起才可以使用正则
             if next_page :     # 还存在下一页继续翻页
                 yield scrapy.Request(url = next_page[0] , callback = self.parse)
         def parse_body(self , response):
             item = response.meta['item']
             body = response.xpath(".//*[@class='postBody']")
             item['image_urls'] = body.xpath(".//img//@src").extract()   #　刚好也是返还列表
             yield item    # 下载图片没有必要生成新的request,秩序哟返还Item到Item Pipeline即可
     ```

  4. 上述的方法是针对我们的默认的FilePipeline和ImagePipeline但是我们有时候仍然需要自定义这两个数据处理流

     * 方法：

       继承两个类重写get_media_requiest / item_completed()方法

       ```python
       # get_media_requests(item , info)
       # 该方法将Item中的对应的要下载的文件或者图片的URL手动打包成请求发送给调度器
       def get_media_requests(self , item , info):
           for image_url in item['image_urls']:
               yield scrapy.Request(url = image_url)
       #　该方法的返回值是item和二元元组的列表
       # 下载成功是True否则是False,下载成功时，checksum是下载文件的MD5哈希，path是文件的存储地址，url是文件的URL,失败则直接使用Failure()异常
       [
         (True ,
          {
            'checksum' : ...,
            'path' : ...,
            'url' : ...
          }
         ),
         (False , Failure(...)
         )
       ]

       # item_completed(result , item , info)
       #　当一个Item的所有的文件连接全部都处理之后(成功或者失败)就会调用该方法
       # 该方法的输出是一个Item / DropItemDU异常传到之后的数据处理流中
       ```

       定制整个子类

       ```python
       from scrapy.pipelines.images import ImagesPipeline    # 这是最新版scrapy的导入方式

       class myimagepipeline(ImagesPipeline):
           def get_media_requests(self , item , info):
               for image_url in item['image_urls']:
                   yield scrapy.Request(url = image_url)
           def item_completed(self ,results , item , info):
               image_paths = [x['path'] for ok , x in results if ok]
               if not image_paths:
                   raise DropItem("Item is nothing.")
               item['images'] = image_paths    # 下载后的完成队列的添加
               return item
       # 我们需要知道最后我们还是需要在settings.py中对我们的定制的类进行设定 cnblogs.pipelines.myimagepipeline : ...
       ```

  ​


#### 3. Scrapy深入

1. Spider:

   ​

