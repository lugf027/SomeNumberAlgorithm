#include <string.h>

#include "util.h"

int judgeCharListIsAllNum(char *chars){
    int len = (int)strlen(chars);
    for(int i = 0; i<len; i++){
        if(chars[i] < '0' || chars[i] > '9'){
            return 0;
        }
    }
    return len; // so return 0 when strLen is 0
}
