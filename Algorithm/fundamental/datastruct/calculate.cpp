#include <stack>
#include "stdio.h"
#include <iostream>
#include <string>

/*
    Noted: get the line with spaces in C++ should use cin.getline
    cin.getline(str, sizeof(str));
 */

using namespace std;

char str[220]; //保存表达式字符串
int mat[][5] = { 
1,0,0,0,0,
1,0,0,0,0,
1,0,0,0,0,
1,1,1,0,0,
1,1,1,0,0,
};

stack<int> op; //运算符栈,保存运算符编号
stack<double> in; //数字栈,运算结果可能存在浮点数,所以保存元素为double

void getOp(bool &reto,int &retn,int &i) { //获得表达式中下一个元素函数,若函
//数运行结束时,引用变量reto为true,则表示该元素为一个运算符,其编号保存在引用变量retn中;
//否则,表示该元素为一个数字,其值保存在引用变量retn中.引用变量i表示遍历到的字符串下标
    if (i == 0 && op.empty() == true) { //若此时遍历字符串第一个字符,且运算符栈
    //为空,我们人为添加编号为0的标记字符
        reto = true; //为运算符
        retn = 0; //编号为0
        return; //返回
    }
    if (str[i] == 0) { //若此时遍历字符为空字符,则表示字符串已经被遍历完
        reto = true; //返回为运算符
        retn = 0; //编号为0的标记字符
        return; //返回
    }
    if (str[i] >= '0' && str[i] <= '9') { //若当前字符为数字
        reto = false; //返回为数字
    }
    else { //否则
        reto = true; //返回为运算符
        if (str[i] == '+') { //加号返回1
            retn = 1;
        }
        else if (str[i] == '-') { //减号返回2
            retn = 2;
        } else if (str[i] == '*') { //乘号返回3
            retn = 3;
        }
        else if (str[i] == '/') { //除号返回4
            retn = 4;
        }
        i += 2;//i递增,跳过该运算字符和该运算字符后的空格
        return; //返回
    }
    retn = 0; //返回结果为数字
    for (;str[i] != ' ' && str[i] != 0;i ++) { //若字符串未被遍历完,且下一个字
            // 符不是空格,则依次遍历其后数字,计算当前连续数字字符表示的数值
        retn *= 10;
        retn += str[i] - '0';
    } //计算该数字的数字值
    if (str[i] == ' ') //若其后字符为空格,则表示字符串未被遍历完
        i ++; //i递增.跳过该空格
    return;//返回
}

int main () {
    while(true) { //输入字符串,当其位于文件尾时,gets返回0
        cin.getline(str, sizeof(str));
        if (str[0] == '0' && str[1] == 0) break; //若输入只有一个0,则退出
        bool retop;int retnum; //定义函数所需的引用变量
        int idx = 0; //定义遍历到的字符串下标,初始值为0
        while(!op.empty()) op.pop();
        while(!in.empty()) in.pop(); //清空数字栈,和运算符栈
        while(true) { //循环遍历表达式字符串
            getOp(retop,retnum,idx); //获取表达式中下一个元素
            if (retop == false) { //若该元素为数字
                in.push((double)retnum); //将其压入数字栈中
            }
            else { //否则
                double tmp;
                if (op.empty() == true || mat[retnum][op.top()] == 1) {op.push(retnum);
                }//若运算符堆栈为空或者当前遍历到的运算符优先级大于栈顶运算符,将该运
                else { //否则
                    while(mat[retnum][op.top()] == 0) { //只要当前运算符优先级
                        int ret = op.top(); //保存栈顶运算符
                        op.pop(); //弹出
                        double b = in.top();
                        in.pop();
                        double a = in.top();
                        in.pop(); //从数字堆栈栈顶弹出两个数字,依次保存在遍历a.b中
                        if (ret == 1) tmp = a + b;
                        else if (ret == 2) tmp = a - b;
                        else if (ret == 3) tmp = a * b;
                        else tmp = a / b; //按照运算符类型完成运算
                        in.push(tmp); //将结果压回数字堆栈
                    }
                    op.push(retnum); //将当前运算符压入运算符堆栈
                }
            }
            if (op.size() == 2 && op.top() == 0) break; //若运算符堆栈只有两
        }
        printf("%.2f\n",in.top()); //输出数字栈中唯一的数字,即为答案
    }
    return 0;
}
