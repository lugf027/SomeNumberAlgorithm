#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c11exponent.h"
#include "util.h"

long initC11ByInput() {
    long a; // 正整数
    long fq; // 域
    long g; // 域元素

    printf("please input: a q g\n");
    char aStr[10], fqStr[10], gStr[10];
    scanf("%s %s %s", aStr, fqStr, gStr);

    if(judgeCharListIsAllNum(aStr) && judgeCharListIsAllNum(fqStr) && judgeCharListIsAllNum(gStr)){
        a = strtol(aStr, NULL, 10);
        fq = strtol(fqStr, NULL, 10);
        g = strtol(gStr, NULL, 10);

        return convertE(a, fq, g);
    }else{
        printf("input invalid!\n\n");
        return -1;
    }
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

        // c) 置x=g
        ga = g;

        //d) 对 i 从r-1降至0执行：
        //d.1) 置x=x*x ；
        //d.2) 若ei =1，则置x=g*x；
        int binLen = (int)strlen(eBin);
        for (int i = 1; i < binLen; i++) {
            ga = ga * ga % fq;
            if (eBin[i] == '1') {
                ga = g * ga % fq;
            }
        }
    }
    // e) 输出x
//    printf("Result:\t%ld\n", ga);
    return ga;
}

long handleC11() {
    return initC11ByInput();
}

long handleC11WithDate(long a, long fq, long g){
    return convertE(a, fq, g);
}
