有两个文件`main.c`和`swap.c`你中有我, 我中有你. `main.c`有`swap`函数的声明, 依赖`swap.c`文件中的定义, `swap.c`文件有数据`buf`的声明, 依赖`main.c`文件的定义.

``` C
// demo/main.c
void swap();

int buf[2] = {1, 2};

int main() {
	swap();
	return 0;
}
```

``` C
// demo/swap.c
extern int buf[];

int *bufp0 = &buf[0];
int *bufp1;

void swap() {
	int temp;

	bufp1 = &buf[1];
	temp = *bufp0;
	*bufp0 = *bufp1;
	*bufp1 = temp;
}
```

得到可执行目标文件`p`

``` shell
gcc -O2 -g -o p main.c swap.c
```

## 过程回放

``` bash
# 1.预处理 (C预处理器) 生成Ascii码文件
cpp main.c main.i
# 2.编译 生成Ascii码汇编文件
cc -S main.i -O2 -o main.s
# 3.汇编 生成可重定位目标(o)文件
as -o main.o main.s
# 4.链接 生成可执行目标文件p
ld -o p main.o swap.o
```

## 链接器命令

之前的`ld`程序以可重定位目标文件(main.o swap.o) + 命令行参数(-o p)作为输入, 生成一个可执行目标文件(p)

以上是链接器的输入输出, 链接器具体做的内容:

- 符号解析 
  - 符号引用&符号定义 
  - eg main.c中的swap找到对应的定义 swap.c中的buf找到对应的定义
- 重定位 符号定义&存储器位置

什么是目标文件呢? 符号是什么?

### 目标文件

目标文件有两种

- 可重定位目标文件 `main.o swap.o` 编译汇编生成, 可以和其他同类生成可执行目标文件
  - 共享目标文件 特殊类型的可重定位目标文件, 可以在加载 运行时被动态的加载并链接  (xxx.a xxx.so)
- 可执行目标文件 链接器生成 可执行

### 符号和符号表

程序中定义的变量和函数都属于符号.

符号有三种

1. 自己定义并且可以被其他模块引用的**全局符号**: 自己定义的非静态的C函数 + 非静态的全局变量
2. 其他模块定义自己声明引用的**全局符号**: 其他模块定义的非静态的C函数 + 非静态的全局变量
3. 只被自己定义和使用的**本地符号** 静态的函数 + 静态变量 (可以使用static隐藏达到private的效果)

之前两个文件生成的`main.o swap.o`文件来说, 文件中的`.symtab`包含了符号的信息, 输出对应符号

> 注意: 编译时并没有使用`-g` , 没有局部变量的entry, 但是有全局变量的entry

``` bash
$ readelf main.o -s
Symbol table '.symtab' contains 11 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS main.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    7 
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     8: 0000000000000000     8 OBJECT  GLOBAL DEFAULT    3 buf
     9: 0000000000000000    21 FUNC    GLOBAL DEFAULT    1 main
    10: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND swap
```

前面7个都是第三种符号变量, 第8个符号变量`buf`属于第一种符号, 最后一个符号`swap`属于第二种符号

``` bash
各个字段的代表的意思
value : 
	可重定位文件:距定义目标section的起始位置的偏移量
	可执行文件:符号的地址 
size : 目标的大小 (byte)
type : 目标类型
bind : 符号是本地还是全局
Ndx : 符号所在的section
		1.text 3.data ABS表示不该被重定向 UND表示不确定 COM表示未初始化数据 
```

### static 

``` C
int f() {
    static int x = 0;
    return x;
}
int g() {
    static int x = 1;
    return x;
}
static void x() {}
```

编译器在`.data`中为两个整数分配空间, 并且给两个名字相同的static变量赋予各自唯一的符号. 由于f中的初始化后是0, 所以改为`bss`区. x函数是有效的, 并且其他模块不可见, 达到了private的效果

