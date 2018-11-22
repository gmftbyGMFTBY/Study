## IRC Information

#### 1.IRC 简介

1. IRC全程互联网中继聊天，占用很小的带宽和并且非常高速的实现用户的交谈和密谈，每一个IRC都以一个昵称，用户在称为频道的地方进行交谈

2. IRC起源于1988年的芬兰，现在已经覆盖到全球的60个国家，是一个多用户多频道的讨论系统，IRC语序互联网内的人以用户进行及时交谈

3. 优点:

   * 实时交谈
   * 速度快，功能多(相对于电子邮件或者新闻联络组的形式)
   * 支持声音和图像信息的传播
   * 支持保密性传播(不经过服务器)

4. 概念介绍

   * 直接信道交流

     ```sequence
     Alice->Bob: Hello Bob, how are you?
     ```

   * 中转通信交流

     中转的优点

     * 群聊方便，简便的信息广播(广播任务由中转站承担)
     * 形成了 C / S 的客户端和服务端的分离

     ```sequence
     Alice->Carly:
     Carly->Bob:
     Bob-->Carly:
     Carly->Alice:
     ```

   * 服务器网络

     单个的服务器的负担太大的解决方案:**服务器网络**

     * 将用户的请求分散到不同的服务器上
     * 服务器网络树型连接
     * 服务器网络中的每一台服务器都承担着转发用户请求的责任

   * 频道

     * 频道的本质是**广播组(聊天室)**
     * 用户可以进入频道，也可以离开频道
     * 当用户在频道说话，其他成员都接受到广播信息
     * 频道在第一个用户进入创建，在最后一个用户离开取消

   * 请求应答机制

     IRC上的信息交流采用请求和应答的模式

     * 请求(命令) : 是服务器或者客户端发出(请求另一服务器的操作和信息提供)
     * 应答 : 服务器队请求的回应,**应答引入了三位数字作为数字应答标识**

#### 2.IRC基本理念

1. 遵守IRC守则

   * 不要打招呼，直接问问题(避免hi,hello)
   * 不要放大段文字，发链接
   * 给出充分的**条件**,事情的**步骤**,想要的**结果**,做事情的**原因**,你要做的**事**
   * 别搞私聊
   * 明白言行的意义(公共场合存在历史记录)

2. IRC命令

   * ```
     /j    # 加入频道，必须位于同服务器
     ```

   * ```
     /me 
     ```

   * ```
     /nickname:somthing you want to say
     ```

3. 特点

   * 开源社区的基础
   * 热心并且好学
   * 多用户多频道的讨论系统
   * channel按照主题分类
   * 无广告，非利润
   * 界面简单，设置容易
   * 可以绕过服务器进行交流，安全性得到保证    

#### 3.基本命令

* 帮助

  ```c
  /help commands-name
  ```


* 连接服务器

  ```c
  /server irc.ubuntu.com
  ```

* 加入频道

  ```c
  /join #ubuntu-cn    # 如果频道不存在将会创建频道，适合练习使用
  ```

* 退出服务器

  ```c
  /quit
  ```

* 修改昵称

  ```c
  /nick nickname
  ```

* 离开单个频道

  ```c
  /wc
  ```

* 退出服务器

  ```c
  /disconnect irc.ubuntu.com
  ```

* 查看频道上的所有人

  ```c
  /who
  ```

* 查看某人详细信息

  ```c
  /whois nickname
  ```

* 退出频道

  ```c
  /part #channel-name   # 不加参数默认退出当前频道，可以选择退出频道，后面加上退出原因
  ```

* 罗列查看频道

  ```c
  /list #channel-name
  ```

* 向别人单独发送消息

  ```c
  /msg nick-name the-word
  ```

* 告知要和我聊天的人我不在线

  ```c
  /away the-reason    # 如果再发一条信息之后就会上线
  ```

* 和某人聊天

  ```c
  /query the word    # 如果对方away我们会受到对方的away reason，但是对方可以看到消息，只不过可能回复不了
  ```

* 邀请别人进入频道

  ```c
  /invite nick-name #channel-name    # 只是给默认邀请，进不进是别人的join的事情
  ```

* 主语+动作

  ```c
  /me the moving
  ```

* 如果是管理员

  * 踢人

    ```c
    /kick #channel-name nick-name
    ```

  * 改变主题

    ```c
    /topic #channel-name new-name
    ```

#### 4.常见的服务器和频道

1. ```c
   server: irc.mindforge.org
   channel: #china
   ```

2. ```c
   server: irc.ubuntu.com
   channel: #ubuntu-cn
   ```

3. ```c
   server: irc.ubuntu.com
   channel: #fedora
   ```

4. ```c
   server: irc.freenode.net
   channel: #opensuse-cn
   ```

5. ```c
   server: irc.freenode.net
   channel: archlinux-cn
   ```

   ​