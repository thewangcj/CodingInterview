#include <stdio.h>
#include <cstring>
#include <iostream>
#include <assert.h>
using namespace std;
//不考虑内存重叠
/*
2.为什么要返回char *？
返回dst的原始值使函数能够支持链式表达式。
链式表达式的形式如：
int l=strlen(strcpy(strA,strB));
又如：
char * strA=strcpy(new char[10],strB);
返回strSrc的原始值是错误的。
其一，源字符串肯定是已知的，返回它没有意义。
其二，不能支持形如第二例的表达式。
其三，把const char *作为char *返回，类型不符，编译报错。
*/
char *strcpy(char *dst, const char *src) //[1]
{
    assert(dst != NULL && src != NULL); //[2]

    char *ret = dst; //[3]

    while ((*dst++ = *src++) != '\0')
        ; //[4]

    return ret;
}
char *strcpy2(char *dst, const char *src)
{
    assert(dst != nullptr && src != nullptr);

    char *ret = dst;

    my_memcpy(dst, src, strlen(src) + 1);

    return ret;
}

char *my_memcpy(char *dst, const char *src, int cnt)
{
    assert(dst != NULL && src != NULL);

    char *ret = dst;

    if (dst >= src && dst <= src + cnt - 1) //内存重叠，从高地址开始复制
    {
        dst = dst + cnt - 1;
        src = src + cnt - 1;
        while (cnt--)
            *dst-- = *src--;
    }
    else //正常情况，从低地址开始复制
    {
        while (cnt--)
            *dst++ = *src++;
    }

    return ret;
}