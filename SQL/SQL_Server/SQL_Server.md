## 1 SQL Server

### SQL Server引擎实例

1. 数据库引擎实例管理多个系统数据库和用户数据库
2. 每台计算机可以运行多个数据库引擎实例，一台计算机上只可以安装一个数据库默认实例
3. 应用程序只有通过数据库实例才可以访问具体的数据库
4. 一个数据库实例就是一个进程
5. 实例处理所有的数据库请求的服务操作，应用程序讲对应的SQL语句传递给我们的数据库实例，实例讲对应的SQL语句拆分成对应的操作并将结果返还给应用程序
6. SQL Server服务是对应的数据库实例的windows进程，必须要保证该服务是处于运行状态(SQL Server的配置管理器中)

### SQL Server Management Studio工具

连接SQL Server服务器的的工具

1. 对象资源管理器的按钮的作用 : 连接(新用户链接别的数据库)，断开连接，停止，刷新，筛选

2. 查询编辑器

   点击新建查询打开了我们的新的查询窗口可以执行SQL语句，并且还可以讲结果保存到对应的文件或者其他的数据保存实例中

3. 数据库

   在对象资源管理器中我们打开对应的数据库的内容可以显示当前连接上的所有的数据库

4. 安全性

   在对应的对象资源管理器中打开对应的安全性的选项可以打开我们的安全查询选项，在其中的登录名中可以查看到我们的当前的登录账户

### 身份验证模式的设定

无论是哪一种身份验证模式都需要我们连接到对应的数据库服务器

* Windows身份验证模式

  假定登录的Windows账户是安全的，登录数据库的时候不需要额外提供账户名和密码，**是相对第二种来说的更安全的登录方式**,**更常用**

* SQL Server和Windows混合验证模式

  提供具体的SQL Server登录的账户和密码,比如说是使用网络链接的用户，或者特殊的应用程序，只能使用SQL Server的方式登录

修改身份验证的的登录模式

* 右键SSMS对象资源管理器的PC服务器后选择属性打开服务器属性窗口
* 选中安全性切换之后确定

### 登录管理

1. Windows新账户登录SQL Server
   * 控制面板创建新的额windows账户
   * 使用新的windows账户的登录系统
   * 登录之后使用windows验证登录进入
2. SQL Server账户登录
   * 对象资源管理的安全性右键打开新建登录
   * 可以再脚本选项中讲我们本次操作的对应的SQL语句保存到文件中一遍下次使用

### 修改sa的登录和口令状态

sa登录是特殊登录，是最高权限登录，需要对密码进行重点的保护	

在对象资源管理中的安全性中打开sa进行管理在状态中打开登录启用并可以修改密码

* 记住必须要使用SQL Server和Windows混合登录模式


* 勾去强制密码策略
* 状态中勾选启用sa登录的选择
* 修改自己的密码


* 在对象资源管理中断开连接并重新登录，记住重启

## 2 安全管理

### 服务器角色授予登录权限

1. 系统定义了9个对数据库的服务器操作权限，但是仅限于添加和删除成员，不可创建服务器角色和删除服务器角色，也不可修改服务器角色权限，是固定的服务器角色
2. 可以创建服务器角色并进行权限设定
3. 将某一个登录添加到一个服务器角色中，该账户登录就继承了而对应的服务器角色的操作权限
4. 如果不需要对服务器进行管理，一般使用数据库角色进行权限的配置

### 权限不足的操作

如果我们的用户没有相应的操作的权限，在执行数据库的操作的时候会显示我们的操作失败，错误的描述是缺少相应的权限

* 利用sa创建我们的SQL Server账户student
* 利用student登录我们的SQL Server
* 利用student账户创建性的登录账户会发现创建失败，缺失权限

### 修改登录服务器的角色集

每一个登录SQL Server的账户都存在一个角色集合，我们在这个集合中可以添加对应的SQL Server的角色权限，对应的额账户就会集成对应的角色的权限，因此修改一个账户的全下你可以使用我们的修改登录服务器的角色集的方式实现

方式

* 对象资源管理器中，在对应的的登录中我们选择安全性的节点在最终的服务器角色选项中我们可以设定对应的服务器角色

* SQL 语句实现

  ```mssql
  --以下语句的执行需要更高的数据库的权限
  --以下的语句逻辑都是从我们的角色出发的，从我们的角色中删除对应的所加入的成员
  --对应的sysadmin角色的全显示最高级权限，可以实现所有的对数据库的操作
  ALTER server role [sysadmin] add memeber [student]	
  GO
  --移除操作
  alter server role [sysadmin] drop member [student]
  GO
  ```

### 使用数据库角色授权

* 针我们对用户的权限的分批额在数据库上并不是直接将我们的权限分配给某一次登录
* 我们讲某一次登录映射到对应的用户上
* 将用户加入到对应的数据库角色列表中
* 这样，登录就和具体的用户绑定，具体的用户和具体的数据库角色绑定，从而让我们的登录继承我们的数据库权限

操作:

在执行该操作之前记得讲我们的执行SQL语句的对应的用户的权限加上

1. 利用sa或者windows账户创建新的登录

   ```mssql
   create login student with password='',default_database=master
   ```

2. 建立登录和用户的映射

   **没有建立映射到用户的登录是不会登录成功的**

   ```mssql
   use AdventureWorks;
   GO
   --用户stu是现添加的
   CREATE USER stu for login student;
   GO
   ```

3. 用户添加到数据库角色中

   ```mssql
   use AdventureWorks;
   GO
   ALTER ROLE [db_owner] add member stu
   GO	
   ```

之后我们的student登录就会成为我们的数据库的拥有者可以执行数据库的相应的操作

### 指定特定对象的权限

必要的概念的理解

* 数据库的对象 : 数据库中的表，视图，索引等等都是我们的数据库对象
* 数据库服务器角色 : 我们在数据库服务器等级的角色分配是针对**所有的数据库**的**所有的对象的**
* 使用数据库角色 : 使用数据库角色实际上是对我们的**特定的数据库的所有的对象的权限的**分配

下面我们来讨论如何对特定的数据库的特定的对象进行授权

* 利用sa创建针对数据库AdventureWorks的登录

  ```mssql
  create login app with password='xxxxxxx' ,default_database=AdventureWorks
  ```

* 建立登录到用户的映射

  ```mssql
  use AdventureWorks 
  go
  create user stu_user for login app
  go
  ```

* 还是使用sa进行操作，打开AdventureWorks数据库在安全性中选择用户，点击我们刚才创建的stu_user用户

  在安全对象选项中使用搜索，点击**特定对象**,添加我们感兴趣的特定数据库对象，然后在我们的下面勾选针对该特定对象的**使用权限**

  还可以继续点击我们的对应的权限针对不同的列设置我们的权限

  也可以使用SQL语句实现

  ```mssql
  use AdventureWorks
  go
  grant select on Person.Address to app
  grant update on Person.Address(col1,col2,col3) to app as dbo
  go
  ```


## 3 表

### 表的概念

1. 表示数据库中包含所有数据的数据库对象，表示列集合

### 数据完整性

1. 列数据类型的确认明确了列的数据类型和列的域

2. 域 : 数据类型 + 数据值的范围

3. NULL / NOT NULL，关于NULL的任何比较结果都不会存在TRUE / FALSE

4. 数据库完整性

   * 保证数据库中的值一定是正确的
   * 参照完整性

5. 约束

   列约束 : 只针对一个列的约束条件

   表约束 : 应用整个表上

   * NOT NULL : 不接受NULL值

   * CHECK : 强制执行我们的表中的完整性，计算结果是FALSE拒绝

   * UNIQUE : 列上数据唯一

   * PRIMARY KEY : 小整数作为主键，**一列或者一组**

     1. 表的实体完整性
     2. 不接受NULL
     3. 主键会建立唯一索引，会加快查询
     4. 没有具体指定，可以再表中加入表级PRIMARY KEY约束
     5. 多列PRIMARY KEY一旦确定，不允许改变列的数目的前提下可以更改我们的主键

   * FOREIGN KEY : 表级的依赖关系

     该表的外键指向另一个表的的主键，构建两个表之间的联系

     ON DELETE 选项

     * CASCADE : 及联删除
     * SET DEFAULT : 当主键删除的时候，对应的该表中的对应的外键全部设置成默认值
     * SET NULL : ~~~~NULL
     * ON ACTION : 执行错误

     ON UPDATE选项 : 同上

### 创建表 / 修改表

1. 创建

   ```mssql
   create table student (
     StudentID int primary key,
     Name varchar(10) not null,
     Sex char(1) check(Sex in ('F','f','M','m')),
     Age int,
     Class char(8)
   )
   ```

   * **列没有顺序**
   * 每个表的猎德最大长度是1024

2. 查询

   `INDENTITY` : 类似于MySQL的auto_increment

   * 一个表只能存在一个IDENTITY,并且必须是数值类型的
   * 可以制定初始值和增量，默认是都是1
   * 标识符列不允许NULL , DEFAULT

   一个会话中一次只可以指定一个表打开我们的 IDENTITY_INSERT选项

   ```mssql
   use database_name;
   --开启我们的插入修补选项，开启之后我们徐娅手工计算要填补的漏洞并且insert语句中必须要指定列名
   set identity_insert on    
   insert into table_name(indentity_col , col2) values(... , ...);
   ```

   ```mssql
   --关闭我们的插入修补选项
   set identity_insert off
   ```

## 4 Transact-SQL编程

### 异常处理

**`PRINT`可以作为异常处理的机制之一**

启动错误会话处理机制

```mssql
RAISERROR ( { msg_id | msg_str | @local_variable }
{ ,severity ,state }
[ ,argument [ ,...n ] ] )
[ WITH option [ ,...n ] ]
```

* msg_id > 50000 , 未指定id自动引发50000的错误消息
* msg_str : 用户自定义的错误消息,2047字符个数是上限 ， 引发的错误号是5000
* @local_variable : 数据库变量，必须是char / varchar

```mssql
raiserror(N'this is a message %s %d',
         10,    --错误等级
          1，   --错误状态
          N'number'   --第一个参数
          5     --第二个参数
         )
```

当错误的严重程度>=11变回进入CATCH块进行处理，大于20终止数据库连接

```mssql
BEGIN TRY
-- 错误级别小于10时执行下面的语句且打印系统错误信息；
-- 错误级别等于10，则仅执行下面的语句；
-- 错误级别大于10则会导致执行跳转到CATCH 块.
    RAISERROR ('Error raised in TRY block.', -- 信息.
               16, -- 错误级别.
               1 -- 状态.
               );
END TRY
BEGIN CATCH
    DECLARE @ErrorMessage NVARCHAR(4000);
    DECLARE @ErrorSeverity INT;
    DECLARE @ErrorState INT;

    SELECT 
        @ErrorMessage = ERROR_MESSAGE(),
        @ErrorSeverity = ERROR_SEVERITY(),
        @ErrorState = ERROR_STATE();

    -- 在CATCH块内使用RAISERROR返回关于导致执行
	-- 跳转到CATCH块的原始错误的错误信息
    RAISERROR (@ErrorMessage, -- 信息.
               @ErrorSeverity, -- 错误级别.
               @ErrorState -- 状态.
               );
END CATCH;

--输出消息 50000，级别 16，状态 1，第 22 行
--Error raised in TRY block.
```

### 游标

```mssql
USE AdventureWorks
GO
-- （1）声明游标contact_cursor
DECLARE contact_cursor CURSOR FOR
SELECT LastName FROM Person.Contact
WHERE LastName LIKE 'B%'
ORDER BY LastName

-- （2）打开游标
OPEN contact_cursor

-- （3）执行第一次提取.
FETCH NEXT FROM contact_cursor

-- （4）检查@@FETCH_STATUS 以查看是否还有更多的行可以提取.
-- 如果有则提取下一行
WHILE @@FETCH_STATUS = 0
BEGIN
   -- This is executed as long as the previous fetch succeeds.
   FETCH NEXT FROM contact_cursor
END

-- （5）关闭并删除游标
CLOSE contact_cursor
DEALLOCATE contact_cursor
GO
```

* 声明 -> 打开 -> 提取 -> 关闭 -> 删除
* 游标对应的查询语句不能存在变量，SELECT支持变量查询
* 游标打开开始执行SELECT操作
* @@FETCH_STATUS : 检测提取的结果是否成功
* 关闭并不释放游标的资源，删除才是

**游标选项**

游标选项在创建的时候添加

* GLOBAL

  作用域是全局的，隐形自动释放

  是跟随**连接**的

* LOCAL

  作用域是本次的存储过程，函数内的

  是跟随代码块的

* UPDATE : 可修改的游标

* SCROLL : 双向的随意移动的游标

  ```mssql
  fetch prior from cursor_name;
  fetch next from cursor_name;
  fetch absolute 2 from cursor_name;
  fetch relative -2 from cursor_name;
  ```

**游标信息查询**

```mssql
@@cursor_rows    --游标的行数
@@fetch_status   --游标当前是否还可以提取的状态
    0 - 正常
    -1 - 错误
    -2 - 行不存在
```

**数据提取**

* 系统变量必须使用@开头

* ```mssql
  print '111' + '222' + '333'    --字符串打印标准输出
  ```

* ```mssql
  fecth next from name into @var1,@var2;
  ```

### 触发器

1. 特殊的存储过程

2. 优点

   * 可以更好的实现对应的参照完整性，保证数据库的一致性
   * 防止恶意的更新操作(BEFORE)
   * 评估我们的修改前后的表的状态
   * 触发器可以多个，针对同一个语句可以实现多种的响应动作
   * 自动执行，对目标表的操作执行了修改会立即执行对于国内的预制的措施，**触发器是可以连锁的**

3. 类型

   * AFTER : 事后触发器
     * 晚于约束执行
     * 表
     * 一个表可以多个
     * 只能对基表使用
   * INSTEAD OF : 代替触发动作
     * 先于约束执行
     * 表和视图
     * 一个表只有一个
     * 还可以针对视图创建，视图的唯一的触发器

4. AFTER触发器创建

   ```mssql
   --AFTER TRIGGER
   --需要注意一点，我们的触发器必须是第一个执行的查询语句，use test之后必须使用go否则下面的语句现实的不是第一条SQL语句
   /*
   下面的测试用例中
   a
     PK name char(20)
        id int foreign key references b(id)
   b
     PK id int
        vender int;
   */
   /*
   use test;
   go
   create trigger defend_insert on dbo.a
   after insert
   as
   begin
   declare @test int
   select @test=j.vender from inserted i,dbo.b j where i.id = j.id
   if @test < 5
   begin 
   raiserror('low vender' , 16 , 1)
   rollback transaction
   end
   go*/    --go必不可少，无法判断是否结束
   use test;
   go
   --insert into b values(1,3),(2,6),(3,7),(4,4),(5,1),(6,2);
   --select * from b;

   --insert into a values('lantian' , 2);
   select * from a;
   ```

5. 禁止和允许触发器

   ```mssql
   alter table table_name disable trigger trigger_name;
   alter table table_name enable trigger trigger_name;
   ```

6. 特殊表(deleted / inserted)

   * SQL Server自动创建和管理这两个表
   * 不可以直接对这两种表执行DML操作
   * 作用主要在于找出表的更改前后的状态差异并采取相应的措施
   * deleted / inserted 表用来存储被影响的行的副本
     * deleted : DELETE / UPDATE
     * inserted : INSERT / UPDATE
   * UPDATE :
     1. 旧记录 存放在deleted表
     2. 新记录 存放在inserted表

7. INSTEAD OF 触发器的创建

   ```mssql
   --create database record
   /*
   use record;
   go

   create table person(
   ssn char(20) primary key,
   name char(20),
   address char(20),
   birthdate datetime
   )

   create table employee(
   employeeid int primary key,
   ssn char(20),
   department char(20),
   salary int
   )

   create table preson_duplicate(
   ssn char(20),
   name char(20),
   address char(20),
   birthdate datetime,
   inserttime datetime
   )

   create view person_show as
   select person.ssn as ssn , name , address , birthdate , employeeid , department , salary
   from person , employee
   where person.ssn = employee.ssn
   go

   use record;
   go
   create trigger defend on person_show
   instead of insert
   as
   begin
   if(not exists(select * from inserted , person where inserted.ssn = person.ssn))
       insert into person 
   	    select ssn, name, address , birthdate from inserted;
   else
       insert into preson_duplicate
   	    select ssn , name , address , birthdate , getdate() from inserted;

   if(not exists(select * from inserted , employee where inserted.ssn = employee.ssn))
       insert into employee
   	    select employeeid , ssn , department , salary from inserted;
   else
       update employee
   	    set employeeid = i.employeeid,
   			department = i.department,
   			salary = i.salary
   	from employee , inserted as i
   	where employee.ssn = i.ssn
   end
   go

   */
   use record;
   go
   insert into person_show values('i am ssn' , 'lantian' , 'bit' , getdate() , 1 , 'xinyi' , 400);

   drop trigger defend;
   select * from person_show;
   select * from employee;
   select * from person;
   select * from preson_duplicate;
   ```

8. 触发器相关的系统参数

   * not for replication : 复制代理拒绝执行触发器
   * `@@rowcount` : 返回上一句语句的影响行数
   * `@@trancount` : 返回当前连接上的transcation语句的数目
   * `set nocount on`  : 组织返回受影响的行数信息，只返回语句是否执行成功，可以提高效率

9. 触发器回滚操作

   1. 当前事务中该时间点之前所做的所有数据修改都将回滚，包括触发器所做的修改。
   2. 触发器继续执行 ROLLBACK 语句之后的所有语句。如果这些语句中的任意语句修改数据，则不回滚这些修改。

### 存储过程

1. Transact-SQL语句的预编译集合，这些语句整体作为一个单元来进行处理

2. SQL Server 提供的存储过程称为系统存储过程。

3. 基本元素

   * 可以**接收参数**或者**返回参数**
   * 包含基本的数据库语句
   * 返回状态值，表明是否是成功或者是失败

4. 优点

   * 程序模块化
   * 执行速度块(预编译)
   * 减少网络流量(只用传递参数，不需要传递SQL语句)
   * 增加安全性(防止SQL 注入，用户执行的SQL 语句是预先生成和编译过的)

5. 创建存储过程

   1. **创建的注意要点**:

      * 创建存储过程的权限默认属于我们的数据库的所有者
      * 存储过程是一种数据库对象，只可以在当前的数据库中创建存储过程

   2. 系统存储过程

      * 系统存储过程都在master数据库中，有 **`sp_`** 前缀,可以从任何数据库中执行

      * 查找顺序

        1. master数据库
        2. 指定的限定符号的路径
        3. dbo作为所有者查询

        因此，虽然当前数据库中可能存在带 sp_ 前缀的用户创建的存储过程，但总会先检查 master 数据库（即使该存储过程已用数据库名称限定）。

      * 重要 : 如果用户创建的存储过程与系统存储过程同名，则永远不执行用户创建的存储过程。

   3. 创建语法

      ```mssql
      CREATE PROC [ EDURE ] procedure_name [ ; number ]
          [ { @parameter data_type }
              [ VARYING ] [ = default ] [ OUTPUT ]
          ] [ ,...n ] 

      [ WITH
          { RECOMPILE | ENCRYPTION | RECOMPILE , ENCRYPTION } ] --参数

      [ FOR REPLICATION ] 
      AS 
          sql_statement [ ...n ] 
      GO
      ```

   4. 使用存储过程

      ```mssql
      exec procedure_name @var1 = 'default1',@var2 = 'default2'
      ```

   5. 修改和删除存储过程

      ```mssql
      --修改存储过程

      --修改名称
      sp_rename newname , oldname
      --修改语句体
      alter procedure procedure_name
      as
          ....
      GO
      --删除存储过程
      drop procedure procedure_name;	
      ```

   6. 从存储过程中返回数据

      * 输出参数 : 在语句体中可以执行我们的  `RETURN`  语句中断我们的语句的执行
      * 引用全局游标

   7. 系统查询存储过程的信息

      * `sp_help` : 显示存储过程的所有者和创建日期
      * `sp_helptext` : 显示存储过程的源代码
      * `sp_depends` : 现实存储过程的引用对象

### 函数

```mssql
CREATE FUNCTION CubicVolume
-- Input dimensions in centimeters
   (@CubeLength decimal(4,1), @CubeWidth decimal(4,1),
    @CubeHeight decimal(4,1) )
RETURNS decimal(12,3) -- Cubic Centimeters.
AS
BEGIN
   RETURN ( @CubeLength * @CubeWidth * @CubeHeight )
END
```

## 5 数据库备份和恢复

1. 数据的备份（“数据备份”）的范围可以是完整的数据库、部分数据库或者一组文件或文件组。对于这些范围，SQL Server 均支持完整和差异备份

2. 备份类型

   * 完整备份

     包含要备份的特定的数据库的所有的数据以及可以回复这个数据库的足够多的日志

   * 差异备份

     * 完整备份成为差异备份的基准
     * 差异备份基于数据库
     * 建立备份的速度快
     * 还原的时候首先还原我们的完整备份然后在回复对应的差异备份
     * 差异备份需要定时的转化成完整备份，因为差异备份的数据量太大

   * 日志备份

     每个日志备份都包括创建备份时处于活动状态的部分事务日志，以及先前日志备份中未备份的所有日志记录。

3. 回复模式

   * 简单恢复模式

     * 不进行事务备份，备份易于管理，但是回复的时候只会恢复到最新的一次的备份的结尾，数据库最新进行的修改操作都会被丢失
     * 简单模式下，工作损失的风险会随着时间的推移而增加，直到进行下一次的完整备份和差异备份为止

   * 完整恢复模式

     完整恢复模式使用**日志备份**策略

     * **使用日志**在最大范围内保障我们的数据安全，需要使用**备份事务日志**的方法

     * 优点是可以将数据库的状态回复到任意保存了日志的记录点，缺点就是会增加数据库备份和回复的复杂性

     * 大多数的应用环境都会使用

     * **尾日志备份** 如果尾日志(尚未备份的日志)备份成功，可以避免所有的数据的丢失

     * 策略

       有时候为了尽可能的缩短我们的还原的时间，可以对相同数据进行一系列的差异备份甚至是完整备份来加快我们的回复进程

       **完整数据库备份 -> 事务日志 -> 差异数据库备份 -> 事务日志 -> 完整数据库备份**

4. 日志备份

   1. 在完整恢复模式和大容量日志恢复模式下,使用日志备份是非常的有必要的
   2. 日志备份可以将数据库的回复到故障点和特定的时间点
   3. 建议经常执行日志备份(在业务的允许范围之内)
   4. 在创建日志备份之前请先确定我们的完整的数据库的备份作为基准
   5. 日志链 : 连续的日志备份序列，日志链从数据库的完整备份开始

5. 简单回复模式下的备份和回复操作

   * 数据库的还原
     1. 还原的操作只是将数据从备份集中拷贝到数据库的文件中，它不会进行末提交事务的撤消，也不会重做记录的日志文件中已经提交的事务
     2. 在还原状态下的数据库可以继续还原后续的差异备份
     3. 可以将还原状态理解成是加载我们的还原的进度，回复操作在进度加载完确定完之后执行

   * 数据库的回复

     ```mssql
     /*
     1.每次备份会产生一个备份集文件，而一个备份集文件可以保存多个备份集。
     2.我们通过制定选用的备份集文件编号从而使用不同的备份文件
     3.备份集在备份集文件中有一个唯一的编号，如果不加指定，文件中的第一个备份集的编号是1，第2个备份集的编号是2，以此类推。备份集的编号在管理备份时和恢复数据库时使用。第1步中的备份集在该文件中的编号为1。
     */
     USE master;
     --1. 设置数据库为简单恢复模式
     ALTER DATABASE AdventureWorks SET RECOVERY SIMPLE;
     GO
     -- 2.执行数据库的完整备份
     -- 首先建立我们的完整备份，之后是我们的各各差异备份
     BACKUP DATABASE AdventureWorks 
         TO DISK = 'C:\SQLServerBackups\AdventureWorks.bak' 
         WITH FORMAT;
     GO
     /*
     这里忽略其中的一大批的数据库的语句
     */
     --3. 执行数据库的差异备份，使用和上面一样的文件，自动计算文件的编号是2，如果是新文件自动计算为1
     BACKUP DATABASE AdventureWorks
         TO DISK = 'C:\SQLServerBackups\AdventureWorks.bak'
         WITH DIFFERENTIAL;
     GO
     /*
     可以考虑删除数据库，然后使用下面的语句对数据进行还原操作
     */
     --4. 还原数据库完整备份 (自备份集 1)，但不恢复数据库.
     RESTORE DATABASE AdventureWorks 
         FROM DISK = 'C:\SQLServerBackups\AdventureWorks.bak' 
         WITH FILE=1, NORECOVERY;
     --5. 还原数据库差异备份 (自备份集 2)，恢复数据库.
     RESTORE DATABASE AdventureWorks
         FROM DISK = 'C:\SQLServerBackups\AdventureWorks.bak' 
         WITH FILE=2, RECOVERY;
     GO
     ```

6. 完整恢复模式下的备份和恢复文件

   1. 也就是说，完整恢复模式下的备份由数据库备份和日志备份组成。

   2. ```mssql
      USE master;
      --1. 将数据库修改为完整恢复模式.默认是简单的恢复模式
      ALTER DATABASE AdventureWorks SET RECOVERY FULL;
      GO
      --2. 执行数据库的完整备份.FORMAT表示如果备份文件中存在文件则清空病创建新的内容，否则创建一个新的备份文件
      BACKUP DATABASE AdventureWorks 
          TO DISK = 'C:\SQLServerBackups\AdventureWorks.bak' 
          WITH FORMAT;
      GO
      --3. 创建日志文件备份.编号是2的备份文件
      BACKUP LOG AdventureWorks
          TO DISK = 'C:\SQLServerBackups\AdventureWorks.bak';
      GO

      --4.创建尾日志备份.使用了NORECOVERY选项表示创建的是尾日志备份文件，尾日志备份完成之后不可以在进行数据库的任何日志备份，整个数据库进入还原状态
      BACKUP LOG AdventureWorks 
           TO DISK = 'C:\SQLServerBackups\AdventureWorks.bak'
           WITH NORECOVERY; 
      GO

      --开始还原数据库
      --5.还原数据库的完整备份
      restore database AdventureWorks
      from disk = 'C:\SQLServerBackups\AdventureWorks.bak'
      with file = 1,
      norecovery
      --6.还原常规日志备份
      restore log AdventureWorks
      from disk = 'C:\SQLServerBackups\AdventureWorks.bak'
      with file = 2,
      norecovery
      --7.还原尾日志备份文件
      restore log AdventureWorks
      from disk = 'C:\SQLServerBackups\AdventureWorks.bak'
      with file = 3,
      norecovery
      go
      --8.开始恢复数据库,前面的操作文成之后数据库进入还原状态，下面的语句执行完之后数据库完成恢复
      restore database AdventureWorks with recovery
      go
      ```

   3. 时间点恢复

      1. 如果发生了部分的日志文件的破坏或者说为了专门恢复到一个过去对应的时间点需要我们使用时间点回复策略

      2. 时间点恢复是部分恢复的一种，其它的方法还可以基于日志序列号、事务序列号等。

      3. 使用

         ```mssql
         restore log database_name 
         from disk = 'path'
         with file = 3,recovery,stopat='2007-10-7 17:35:18';
         ```

## 6 数据库设计

### 概述

1. 数据库设计要素
   * 应用环境:首选重视，业务需求，应用程序设计和数据库设计不应该分开来看待
   * 数据库模式(数学模型)
   * 满足的功能
2. 数据库设计的关键要素 : 数据的完整性

### 数据库设计方法

1. 数据库设计存在很多的设计方法

   这些方法的核心阶段是数据建模，而数据建模又包括**逻辑建模**和**物理建模**阶段。

2. 逻辑建模是数据库设计的最重要的阶段

   逻辑模型的设计，只考虑业务需求不考虑特定的数据库环境

3. 物理建模阶段

   将具体的逻辑模型映射到对应的特定的DBMS数据库系统上，在逻辑建模的基础上实现


### 数据模型和数据建模

* 模型是现实世界中对某个事务或者对象的模拟或者抽象
* 模型的特性
  * 真实的反应现实世界
  * 简单容易理解
  * 便于实现
* 阶段
  * 逻辑模型
  * 物理模型
    * 层次模型
    * 网状模型
    * 关系数据库模型

### 建模方法论

1. 实体 : 实体（entity）是现实世界中具有一组相同属性的“事务”或“对象”的集合，集合中的每个元素称为实体的实例（entity instance）

   * 独立实体 四边形
   * 从属实体 圆角四边形

   实体规则

   * 每一个实体必须使用唯一的实体名，相同的含义必须总是用于同一实体名。
   * 一个实体可以有一个或多个属性，这些属性可以是实体自身所具有的，也可以是通过一个联系而继承得到的。
   * 一个实体应有一个或多个能唯一标识实体中每一个实例的属性（主关键字和次关键字）。
   * 任意实体都可以与模型中其它的实体有0个、1个或多个联系。
   * **如果一个外键是一个主键的全部或部分，那么该实体就是从属实体。相反地，如果根本没有外键属性用作一个实体的主键，那么这个实体就是独立实体。**

2. 属性 : 

   * 一个“属性”表示一类现实或抽象的事务的一种特征或性质（如：人、物、地点、事件、概念等）。

   * 实体的每一个相关属性都必须具有一个单一且确定的值

   * 每个属性都必须有一个唯一的名称来标记，这个名称用一个名词或名词短语来表示，它描述了属性所表述的实体特征

   * 在实体的四边形内，属性被列出且每一行只有一个属性，主键属性被放在列表的最上面，且用水平线将它与其它属性分开

3. 主键

   * 一个实体必须具有一个属性或属性组，其值唯一地确定该实体中的每一个实例，这些属性或属性组称为侯选键或侯选码
   * 实体中的任意两个不同的实例都不允许同时在键属性上具有相同的值。

4. 联系

   * 一个确定性联系（specific connection relationship）或简称联系（relationship）是指实体间的相互关联
   * 有三个属性：名称、基数（cardinality，有时也称为度量）和联系的类型（标识或者非标识、非空）。除此以外，联系还是双向的，命名、设置基数和类型都需要在两个方向上进行。

5. 分类

   * 标识联系

     1. **父实体的主码**在子实体中既是外码又是主码的一部分或者全部
     2. 子实体必须依赖于父实体才可以存在

   * 非标识联系

     父实体中的主码在子实体中仅仅作为外码

   * 分类联系

     当多个实体有共同的属性时，而这些实体又分别有一些不同的属性时，可以创建一个一般实体并将这些实体共同的属性作为一般实体的属性