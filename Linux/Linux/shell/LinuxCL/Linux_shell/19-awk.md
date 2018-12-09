## sed & awk

---

### `awk`

1. 可以实现的工作

   * 定义变量保存数据

   * 使用算数或者字符串操作符处理数据

   * 引入结构化变成概念

   * 提取数据元素，重新格式化生成报告

   * **`awk` 允许和 `sed` 一样，定义使用正则表达式来进行行匹配**

     ```shell
     awk '/as/{print $0}' test
     awk '/line1/,/line2/{print $0}' test
     ```

2. 命令格式

   ```shell
   awk options program file    # program脚本中的字符串必须加双引号
   ```

   * 参数

     1. -F : 字段分隔符号
     2. -f : 指定从文件中读取 `awk` 脚本
     3. -v : 定义 `awk` 变量及其默认值
     4. -mf N : 指定处理数据文件的最大字段数
     5. -mr N : 指定处理文件的最大行数

   * 脚本 `program`

     * 使用 {} 定义脚本

     * 脚本是用单个文本字符串定义的

     * e.g.

       ```shell
       awk '{print "Hello World!"}'
       line1
       Hello World!
       line2
       Hello World!
       line3
       Hello World!
       # ----
       # 这里使用Ctrl+D EOF　终止
       ```

   * `file`

     指定要读取的文本，和 `sed` 一样，一次读取一整行

3. 数据字段

   1. 数据字段

      1. $0 : 一整行
      2. $1 : 第一个**数据字段**
      3. ...

   2. 字段分隔符号

      1. 读取一行处理的时候，会使用默认的 **字段分隔符号** 划分字段
      2. 默认是所有的空白字符(空格，制表符)

   3. 修改字段分隔符号

      1. 命令行方式

         ```shell
         awk -F: '{print $1}' /etc/passwd
         ```

      2. 脚本方式

         ```shell
         # file.awk
         BEGIN {
           print "This is the begining"
           FS=":"    # 定义新的分隔符号
         }

         {
           ...
         }
         ```

4. 多命令编辑

   1. 命令行模式

      - 在 {} 中加分号即可 `;`

      - ```shell
        echo "I am lantian" | awk '{$3="asshole"; print$0}'
        ```

      - 多行模式

        ```shell
        awk '{
        $4="asshole"
        print $0}' test
        ```

   2. 脚本文件模式

      * **脚本必须是 {} 中书写**

      * 书写格式

        1. ```shell
           {$3= "asshole"; print $0}
           ```

        2. ```shell
           {
             $3="asshole"
             print $0
           }
           ```

        3. ```shell
           # 多脚本域,顺序执行
           {
             print "script one"
           }

           {
             print "script two"
           }
           ```

   3. **定义变量**

      ```shell
      {
        text = 'is the stupid'    # 定义变量,不用$符号使用变量，和shell不一样
        print $1 text $2
      }
      ```

5. 运行时机

   1. 处理前运行

      * 输出必要的提示信息
      * 初始化

      ```shell
      # 输出标题之后，输出整个文本，添加标题
      awk 'BEGIN {print 'This is the title !'} {print $0}' test
      ```

   2. 处理后运行

      * 输出必要的提示信息
      * 后处理

      ```shell
      # 后处理
      awk 'BEGIN {print "This is the begining"} {print $0} END {print "fuck you"}' test
      ```

      ​


---

### 进阶

---

#### 变量

1. 变量分类

   **awk中的变量使用方式和shell的不一样，不需要加入$符号用来标识**

   * 內建变量

     1. 数据字段变量 : 字段分隔符号界定

     2. 字段分隔变量组

        1. FS : 决定数据字段分隔符号

        2. OFS : 输出数据字段分隔符号

           输出字段分隔符号默认是空白字符

           ```shell
           # 不修改OFS,逗号默认的分隔符号是空白字符，现在修改成 >>
           awk 'BEGIN {OFS=">>"} {print $1,$2}' test
           ```

        3. FIELDWIDTHS : 允许使用长度分隔，不适用分隔符号分隔

           ```shell
           awk '{FIELDWIDTHS="3 5 2 5"} {print $1,$2}' test
           ```

        4. RS : 行解析界定符号

           默认是换行符号

        5. ORS : 输出行解析界定符号

     3. 其他

        1. ENVIRON

           ```shell
           awk 'BEGIN {print ENVIRON["HOME"]}' 
           /home/lantian
           ```

        2. FNR

           当前文件中处理的数据行的数目

           ```shell
           awk '{print FNR}' test test1
           ```

        3. NR

           已经处理的行的总数，牵扯到多个输入处理文件的时候，该值不会重置，但是FNR会

           ```shell
           awk '{print NR}' test test1
           ```

        4. NF

           当前处理行的字段的总数

           ```shell
           awk '{print NF}'  test
           awk '{print $NF}' test
           ```

   * 自定义变量

     1. 变量分为字符串变量和数字变量

        ```shell
        awk '{text="this is a text !"; print text}' test
        ```

     2. 数字变量支持数学运算

        +, -, *, /, %, ^,+=,++,-=,--

        ```shell
        awk 'BEGIN {sum=0} {sum+=$1} END {print sum}' test
        ```

   * 命令行变量参数 `-v`

     ```shell
     awk -v n=2345632345 '{print n}' test
     awk -v n="2345632345" '{print n}' test
     ```

   * 数组变量 (python中的字典)

     ```shell
     awk 'BEGIN {var[0] = 0;var[1] = 1;var[2] = 2} {print var[0],var[1],var[2]}' test 
     ```

     1. 引入awk的简化 `for` 语句

        ```shell
        for (var in array)    # var是键，array[var]是值
        {
          statements
        }
        ```

     2. 删除数组变量

        ```shell
        delete var[0]    # 删除数组变量
        ```

#### 模式

1. **可以使用模式来和sed一样限定处理的行的位置**

   ```shell
   awk '/pattern/{print $0}' test
   ```

2. 排除语法

   ```shell
   # 不匹配则实行，匹配不执行
   awk '!/pattern/{print $0}' test

   # 有用的例子，去重文件
   awk '!a[$0]++' test    # 就是 awk '!a[$0]++{print $0}' test 的缩略版
   ```

3. 匹配操作符号 **`~`**

   1. 语法

      ```shell
      # $1 字段中满足 pattern正则要求的字符
      awk '$1 ~ /pattern/{print $0}' test  

      # 排除语法
      awk '$1 !~ /pattern/{print $0}' test
      ```

4. 数学表达式(绝对匹配)

   ```shell
   awk -F: '$4 == 0{print $1}' /etc/passwd
   ```



#### 结构化编程

1. if-then-else

   ```shell
   awk '{if ($1 > 15) {print "> 15"} else {print "< 15"}}' test
   ```

2. while

   * 允许使用break和continue

   ```shell
   # 对行总和求平均值
   awk '{total=0;i=1;while (i < 4) {total+=$i;i++;} avg=total / 3;print "average:",avg}' test
   ```

3. for - C风格

   ```shell
   awk '{total=0;for(i=1;i<=2;i++) {total += $i} ; avg = total / 2;print "average",avg}' test
   ```



#### 格式化打印 printf

```shell
printf "format string" var1, var2, ...
```

* `format string`

  ```shell
  %[modifier]control-letter
  ```

  * `control-letter`

    c : 字符

    d : 整数

    e : 科学计数法

    f : 浮点数

    s : 字符串

  * `modifier`

    ```shell
    %-5.2f    # 左对齐，小数点后两位，总长度是5的浮点数，不足使用空格填充
    ```

    ​