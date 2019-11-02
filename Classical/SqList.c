#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define INIT_SIZE 10
#define INCREMENT_SIZE 5

typedef int Status;
typedef int Elemtype;


typedef struct 
{
    /* data */
    Elemtype *elem;
    int length;
    int size;
}SqList;


Status InitList(SqList* L)
{
    L->elem = (Elemtype *) malloc(INIT_SIZE * sizeof(Elemtype));
    if(!L->elem)
    {
        return ERROR;
    }

L->length = 0;
L->size = INIT_SIZE;
return OK;
}

// 销毁线性表
Status DestroyList(SqList *L)
{
    free(L->elem);
    L->length = 0;
    L->size = 0;
    return OK;
}

// 清空线性表
Status CLearList(SqList* L)
{
    L->length = 0;
    return OK;
}

Status isEmpty(const SqList *L)
{
    if(0==L->length)
    {
        return TRUE;
    }

    return FALSE;
}

Status compare(Elemtype e1, Elemtype e2)
{
    if(e1 == e2)
    {
        return 0;
    }
    else if(e1 < e2) return -1;
    else return 1;
}

Status getLength(const SqList* L)
{
    return L->length;
}

Status GetElem(const SqList* L, int i, Elemtype *e)
{
    if(i < 1 || i > L->length)
    {
        return ERROR;
    }

    else
    {
        *e = L->elem[i-1];
        return OK;
    }
}

Status FindElem(const SqList* L, Elemtype e,Status (*compare)(Elemtype e1, Elemtype e2))
{
    int i;
    for(i = 0; i < L->length; i++)
    {
        if((*compare)(L->elem[i], e) == 0)
        {
            return i + 1;
        }
    }
    if(i >= L->length)
    {
        return ERROR;
    }
}

Status PreElem(const SqList* L, Elemtype cur_e, Elemtype *pre_e)
{
    int i;
    for(i = 0; i < L->length; i ++)
    {
        if(cur_e == L->elem[i])
        {
            if(i == 0)
            {
                return ERROR;
            }
            *pre_e = L->elem[i-1];
            return OK;
        }
    }

    return ERROR;
}

Status NextElem(const SqList* L, Elemtype cur_e, Elemtype *next_e)
{
    int i;
    for (i = 0; i < L->length; i ++)
    {
        if (cur_e == L->elem[i])
        {
            if(i == L->length - 1)
            {
                return ERROR;
            }
            *next_e = L->elem[i+1];
            return OK;
        }
    }

    return ERROR;
}

// 插入元素
Status InsertElem(SqList *L, int i, Elemtype e)
{
    Elemtype* new;
    if(i < 1 || i > L->length + 1)
    {
        return ERROR;
    }

    if(L->length >= L->size)
    {
        new = (Elemtype *)realloc(L->elem, L->size + INCREMENT_SIZE);
        L->elem = new;
        L->size += INCREMENT_SIZE;
    }

    Elemtype* p = &L->elem[i-1];
    Elemtype* q = &L->elem[L->length - 1];

    for(;q > p; q--)
    {
        *(q+1) = *q;
    }
    *p = e;
    ++(L->length);
    return OK;
}


// 删除元素
Status DeleteElem(SqList* L, int i, Elemtype *e)
{
    if(i < 1 || i > L->length)
    {
        return ERROR;
    }
    *e = L->elem[i-1];
    Elemtype* p = &L->elem[i-1];
    for(;p < &L->elem[L->length]; p++)
    {
        *p = *(p + 1);
    }
    --(L->length);
    return OK;
}

void visit(Elemtype e)
{
    printf("%d ", e);
}


// 遍历列表
Status TraverseList(const SqList *L, void(*visit)(Elemtype e))
{
    int i;
    for(i = 0; i < L->length; i ++)
    {
        visit(L->elem[i]); 
    }
    return OK;
}

int main()
{
    SqList L;
    if(InitList(&L))
    {
        Elemtype e;
        printf("Initialization Successs!\n\n");
        int i;
        for(i = 0; i < 10; i++)
        {
            InsertElem(&L, i+1, i);
        }
        printf("length is %d\n", getLength(&L));
        if(GetElem(&L, 1, &e)){
            printf("Element is : %d\n", e);
        }
        else
        {
            printf("Element is not exist\n");
        }
        if(isEmpty(&L))
        {
            printf("List is empty\n");
        }
        else
        {
            printf("List is not empty\n");
        }
        printf("The 5 at %d\n", FindElem(&L, 5, *compare));
        PreElem(&L, 6, &e);
        printf("The 6's previous element is: %d\n", e);
        NextElem(&L, 6, &e);
        printf("The 6's next element is: %d\n", e);
        DeleteElem(&L, 1, &e);
        printf("Delete first item is : %d\n", e);

        printf("Now the length is : %d\n", L.length);

        printf("List: ");
        TraverseList(&L, visit);
        if(DestroyList(&L))
        {
            printf("\nDestroy success!\n");
        }    
    }
    else
    {
        printf("\nInitialize unsuccessful!\n");
        return ERROR;
    }
    return 0;
}