/********************************************
* c11exponent.c                              *
* Created by lugf027 on 2020/5/2.            *
* Github: https://github.com/lugf027         *
*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "c11exponent.h"

long initC11ByInput() {
    long a; // 正整数
    long fq; // 域
    long g; // 域元素

    printf("please input integer in sequence: a(Positive) Fq(Field) g(Field element)\n");
    char aStr[10], fqStr[10], gStr[10];
    scanf("%s %s %s", aStr, fqStr, gStr);
    a = strtol(aStr, NULL, 10);
    fq = strtol(fqStr, NULL, 10);
    g = strtol(gStr, NULL, 10);

    if (!(a > 0 && fq > 0 && g > 0)) {
        printf("input invalid!");
        return -1;
    }
    printf("((long long)pow(g:%ld, a:%ld)) mod fq:%ld = %lld\n", g, a, fq, ((long long)pow(g, a)) %fq);
    return convertE(a, fq, g);
}

long convertE(long a, long fq, long g) {
    long ga; // 结果
    char *eBin; // e=(a mod (q-1))的二进制表示
    // a) 置e=a mod(q-1)，若e=0，则输出1；
    long e = a % (fq - 1);
    if (e == 0)
        ga = 1;
    else {
        // b) 设e的二进制表示是er er-1 ... e1 e0 ，其最高位er 为1；
        char buffer[33];
        int base = 2;
        eBin = ltoa(e, buffer, base);

        printf("countGAHere with\tbin(a mod(q-1)):%s binLen:%lld\n\n", eBin, strlen(eBin));
        // c) 置x=g
        ga = g;
        printf("initGA\tga = g = %ld\n", g);

        //d) 对 i 从r-1降至0执行：
        //d.1) 置x=x*x ；
        //d.2) 若ei =1，则置x=g*x；
        int binLen = (int)strlen(eBin);
        for (int i = 1; i < binLen; i++) {
            printf("e%d:%c\t(ga:%ld*ga:%ld) mod fq:%ld = ", binLen-1-i, eBin[i], ga, ga, fq);
            ga = ga * ga % fq;
            printf("%ld\n", ga);
            if (eBin[i] == '1') {
                printf("\t\t(g:%ld*ga:%ld) mod fq:%ld = ", g, ga, fq);
                ga = g * ga % fq;
                printf("%ld\n", ga);
            }
        }
    }
    // e) 输出x
    printf("Result:\t%ld\n\n", ga);
    return ga;
}

long handleC11() {
    return initC11ByInput();
}

long handleC11WithDate(long a, long fq, long g){
    return convertE(a, fq, g);
}
