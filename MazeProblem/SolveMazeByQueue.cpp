#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "MazeGraph.h"
#include "Queue.h"
#include "SolveMazeByQueue.h"

int AppendHeadSur(PCQ que,PMazeG pmg)//�����¼����һ�����ݽ���ͷָ�룬�����ض����Ƿ���ԣ�������������������������
{
    int tmp=0;
    PMazeN pmn=GetheadQueue(que);
    if(SurroundBeen(pmg,pmn,0)==0)
    {
        AddToQueue(que,*(pmg->maze+pmg->N*pmn->x+pmn->y+1));
        (pmg->maze+pmg->N*pmn->x+pmn->y)->dirc[0]=1;
        (pmg->maze+pmg->N*pmn->x+pmn->y+1)->been=1;
        (pmg->maze+pmg->N*pmn->x+pmn->y+1)->dirc[2]=-1;
        tmp++;
    }
    if(SurroundBeen(pmg,pmn,1)==0)
    {
        AddToQueue(que,*(pmg->maze+pmg->N*(pmn->x+1)+pmn->y));
        (pmg->maze+pmg->N*pmn->x+pmn->y)->dirc[1]=1;
        (pmg->maze+pmg->N*(pmn->x+1)+pmn->y)->been=1;
        (pmg->maze+pmg->N*(pmn->x+1)+pmn->y)->dirc[3]=-1;
        tmp++;
    }
    if(SurroundBeen(pmg,pmn,2)==0)
    {
         AddToQueue(que,*(pmg->maze+pmg->N*pmn->x+pmn->y-1));
        (pmg->maze+pmg->N*pmn->x+pmn->y)->dirc[2]=1;
        (pmg->maze+pmg->N*pmn->x+pmn->y-1)->been=1;
        (pmg->maze+pmg->N*pmn->x+pmn->y-1)->dirc[0]=-1;
        tmp++;
    }
    if(SurroundBeen(pmg,pmn,3)==0)
    {
        AddToQueue(que,*(pmg->maze+pmg->N*(pmn->x-1)+pmn->y));
        (pmg->maze+pmg->N*pmn->x+pmn->y)->dirc[3]=1;
        (pmg->maze+pmg->N*(pmn->x-1)+pmn->y)->been=1;
        (pmg->maze+pmg->N*(pmn->x-1)+pmn->y)->dirc[1]=-1;
        tmp++;
    }
    return tmp;//���������
}

PMazeN CheckQueHead(PCQ que, PMazeG pmg)
{
    if( GetheadQueue(que)->x==pmg->xe && GetheadQueue(que)->y==pmg->ye ) return (que->cque+que->f);
    else return NULL;
}

int SolveByQue(PMazeG pmg)
{
    MazeN ininode=*(pmg->maze+pmg->N*pmg->xb+pmg->yb);

    PCQ que=CreatEmptyCQ(100);
    que=AddToQueue(que,ininode);

    while(CheckQueHead(que,pmg)==NULL)//ʵʱ�����Թ�ͼ
    {
        AppendHeadSur(que,pmg);
        PopQueue(que);
        if(IsEmptyQueue(que)==true)break;
        ShowQueue(que);
        ShowMazeBeen(stdout,pmg);
        getchar();
    }
    if(CheckQueHead(que,pmg)==NULL)pmg->solve=0;
    else pmg->solve=1;

    return pmg->solve;
}
