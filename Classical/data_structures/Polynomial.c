#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVER_FLOW -2


typedef struct Polynomial
{
    float *coef;
    int order;
    int maxSize;
}Polynomial;

void Add(Polynomial &A, Polynomial &B, Polynomial &C)
{
    int i;
    int a = A.order;
    int b = B.order;
    for(i = 0; i <= a && i <=b; i ++)
    {
        C.coef[i] = A.coef[i] + B.coef[i];
    }
    while(i < a)
    {
        C.coef[i] = A.coef[i];
    }
    while(i < n)
}
