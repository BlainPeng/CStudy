#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void func1() {

    int a = 0;
    /**
     * 定义了一个指针变量，名字叫p，类型是int *
     * int * 代表可以存放一个int类型的地址编号
     * 变量p的值就是a的地址
     */
    int *p = &a;
    /**无类型指针可以指向任意类型的地址*/
    void *p2 = &a;

    char b = 0;
    register int c = 0;
//    p = &b; p只能指向int类型的地址，类型不兼容
//    p = &c; 寄存器变量没有内存地址
//    p = 20; 20是一个int常量，但不是一个地址
    /**通过指针变量来访问a的值*/
    printf("a = %d \n", *p);
    /**通过指针变量来改变a的值*/
    *p = 100;
    printf("a = %d \n", *p);
    /**指针变量初始化，不然会变成野指针*/
    long long *p3 = NULL;
    /**
     * 相同系统下，不管是何种类型的指针，在内存中的大小都是一样的
     * 如64位系统：8个byte，32位系统：4个byte
     */
    printf("%lu,%lu,%lu", sizeof(p), sizeof(p2), sizeof(p3));
}

void func2() {

    int a = 100;
    int b = 20;
    /**
     * 常量指针
     * 定义一个指向常量的指针，那么就不能够修改这个指针反对应的地址值，只能读，因为值是个常量了
     * 不过可以修改这个指针所指向的地址嘛
     */
    const int *p = &a;
//    *p = 10;  这样写是不行的
    p = &b;
    /**
     * 指针常量
     * 一旦初始化之后内容不可改变，因为这个指针指向的地址已经被固定了,
     * 不过可以修改这个地址的值嘛
     */
    int *const p2 = &b;
//    p2 = &a;  这样写是不行的
    *p2 = 30;
}

void func3() {

    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    /**数组名是a，a是第一个元素的地址常量：&a[0]*/
    int *p = a;
    /**指针变量指向了数组的首地址，这个时候指针变量可以当数组名使用了*/
    *p = 100;  //这里其实就相当于p[0] = 100
//    a = 100;  这是不行的，因为a是一个地址常量，不能做赋值动作
    /**
     * p重新指向了数组中的第6个位置，所以此时这个位置相对来说就变成了首地址
     * 若此时改变这个位置之后的其他位置的值，都是以这个位置为基础的
     */
    p = &a[6];
    p[0] = 90;  // a[6]的值由7 --> 90
    p[2] = 0;   // 此时改变的值若是相对于整个数组来说的话应该是a[8] 9-->0
    int i;
    for (i = 0; i < sizeof(a) / sizeof(int); i++) {

        printf("%d \n", a[i]);
    }
}

void func4() {

    /**
     * 指针的运算是指所代表的类型在内存中一个单位所占内存空间大小的移动
     */
    int a = 0;
    int *p = &a;
    printf("%p,\t%p \n", p, p + 1);     // 0x7fff5f40277c,	0x7fff5f402780
    short b = 0;
    short *p1 = &b;
    printf("%p,\t%p \n", p1, p1 + 1);   // 0x7fff5f40276e,	0x7fff5f402770
    char c = 0;
    char *p2 = &c;
    printf("%p,\t%p \n", p2, p2 + 1);   // 0x7fff5f40275f,	0x7fff5f402760
    long long d = 0;
    long long *p3 = &d;
    printf("%zu \n", sizeof(d));        // %zu无符号输出
    printf("%p,\t%p \n", p3, p3 + 1);   // 0x7fff5f402748,	0x7fff5f402750


    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *p4 = array;
    *(p4 + 2) = 0;      // 3 --> 0
    p4++;               // 这里相当于 p4 = &a[1]
    *(p4 + 2) = 100;    // 4 -->100
    p4 += 2;            // 这里相当于 p4 = &a[3]
    *(p4 + 2) = 1000;   // 6 -->1000
    p4 = array + 3;     // 这里是给指针重新赋值，相当于前面的运算都不起作用了 p4 = &a[3]
    p4[0] = 10000;      // 100 -->10000

    int i;
    for (i = 0; i < sizeof(array) / sizeof(int); i++) {
        printf("array[%d] = %d \n", i, array[i]);
    }
}

void func5() {

    /**
     * 指针数组
     */
    int a[10];          // 定义了一个int型的数组，数组成员都是int类型
    int *a1[10];        // 定义了一个int *类型的数组，数组成员都是int *类型
//    a1 = NULL;        这肯定是不行的，a1是数组名，是一个常量，不能做赋值动作
    a1[0] = NULL;
    a1[1] = a;
    a1[2] = &a[2];

    /**
     * 多级指针
     *
     * *p1是什么？
     * *p2是什么？
     * p2是什么？
     *
     * p是b的地址
     * *p就是b的值
     * p1是p的地址
     * *p1是p的值，而p是b的地址
     * p2是p1的地址
     * *p2就是p1的值，而p1是p的地址
     * 详细分析见图
     */
    int b = 10;
    int *p = &b;
    printf("p = %p\n", p);
    int **p1 = &p;
    int ***p2 = &p1;

}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

void func6() {

    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    /** *p的类型int，而数组a的成员也是int，所以可以做这种指向*/
    int *p = a;
    int *b[10] = {0};
    /** 数组b的成员是int * 类型，而*p是int类型，所以不可以做这种指向*/
//    p = b;
    /** *p1是int *类型，而数组b的成员也是int *类型，所以这样是可以的，p1是二级指针，指向一级指针数组b首元素的地址*/
    int **p1 = b;
    p1[0] = p;
    p1[0][2] = 10;

    int **c[10];    // 二级指针数组
    /**数组c中的成员都是int **类型，*p2也是int **类型，p2是三级指针，指向二级指针数组c中首元素的地址*/
    int ***p2 = c;
    p2[0] = b;
    p2[0][0][7] = 100;

    int i;
    for (i = 0; i < sizeof(a) / sizeof(int); i++) {

        printf("a[%d] = %d\n", i, a[i]);
    }

}

/**
 * 改变形参并不会对实参有影响，若要改变形参的同时，实参也要发生变化的话，可以传地址
 * @param a
 * @param b
 */
void func7(int *a, int *b) {

    int temp = *a;
    *a = *b;
    *b = temp;

}

/**
 * 对于形参是数组的情况，我们一般是写成一个指针，但由于像int类型的数组，我们并不知道他的长度，所以会
 * 将这个数组的长度一并传过来，有时，若想这个数组不被改变，形参还可以加一个const，但在C语言中并不能
 * 保证这个值是不可以被修改的，只是从语法上来看是不可以被修改的
 * @param a
 * @param len
 */
void func8(const int *a, int len) {

    //但我们可以间接的来改变
    int *p = (int *) a;

    int i;
    for (i = 0; i < len; i++) {

//        a[i] = i; 这里是不可以直接被改变的，除非去掉const关键字
        p[i] = i;

    }
}

/**
 * 实现在字符串中查找字符功能
 * @param p
 * @param c
 * @return  一个指针
 */
char *func9(char *p, char c) {

    int len = 0;
    while (p[len]) {
        if (p[len] == c) {
            return &p[len];
        }
        len++;
    }
    return NULL;
}

void func10() {

    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    void *p = a;
    /**将指定的一块内存全部清空为0*/
    memset(p, 0, sizeof(a));
    int i;
    for (i = 0; i < sizeof(a) / sizeof(int); ++i) {
        printf("%d\n", a[i]);
    }
    char b[] = "HelloWorld";
    char c[11] = {0};
    char d[11] = {0};
    /**内存拷贝，在使用memcpy时，一定要确保内存没有重叠区域，详见说明图*/
    memcpy(c, b, strlen(b));
    printf("c = %s\n", c);
    /**移动内存数据*/
    memmove(d, b, strlen(b));
    printf("d = %s\n", c);
}


void swap(char *a, char *b) {

    char temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * 字符串逆置
 * @param p
 */
void func11(char *p) {

    /**step 1 先获取字符串的长度*/
    int len = 0;
    while (p[len]) {
        len++;
    }
    /**step 2 记录字符串的首尾字符*/
    char *start = p;
    char *end = p + len - 1;
    /**step 3 首尾字符不停交换*/
    while (start < end) {

        swap(start, end);
        start++;
        end--;
    }

}

/**
 * 指针类型不同内存拷贝的几个例子
 */
void func12() {

    int a = 0x12345678;
    int *p = &a;
    printf("%x\n", *p);
    char *p1 = (char *) &a;
    /**
     * 这里打印结果为：78，原因分析见图
     */
    printf("%x\n", *p1);

    int a1[10] = {0};
    char a2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//    memcpy(a1, a2, sizeof(a2));
    int i;
    /**
     * 为了正确的拷贝值，我们可以这样做
     */
    for (i = 0; i < 10; ++i) {

        a1[i] = a2[i];
    }

    for (i = 0; i < 10; ++i) {

        /**
         * 若是使用memcpy的话，a1的结果：
         *  a1[0] = 4030201     实际这里是:  04030201
         *  a1[1] = 8070605                08070605
         *  a1[2] = a09                    00000a09
         *  a1[3] = 0
         *  a1[4] = 0
         *  a1[5] = 0
         *  a1[6] = 0
         *  a1[7] = 0
         *  a1[8] = 0
         *  a1[9] = 0
         *
         *  原因分析见图
         */
        printf("a1[%d] = %x \n", i, a1[i]);
    }
}

void test(char **p, int len) {

    int i;
    for (i = 0; i < len; ++i) {

        printf("%s \n", p[i]);
    }


}

void func13() {

    char *s[10] = {0};
    char a1[] = "hello";
    char a2[] = "world";
    char a3[] = "abc";
    char a4[] = "123456";
    char a5[] = "哈哈";
    s[0] = a1;
    s[1] = a2;
    s[2] = a3;
    s[3] = a4;
    s[4] = a5;
    test(s, 5);
}


#pragma clang diagnostic pop

int main1() {

//    func6();

//    int a = 10;
//    int b = 20;
//    func7(&a, &b);
//    printf("a = %d \t b = %d \n", a, b);

//    int a[] = {78, 67, 90, 34, 91, 23, 45, 76, 43, 61};
//    func8(a, sizeof(a) / sizeof(int));
//    int i;
//    for (i = 0; i < sizeof(a) / sizeof(int); ++i) {
//        printf("%d \n", a[i]);
//    }

//    char a[] = "Hello World!";
//    char *result = func9(a, '!');
//    if (result == NULL) {
//        printf("not found\n");
//    } else {
//        printf("%s\n", result);
//    }

//    func10();

//    char a[] = "Hello World!";
//    func11(a);
//    printf("%s", a);

//    func12();
    func13();

    return 0;
}

/**
 * main函数是操作系统调用的；
 * main函数的参数是操作系统填写的
 * 可执行程序名本身就是一个参数，是第一个参数
 * @param argc  命令行有几个参数
 * @param args  每个参数组成一个char *类型的数组
 * @return
 */
int main2(int argc, char **args) {

    int i;
    for (i = 0; i < argc; ++i) {
        printf("%s\n", args[i]);
    }
    return 0;
}

/**
 * main函数实现两个整数相加
 * @param argc
 * @param args
 * @return
 */
int main3(int argc, char **args) {

    if (argc < 3) {
        printf("usage:%s num1 num 2\n", args[0]);
        return 0;
    }
    /**
     * 假若要取出在命令行输入的字符串中的某个字符，需要这样取
     * args[n][n]
     */
    printf("%d\n", atoi(args[1]) + atoi(args[2]));
    return 0;
}

int main() {
    /**
     * IPV4的地址其实都是一个unsigned int
     */
    unsigned int a = 23456789;
    unsigned char *s = (unsigned char *) (char *) &a;
    printf("%x\n", a);                                  // 165ec15
    /**
     * 所有的数据类型，都是一个char的数组
     * s[3] ~ s[0]是小端对齐
     * 上面的十进制数165ec15变成十进制
     * 1    - > 1,
     * 65   - > 102
     * ec   - > 234
     * 15   - > 21
     */
    printf("%d.%d.%d.%d\n", s[3], s[2], s[1], s[0]);    // 1.101.236.21
    return 0;
}