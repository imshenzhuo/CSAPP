/*************************************************************************
    > File Name: swap.c
    > Author: shenzhuo
    > Mail: im.shenzhuo@gmail.com 
    > Created Time: 2019年11月19日 星期二 16时12分57秒
 ************************************************************************/

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
