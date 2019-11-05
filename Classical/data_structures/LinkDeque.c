#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int QElemType;
typedef int Status;

typedef struct QNode{
    QElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct 
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;


Status InitQueue(LinkQueue *Q)
{
    Q->front = (QueuePtr)malloc(sizeof(QNode));
    Q->rear = Q->front;
    if(Q->front == NULL)
    {
        exit(OVERFLOW);
    }
    Q->front->next = NULL;
    return OK;
}

Status DestroyQueue(LinkQueue *Q)
{
    QueuePtr tmp = NULL;
    while(Q->front)
    {
        tmp = Q->front->next;
        free(Q->front);
        Q->front = tmp;
    }
    return OK;
}

Status ClearQueue(LinkQueue *Q)
{
    DestroyQueue(Q);
    InitQueue(Q);
    return OK;
}

Status IsEmpty(LinkQueue Q)
{
    if(Q.front == Q.rear)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int GetLength(LinkQueue Q)
{
    int i = 0;
    QueuePtr p = Q.front;
    while(p != Q.rear)
    {
        i++;
        p = p->next;
    }
    return i;
}

Status GetHead(LinkQueue Q, QElemType *e)
{
    QueuePtr p;
    p = Q.front->next;
    if(p && Q.front != Q.rear)
    {
        *e = p->data;
        return OK;
    }
    else
    {
        return ERROR;
    }
}

Status EnQueue(LinkQueue *Q, QElemType e)
{
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if(!p)
    {
        exit(OVERFLOW);
    }
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}

Status DeQueue(LinkQueue *Q, QElemType *e)
{
    QueuePtr p;
    if(Q->front == Q->rear)
    {
        return ERROR;
    }
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if(p == Q->rear)
    {
        Q->rear = Q->front;
    }
    free(p);
    return OK;
}

void visit(QElemType e)
{
    printf("%d ", e);
}

Status TraverseQueue(LinkQueue Q, void(*visit)(QElemType ))
{
    QueuePtr p = Q.front;
    p = p->next;
    while(p)
    {
        visit(p->data);
        p = p->next;
    }
    return OK;
}

int main()
{
    LinkQueue Q;
    if(InitQueue(&Q))
    {
        QElemType e;
        int i;

        printf("init_success\n");


        if(IsEmpty(Q))
        {
            printf("EMPTY!\n");
        }

        for(i = 0; i < 10; i++)
        {
            EnQueue(&Q, i);
        }

        GetHead(Q, &e);
        printf("The first element is %d\n",e);

        printf("Length is %d\n", GetLength(Q));

        DeQueue(&Q, &e);
        printf("delete element is %d\n", e);

        TraverseQueue(Q, visit); 


        if(DestroyQueue(&Q))
        {
            printf("\nDestroyed success!\n");
        }
    }

    return 0;
}