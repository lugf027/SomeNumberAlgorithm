/********************************************
* c13Lucas.c                              *
* Created by lugf027 on 2020/5/2.            *
* Github: https://github.com/lugf027        *
*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c13Lucas.h"
#include "util.h"

void initC13ByInput() {
    long q;     // 奇素数
    long x, y;  // 整数x&y
    long k;     // 正整数k

    printf("please 输入：奇素数q，整数X和Y，正整数k(like '7 1 2 3' without \"'\")\n");
    char qStr[10], xStr[10], yStr[10], kStr[10];
    scanf("%s %s %s %s", qStr, xStr, yStr, kStr);

    if (judgeCharListIsAllNum(qStr) && judgeCharListIsAllNum(xStr) && judgeCharListIsAllNum(yStr) &&
        judgeCharListIsAllNum(kStr)) {
        q = strtol(qStr, NULL, 10);
        x = strtol(xStr, NULL, 10);
        y = strtol(yStr, NULL, 10);
        k = strtol(kStr, NULL, 10);
        countRet(q, x, y, k, NULL);
    } else {
        printf("input invalid!\n\n");
    }
}

void countRet(long q, long x, long y, long k, long ret[2]) {
    // 生成式
    long us[k + 1], vs[k + 1];
    us[0] = 0, us[1] = 1;
    vs[0] = 2, vs[1] = x;
    for (long i = 2; i <= k; i++) {
        us[i] = x * us[i - 1] - y * us[i - 2];
        vs[i] = x * vs[i - 1] - y * vs[i - 2];
    }
    printf("u[%ld]:%ld\tv[%ld]:%ld\n", k, us[k] % q, k, vs[k] % q);


    long u, v; // result
    // a) 置∆=X*X - 4Y
    long tmp = x * x - 4 * y;
    printf("∆ = X*X - 4Y = %ld\t\t", tmp);
    // b) k二进制kBin -> Kr Kr-1 ... K1 K0
    char buffer[33];
    int base = 2;
    char *kBin = lltoa(k, buffer, base);
    printf("kBin = %s\n", kBin);
    // c) 置U=1，V= X；
    u = 1, v = x;
    // d) 对i从r-1降至0执行：
    // d.1) 置(U,V)=( (U·V)mod q, ((V*V +∆·U*U )/2) mod q )；
    // d.2) 若k i = 1，则置(U,V)=( ((X·U+V)/2)mod q, ((X·V +∆·U)/2)mod q ) ；
    int kBinLen = (int) strlen(kBin);
    printf("\nr-1 = %d\n", (kBinLen - 1) - 1);
    for (int i = 1; i < kBinLen; i++) {
        printf("k%d:%c\t((U·V) mod q, ((V·V +∆·U*U )/2) mod q) = ", kBinLen - 1 - i, kBin[i]);
        long tmpU = u;
        u = u * v % q;
        v = (v * v + tmp * tmpU * tmpU) / 2 % q;
        printf("(U:%ld, V:%ld)\n", u, v);
        if (kBin[i] == '1') {
            tmpU = u;
            printf("\t\t((X·U+V)/2) mod q, ((X·V +∆·U)/2) mod q) = ");
            u = (x * u + v) / 2 % q;
            v = (x * v + tmp * tmpU) / 2 % q;
            printf("(U:%ld, V:%ld)\n", u, v);
        }
    }
//    if (u < 0) u += q;
//    if (v < 0) v += q;
    printf("Result\tU:%ld\tV:%ld\n\n", u, v);

    if (ret != NULL) {
        ret[0] = u;
        ret[1] = v;
    }
}

void handleC13() {
    initC13ByInput();
//    clearC13BeforeBack();
}

void handleC13WithData(long q, long x, long y, long k, long ret[2]) {
    countRet(q, x, y, k, ret);
}
