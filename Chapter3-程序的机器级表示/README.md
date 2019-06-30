# 程序的机器级表示

> 本文是书籍CSAPP第三章的整理，以应用最广泛的x86-64为例讲述，所有的实验都是在intel处理器的Linux操作系统上完成的
> ps x86是指 Intel处理器，64代表64位

#### 高级语言和机器语言有什么不同？为什么还要学机器代码呢？

高级语言屏蔽了底层细节，级别高（抽象），所以效率高，而且跨机器。

学习机器代码是因为：

1. 写更高效的代码。通过查看生成的汇编代码纠正隐含的低效代码
2. 必要时刻查看被高级语言屏蔽的底层(比如 **并发**、**缓冲区溢出攻击**等)

## 目录

1. [准备](<https://github.com/imshenzhuo/CSAPP/blob/master/Chapter3-%E7%A8%8B%E5%BA%8F%E7%9A%84%E6%9C%BA%E5%99%A8%E7%BA%A7%E8%A1%A8%E7%A4%BA/Part1.md>)
2. [从机器代码角度了解学习C语言](<https://github.com/imshenzhuo/CSAPP/blob/master/Chapter3-%E7%A8%8B%E5%BA%8F%E7%9A%84%E6%9C%BA%E5%99%A8%E7%BA%A7%E8%A1%A8%E7%A4%BA/Part2.md>)
3. [从机器代码角度理解C语言的调用细节](<https://github.com/imshenzhuo/CSAPP/blob/master/Chapter3-%E7%A8%8B%E5%BA%8F%E7%9A%84%E6%9C%BA%E5%99%A8%E7%BA%A7%E8%A1%A8%E7%A4%BA/Part3.md>)

## 准备

1. Linux环境C语言回顾
2. C语言、汇编语言、机器代码之间是什么关系
3. x86-64细节：数据的表示、处理、控制（学会看懂汇编）

## 从机器代码角度理解C语言

1. C语言控制结构的实现
2. 机器级数组实现及二维数组使用优化
3. 机器级结构体实现
4. 机器级联合体实现

## C语言的调用细节

- C语言过程调用的实现

- 解决问题：存储器访问越界、stack overflow 攻击


