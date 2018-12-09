### MySQL - C语言中文网资源笔记

#### MySQL基础

1. 存储引擎

   | 特点      | Myisam | BDB  | Memory | InnoDB | Archive |
   | ------- | ------ | ---- | ------ | ------ | ------- |
   | 存储限制    | 没有     | 没有   | 有      | 64TB   | 没有      |
   | 事务安全    |        | 支持   |        | 支持     |         |
   | 锁机制     | 表锁     | 页锁   | 表锁     | 行锁     | 行锁      |
   | B树索引    | 支持     | 支持   | 支持     | 支持     |         |
   | 哈希索引    |        |      | 支持     | 支持     |         |
   | 全文索引    | 支持     |      |        |        |         |
   | 集群索引    |        |      |        | 支持     |         |
   | 数据缓存    |        |      | 支持     | 支持     |         |
   | 索引缓存    | 支持     |      | 支持     | 支持     |         |
   | 数据可压缩   | 支持     |      |        |        | 支持      |
   | 空间使用    | 低      | 低    | N/A    | 高      | 非常低     |
   | 内存使用    | 低      | 低    | 中等     | 高      | 低       |
   | 批量插入的速度 | 高      | 高    | 高      | 低      | 非常高     |
   | 支持外键    |        |      |        | 支持     |         |

   最常使用的2种存储引擎：

   ​	存储位置在`/var/lib/mysql`下，需要root后才可以进入

   - Myisam是Mysql的默认存储引擎。当create创建新表时，未指定新表的存储引擎时，默认使用Myisam。每个MyISAM在磁盘上存储成三个文件。文件名都和表名相同，扩展名分别是**.frm（存储表定义）、.MYD (MYData，存储数据)、.MYI (MYIndex，存储索引)**。数据文件和索引文件可以放置在不同的目录，平均分布io，获得更快的速度。   
   - InnoDB存储引擎提供了具有提交、回滚和崩溃恢复能力的**事务安全**。但是对比Myisam的存储引擎，InnoDB写的**处理效率差一些并且会占用更多的磁盘空间以保留数据和索引**。

2. 选择的基本原则

   1. 根据存储引擎，确定数据类型

   2. 常用的分类

      - MyISAM 数据存储引擎和数据列：MyISAM数据表，**最好使用固定长度(CHAR)的数据列**代替可变长度(VARCHAR)的数据列。
      - MEMORY存储引擎和数据列：MEMORY数据表目前都使用**固定长度的数据行**存储，因此无论使用CHAR或VARCHAR列都没有关系。两者都是作为CHAR类型处理的。
      - InnoDB 存储引擎和数据列：**建议使用 VARCHAR类型**。

   3. `CHAR`  V.S. `VARCHAR`

      1. `CHAR`是固定长度的，无论存储多少数据，占用的存储空间是固定的，`VARCHAR`是不固定的，动态分配的
      2. `CHAR`尾部的空格保留，`VARCHAR`尾部的空格不保留

      ```mysql
      # 测试
      create table table_name(c char(5) , v varchar(5));
      insert into table_name values("ab " , "ab ");
      select CONCAT(c , "+") ,CONCAT(v , "+") from table_name;
      # 结果
      +-----------------+-----------------+
      | CONCAT(v , '+') | CONCAT(c , '+') |
      +-----------------+-----------------+
      | ab +            | ab+             |
      +-----------------+-----------------+
      ```

   4. `text` V.S .`blob`

      字符串存储和二进制存储类型

      1. 清理碎片

         ```mysql
         #如果您已经删除了表的一大部分，或者如果您已经对含有可变长度行的表（含有VARCHAR, BLOB或TEXT列的表）进行了很多更改，则应使用
         #OPTIMIZE TABLE。被删除的记录被保持在链接清单中，后续的INSERT操作会重新使用旧的记录位置。您可以使用OPTIMIZE TABLE来重新
         #利用未使用的空间，并整理数据文件的碎片。

         #在多数的设置中，您根本不需要运行OPTIMIZE TABLE。即使您对可变长度的行进行了大量的更新，您也不需要经常运行，每周一次或每月一次
         #即可，只对特定的表运行。

         #OPTIMIZE TABLE只对MyISAM, BDB和InnoDB表起作用。
         #注意，在OPTIMIZE TABLE运行过程中，MySQL会锁定表。
         optimize table table_name;    #　清理表空间
         ```

      2. 避免不必要的检索大型的`blob` , `text`，尽量使用索引

   5. 浮点数和定点数

      例子

      ```mysql
      create table test(c1 float(10,2) , c2 decimal(10,2));    # 创建10长度精度是2位的浮点数
      insert into test values(131072.321 , 131072.321);
      select * from test;
      #　结果
      +-----------+-----------+
      | c1        | c2        |
      +-----------+-----------+
      | 131072.31 | 131072.32 |
      +-----------+-----------+
      ```

      上述的问题来源是因为浮点数的存储不精确导致的

      * 浮点数存储数据范围更大，但是精度低
      * 对货币和时间等精度敏感的数据使用`decimal`存储
      * 尽量避免使用浮点数比较运算

   6. 字符集

      * 字符集的更改是高代价的处理，尽量在添加数据之前就确定好数据字符集
      * mysql的字符集包括字符集（CHARACTER）和校对规则（COLLATION）两个概念。字符集是用来定义mysql存储字符串的方式，校对规则则是定义了比较字符串的方式
      * 每个字符集至少对应一个校对规则

      ```mysql
      show character set;    # 查看当前的mysql支持的字符集，支持数据库，表和字段的设定字符集操作
      show collation like "utf8%";    # 查看utf8的校对规则
      ```

      * `UNICODE`

        为了实现对多个字符编码的容纳和控制，出现了`UNICODE`编码

      * 选择合适的字符集

        我们建议在能够完全满足应用的前提下，尽量使用小的字符集。因为更小的字符集意味着能够节省空间、减少网络传输字节数，同时由于存储空间的较小间接的提高了系统的性能

      * MySQL字符集

        mysql的字符集和校对规则有4个级别的默认设置：**服务器级、数据库级、表级和字段级**。分别在不同的地方设置，作用也不相同。

        服务器字符集和校对，在mysql服务启动的时候确定。可以在my.cnf[/etc/mysql]中设置：

        ​    [mysqld]

        ​    default-character-set=utf8

        或者在启动选项中指定：

        ```mysql
        mysql -u root -p --default-character-set=utf8
        ```

        或者在编译的时候指定：

        ​    ./configure --with-charset=utf8

        如果没有特别的指定服务器字符集，**默认使用latin1作为服务器字符集**。上面三种设置的方式都只指定了字符集，没有指定校对规则，这样是使用该字符集默认的校对规则，如果要使用该字符集的非默认校对规则，则需要在指定字符集的同时指定校对规则。

        ```mysql
        show variables like "character_set_server";     # 现实当前使用的字符集
        ```

#### 索引和锁

1. 索引概述

   1. MySQL中的所有的列类型都可以被索引，可以提高我们的SELECT的查询效率

2. 索引的设计原则

   1. 并不是要查询的列要被索引而是`WHERE`的过滤列才是主要的考虑点
   2. 唯一索引好处多 : 当我们的索引的独立性越强索引的效果越好(比如分男女的索引效果最差)
   3. 使用短索引 : 只要我们在移动成都上可以很独立的区分开我们的数据，尽量就使用短索引(前缀)
   4. **在创建一个n 列的索引时，实际是创建了MySQL可利用的n 个索引**。多列索引可起几个索引的作用，因为可利用索引中最左边的列集来匹配行。这样的列集称为最左前缀。（这与索引一个列的前缀不同，索引一个列的前缀是利用该的前n 个字符作为索引值。）
   5. 索引并不是越多越好，维护索引的时间和控件开销和存储索引的开销都很大

3. 索引

   当我们使用`SELECT`语句进行检索的时候，实际上我们的内部的`WHERE`中对运算符号都进行一定的索引匹配操作

   索引用于快速找出在某个列中有一特定值的行

   `PRIMARY KEY`和`UNIQUE`会建立索引

4. 事务

   1. START TRANSACTION或BEGIN语句可以开始一项新的事务。
   2. COMMIT和ROLLBACK用来提交或者回滚事务。
   3. CHAIN和RELEASE子句分别用来定义在事务提交或者回滚之后的操作，chain会立即启动一个新事物，并且和刚才的事务具有相同的隔离级别，release则会断开和客户端的连接。
   4. SET AUTOCOMMIT可以修改当前连接的提交方式，如果设置了SET AUTOCOMMIT=0，则设置之后的所有事务都需要通过明确的命令进行提交或者回滚。

#### MySQL安全

##### SQL注入

结构化查询语言(SQL)是一种用来和数据库交互的文本语言。SQL Injection 就是利用某些数据库的外部接口把用户数据插入到实际的数据库操作语言(SQL)当中，从而达到入侵数据库乃至操作系统的目的。它的产生主要是由于程序对用户输入的数据没有进行**严格的过滤**，**导致非法数据库查询语句的执行**。

目前的方法可以使用我们的正则表达式对用户的输入数据进行合理的过滤从而尽可能较少SQL注入的危险

##### MySQL SQL Mode

MySQL可以工作在不同的SQL模式下，明确了某种模式下的支持的语法和在数据集上支持什么样的检查的

```mysql
select @@sql_mode \G    # 输出当前环境下的我们的SQL模式
```

例如:

​	有时候我们创建的字符串的长度远远小于我们的插入数据的大小，有时候MySQL会自动截断，但是实际上我们应该弹出非法错误的提示，这就是因为没有打开对应的SQL模式导致的不精确检查

**常用的SQL Mode**

* `STRICT_TRANS_TABLES` : 严格模式，表更新不符合定义的时候会自动拒绝执行
* `ANSI` : 不严格模式，领输入的SQL语句更符合语法定义(自动的修补语法)
* `TRADITION` : 严格模式，传统的拒绝错误输入和更新，和`STRICT_TRANS_TABLES`基本一致

**两种模式的要点**

1. 如果数据库运行在严格模式下并且不支持回滚操作，有可能会出现数据库的数据不一致的情况(数据错误)

   因为有可能多条语句相关联，前一个执行成功，后一个执行失败但是不能回滚导致拒绝更新，从而前面成功执行的SQL语句破坏了数据库的一致性

2. 使用严格模式，对于不正确的更新操作，MySQL会给出错误提示

SQL Mode中MySQL和其他的数据库有关联的地方(可共用的效果)

**SQL Mode 数据校验**

* `datetime`等日期数据的合法性检查
* 除零错误
* 禁用`\`符号
* `||`视为`CONCAT`操作而不是逻辑`OR`

#### SQL语句和表优化

```mysql
# MySQL的系统基本查询语句
show variables like "%abc%"    # 检查系统的配置信息
show global status like "%abc%"    # 检查数据库的运行状态值
```

```mysql
# 根据我们查询的结果可以大致的看出来我们使用的数据库是什么类型的(Insert / Select)
show status \G    #显示我们的当前的MySQL数据库的基本查询状态
# 对MyISAM和InnoDB的操作计数
# Com_select    select操作的次数
# Com_insert
# Com_update
# Com_delete
# 对InnoDB的行数计数
# Innodb_rows_read    查询行数
# Innodb_rows_insert
# Innodb_rows_updated
# Innodb_rows_deleted
# 数据库的正确适用性检验(提交和回滚次数的查询检验)
# Com_commit
# Com_rollback
# 数据库情况
# Connections    数据库的连接情况
# Uptime    数据库服务器的工作时间
# Slow_queries    慢查询的次数(时间长度很长的查询操作)
#
#
# 上述的数据可以使用如下的方式精确快速的查询
show global status like "Com_rollback";
show variables like "max_connections"
```

慢查询的查询

* MySQL数据库可以调用慢查询日志查询所有查询时间查过`long_query_time`的查询操作

##### 索引优化

1. 索引类型
   * `btree`
   * `hash`

2. 索引限制
   * 不支持函数索引
   * 索引只对列前一部分执行(前缀索引对字符串类型更有效)
   * 多列索引必须要使用左边前缀才可以执行否则拒绝(在前一篇文章中记录了)
   * MySQL认为索引时间效率不如全表扫描拒绝索引
   * `like`是用`%`开始的模糊匹配
   * 字符串一定用引号，否则MySQL拒绝使用索引

3. 索引效率检查
   * 上面的方法
   * `Handler_read_key`很高索引有效，很低代表索引的效果不明显考虑更换索引
   * `Handler_read_rnd_next`的值如果很大代表正在进行大表扫描，查询运行低效应该使用索引补救

4. `Innodb`引擎的索引策略

   * 唯一性检验

     ```mysql
     select @@UNIQUE_CHECKS;     # 检查是否打开的插入等操作的唯一性检验
     #在大表数据大量打入的时候，我们可以先将唯一性检验关闭最后再打开
     set UNIQUE_CHECKS = 0;
     ```

   * 自动提交

     ```mysql
     set autocommit = 0;     # 关闭自动提交的方式可以提高导入效率   ???
     ```

##### `Insert`语句的优化

* `Insert`语句重合

  ```mysql
  insert into table_name values(...),(...),(...),...;    # 一次插入一批的数据，使用逗号分开记录，有时候闭分开多次插入要快几倍
  ```

* `Insert delayed`的操作

  ```mysql
  insert delayed into table_name values(...),(...),(...),...;    # delayed模式表示不在内存存储，直接写入数据库，执行速度快无需等待
  ```

* 更换成`LOAD DATA INFILE`

  ```mysql
  load data infile     # 在导入大量数据的时候该操作比我们的insert速度要快
  ```

* `Insert ignore into`

  ```mysql
  insert ignore into  ... ; # 对于草屋只以警告的形式(重复记录)返回并不是返回错误，节省效率
  ```

##### `Group by`语句的优化

对于`Order by`语句，如果指定的列是相同的，`Group by `将会对执行进行优化，结果依然是排序的

换句话说，如果使用`group by`和`order by`针对相同的列进行操作，显然使用`group by`将会更好

##### `Order by`语句优化

1. 禁止排序

   ```mysql
   select * from table_name order by NULL;     # 禁止排序会加快速度
   ```

2. 要点

   **`WHERE`语句和`order by`使用相同的索引来加快速度**，但是会有差别

   * 混合排序方式不使用索引

     ```mysql
     SELECT * FROM t1 ORDER BY key_part1 DESC, key_part2 ASC；
     ```

   * `WHERE`子句中的过滤列和`ORDER BY`中的不同

     ```mysql
     SELECT * FROM t1 WHERE key2=constant ORDER BY key1；
     # 实际上只要order by中的其中一个和where中的一个一直就可以使用索引
      SELECT * FROM t1 WHERE key_part1=1 ORDER BY key_part1 DESC, key_part2 DESC;    # 使用索引	
     ```

##### `Join`语句的优化

1. Mysql4.1开始支持SQL的子查询。这个技术可以使用SELECT语句来创建一个单列的查询结果，然后把这个结果作为过滤条件用在另一个查询中。使用子查询可以一次性的完成很多逻辑上需要多个步骤才能完成的SQL操作，**同时也可以避免事务或者表锁死**，并且写起来也很容易。但是，有些情况下，**子查询可以被更有效率的连接JOIN替代**。
2. 连接JOIN之所以更有效率一些，是因为 MySQL不需要在内存中创建临时表来完成这个逻辑上的需要两个步骤的查询工作。

##### 语句优先级优化

1. MyISAM : MySQL对具体的数据操作例如`SELECT` , `INSERT`等都采取了具体的调度策略，但是该调度策略可以进行时候修改
2. InnoDB : 数据的优先级操作根据表的锁的情况决定

**对MyISAM存储引擎的表结构来说**

* 写操作优先与读操作
* 排它锁
* 共享锁

**事后修改调度策略**

* `LOW_PRIORITY` : 应用更新和插入，插入等**修改操作**，将器执行的优先级降低到`SELECT`语句优先级之下，有可能会导致更新操作被读操作阻塞很长时间
* `HIGH_PRIORITY` : 应用给`SELECT` , `INSERT`操作中，提高优先级，对于`SELECT`操作来说，可以将查询的优先级提升从而阻塞写操作

##### 数据表优化

1. 数据库规范化的权衡

2. 锁冲突频繁重点的表采用`InnoDB`的存储引擎 , 查询操作频繁可以考虑采用`MyISAM`数据存储引擎

3. 列类型的优化建议

   ```mysql
   SELECT ... FROM ... WHERE ... PROCEDURE ANALYSE([max_elements,[max_memory]]) \G
   # max_memory   默认分配的最大的内存数量
   # max_elements   查找不同值是的最大关注数量，如果不同的值超过了max_elements之后就不讲ENUM作为优化的数据类型，ENUM经常会作为优化的类型
   ```

##### 锁优化

[1]锁等级的确定

1. 表级锁的优势
   * 大多数操作都是读表操作
   * 索引读取优化
   * `Group by`操作频繁
2. 行级锁的优势
   * 回滚少量记录
   * 长时间锁定单一行
   * 长时间访问很多的行的时候行级表冲突数目不高
3. 行级锁的劣势
   * 占用更多的内存
   * 当在表中大范围使用的话，锁定速度变慢
   * `Group by`操作频繁

[2]`Insert into select`语句的适用性

```mysql
insert into table_name(col1 , col2 , col3 , ...) select * ...;     # 使用查询的结果插入到对应的表中，在此种情况下会对目标插入表进行锁定
```

##### 语句优化

* 减少重复访问

* `SQL QUERY CACHE`

  ```mysql
  show variables like "%query_cache%" ;
  # 结果
  +------------------------------+----------+
  | Variable_name                | Value    |
  +------------------------------+----------+
  | have_query_cache             | YES      |       # 服务器是否配置了高速缓存
  | query_cache_limit            | 1048576  |       # 
  | query_cache_min_res_unit     | 4096     |
  | query_cache_size             | 16777216 |       # 缓存区大小
  | query_cache_type             | OFF      |　　　　# 0 - 缓存关闭，1/2 - 缓存打开
  | query_cache_wlock_invalidate | OFF      |
  +------------------------------+----------+
  ```

#### 日志管理

* 错误日志[--log-error]

  ```mysql
  show variables like "%log_error%" ;     # 存储mysql的错误日志的具体存放位置
  /etc/init.d/mysql start --log_error=path;    # 再启动的时候决定日志的启动的位置(本次),(永久)修改my.cnf中的log_error参数的配置
  ```

* `BINLOG`[--log-bin]

  二进制日志保存了**所有更新了数据或者潜在更新了数据的操作**(不含查询数据的语句),用事件存储

  ```mysql
  mysql>reset master;    # 删除二进制日志
  mysql>select @@SQL_LOG_BIN;    # 1表示自动写入二进制日志，0表示不写入二进制日志
  mysql>show variables like "%log_bin%";
  ```

* 查询日志[--log]

  记录客户端的所有语句

  ```mysql
  show variables like "%general_log%";  
  #结果
  +------------------+---------------------------+
  | Variable_name    | Value                     |
  +------------------+---------------------------+
  | general_log      | OFF                       |
  | general_log_file | /var/lib/mysql/GMFTBY.log |
  +------------------+---------------------------+
  #
  set global general_log = 1;    #打开
  select @@general_log;    #显示是否打开日志
  ```

* 慢查询日志

  1. 记录包含所有执行时间超过long_query_time秒的SQL语句的日志文件。获得初使表锁定的时间不算作执行时间。

  2. ```mysql
     show variables like "%slow%";    # 显示保存路径　　　show variables 是查询变量(路径),status查询功能状态(是否开启)
     ```