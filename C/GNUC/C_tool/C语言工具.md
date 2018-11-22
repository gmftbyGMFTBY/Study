### Gcc

```bash
gcc -c    # 只生成目标文件，等待链接
gcc -o    # 制定生成文件的名称
gcc -g    # 加入调试信息，等待gdb
gcc -O[0,1,2,3]    # 对代码做默认优化，默认是2,不和-g选项同时运作
gcc -Idir    # 将dir加入到gcc搜索的头文件目录列表中，允许绝对路径和相对路径
gcc -M    # 输出制定的源文件的以依赖文件，包含有众多的系统头文件
gcc -MM    # 同上，但是过滤掉了系统头文件
```

### Make

1. 编码流程
   * 源代码编写
   * 每个模块源代码编译生成二进制目标文件
   * 目标文件连接成为可执行文件(程序)

2. make
   1. 为了优化编译的速度和节省开发效率，使用make和makefile文件生成代码的自动编译脚本，使用make命令在本地目录自动执行
   2. makfile文件中描述了各各文件之间的依赖关系，并提供跟新文件的命令
   3. make 根据源文件的编辑的**最新时间**判断文件的新旧程度决定那个需要更新

3. makefile格式

   ```bash
   target : list of the need
   	bash command ...
   ```

   * 语句命令之前必须是一个制表符号
   * 注释以`#`开头
   * `\`过滤换行符号
   * 在需要过滤不显示某一行的具体执行结果可以使用`@`过滤语句的输出
   * makefile文件在源文件统一目录下

   常用参数

   ```bash
   make -f     # 指定具体的文件名
   make -p     # 打印相关行
   make -n     # 实际显示按照执行顺序现实命令的执行情况，但是并不执行，只是为了检验makefile文件的正确性
   ```

4. 变量

   建议大写，定义在makefile文件额头部

   * 保存大量的文件名列表
   * 保存编译参数

   ```bash
   variable_name=string......    # 定义变量
   $(string...)    # 使用变量
   ```

5. 伪目标

   并不是所有的目标都要对应磁盘上的一个文件，有时候只是为了构成一条命令完成特定的工作

   * all

     检查以来文件的更新情况


   * clean

     make clean执行清理操作

### Gdb

```bash
gdb a.out
```

基本命令

```bash
file PATH    # 加入想要调试的可执行文件
kill   #　终止调试
list / l function_name / lineno    # 列出源码
next    # 下一步不进入函数
step    # 下一步进入函数
run    # 启动或者重新启动程序进行调试
quit    # 退出
watch    # 动态见识一个变量的值
break / b file_path:lineno / file_path.c fucntion_name   # 设置断点
print / p    # 打印指定变量
```
