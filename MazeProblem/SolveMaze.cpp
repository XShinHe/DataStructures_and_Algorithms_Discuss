#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "MazeGraph.h"
#include "Queue.h"
#include "SolveMaze.h"

PCQ AddLevelSurround(PCQ que, PMazeG pmg, int rcd)
{
    printf("the Add one level progress:\n\n");//___________________
    int tmp=que->r;//��������ݹ�
    for(;(rcd)%que->M != tmp;rcd++)
    {
        for(int k=0;k<4;k++)
        {
            if(SurroundBeen(pmg,(que->cque+rcd),k)==0)
            {
                AddNodeSurround(que, pmg, (que->cque+rcd),k);
            }
        }
    }
    return que;//����ֵ������һ���rcd
    ShowQueue(que);//___________
    ShowMazeBeen(stdout,pmg);//_______________
}

int AddNodeSurround(PCQ que,PMazeG pmg,PMazeN pmn,int i)//�����¼����һ�����ݽ���ͷָ�룬�����ض����Ƿ���ԣ�������������������������
{
    int tmp=0;
    if(i==0)
    {
        if(SurroundBeen(pmg,pmn,0)==0)
        {
            AddToQueue(que,*(pmg->maze+pmg->N*pmn->x+pmn->y+1));
            (pmg->maze+pmg->N*pmn->x+pmn->y)->dirc[0]=1;
            (pmg->maze+pmg->N*pmn->x+pmn->y+1)->been=1;
            (pmg->maze+pmg->N*pmn->x+pmn->y+1)->dirc[2]=-1;
            tmp++;
        }
    }
    if(i==1)
    {
        if(SurroundBeen(pmg,pmn,1)==0)
        {
            AddToQueue(que,*(pmg->maze+pmg->N*(pmn->x+1)+pmn->y));
            (pmg->maze+pmg->N*pmn->x+pmn->y)->dirc[1]=1;
            (pmg->maze+pmg->N*(pmn->x+1)+pmn->y)->been=1;
            (pmg->maze+pmg->N*(pmn->x+1)+pmn->y)->dirc[3]=-1;
            tmp++;
        }
    }
    if(i==2)
    {
        if(SurroundBeen(pmg,pmn,2)==0)
        {
            AddToQueue(que,*(pmg->maze+pmg->N*pmn->x+pmn->y-1));
            (pmg->maze+pmg->N*pmn->x+pmn->y)->dirc[2]=1;
            (pmg->maze+pmg->N*pmn->x+pmn->y-1)->been=1;
            (pmg->maze+pmg->N*pmn->x+pmn->y-1)->dirc[0]=-1;
            tmp++;
        }
    }
    if(i==3)
    {
        if(SurroundBeen(pmg,pmn,3)==0)
        {
            AddToQueue(que,*(pmg->maze+pmg->N*(pmn->x-1)+pmn->y));
            (pmg->maze+pmg->N*pmn->x+pmn->y)->dirc[3]=1;
            (pmg->maze+pmg->N*(pmn->x-1)+pmn->y)->been=1;
            (pmg->maze+pmg->N*(pmn->x-1)+pmn->y)->dirc[1]=-1;
            tmp++;
        }
    }
    return tmp;//���������
}

PMazeN CheckOutLevel(PCQ que, int rcd, PMazeG pmg)
{
    for(;(rcd)%que->M != que->r;rcd++)
    {
        if((que->cque+rcd)->x == pmg->xe && (que->cque+rcd)->y == pmg->ye ) return (que->cque+rcd);
    }
    return NULL;
}

int Solve(PMazeG pmg)
{
    MazeN ininode=*(pmg->maze+pmg->N*pmg->xb+pmg->yb);

    PCQ que=CreatEmptyCQ(100);

    que=AddToQueue(que,ininode);
    int rcd=0;//��¼��չ֮ǰ�Ķ�βλ�ã����ڵ�Ԫ�����У�֮ǰ�Ķ�βrcd=0

    while(CheckOutLevel(que,rcd,pmg)==NULL)//ʵʱ�����Թ�ͼ
    {
        int tmp=que->r;
        que=AddLevelSurround(que,pmg,rcd);
        rcd=tmp;
        if(rcd==que->r)break;//�޷�����������ȥ
        ShowQueueRcd(que,rcd);
        ShowMazeBeen(stdout,pmg);
    }
    if(CheckOutLevel(que,rcd,pmg)==NULL)pmg->solve=0;
    else pmg->solve=1;

    return pmg->solve;
}
