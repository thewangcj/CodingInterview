#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;

void *my_memcpy_byte(void *dst, const void *src, int n)
{
    if (dst == nullptr || src == nullptr || n <= 0)
        return nullptr;

    char *pdst = (char *)dst;
    char *psrc = (char *)src;

    if (pdst > psrc && pdst < psrc + n)
    {
        pdst = pdst + n - 1;
        psrc = psrc + n - 1;
        while (n--)
            *pdst-- = *psrc--;
    }
    else
    {
        while (n--)
            *pdst++ = *psrc++;
    }
    return dst;
}

void SWAP(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void testSrc(char *s)
{
    s[0] = 't';
}

char *my_memcpy1(char *dest, char *src, unsigned count)
{
    dest = (char *)malloc(count);
    char *res = dest;
    while (count--)
    {
        *dest++ = *src++;
    }

    return res;
}

char *test2()
{
    char a[] = {"hello world!"};
    char *str = NULL;
    str = (char *)malloc(20);
    strncpy(str, a, 20);
    return str;
}

int main()
{
    char src[] = "hello";
    char *dest = NULL;

    dest = my_memcpy1(dest, src, 5);
    //dest = test2();
    cout << "dest:" << dest[0] << endl;

    int a = 1;
    int b = 2;
    int *pa = &a;
    int *pb = &b;
    SWAP(pa, pb);
    cout << "a :" << a << endl;

    testSrc(src);
    cout << "testSrc:" << src[0] << endl;
    return 0;
}
