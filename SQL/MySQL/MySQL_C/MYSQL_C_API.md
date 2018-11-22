### MYSQL C

#### C对MySQL的接口

1. 库文件

   ```bash
   sudo apt-get install libmysqlclient-dev    #　安装对于国内的C操作MySQL的库文件，存放在/usr/include/mysql下
   ```

   `mysql.h`中的定义数据结构

   ```c
   MYSQL			//连接句柄,使用的时候都是使用MYSQL,不使用MYSQL*,后者不会创建对应的结构体，只是一个指针，这一点要记住
   MYSQL_RES       //获取结果集合
   MYSQL_ROW       //保存记录
   MYSQL_FIELD     //字段
   ```

2. 步骤

   * 初始化MySQL结构

   * 连接

     ```c
     #include <mysql/mysql.h>
     MYSQL* mysql_init(MYSQL* mysql);    //初始化一个连接结构并返回，可以是NULL

     //返回值和第一个参数一致
     MYSQL* mysql_real_connect(MYSQL* conn , const char* host , const char* user , const char* password,const char* db_name,unsigned int port , const char* unix_socket , unsigned int client_flag);   //使用初始化的数据库连接结构构建一个针对具体数据库的连接
     //host是对应的主机的IP地址和计算机名称,loclhost
     //端口号默认填0,套接字默认是NULL
     //client_flag的选项 : CLIENT_FOUND_ROWS(返回找到的行数) , CLIENT_NO_SCHEMA(隔绝特殊的使用语法),CLIENT_COMPRESS(压缩协议),CLIENT_ODBC,一般使用第一个参数

     void mysql_close(MYSQL* mysql);    //关闭数据库连接，MYSQL指针将会清空和无效化
     ```

   * 编译选项

     ```c
     gcc -g -o a.out mysql_test.c -lmysqklclient
     ```

   * 错误

     ```c
     unsigned int mysql_errno(MYSQL* mysql);   //针对指定的数据库连接，返回最近的错误代码,0正常运行,/usr/include/mysql/errmsg.h中存有对应的异常代码的标号
     const char* mysql_error(MYSQL* mysql);    //错误返回失败的错误描述字符串(NULL结尾)，否则会返回空字符串或者以前的错误字符串
     ```

3. SQL语句执行

   接口函数只有一个

   ```c
   //运行成功0 , 失败非0 , GDB按照顺序执行可以瞬时打印错误的位置和消息
   int mysql_query(MYSQL* mysql , const char* query);    //对具体的数据库连接SQL语句，可以不加分号
   ```

   * 无返回数据的SQL语句

     `UPDATE` , `DELETE`,`INSERT`三种语句

     ```c
     my_ulonglong mysql_affected_rows(MYSQL* mysql);     //返回上次的更改行数，推荐使用%lu在printf中输出
     printf("%lu\n" , (unsigned long)mysql_affected_rows(MYSQL* mysql));   //强制类型转关成C的数据结构
     ```

   * 返回数据的SQL语句

     `SELECT`语句

     步骤

     * 发出查询

       构建SQL语句

       ```c
       int mysql_query(MYSQL* mysql , const char* SQL_query);
       ```

     * 检索数据

       ```c
       MYSQL_RES* mysql_store_result(MYSQL* mysql);   //返回指向集合结构体的指针，语句失败返回NULL(这一点和有必要，一般很多的BUG都是源自于此)
       MYSQL_RES* mysql_use_result(MYSQL* mysql);   //和上面基本一样，但是可以显著降低客户端的信息存储和资源消耗，但是有些函数不能使用了
       //对于无法得知集合的大小的情况，我们可以采用函数查询
       my_ulonglong mysql_num_rows(MYSQL_RES* result);    //返回集合中的行的数目，只有上一个函数成功后一个函数才可以调用
       ```

     * 处理数据

       ```c
       MYSQL_ROW mysql_fetch_row(MYSQL_RES* result);   //获取记录结构体，该函数返回单个行病返回分配的数据，如果检索完毕将会返回NULL(很重要)

       void mysql_data_seek(MYSQL_RES* result , unsigned long long offset);    //切换我们的指针的位置,offset表示行号(0 - [length -1])

       MYSQL_ROW_OFFSET mysql_row_tell(MYSQL_RES* result);   //返回当之前指针的行号

       //清理数据
       void mysql_free_result(MYSQL_RES* result);
       ```

     * 整理数据

       检索数据的分类

       * 实际数据
       * 元数据

       ```c
       unsigned int mysql_field_count(MYSQL* result);    //返回结果集合中的列数目(字段数目)
       //该函数可以用来做我们的异常检查
       //如果mysql_store_result是NULL，但是字段返回一个非零整数表明检索的时候存在问题导致检索的数据行记录数目是0，如果该值是0表示没有检索到
       ```

       ```c
       //处理数据的方式
       MYSQL_ROW sqlrow;
       MYSQL conn;
       MYSQL_RES* res_ptr;

       mysql_query(&conn , char* sqlcmd);
       res_ptr = mysql_store_result(&conn);

       while((sqlrow = mysql_fetch_row(res_ptr)))   //指针遍历结束，或者出现异常返回NULL跳出循环
       {
         unsigned int field_count = 0;
         while(field_count < mysql_field_count(&conn))    //列数没有遍历完
         {
           printf("%s\t" , sqlrow[field_count]);
           field_count ++;
         }
         printf("\n");
       }
       ```

       ```c
       //返回结果集合的列定义，循环遍历可以获取所有的结果集合的列定义，最后返回NULL(所谓的元数据)
       MYSQL_FIELD* mysql_fetch_field(MYSQL_RES* result);
       //MYSQL_FIELD结构体的信息
       //char* name   列名
       //char* table  表名
       //unsigned int length   列宽
       //enum enum_field_types type   列类型(FIELD_TYPE_VAR_STRING / FIELD_TYPE_LONG)　　IS_NUM(enum)数字类型返回真
       ```

       收集数据方式

       * 打印到标准输出
       * strcpy存储在具体的字符串数组中