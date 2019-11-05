#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INIT_SIZE 20
#define INCREMENT_SIZE 5

typedef int SElemType;
typedef int Status;

typedef struct SqStack
{
    SElemType *base;
    SElemType *top;
    int size;
}SqStack;

Status InitStack(SqStack *S)
{
    S->base = (SElemType *)malloc(INIT_SIZE * sizeof(SElemType));
    if (!S->base)
    {
        exit(OVERFLOW);
    }
    S->top = S->base;
    S->size = INIT_SIZE;
    return OK;
}

Status DestroyStack(SqStack *S)
{
    free(S->base);
    S->base = NULL;
    S->top = NULL;
    S->size = 0;
    return OK;
}

Status IsEmpty(SqStack S)
{
    if(S.base == S.top)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int GetLength(SqStack S)
{
    return S.top - S.base;
}

Status GetTop(SqStack S, SElemType *e)
{
    if (S.top > S.base)
    {
        *e = *(--S.top);
        return OK;
    }
    else
    {
        return ERROR;
    }   
}

Status Push(SqStack *S, SElemType e)
{
    if((S->top - S->base) / sizeof(SElemType) >= S->size)
    {
        S->base = (SElemType *)realloc(S->base,((S->size + INCREMENT_SIZE) * sizeof(SElemType)));
        if(!S->base)
        {
            exit(OVERFLOW);
        }
        S->top = S->base + S->size;
        S->size = S->size + INCREMENT_SIZE;
    }
    *(S->top) = e;
    S->top ++;
    return OK;
}

Status Pop(SqStack *S, SElemType *e)
{
    if(S->base == S->top)
    {
        return ERROR;
    }
    S->top--;
    *e = *(S->top);
    return OK;
}

void visit(SElemType e)
{
    printf("%d\t", e);
}

// 很奇怪，为什么不能将指向S的指针作为参数传入，传入就会在运行阶段报错，显示是指针方面的问题
Status TraverseStack(SqStack S, void (*visit)(SElemType ))
{
    while((S.top) > (S.base))
    {
        SElemType tmp = *S.base;
        visit(tmp);
        S.base++;
    }
    return OK;
}

int main()
{
    SqStack S;
    int stat = InitStack(&S);
    if(stat)
    {
        SElemType e;
        int i;

        printf("Init_success!\n");

        if(IsEmpty(S))
        {
            printf("Stack is empty!\n");
        }

        for(i = 0; i < 10; i ++)
        {
            Push(&S, i);
        }

        GetTop(S, &e);
        printf("First element is : %d\n", e );

        printf("Length is %d\n", GetLength(S));

        Pop(&S, &e);
        printf("Pop element is %d\n", e);

        TraverseStack(S, visit);

        if(DestroyStack(&S))
        {
            printf("\nDestroy_success\n");
        }    
    }

    return 0;
}