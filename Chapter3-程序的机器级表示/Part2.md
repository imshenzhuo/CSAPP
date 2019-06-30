# 从机器代码角度理解C语言

1. do-while、while、for三种循环底层是一样的吗？
2. switch和if-else有什么不同？为什么只能switch整数？
3. 定长、变长数组在底层是如何实现的？定长数组为什么可以优化？
4. 结构体和数组有什么相似的地方？是如何对齐的？
5. 联合体是用来做什么的？

## 循环

C语言提供了三种循环结构：do-while、while、for。大多数汇编器根据一个循环的do-while形式（虽然在高级语言中用的少）编译成机器代码。

## 控制

### if语句

if控制语句比对应的机器代码更加简洁，机器代码的goto风格让人抓狂。一般的if语句，如下

``` C
if (test-expr)
    then-statement
else
	else-statement
```

对应的汇编代码的逻辑为

``` C
	t = test-expr;
	if(!t)
        goto false;
	then-statement;
	goto done;
false:
	else-statement;
done:	
```

┑(￣Д ￣)┍

### switch

switch并不是连续的if-else-if，switch使用了一个叫做跳跃表的东西。什么是跳跃表呢？编译器根据switch后值的范围，生成一个表，表的key是从最小到最大的连续不间断的值（所以只能针对基本数据类型中的整型类型使用），比如是从1到100一百个数字，每个表项对应case中程序的地址。

通过跳跃表，switch就可以直接转移到对应的case，而不是遍历if-else。不过由于跳跃表的key是连续不间断的，所以只有在switch数量比较多并且跨度小的情况下，switch的高效才体现的出来。

## 数组

### 回顾

``` C
T A[N];
```

这一行代码在存储器中分配了一个N\*L ( L= sizeof(T) )字节的空间，xa代表起始地址，标识符A，第i个元素A[i]的地址就是xa+L\*i

``` C
A[i] == *(A+i)
```

数组标识符即（常量）指针，并且指针会自动伸缩：A+i => xa + L\*i

取一维数组A[i]的汇编实现

``` assembly
movl	12(%ebp), %eax				get i 
movl	8(%ebp), %edx				get A
movl	(%edx, %eax, 4), %eax		get A[i]
```

### 二维数组

``` C
&D[i][j] = xd + L(C*i + j)
```

假设xd、i、j分别位于%ebp偏移量为8、12、16的地方，D的大小为5×3，int类型L为4，取出`D[i][j]`的汇编为

``` assembly
movl	12(%ebp), %eax				get i 
leal	(%eax, %eax, 2),%eax		get i*3 to eax
movl	16(%ebp), %edx				get j	
sall	$2, %edx					get 4j to edx
addl	8(%ebp), %edx				get 4j + xd to edx
movl 	(%edx, %eax, 4), %eax		M[xd + 4j +12i]  xd + 4(4i+j)
```

取二维数组要六条指令，当矩阵操作只取一行的时候，取该行首元素的指针当作一维数组，就可以优化，不过谁知道是不是编译器自己就完成优化了呢？

## 结构体

结构体其实是包含不同数据类型的数组，内部的数据由对齐安排。

对齐：任何K字节的基本对象的地址必须是K的倍数

## 联合

``` C
union S3{
    char c;
    int i[2];
    double v;
}
```

联合的直接解释是允许以多个类型来引用一个对象，数据的大小等于成员最大的大小。即`sizeof(double)` ，对相同的数据二进制可以用char int*[2] double 三种方式来得到信息。（信息=位+解释）

绕过C语言提供的检查数据类型的安全措施

举例来说就是用一个联合，来办多件事情，事情之间互相独立，C语言真的是丧心病狂节省空间啊。