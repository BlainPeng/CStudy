#include <stdio.h>

/**
 *
 */

void study1() {

    unsigned int a = 0;
    unsigned char *p = (unsigned char *) &a;
    p[0] = 1;
    p[1] = 2;
    p[2] = 3;
    p[3] = 4;
}

/**全局变量，作用域是整个文件*/
int a = 10;

void test() {
    /**
     * 局部变量，作用域只在整个函数中
     * C语言中，默认变量都是auto类型，一般不写，编译器会自动加上
     */
    auto int a = 0;
    a++;
    /**
     * 这里打印结果全是1，为什么？因为局部变量保存在栈中，函数执行完
     * 后，这个变量就会被释放掉了，下次被调用时，都会重新初始化
     */
    printf("a = %d\n", a);
    /**
     * 静态变量在程序刚加载到内存的时候就出现，所以和定义静态变量的大
     * 括号无关，一直到程序结束的时候才从内存中消失，同是静态变量的值
     * 只初始化一次
     */
    static int b = 0;
    b++;
    /**所以，这里的值：1 ~ 10*/
    printf("b = %d\n", b);

    /**
     * 寄存器变量
     * 一般变量是保存在内存中，而register变量是放到CPU的寄存器里面，
     * 所以它是没有地址的，但代码执行效率高
     */
    register int c = 0;
}

int main() {

    for (int i = 0; i < 10; ++i) {
        test();
    }
    return 0;
}