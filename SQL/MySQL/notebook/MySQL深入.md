### MySQL架构

#### MySQL介绍

##### MySQL Server

MySQL Server是由**SQL层**和**存储引擎层组成**的，每一层各自都包含有协调工作的子模块

* SQL层：

  权限判断，SQL解析，查询缓存

* 存储引擎层：

  完成底层数据库的数据存储操作

基本的运行流程

1. 客户端发起SQL请求，服务端的连接线程处理层处理客户端的请求，身份验证并检查数据库的安全性
2. 服务端查询缓存和分析SQL是核心
3. 将最后的请求转交给优化器获取数据


1. 物理文件组成

   查询存储的文件的地址

   ```mysql
   show variables like "%datadir%"    # 显示地址一般都是 /var/lib/mysql/...，所有的文件都在该文件下进行存储
   ```

   * 日志文件

     1. 记录数据库的操作信息和错误信息

     2. 组成

        * 错误日志：记录错误信息和启动关闭的信息

        * 二进制日志：记录修改数据库的操作，每条语句的执行时间和资源消耗，记录相关的事务

        * 查询日志：记录所有的select查询信息，比较庞大，尽量少开启

        * 慢查询日志：记录所有的之心改时间超过SQL的最大查询上限的语句，可以针对该语句调优

          ```mysql
          select @@long_query_time    # 现实最大查询上限时间
          ```

        * Redo日志：记录了所有的物理变更和事务信息，加强了安全性

   * 数据文件

     我们在`/var/lib/mysql`文件夹下可以查看到基本的数据文件，每个数据库会对应建立一个目录用来存储数据

     * .frm : 所有的存储引擎都会常见这样的存储文件，一个表对应一个，存放与表相关的数据信息，包括表结构的定义信息，数据库崩溃的时候，可以通过该文件回复表结构
     * .MYD : MyISAM不支持事务的存储引擎的创建方式，存放MyISAM的数据
     * .MYI : 存放索引的数据数，保留缓存信息
     * .ibd / ibdata: 存放InnoDB的数据信息，主要包括索引信息,ibdata共享表方式存储数据，独享表的方式使用ibd
     * opt : 数据库的属性信息，比如数据库的编码等等

   * 其他文件

     配置文件基本上都在`/etc/mysql`中

2. 逻辑块介绍

   MySQL使用逻辑架构采用SQL层和存储引擎分离的模式，实现了数据的存储和逻辑业务的分离

   **SQL层模块**

   * 初始化模块

     数据库启动的时候，对数据库进行初始化操作，包括环境变量的初始化，存储引擎初始化和缓存初始化等等

     ```bash
     mysqld --verbose --help    # 查询当前的数据库系统的所带的参数设置
     ```

     数据库会首先读取`/etc/my.cnf`及其相关文件设置MySQL的全局选项和配置，最后解析有关用户设定的选项

   * 核心API

     设计数据库的底层优化，包括IO，格式化输出(\G),算法的优化，字符串处理，**内存管理**

   * 网络交互模块

     将底层数据操作模块抽象出对外API接口

   * C/S交互模块

     建立在现有的网络通信协议之上，构建MySQL中的客户端和服务端的连接和通讯

   * 用户模块

     用户登录连接和授权管理

   * 访问控制模块

     约束用户的使用数据库的权限，和用户模块构成了权限管理功能

   * 线程管理模块

     线程管理模块负责管理生成的线程并对所有的客户请求都分配对应的线程作为单独的服务

   * 转发模块

     将对应的SQL查询请求发送给不同的模块去处理

   * 缓存模块

     查询缓存模块主要功能就是将客户端的查询请求返回到结果集的缓存中病构建一个哈希值和其对应，当查询的基表的数据一旦发生变化，缓存失效

   * 优化器模块

     根据客户端的查询请求，利用算法分析计算出最优的查询策略并生成查询语句

   * 表变更模块

     对`update`,`insert` ,`alter`,`delete`,`create`等语句处理

   * 表维护模块

     检测表状态，分析优化表结构以便修复

   * 系统状态模块

     ```mysql
     show variables ...;
     show status ...;
     # 利用上述的语句从不同的模块中提取出系统状态数据以返还给用户
     ```

   * 表管理器

     表级锁管理，生成维护系统生成的表文件

   * 日志记录模块

   * 存储引擎接口模块

     插件式数据库底层引擎的管理，将数据处理高度抽象化

   ​      **逻辑块工作逻辑**

   ![1](/home/lantian/File/Study/MySQL/notebook/1.png)

   交互流程

   1. MySQL初始化，从配置文件中读取系统参数和命令参数，病初始化整个系统，启动存储引擎，并且连接模块会监听客户端程序并将请求转发给线程管理模块请求连接线程

   2. 将请求的线程进行用户模块的授权检查，并从**线程池或者新建线程**处理请求

   3. 命令记录写入日志

   4. 对于查询操作，如果是Query类型会启动对应的解析器，如果是`SELECT`类型的查询，打开对应的查询缓存模块，并将数据结果返回给客户端

      如果不是`SELECT`类型的查询则命令解析分发给不同的模块去处理

   5. 如上图，对分发的不同结果执行不同的模块

##### 存储引擎介绍

1. 采用插件的形式将存储引擎加载到对应的正在运行的MySQL中

2. 查看当前默认的表存储引擎

   ```mysql
   alter table table_name engine=Innodb / MyISAM;     # 变更表的存储引擎
   show create table table_name \G     # 查看表的详细信息
   show engines;    # 查看当前数据库中的存储引擎
   ```

3. 创建表制定存储引擎

   ```mysql
   create table table_name(
     id integer primary key auto_increment,
     name varchar(20) not null
   )engine = InnoDB , charset = utf8;
   ```

4. 存储引擎特性

   1. 都使用.frm文件记录表信息和数据属性
   2. 都是用了高速缓存
   3. .frm文件会被加载在缓存中以便下次使用
   4. `InnoDB`
      * 实现了自动增长列(auto_increment)和事务处理
      * 外键约束 : 只有`InnoDB`实现

##### MySQL工具

###### 服务端

1. mysqld:

   SQL服务器进程(MySQL后台程序)，只有该程序运行客户端才可以连接数据库

2. mysqld_safe:

   服务器启动脚本，启动mysqld

3. myisamchk:MyISAM维护工具

###### 客户端

1. mysql / mycli:交互式命令行工具

   ```bash
   mysql -h IP -u root -P -pxxxx    # -h远程登录，-u制定用户，-P指定远程登录端口(默认3306),-p密码

   select current_user();    # 显示当前的登录用户
   ```

   ```mysql
   # -h无法远程登录的问题解决思路
   # 在/etc/mysql/配置文件中将bind-address注释，允许我们使用IP登录,不仅仅是localhost才可以登录
   show grants for 'user';    # 查看指定用户是否可以使用IP登录
   grant all privileges on *.* to "root"@"%" identified by "xxxxx" with grant option;    # 对所有数据库root都可以使用IP登录利用密码"xxxxx"的设置
   ```

   ```mysql
   show variables like "char%";    # 显示字符集
   ```

2. myisampack:MyISAM压缩工具

   ```bash
   myismpack table_name;    # 压缩表，亚索后只读，但是占用更少的数据空间
   ```

3. mysqldump:转储数据到文件中

4. mysqlshow:显示数据库数据库和表列信息

5. mysqladmin:管理操作客户端软件

   检查数据库的配置和当前状态并执行部分数据库操作

   ```bash
   #mysqladmin
   #	-p : 输入密码
   #	-P : 端口
   #	-u : 账户信息
   mysqladmin -u root -p create database_name;    # 创建数据库
   mysqladmin -u root -p drop database_name;    # 删除数据库
   ```

6. mysqlbinlog:

   日志管理工具

   ```mysql
   reset master;    # 删除日志文件
   ```

### MySQL权限和安全

1. 权限表[ENUM('Y','N')]

   1. `user`表(mysql数据库中)

      user表是MySQL中很重要的权限表，记录了允许连接到服务器的账号信息，权限是全局类型的

      ```mysql
      use mysql;
      show * from user \G    # 打印所有的用户权限
      ```

      * user , host , password作为核心的匹配数据库的验证方式

      * 权限列字段决定了用户的权限，普通权限用于操作数据库，高级权限用于数据库管理

      * 可以使用`GRANT` / `UPDATE`语句更改权限和信息

      * 资源控制列

        限制用户使用的资源，`max_*`

   2. `db`和`host`表

      db表存储了用户对数据库的操作权限,host不常用

      ```mysql
      *************************** 1. row ***************************
                       Host: localhost
                         Db: performance_schema
                       User: mysql.session
                Select_priv: Y    # 选择权限
                Insert_priv: N    # 插入权限
                Update_priv: N
                Delete_priv: N
                Create_priv: N
                  Drop_priv: N
                 Grant_priv: N
            References_priv: N
                 Index_priv: N
                 Alter_priv: N
      Create_tmp_table_priv: N
           Lock_tables_priv: N
           Create_view_priv: N
             Show_view_priv: N
        Create_routine_priv: N
         Alter_routine_priv: N
               Execute_priv: N
                 Event_priv: N
               Trigger_priv: N
      ```

      * 用户列

        host ,  db , user - 三个字段代表了db表的主键

        ```mysql
        select * from user \G    # 其中包含了所有的数据库的表的用户，localhost的root和%的root是两个不同的用户
        # 该命令可以显示数据库的主要的成员的详细信息，其中的信息是针对所有的数据库的
        ```

   3. 权限的更新

      因为权限的数据量比较小，MySQL在内存中对权限信息进行了缓存，每次修改完权限之后都要`FLUSH PRIVILEGES`更新权限信息

### 账户管理

1. 新建用户

   * 新创建的用户不存在任何权限

   * `CREATE USER`

     ```mysql
     create user 'user_name'@'%' identified by "xxxxxxx";
     create user 'user_name'@'%' identified by password "xxxxxxxxxxxxxxxxxxxxxxxx";       # 使用哈希值用来设定密码
     select password('xxxxxx');    # 显示xxxxxxx的哈希值之后可以插入使用到我们的创建用户中,password库函数用来加密密码
     ```


   * `GRANT`

     因为`CREATE USER`的用户不存在任何权限，我们需要使用`GRANT`对权限进行限定，使用`GRANT`语句必须要有`GRANT`权限

     甚至而已用来生成新用户病赋予相应权限

     ```mysql
     grant all privileges on database_name.table_name to user@host identified by "password" with grant option;
     ```

   * 直接操作mysql.user用户表修改

     如果存在`INSERT`权限，可以使用`INSERT`向mysql.user表中插入数据

2. 删除用户

   ```mysql
   drop user 'name'@'host';     # 删除对应的表中的用户
   #　还可以使用delete语句来实现，但是需要有对应的权限
   ```

3. 修改密码

   ```bash
   # 1
   mysqladmin -u user_name -p password "xxxxxx"     # 将密码修改为xxxxx
   # 密码存储在 mysql.user authentication_string字段中，用哈希加密保存
   # 2
   (update) + (FLUSH PRIVILEGES)
   # 3
   # 在用户登录下,修改用户的密码
   set password=password("xxxxxx")    # 新密码必须要加密处理
   ```

4. 丢失密码的处理方式

   1. 进入操作系统超级管理员模式

      ```bash
      su    # 目的是获取对/etc/mysql中的配置文件的修改权限
      ```

   2. 在`[mysqld]`下添加

      ```bash
      skip-grant-tables    # 忽略权限表的验证机制，使用操作系统root用户登录
      ```

   3. 重启mysql服务

      ```bash
      /etc/init.d/mysql restart
      ```

   4. 进入mysql

      ```bash
      mysql -u root    # 无需密码即可登录
      ```

   5. 修改密码

      ```mysql
      set password=password('xxxxxx')
      FLUSH PRIVILEGES;    # 刷新权限
      ```

   6. 恢复配置文件中的选项，注释掉`skip-grant-tables`的设置重新启动mysql服务即可恢复正常

   ​

   ​