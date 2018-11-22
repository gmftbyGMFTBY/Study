## extern 关键字
---

1. 在同一文件中使用
    如果使用的变量没有在一个函数或者语句的前面定义或者声明的话，市级变异的过程中是会失败的，为了保证可以正常的编译成功，需要告诉编译器起到别的地方(文件后面)去找这个变量，需要使用 `extern` 这个关键字
    详细可见文件 `test1.c`

2. 不同文件中使用
    1. `extern` 关键字的真正作用是引用不同文件中的变量或者函数名称
    2. 使用方式请见文件 `test2_1.c`, `test2_2.c`
        ```shell
        gcc test2_1.c test2_2.c -o a.out
        ./a.out
        ```
    3. `extern` 只可以导入全局变量，函数内的局部变量是无法导入的(可以尝试将 `test2_2.c` 中的 num 变量放在函数 `func` 中，编译失败)
    4. `extern` 只可以在原文件中被初始化，在 `extern` 带入的时候不可以重新赋值，如果原文件不重新赋值的话，全局变量会被编译器自动初始化成 0
    5. `extern` 导入之后便可以重新的修改变量的值,但是很危险,如果不想修改可以使用 `const` 修饰
        ```c
        const int num;              // 原文件
        extern const int num;       // 导入文件，不可修改
        ```
    6. 一般来说，如果直接导入全部文件的话，也可以使用另一个文件的变量，但是这样非常不安全，使用 `extern` 关键字就可以方便的实现导入部分需要的变量的目的
        ```c
        // test2_1.c, 编译只需要编译自己即可, gcc test2_1.c
        #include <stdio.h>
        #include "test2_2.c"        // ""　内部的是文件的路径

        ...     // use the test2_2.c variable as in the test2_1.c
        ```