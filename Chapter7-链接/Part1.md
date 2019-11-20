# 静态链接

链接器的两个主要任务

- 符号解析：将目标文件中的每个全局符号都绑定到一个唯一的定义
- 重定位：确定每个符号最终的内存地址

## 可重定位目标文件

![](./img/ELF1.JPG)

## 符号解析

### 1 解析多次定义的全局符号

编译器向汇编器输出的每个全局符号，有强弱之分，函数和初始化的全局变量是强，未初始化的全局变量为弱，强强相遇报错，强弱相遇取强，弱弱相遇随机取，这样的策略可能会带来莫名其妙的bug，**尤其是变量类型不相同的时候。**

``` C
// main.c
#include <stdio.h>
void f();
int x = 1234;
int main(){
	f();
	printf("%d\n", x);
	return 0;
}

// bar3.c
int x;
void f(){
	x = 210;
}
```

文件`main.c`有全局符号f x `bar3.c`有全局符号 x f; 虽然x有两个定义, 但是main中初始化是



### 2 静态链接库

#### 静态库

静态库以一种存档（archive）文件格式（后缀.a），将一组可重定位目标文件打包成一个文件。
当链接器生成可执行文件时，只拷贝应用程序引用静态库对应的模块。

- 减少可执行文件的文件大小
- 程序员需要较少的库名字(不需要一个个的.o)

#### 举例 自己做一个库

使用[例子](https://github.com/imshenzhuo/CSAPP/tree/master/code/ch07)中的文件`addvec.c multvec.c` 生成静态库

``` bash
gcc -c addvec.c multvec.c
ar rcs libvector.a addvec.o multvec.o
```

就生成了静态库文件`libvector.a`，然后在[main](https://github.com/imshenzhuo/CSAPP/tree/master/code/ch07)中的`main2.c`使用该静态库

``` bash
gcc -c main2.c 
gcc -static -o prog2c main2.o ./libvector.a
```

`-static`表明之后不需要链接，直接可以加载运行

实际过程如下

![](./img/process.JPG)

注意到: 链接器复制了libvector中的addvec函数，但是没有复制multvec函数，类似的只复制了libc中的printf相关函数

### 3 使用静态库来解析引用

**静态库要放到命令行的尾部 甚至会出现多次**

 