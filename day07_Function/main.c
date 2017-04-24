#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * 获取字符串的长度
 */
void getStringLen() {

    char a[100] = {0};
    /**
     * 获取从键盘中输入的内容
     * scanf    该函数具有内存溢出的风险，且遇到空格和回车就结束
     * gets     该函数具有内存溢出的风险，遇到空格会当成字符，而遇到回车就结束  deprecated了
     * fgets    该函数的第一个参数只能是一个char的数组，且不能获取到整数值，但scanf可以；
     *          然后在接受用户输入的时候，会把最后的回车也放到字符串里面去，scanf和gets不会
     */
    fgets(a, sizeof(a), stdin);
    int len = 0;
    while (a[len]) {
        //干掉回车符
        if (a[len] == '\n') {
            a[len] = '\0';
            break;
        }
        len++;
    }
    printf("%d \n", len);
    //调用系统库函数
    printf("%d", (int) strlen(a));

}

/**
 * 将键盘中第二次输入的内容追加到第一次
 */
void test1() {

    char a[100] = {0};
    char b[100] = {0};
    char c[100] = {0};
    fgets(a, sizeof(a), stdin);
    fgets(b, sizeof(b), stdin);
    int len = 0;
    while (a[len]) {
        //干掉回车符
        if (a[len] == '\n') {
            a[len] = '\0';
            break;
        }
        len++;
    }
    strcat(a, b);
    strncat(c, b, 1);
    printf("a = %s", a);
    printf("c = %s \n", c);
    printf("len = %zu", strlen(a));

}

void stringOperation() {

    char a[] = "Hello";
    char b[] = "Hello123";
    /**比较两个字符串是否相等*/
    if (strcmp(a, b) == 0) {
        printf("相等\n");
    } else {
        printf("不相等\n");
    }
    /**比较两个字符串指定内容是否相等*/
    if (strncmp(a, b, 5)) {
        printf("指定内容相等\n");
    } else {
        printf("指定内容相等\n");
    }
    /**复制字符串*/
    char c[100] = {0};
    strcpy(c, b);
    printf("%s\n", c);
    /**复制指定内容*/
    char d[100] = {0};
    strncpy(d, b, 5);
    printf("%s\n", d);
    /**将格式化的数据写入字符串*/
    char e[100] = {0};
    int n = 10;
    sprintf(e, "%d", n);
    printf("%s\n", e);
    /**在字符串中查找字符*/
    char *p = strchr(a, 'l');
    if (p == NULL) {
        printf("not found");
    } else {
        printf("%s\n", p);
    }
    /**在字符串中查找子字符串*/
    char *p1 = strstr(b, "l12");
    if (p1 == NULL) {
        printf("not found \n");
    } else {
        printf("%s\n", p1);
    }
    /**分割字符串*/
    char f[] = "acb_123_aaaa_zzzz_adasdfa";
    char *p2 = strtok(f, "_");
    while (p2 != NULL) {
        printf("%s\n", p2);
        p2 = strtok(NULL, "_");
    }
    /**字符串转int*/
    char g[] = "100";
    printf("%d \n", atoi(g));
}

/**
 * 一个字符串：char a[100] = "345运算符12=";
 * 写一个程序，先算出结果并把结果追加到原字符串后面
 */
void test2() {

    char a[100] = "345+12=";
    /**step 1 先按字符串规则提取字符串元素*/
    int n1 = 0, n2 = 0;
    char op = 0;
    sscanf(a, "%d%c%d=", &n1, &op, &n2);
    /**step 2 根据操作符进行运算*/
    int ret = 0;
    switch (op) {

        case '+':
            ret = n1 + n2;
            break;
        case '-':
            ret = n1 - n2;
            break;
        case '*':
            ret = n1 * n2;
            break;
        case '/':
            ret = n1 / n2;
            break;
        default:
            ret = 0;
    }
    /**step 3 将计算结果按格式写入字符串中*/
    char b[100] = {0};
    sprintf(b, "%d", ret);
    /**追加到原字符串中*/
    strcat(a, b);
    printf("%s\n", a);
}

/**
 * 一个字符串：char a[] = "23+5=;45*2=;8-2=;12-5=";
 * 写一个程序，先算出结果并把结果追加到原字符串后面
 */
void test3() {

    char a[] = "23+5=;45*2=;8-2=;12-5=";
    char result[100] = {0};
    // step1 分割字符串
    char *p = strtok(a, ";");
    while (p != NULL) {
        // step 2 提取子字符串中的元素记录变量中
        int v1 = 0;
        char op = 0;
        int v2 = 0;
        sscanf(p, "%d%c%d=", &v1, &op, &v2);
        // step 3 计算
        int ret = 0;
        switch (op) {

            case '+':
                ret = v1 + v2;
                break;
            case '-':
                ret = v1 - v2;
                break;
            case '*':
                ret = v1 * v2;
                break;
            case '/':
                ret = v1 / v2;
                break;
            default:
                ret = 0;
        }
        // step 4 按格式将表达式和结果写到字符串中
        char temp[1000] = {0};
        sprintf(temp, "%d%c%d=%d;", v1, op, v2, ret);
        // step 5 将每个表达式追加到一个字符串中
        strcat(result, temp);
        p = strtok(NULL, ";");
    }
    printf("%s \n", result);
}

/**
 * 获取一个整数的位数
 * @param num
 * @return
 */
int getNumLen(int num) {

    int len = 0;
    while (num) {

        num /= 10;
        len++;
    }
    return len;
}

/**
 * 获取10的n次幂
 * @param num
 * @return
 */
int powerOfTen(int num) {

    /**10的0次幂为1*/
    if (num == 0)
        return 1;
    int base = 10;
    int i;
    for (i = 1; i < num; i++) {

        base *= 10;
    }
    return base;
}

/**
 * 输入一个整数，输出时将这个整数逆置 如123 -> 321
 */
void test4(int num) {

    /**step 1 获取这个整数的位数*/
    int len = getNumLen(num);
    /**
     * step 2 根据这个长度来计算每一位需扩大的倍数
     * 如：  个位：10的len-1次幂
     *      十位：10的len-2次幂
     *      百位：10的len-3次幂
     *      ...
     */
    int result = 0;
    int i;
    for (i = 1; i <= len; i++) {

        /**step 3 获取整数的每一位数*/
        int n = num % 10;
        /**step 4 根据这个位置数来计算扩大几倍*/
        int l = powerOfTen(len - i);
        /**step 5 将结果累加*/
        result += n * l;
        /**step 6 将原数位数减少一位*/
        num /= 10;
    }
    printf("%d \n", result);

}

/**
 * 递归问题
 */
int test5(int index) {

    /**
     * 有n个人排成一队，问第n个人多少岁，他回答比前面一个人大2岁，
     * 再问前页一个人多少岁，他回答比前面一个人大2岁，一直问到最后，
     * 问第一个人，他回答10岁
     */
    int age;
    if (index == 1) {

        //说明是第一个人
        age = 10;

    } else {

        age = test5(index - 1) + 2;
    }
    printf("age = %d \n", age);
    return age;

}

/**
 * 将十进制数转化成二进制
 * @param num
 */
void test6(unsigned int num) {

    /**获取一个数的二进制，只需要获取它的余数是0或还是就可以了*/
    int ret = num % 2;
    if (num >= 2)
        test6(num / 2);
    printf("%d", ret);
}


int main() {

//    getStringLen();
//    test1();
//    stringOperation();
//    test2();
//    test3();
    int num;
    scanf("%d", &num);
//    test4(num);
//    test5(num);
    test6(num);
    return 0;
}