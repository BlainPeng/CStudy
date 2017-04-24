//
//  main.c
//  C语言基础
//
//  Created by PengBaiLiang on 17/4/16.
//  Copyright © 2017年 PengBaiLiang. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *p1, int *p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void setValue(int *p, int len) {
    for (int i = 0; i < len; i++) {
        *(p + i) = i;
    }
}

void getSecondMax() {
    /*
     找出一个数组中第二大的数
     */
    int a[] = {3, 56, 34, 78, 45, 98, 32, 789, 453, 67};
    //  step 1 获取数组的长度
    int len = sizeof(a) / sizeof(a[0]);
    //  step 2 假设第一个和第二个元素为最大和第二大值
    int max, smax;
    if (a[0] > a[1]) {
        max = a[0];
        smax = a[1];
    } else {
        max = a[1];
        smax = a[0];
    }
    //  step 3 从第三个元素开始遍历数组
    int i;
    for (i = 2; i < len; i++) {
        if (max < a[i]) {
            //  step 4 遍历到的元素比初始最大值大的话，原先最大值需变成第二大值
            smax = max;
            //  step 5 最大值变为遍历到的元素
            max = a[i];
        } else if (max > a[i] && a[i] > smax) {
            // step 6 遍历到的元素比初始最大值小，比初始第二大值大的话，改变初始第二大值
            smax = a[i];
        }
    }
    printf("%d \n", smax);
}

void bubbleSort() {
    /*
     给一维数组进行冒泡排序
     */
    int a[] = {3, 56, 34, 78, 45, 98, 32, 789, 453, 67};
    //  step 1 获取数组的长度
    int len = sizeof(a) / sizeof(a[0]);
    //  step 2 遍历数组
    int i, j;
    for (i = 0; i < len; i++) {
        //  step 3 内循环控制比较次数,每比较完一次后会得出一个较大值，同时，比较的长度会依次减少
        for (j = 1; j < len - i; j++) {
            //  step 4 从小到大排序
            if (a[j] < a[j - 1]) {
                int temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
        }
    }
    // step 5 重新遍历获取排序后的数组
    for (i = 0; i < len; i++) {
        printf("%d \n", a[i]);
    }
}

void multiArray() {
    /*
     a是一个三维数组名；
     a[0]是一个二维数组的数组名；
     a[0][0]是一个一维数组的数组名；
     a[0][0][0]是一个int类型的变量
     */
    int a[2][3][4];
    printf("%lu,%lu,%lu,%lu \n", sizeof(a), sizeof(a[0]), sizeof(a[0][0]), sizeof(a[0][0][0])); //96,48,16,4

}

void charArray() {

    /*
     在C语言中，字符串的定义：内存中连续的char，最后以'\0'结尾；
     字符串一定是一个char数组，但char数组不一定是一个字符串
     */
    //char a[5] = {'a','b','c','d','e'};      //abcde`\366\277_\377 结果不正常
    //    printf("%s \n",a);
    char b[6] = {'a', 'b', 'c', 'd', 'e'};
    char c[10] = {'a', 'b', 'c', 'd', 'e'};
    char d[] = "abcde";
    printf("b_len=%lu,c_len=%lu,d_len=%lu \n", sizeof(b), sizeof(c), sizeof(d));

}

void stringCat() {

    /*
     将一个字符串的内容追加到另外一个字符串中
     */
    //方式一，自己实现
    //    char a[100] = {0};
    //    char b[100] = {0};
    //    //从键盘输入的内容分别输出到字符串a，b中
    //    scanf("%s",a);
    //    scanf("%s",b);
    //    int lenA = 0;
    //    int lenB = 0;
    //    //计算A的字符串长度
    //    while (a[lenA]) {
    //        lenA++;
    //    }
    //    //计算B的字符串长度
    //    while (b[lenB]) {
    //        //将b中的字符串添加到a
    //        a[lenA+lenB] = b[lenB];
    //        lenB++;
    //    }
    //    printf("%s",a);

    //方式二，使用系统库函数
    char c[100] = "Hello";
    char d[100] = "World!";
    char e[100] = {0};
    strcat(c, d);
    //只追加指定数量的字符
    strncat(e, d, 3);
    printf("%s \n", c);
    printf("%s \n", e);

}

void deleteBlankString() {

    /*
     去除字符串中末尾空字符串
     */
//    char a[100] = "Hello World";
//    printf("%s",a);

}

int main(int argc, const char *argv[]) {

    //    getSecondMax();
    //    bubbleSort();
    //    multiArray();
    //    charArray();
//    stringCat();
//    deleteBlankString();
    printf("Hello World");
    return 0;
}
