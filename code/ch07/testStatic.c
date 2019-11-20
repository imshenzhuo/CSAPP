/*************************************************************************
    > File Name: testStatic.c
    > Author: shenzhuo
    > Mail: im.shenzhuo@gmail.com 
    > Created Time: 2019年11月19日 星期二 17时04分00秒
 ************************************************************************/

#include<stdio.h>
int f() {
	static int x = 11;
	return x;
}

int g() {
	static int x = 1;
	return x;
}

int x() {
	static int x = 1;
	return x;
}

int global = 1;
static int staticGlobal = 4;


int main() {
	printf("%d\n", f());
	printf("%d\n", g());
	return 0;
}
