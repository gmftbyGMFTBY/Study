<!-- $theme: gaia -->

## docopt
1. `docopt` 是一个python的命令行参数解析库，目的是为了更加方便的编写命令行接口和使用说明，试图构建一个更加Pythonic的接口程序
2. 下载安装
    ```shell
    python3.6 -m pip install docopt
    ```
3. GitHub
    https://github.com/docopt/docopt
    
---
## 注意事项
1. 代码在运行的时候一定要记得加入**命令行参数**，或者我们在`Usage`声明了可以不加命令行参数的功能，否则就会报错
2. 如果参数解析错误，`docopt`会打印doc文档并抛出异常，这一点非常的有效和实用
3. `doocpt`只会加载`Usage`中的参数，对于`Option`中的参数说明只是作为help menu的形式呈献给用户并不会加入真正的命令行参数解析的过程中

---
## 使用方式
1. 导入
   ```Python
   from docopt import docopt
   ```
2. 编写__doc__文档字符串
   ```Python
   """Naval Fate.
    This software is aim to ...    # description
    Usage:
        test.py <cheetsheet>
        test.py -e <fuck>
        test.py
        
    Option:
    　　-h --help	show this
   """
   ```
---
3. 加入参数字典
   ```Python
   arguments = docopt(__doc__, version='Naval Fate 1.1.0')
   ```
   该字典将__doc__文档字符串中的所有的短语切分并构成一个`docopt.dict`类型的字典供用户提取实用，判断用户实用程序的时候的命令行参数的使用情况
  
---
## 核心
１．通过上面的工作模式的判断和分析，我们可以发现，我们最根本的任务在于如何编写一个合适的`docopt`的文档字符串供我们的`docopt`识别和利用
2. 基本组成
    * `Usage`
    * `Option`
    * `Example`
3. 之后可以通过调用`argument`字典(和标准`Python`中的字典接口一致)中的参数实现参数管理
4. 具体的实例可以参考`cheat`项目的调用程序来实现
