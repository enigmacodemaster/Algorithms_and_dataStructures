#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERLOAD -2

typedef int Elemtype;
typedef int Status;

typedef struct LNode
{
    Elemtype data;
    struct LNode *next;
}LNode, *LinkList;


void InitList(LinkList *L)
/* 
L为指向LinkList的指针，而LinkList本身是指向LNode的指针。
所以，L是指针的指针。
*/
{
    *L=(LinkList)malloc(sizeof(LNode));
    if(!L)
    {
        exit(OVERLOAD);
    }
    (*L)->next = NULL;
}


void DestroyList(LinkList *L)
{
    LinkList temp;
    while(*L)
    {
        temp = (*L)->next;
        free(*L);
        *L = temp;
    }
}

void ClearList(LinkList *L)
{
    LinkList p = (*L)->next;
    (*L)->next = NULL;
    DestroyList(&p);
}

Status isEmpty(LinkList L)
{
    if(L->next)
    {
        return FALSE;
    }

    else
    {
        return TRUE;
    }  
}

int GetLength(LinkList L)
{
    int i = 0;
    LinkList p = L->next;
    while(p)
    {
        i++;
        p = p->next;
    }
    return i;
}

Status GetElem(LinkList L, int i, Elemtype *e)
{
    int j = 1;
    LinkList p = L->next;
    while(p && j < i)
    {
        j ++;
        p = p->next;
    }
    if(!p || j > i)
    {
        return ERROR;
    }
    *e = p->data;
    return OK;
}

Status compare(Elemtype e1, Elemtype e2)
{
    if (e1 == e2)
    {
        return 0;
    }
    else if (e1 < e2)
    {
        return -1;
    }
    else
    {
        return 1;
    }
    
}

Status FindElem(LinkList L, Elemtype e, Status (*compare)(Elemtype, Elemtype))
{
    int i = 0;
    LinkList p = L->next;
    while(p)
    {
        i++;
        if(!compare(p->data, e))
        {
            return i;
        }
        p = p->next; // bug1: 买有更新指针到下一个node
    }
    return 0;
}

Status PreElem(LinkList L, Elemtype cur_e, Elemtype *pre_e)
{
    LinkList q, p = L->next;
    while(p->next)
    {
        q = p->next;
        if(q->data == cur_e)
        {
            *pre_e = p->data;
            return OK;
        }
        p = q;
    }
    return ERROR;
}

Status NextElem(LinkList L, Elemtype cur_e, Elemtype *next_e)
{
    LinkList p = L->next;
    while(p->next)
    {
        if(p->data == cur_e)
        {
            *next_e = p->next->data;
            return OK;
        }
        p = p->next;
    }

    return ERROR;
}

Status InsertElem(LinkList L, int i, Elemtype e)
{
    int j = 0;
    LinkList s, p = L;
    while(p && j < i - 1)
    {
        j++;
        p = p->next;
    }
    if(!p || j > i - 1)
    {
        return ERROR;
    }
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

Status DeleteElem(LinkList L, int i, Elemtype *e)
{
    int j = 0;
    LinkList q, p = L;
    while(p->next && j < i - 1)
    {
        j ++;
        p = p->next;
    }
    if(p->next == NULL || j > i - 1)
    {
        return ERROR;
    }

    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}

void visit(Elemtype e)
{
    printf("%d ", e);
}

void TraverseList(LinkList L, void (*visit)(Elemtype e))
{
    LinkList p = L->next;
    while(p)
    {
        visit(p->data);
        p = p->next;
    }
}

int main()
{
    LinkList L;
    InitList(&L);
    Elemtype e;
    int i;
    if(L)
    {
        printf("Init success!\n");
    }

    if(isEmpty(L))
    {
        printf("List is empty\n");
    }

    for(i = 0; i < 10; i++)
    {
        InsertElem(L, i+1, i);
    }

    if(GetElem(L, 1, &e))
    {
        printf("The first item is : %d \n", e);
    }

    printf("length is %d \n", GetLength(L));
    printf("The 5 at %d\n", FindElem(L, 5, *compare));

    PreElem(L, 6, &e);
    printf("The 6's previous element is %d\n", e);

    NextElem(L, 6, &e);
    printf("The 6's next element is %d\n", e);

    DeleteElem(L, 1, &e);
    printf("delete first item is %d\n", e);

    printf("List: ");
    TraverseList(L, visit);

    DestroyList(&L);

    if(!L)
    {
        printf("\nDestroied.\n");
    }

    return 0;

}
