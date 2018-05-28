#include <cstdio>
#include <cstdlib>
#include "Queue.h"

PCQ CreatEmptyCQ(int M)
{
    PCQ que=(PCQ)malloc(sizeof(CQ));
    que->cque=(PMazeN)malloc(M*sizeof(MazeN));
    que->M=M;
    que->f=0;
    que->r=0;
    que->stat=0;//0��ʾ��̬
    return que;
}

bool IsEmptyQueue(PCQ que)
{
    if((que->f)%(que->M)==que->r%(que->M) && que->stat==0)return true;
    else return false;
}

bool IsFullQueue(PCQ que)
{
    if((que->f)%(que->M)==que->r%(que->M) && que->stat==1)return true;
    else return false;
}

PCQ AddToQueue(PCQ que,MazeN mzn)
{
    if(IsFullQueue(que)==true)
    {
        printf("����������\n");
        return que;//��������
    }
    *(que->cque+que->r)=mzn;
    que->r=(que->r+1)%(que->M);
    que->stat=1;
    return que;
}

PCQ PopQueue(PCQ que)
{
    if(IsEmptyQueue(que)==true)
    {
        printf("�����ѿգ�\n");
        return que;//��������
    }
    que->f=(que->f+1)%que->M;
    que->stat=0;
    return que;
}

PMazeN GetheadQueue(PCQ que)
{
    return (que->cque+que->f);
}

int ShowQueue(PCQ que)
{
    printf("               ����״̬����              \n");
    printf("-------------------��ͷ------------------\n");
    for(int i=que->f;IsEmptyQueue(que)==0 && i%(que->M)!=que->r;i++)
    {
        printf("    (%d, %d)\n",(que->cque+i)->x,(que->cque+i)->y);
    }
    printf("-------------------��β------------------\n\n");
    return 0;//??
}

int ShowQueueRcd(PCQ que, int rcd)
{
    printf("-------------------��ͷ------------------\n");
    for(int i=que->f;IsEmptyQueue(que)==0 && i%(que->M)!=que->r;i++)
    {
        if(i==rcd)
        {
            printf("    (%d, %d)  record here!\n",(que->cque+i)->x,(que->cque+i)->y);
        }
        else printf("    (%d, %d)\n",(que->cque+i)->x,(que->cque+i)->y);
    }
    printf("-------------------��β------------------\n\n");
    return 0;//??
}
