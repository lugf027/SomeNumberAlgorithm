/********************************************
* c14square.c                              *
* Created by lugf027 on 2020/5/2.            *
* Github: https://github.com/lugf027        *
*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "c14square.h"
#include "c11exponent.h"
#include "c13Lucas.h"

void initC14ByInput(int type) {
    char qStr[10], gStr[10];
    printf("输入 ：奇素数q，整数g, 0<g<q");
    scanf("%s %s", qStr, gStr);
    long q = strtol(qStr, NULL, 10);
    long g = strtol(gStr, NULL, 10);
    if (!(q > 0 && g > 0)) {
        printf("input invalid!");
        return;
    } else if (g == 0) {
        printf("y: 0"); // 若g=0，则只有一个平方根，即y=0；
        return;
    }

    if (type == 1) {
        method1(q, g);
    } else if (type == 2) {
        method2(q, g);
    } else if (type == 3) {
        method3(q, g);
    }
}

/**
 * 算法1：对q≡3 (mod 4)，即存在正整数u，使得q=4u+3。
 * q mod 4 = 3 mod 4;
 * => q = 4*u + 3;
 * => u = (q-3)/4 = q/4 (in c language)
 */
void method1(long q, long g) {
    //a) 计算y = g的u+1次方 mod q(参见附录C.1.1)；
    //b) 计算z = y 2 mod q；
    //c) 若z=g，则输出 y ；否则输出“不存在平方根”。
    long u = q / 4;
    long y = handleC11WithDate(u + 1, q, g);
    long z = y * y % q;
    if (z == g) {
        printf("y:%ld", y);
    } else {
        printf("不存在平方根");
    }
}

// 算法2：对q≡5 (mod 8)，即存在正整数u，使得q=8u+5。
void method2(long q, long g) {
    //a) 计算z = g的2u+1次方 mod q(参见附录C.1.1)；
    //b) 若z ≡1 (mod q)，计算y = g u+1 mod q，输出y，终止算法；
    //c) 若z ≡ -1 (mod q)，计算y = (2g· (4g)的u次方 ) mod q，输出y，终止算法；
    //d) 输出“不存在平方根”
    long u = q / 8;
    long z = handleC11WithDate(u + u + 1, q, g);
    if (z % q == -1 % q) {
        long tmpY1 = handleC11WithDate(u, q, 4 * g);
        long tmpY2 = (g + g) % q;
        long y = (tmpY1 + tmpY2) % q;
        printf("y:%ld", y);
    } else {
        printf("不存在平方根");
    }
}

// 算法3 ：对q≡1 (mod 8)，即存在正整数u，使得q=8u+1。
void method3(long q, long g) {
    //a) 置Y= g；
    //b) 生成随机数X，0 < X < q；
    //c) 计算Lucas序列元素(见附录C.1.3)：U=U 4u+1 mod q，V=V 4u+1 mod q；
    //d) 若V*V mod q = 4Y mod q，则输出 y = (V/2) mod q，并终止；
    //e) 若U mod q != 1且U mod q != q - 1，则输出“不存在平方根”，并终止；
    //f) 返回步骤b)。
    long u = q / 8;
    long Y = g;
    while (1) {
        srand((int) time(NULL));
        int X = rand() % (int) q;
        printf("random X:\t%d\n", X);
        long uAndV[2];
        handleC13WithData(q, X, Y, 4 * u + 1, uAndV);
        printf("u:%ld\tv:%ld\n", uAndV[0], uAndV[1]);

        if (uAndV[1] * uAndV[1] % q == 4 * Y % q) {
            long y = uAndV[1] / 2 % q;
            printf("y:%ld", y);
            return;
        } else if (uAndV[0] % q != 1 && uAndV[0] % q != q - 1) {
            printf("不存在平方根");
            return;
        }
    }
}

void handleC14(int type) {
    initC14ByInput(type);
//    clearC14BeforeBack();
}
