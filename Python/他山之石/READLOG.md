## 他山之石

#### 1. 写在前面

1. 可以帮助自己提升在语言运用方面的技巧和能力的一些好玩的仓库代码，通过学习这些优秀的代码，提升自己在Python方面学习的实践不足

2. 项目存放路径

   `/home/lantian/admir_repo`

#### 2. 清单和完成情况

1. `cheat`

   > - Time : 2017.1.6
   >
   > - Author :` chrisallenlane`
   >
   > - Link : `https://github.com/chrisallenlane/cheat`
   >
   > - Env : Linux / Unix
   >
   > - Language : Python 3.x
   >
   > - Description : 
   >
   >   有用的Linux命令行笔记工具，强大的自定义功能非常符合我喜欢记笔记的奇怪癖好
   >
   >   工具小巧实用
   >
   > - State : `Done`
   >
   > - 收获
   >
   >   - docopt学习使用 : `Done`
   >   - 学习setup.py文件的编写 : `Undo`
   >   - os模块在编写轮子的时候作用非常大
   >   - \_\_file\_\_和\_\_init\_\_.py文件的具体使用加入了  `DailyCollection` 笔记中
   >   - printh函数中file参数的使用技巧掌握
   >
   > - 感想
   >
   >   - 第一次学习看别人的代码，感触还是很多的，作者的Python能力很强，虽然有一些地方我认为我可以优化
   >   - 可以尝试为作者改代码
   >     1. 对于 `-s` 或者别的使用方式的时候不能就文件目录下出现的子目录筛除只保留文件的这一点实现的不是很好，可以考虑改进
   >     2. `-s` 参数在没有找到对应的文本的时候会报错
   >
   > - 结果 : 为作者发布了一次 `pull request` 等待合并分支

2. `wechat_jump_game`

   >* Time : 2017.1.1
   >
   >* Author : `wangshub`
   >
   >* Link : `https://github.com/wangshub/wechat_jump_game`
   >
   >* Env : Windows / Linux / Mac OS
   >
   >* Language : Python 3.x / Python 2.x
   >
   >* Description : 
   >
   >  基于图片识别的微信跳一跳游戏的辅助，希望可以通过阅读源代码了解对于强化学习的实现细节部分
   >
   >* State : `Undo`

3. `docopt`

   >* Time : 2017.1.10
   >
   >* Author : docopt
   >
   >* Link : `https://github.com/docpt/docopt`
   >
   >* Env : Windows / Linux / MaxOS
   >
   >* Language : Python 3.x / Python 2.x
   >
   >* Description : 
   >
   >  基于命令行的参数提取脚本第三方库，简单高效，需要学习
   >
   >* State : `Undo`
   >
   >* 准备学习的要点
   >
   >  1. `README.md ` 文件的平台和语言说明的编写方案 (Done)
   >  2. `README.md` 图片的上传显示

4. `TSP-Hopfield-Tank`

   >* Time : 2017.1.24
   >
   >* Author : MacStan
   >
   >* Link : `https://github.com/MacStan/TSP-Hopfield-Tank`
   >
   >* Env : Windows / Linux / MaxOS
   >
   >* Language : Python 3.5.1
   >
   >* Description : 
   >
   >  对TSP问题的Hopfield网络求解方式，内部有大量的代码编写技巧需要学习
   >
   >* State : Undo
   >
   >* 准备学习的知识点
   >
   >  1. `ffmpeg` : 视频和图像处理开源软件的基本使用
   >
   >  2. `Python字符串处理的技巧` : 
   >
   >     * `format`
   >     * `f'{x}'`
   >
   >  3. `unittest` : 单元测试框架学习
   >
   >  4. `os.path`
   >
   >     * dirname
   >     * abspath
   >     * os模块对与Linux操作系统亲和性，和该模块存在的必要性(文件管理方面)
   >
   >  5. `subprocess` : 子进程处理模块
   >
   >     * `multiprocessing`
   >     * `threading`
   >
   >  6. 系统路径管理模块
   >
   >     * `pathlib`
   >     * `glob`
   >
   >  7. `PEP 484` : Type Hint(3.5新加入特性)
   >
   >  8. `matplotlib` : 综合使用，尤其是作者在仓扩中，使用其和`ffmpeg`的配合创建的动态图片
   >
   >  9. `numpy` : Python的组合使用
   >
   >  10. `logging` : 日志记录模块使用，和之前的如何记录日志的那一篇笔记以一块学习
   >
   >  11. 学习Hopfiled网络对组合优化问题的求解
   >
   >  12. `typing` 
   >
   >  13. ```python
   >      a = 0 if 0.2 > sigm else sig
   >      ```

   ​
