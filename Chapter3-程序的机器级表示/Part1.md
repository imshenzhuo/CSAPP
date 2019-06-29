## 准备

1. Linux环境C语言回顾
3. x86-64细节：数据的表示、处理、控制（学会看懂汇编）

## Linux环境C语言回顾

假设一个C程序，有两个C文件，`p1.c` , `p2.c` 

``` bash
linux> gcc -Og p1.c p2.c -o p
```

`gcc`是Linux上默认的C语言编译器，由于编译器会默认优化，所以用`-Og`产生符合源文件的优化等级
*ps：编译器优化的内容后面有阐述*

### C语言编译过程

以上一条命令执行后，产生一个二进制可执行文件`p`经历了哪些过程呢？

1. 预处理：**预处理器**扩展源代码，插入`#include`包含的内容、替换`#define`宏
2. 编译：**编译器**产生两个源文件的**汇编代码文件**`p1.s p2.s`
3. 汇编：**汇编器**将汇编代码转换为**目标代码文件** `p1.o p2.o`
4. 链接：**链接器**将目标代码文件和库函数合并生成**可执行文件** `p`

### 示例

``` C
// mstore.c full file
long mult2(long, long);
void multstore(long x, long y, long *dest) {
	long t = mult2(x, y);
	*dest = t;
}
```

使用`-S`选项规定只执行到编译生成汇编代码步骤

``` bash
# 编译
linux> gcc mstore.c -Og -S mstore.c
```

生成文件`mstore.s`，全部内容如下，可以看到堆栈的`push pop ret`和`mov`等指令

``` assembly
	.file	"mstore.c"
	.text
	.globl	multstore
	.type	multstore, @function
multstore:
.LFB0:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdx, %rbx
	call	mult2
	movq	%rax, (%rbx)
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE0:
	.size	multstore, .-multstore
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
```

``` bash
# 汇编
linux> gcc -Og -c mstore.c 
```

完成汇编阶段，生成目标文件`mstore.o` 

因为没有入口`main`函数，所以并不能生成可执行文件

对`main.c`生成可执行文件`proc`

``` bash
# 链接
linux> gcc -Og -o proc main.c mstore.c
```

从文件大小也能侧面看出各个阶段干了什么

``` bash
senzuo@sz:~/learnSth/CSAPP/Chapter3$ ls -lh
total 28K
-rw-rw-r-- 1 senzuo senzuo  230 6月  29 13:41 main.c
-rw-rw-r-- 1 senzuo senzuo  108 6月  29 13:23 mstore.c
-rw-rw-r-- 1 senzuo senzuo 1.4K 6月  29 13:43 mstore.o
-rw-rw-r-- 1 senzuo senzuo  401 6月  29 13:24 mstore.s
-rwxrwxr-x 1 senzuo senzuo 8.6K 6月  29 13:46 proc
```

## x86-64细节

### 数据格式

由于历史原因，Intel用术语字代表16位，也就是双字节，32位是双字（double），64位是四字（quad），在64位Intel机器中

| C声明  | Intel 数据类型 | 汇编代码后缀 | 字节大小 |
| :----: | :------------: | ------------ | -------- |
|  char  |      字节      | b            | 1        |
|  int   |      双字      | l            | 4        |
| short  |       字       | w            | 2        |
|  long  |      四字      | q            | 8        |
| char * |      四字      | q            | 8        |
| float  |     单精度     | l            | 4        |
| double |     双精度     | q            | 8        |

### 访问信息

#### 寻址

插入图片

##### 总结

1. 有一个逗号就分别取内容相加
2. 有两个逗号才有乘法
3. 不写0x一律十进制

#### 数据传送

注意

1. 采用Linux默认的AT&T格式，源操作数在前，目的操作数在后
2. 两个操作数不能同时执行内存
3. 指令的后缀要和寄存器大小对应

##### 1.最简单的传送

插入图片

##### 2.较复杂传送

当两个操作数不相同的时候（eg 将小东西放到大盒子的时候）

插入图片

**示例**

插入图片

值得注意的是，像x这样的局部变量都是存在寄存器中的，比内存里面的快得多

##### 3.堆栈的传送

插入图片

## 算数和逻辑操作

lea指令相当于加载地址到目标数，所以看到的源操作数一般都是寄存器间接寻址

## 控制

#### 控制的依据--条件码

