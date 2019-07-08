# 存储器层次结构

在操作系统层面，用户（程序员）可以简单地把**存储器系统**视为一个连续的巨型数组。实际上，**存储器系统**是一个具有不同容量、不同成本、不同访问时间的存储设备的层次结构。

存储结构如下

1. CPU寄存器，存在CPU上，访问周期：0
2. 高速缓存，CPU芯片封装，访问周期：4~75个
3. 主存，存在内存条上，访问周期：上百个
4. 磁盘，存在硬盘、固态上，访问周期：大约几千万

主要内容

- [存储技术：SRAM、DRAM、ROM、旋转和固态的硬盘](<https://github.com/imshenzhuo/CSAPP/blob/master/Chapter6-%E5%AD%98%E5%82%A8%E5%99%A8%E5%B1%82%E6%AC%A1%E7%BB%93%E6%9E%84/Part1.md>)
- [计算机程序的局部性](<https://github.com/imshenzhuo/CSAPP/blob/master/Chapter6-%E5%AD%98%E5%82%A8%E5%99%A8%E5%B1%82%E6%AC%A1%E7%BB%93%E6%9E%84/Part2.md>)
- [存储器的层次结构](<https://github.com/imshenzhuo/CSAPP/blob/master/Chapter6-%E5%AD%98%E5%82%A8%E5%99%A8%E5%B1%82%E6%AC%A1%E7%BB%93%E6%9E%84/Part3.md>)
- [高速缓存存储器](<https://github.com/imshenzhuo/CSAPP/blob/master/Chapter6-%E5%AD%98%E5%82%A8%E5%99%A8%E5%B1%82%E6%AC%A1%E7%BB%93%E6%9E%84/Part4.md>)