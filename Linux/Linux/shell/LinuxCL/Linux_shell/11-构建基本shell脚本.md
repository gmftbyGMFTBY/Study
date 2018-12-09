## 构建基本shell脚本

学习构建脚本的基础知识

---

1. 命令组合

   ```shell
   date ; who
   ```

   * 最大命令行字符数限制是 255 个字符
   * 没有脚本话，每次需要输入执行

2. 创建脚本

   * `#!/bin/bash` : #!必须出现在第一行，用来指定解释器
   * `#`  : 单行注释

3. 脚本编写技巧

   1. `echo` 命令说明程序的运行信息

      ```shell
      echo this is a line
      echo 'this is a " line'
      echo "this is a ' line"
      echo -n "this is a line"    # 不输出换行
      echo -n "this is a user $USER"    # echo中的名称全部的替换成variable
      echo -n "this costs me \$15"
      ```

   2. 使用变量

      * 使用变量可以临时性的将信息存储在shell脚本中，以便之后的使用	

      * 变量信息

        ```shell
        set     # 查看所有的变量
        unset variable_name    # 删除变量
        ```

      * 用户自定义变量

        * 长度不超过20个

        * 大小写敏感

        * 使用赋值操作，不可以加上空格

          ```shell
          a=1    # yes
          a = 1  # no
          ```

        * shell自动决定数据类型

        * 使用的时候必须加上'$',操作的时候不用加上

   3. 命令替换

      * **shell脚本可以从命令中提取信息**,并将信息在加工处理，这一点非常重要

      * 方式

        1. 反引号 : 

           ```shell
           testing=`date`
           ```

        2. `$()`  :

           ```shell
           testing=$(date)
           ```

           ```shell
           #!/bin/bash
           today=$(date +%y%m%d)
           ls /usr/bin -al > log.${today}    # 生成日志文件
           ```

      * 这种方式开启的是子shell,不能直接使用父shell中的局部变量，除非导出

      * 只有shell的內建命令是不用创建子shell运行的，其他都是父shell创建出的子shell运行

   4. 输入输出重定向

      1. 输出

         * `>` : 覆盖
         * `>>` : 追加

      2. 输入

         * `<` 

         * `<<` : 内联输入重定向

           ```shell
           cat << end
           i am lantian
           eni
           end
           ```

   5. 管道

      管道的好处在于，两者基本上是并行运行的，进程之间采用了管道文件作为进程通信的桥梁，运行速度相对来说比较快

      ```shell
      apt list | sort | less
      ```

   6. 数学运算

      * `$[ operations ]`

        ```shell
        a=$[1 + 2]
        b=$[2*3 ]
        c=$[$b*$a]
        ```

      * 好处

        1. 比 `expr` 命令更加方便
        2. 不会出现转义的问题，因为方括号知道内部的都是运算字符
        3. **但是只支持整数运算**,这是当前的一个限制

      * 浮点解决方案 `bc`

        1. 数字和浮点数

        2. 变量(简单变量和数字)

           * 內建变量 `scale` 表示浮点数的小数点的保存的位数

             ```shell
             3 / 5    # 0, scale = 0
             scale = 5
             3 / 5    # 0.60000, scale = 5
             ```

        3. 注释

           ```shell
           /* ... */
           ```

        4. 表达式

           ```shell
           1. a=1
           2. print a    # 打印变量的值
           ```

        5. 程序语言(if-then)

        6. 函数

        7. 命令行参数

           1. -q : 静默模式，不显示交互式的欢迎界面

        8. 退出 : quit

      * 在脚本中使用 `bc`

        ```shell
        # options 是bc需要使用的参数变量的定义，可以使用分好分隔，expression表示表达式
        variable=$(echo "options; expression" | bc)

        # e.g.
        var=$(echo "a=1;b=2;a+b" | bc)
        echo $var    # var = 3
        var=$(echo "scale=4; 3/5" | bc)
        echo $var    # var = .6000
        a=100
        b=45
        var=$(echo "scale = 4; $b / $a" | bc)    # 混合shell变量
        echo $var

        # ---------- 密集计算 --------- #
        # 1. 输入放入文件中
        # 2. 内联输入重定向,但是必须在脚本中才可以正常运行，可以使用shell的变量(整数或者浮点数)

        var5=$(bc << eof
        scale = 4
        a = 100
        b = 45
        c = a / b
        print c
        eof
        )
        ```

   7. 脚本退出

      * 每一个脚本都有一个退出状态码(0 ~ 255),可以捕获这个值并在脚本中运行

      * 捕获退出码

        ```bash
        echo $?    # ?是一个变量用来保存退出码
        ```

      * 退出码标识

        1. 0 : 正常
        2. 正数 : 不正常
           * 127 : 无效命令

      * 退出脚本

        ```shell
        exit 255    # 返回退出码并退出
        ```

        ​

   8. shell数组
        * 使用空格分开

        ```shell
        array=(1 2 3 4 5 6 7 "lantian")
        ```

        * 数组长度 : array_length=${#array[*]}
        * 数组下表访问 : array_ele=${array[2]}
        * 数组下表赋值 : array[2]=100
            1. 原地修改存在的值
            2. 超过数组的场地追加在数组的末尾
        * 删除数组 : unset array[2]
        * 切片访问 : ${array[@]:1:4}
        * 数组遍历
            ```shell
            for var in ${array[@]}
            do
                echo $var
            done
            ```

