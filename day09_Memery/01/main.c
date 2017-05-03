#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


void note1() {

    /**a和a1都是一个数组，有4个成员，初始化第一个是字符a，最后一个是字符'\n'*/
    char a[4] = {'a', 'b', 'c', '\0'};
    char a1[] = "abc";
    /**定义了一个常量指针变量，指向常量abc的地址，abc存在于常量区*/
    const char *p = "abc";
    a[0] = 'd';/**可以改变数组下标0成员的值*/
//    p[0] = 'd'; /**p指向了一个常量，常量的值是不可改变的*/
}

/**
 * 把一个int的每个字节单独设置成一个值
 */

void study1() {

    unsigned int a = 0;
    unsigned char *p = (unsigned char *) &a;
    p[0] = 1;
    p[1] = 2;
    p[2] = 3;
    p[3] = 4;
    /**打印结果：04030201  小端对齐*/
    printf("%08x\n", a);    // 08指定数据的最小输出位数为8，若不够8位，则补零，若大于8位，则按照原位数输出；
}

/**全局变量，作用域是整个文件*/
int a = 10;
/**
 * 使用外部文件的变量或函数时，需要使用extern关键字来进行声明
 */
extern int abc;

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

void test1(int n) {

    /**
     * 这里若是去掉这个条件的话，这个递归会导致程序崩溃；
     * 原因是栈的大小受到操作系统的限制，一般是k为单位的，
     * 如果超出了栈最大限制，栈就会溢出，那么程序就会崩溃。
     *
     * 64位ubuntu下，默认栈大小是132k，不是所有的系统栈大
     * 小都是一样，不过至少单位是k
     */
    if (n > 10)
        test1(n + 1);
}

void test2() {

    int a = 0;
    /**栈里面的一个指针变量p指向了一个变量a的地址*/
    int *p = &a;
    *p = 10;
    printf("%d\n", a);
    /**在堆内存中分配了4个字节的空间*/
    p = malloc(sizeof(int));
    /**通过指针p间接的访问这块用malloc分配的堆内存*/
    *p = 100;
    printf("%d\n", *p);
    free(p);
}

void modify(char *s) {

    s[0] = 'a';
}

void test3() {

    /**
     * calloc与malloc类似，负责在堆中分配内存
     * malloc只分配，但不负责清理内存；
     * calloc分配内存的同时把内存清空
     */
    char *p = calloc(100, sizeof(char));
    strcpy(p, "Hello World");
    modify(p);
    printf("%s \n", p);
    free(p);
}

void test4(char *p) {

    p = calloc(100, sizeof(char));
    strcpy(p, "Hello World");
    p[0] = 'a';
}

void test5(char **s) {

    *s = calloc(100, sizeof(char));
    strcpy(*s, "Hello World");
    (*s)[0] = 'a';

}

void test6() {

    char *p = calloc(100, sizeof(char));
    *p = 'a';
    p++;
    *p = 'b';
    p++;
    *p = 'c';
    /**
     * 在释放指针之前，需确保指针的开始位置
     * 当两个p++后，相当于p+=2，指针指向的位
     * 置已经向下偏移了2个char，若此时去释放
     * 这个指针，会从这个最新的位置开始释放，
     * 所以会导致多释放2个char并未被申请
     * 的内存，从而程序崩溃，所以，必须
     * 把指针归位
     */
    p -= 2;
    free(p);

}

void test7() {

    char *p = malloc(100);
    /**在已有的堆内存基础上增加内存100*/
    char *p1 = realloc(p, 200);
    if (p == p1) {
        printf("相同内存基础上扩展\n");
    } else {
        printf("重新分配\n");
    }
    /**不要free p 因为realloc自动维护了p的空间,详见realloc.png*/
    free(p1);
}

/**
 * 动态分配堆内存
 * 详细见图：dinamic_memory.png
 */
void test8() {

    /**
     * step 1 定义一个指针来保存用户输入信息
     * 这个为什么不用char p [][]？因为二维数
     * 组的长度我们并不能确定，所以可以用一个指
     * 针，p相当于指向了 char *a[]的一个数组
     */
    char **p = NULL;
    int index = 0;
    while (1) {

        /**step 2 定义临时变量记录用户每次输入的内容*/
        char temp[2048] = {0};
        scanf("%s", temp);
        /**step 3 添加退出死循环条件*/
        if (strcmp(temp, "exit") == 0)
            break;
        /**step 4 申请一块堆内存，并保存栈内变量的内容*/
        char *name = calloc(sizeof(temp) + 1, sizeof(char));
        strcpy(name, temp);
        /**step 5 动态申请保存每次输入内容的堆内存地址*/
        p = realloc(p, sizeof(char *) * (index + 1));
        p[index] = name;
        index++;
    }

    int i;
    for (i = 0; i < index; i++) {

        printf("%s\n", p[i]);
    }

    for (i = 0; i < index; i++) {

        /**先释放数组成员指向的堆内存*/
        free(p[i]);
    }

    /**再释放堆中的char *数组*/
    free(p);

}

void test9(char *s) {

    s[0] = 'a';
}

void test10(char *s) {

    s = calloc(100, sizeof(char));
    strcpy(s, "Hello World");
    s[0] = 'a';
}

void test11(char **s) {

    *s = calloc(100, sizeof(char));
    strcpy(*s, "Hello World");
    (*s)[0] = 'a';
}

char *test12() {

    char a[] = "Hello World";
    return a;
}


int main() {


//    note1();

//    study1();

//    for (int i = 0; i < 10; ++i) {
//        test();
//    }

//    printf("%d", abc);

//    test2();
//    test3();


    /**
     * 将p传入到函数test4中，虽然在test4函数中给p申请了内存并赋了值，
     * 但那只改变了形参，对实参没有影响，除非如函数test5那样，详见图
     * args_heap.png
     */
//    char *p = NULL;
//    test4(p);
//    printf("%s\n", p);
//    char *p1 = NULL;
//    test5(&p1);
//    printf("%s\n", p1);
//    free(p1);

//    test6();
//    test7();
//    test8();

//    char *p = calloc(100, sizeof(char));
//    strcpy(p, "Hello World");
//    test9(p);
//    printf("%s\n", p);//这里是可以修改成功的
//    free(p);

    /**
     * 调用函数test10后，p仍然是NULL，因为在函数中给形参变量重新
     * 申请内存空间，但是当函数结束后，这块内存空间就不存在了，所以
     * 实参还是没有成功的申请内存空间，要想成功的话，请看函数test11
     */
//    char *p = NULL;
////    test10(p);
//    test11(&p);
//    printf("%s\n", p);
//    free(p);

    /**函数test12结束后，内容清空，返回回来无意义*/
    char *p = test12();
    printf("%s\n", p);


    return 0;
}