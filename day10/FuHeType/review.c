//
// Created by PengBaiLiang on 2017/5/4.
//

#include <stdlib.h>

/**
 * 局部变量的作用域是{}。
 * 全局变量和常量以及静态变量的作用域是整个程序生命周期。
 * 堆变量的作用发开关机malloc和free之间
 * 全局变量、局部变量都可以简单的使用变量名就可以访问他
 * 内存的值，但堆里面的变量都是通过一个指针间接引用的。
 */

int a3 = 0; //在静态区中标识了一块4个BYTE的内存，让这块内存的值为0

void note(int a1, int a2, char c) {

    //变量名其实就是一个地址的引用，所以一个栈变量名就
    //是栈地址的一个引用而已；c意思是在栈中间多了一个BYTE的空间

    c = 0;      //让栈中一个BYTE的内存的值为0
    a2 = 200;   //让a2所代表的内存的值为200
    // 在堆中分配了一个int的空间
    int *p = malloc(sizeof(int));
    // *p就是堆内存的一个引用，让*p代表堆内存的值为100
    *p = 100;
    // 不是释放变量p，p是一个在栈中的自动变量，释放的是p
    // 指向的堆内存的空间
    free(p);
}


char *test() {

    char a = 0;
    return &a;
}

char *test1() {

    static char a = 0;
    return &a;
}

/**
 * 错语的模型，因为const并不是真正的常量
 * @return
 */
char *test2() {

    const char a = 0;
    return &a;
}

/**
 * 错语的模型，a在栈里面，栈变量的地址不能通过return返回
 * @return
 */
char *test3() {

    char a[100];
    return &a;
}

/**
 * 正确的模型
 * @param p
 * @return
 */
char *test4(char *p) {

    *p = 0;
    return p;
}

char *test5(char *p) {

    char a = *p;//错误的模型，原因与test3一致
    return &a;
}

char *test6() {

    //正确的模型
    char *a = malloc(sizeof(char));
    //返回的是一个堆地址，堆只要没有free，就是有效的
    return a;
}

char *test7() {
    //正确的
    char *a = "Hello";
    //返回的地址是有效的，因为"hello"是常量，常量和静态
    //变量道理是一样的，只是常量区是只读的，"hello"是一个
    //const char *
    return a;
}

char *test8() {
    //错误的
    //这里只是在栈里面定义了一个char的数组，
    //同时把数组的每个成员初始化
    char a[] = "hello";
    return a;
}

char *test9(char *a) {

    //正确的，这里指针只是做了位移
    char *p = a;
    p += 3;
    return p;
}

char *test10() {

    //正确的
    char *p = malloc(100);
    return p;
}

char *test11() {

    char *p = malloc(100);
    p += 3;
    return p;
}

char test12(char *a) {

    /**
     * 把0x123这块内存的值设为'a'
     * 把0x100这块内存的值设为'a'
     * 把0这块内存的值设为'a'，很显然不行
     */

    a[0] = 'a';//这里就相当于 *(a+0) = 'a'
}

void test13(char *a) {

    a = malloc(100);
    *a = 'a';
}

void test14(char **a) {

    *a = malloc(100);
    **a = 'a';
}

int main1() {

    /**a指向的栈空间已经是一个无效的地址了*/
    char *a = test();


    char num = 100;
    /**得到的是num的地址，num的地址在main{}内部一直是有效的*/
    char *i = test4(&num);

    char array[] = "hello world";
    char *b = test9(array);


    char *p = test11();
    /**
     * 在调用test11函数时，返回回来的指针已经
     * 发生了位移，所以在释放掉的时候必须把指
     * 针归位，否则会释放掉未申请的内存而导致
     * 程序core dumped
     */
    p -= 3;
    free(p);

    /**这里是效的，因为array1的首地址比函数test12后释放掉*/
    char array1[10];
    test12(array1);     //假设首地址为0x123

    /**这里是有效的，因为array2的首地址比函数test12后释放掉*/
    char *array2 = malloc(100);
    test12(array2);     //假设这块内存的地址为0x100
    free(array2);

    /**这里是无效的，空指针怎么能够直接设置值了*/
    char *array3 = NULL;
    test12(array3);     //内存地址为0


    char *array4 = NULL;
    test13(array4);
    /**
     * 调用完函数test13后，array4仍然为NULL，
     * 因为实参的值不会以形参的值改变而改变
     */
    free(array4);

    /**有效：通过二级指针间接修改array5的值*/
    char *array5 = NULL;
    test14(&array5);
    free(array5);
}




