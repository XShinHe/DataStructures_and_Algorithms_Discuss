#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "MazeGraph.h"//�������Թ�ͼ�ṹ

using namespace std;
PMazeG CreatMazeGraph(FILE* fin)//fin�������ļ�
{
    int m,n;
    fscanf(fin,"%d",&m);
    fscanf(fin,"%d",&n);
    PMazeG pm=(PMazeG)malloc(sizeof(MazeG));
    pm->xb=0; pm->xe=0;
    pm->yb=0; pm->ye=0;
    pm->M=m;
    pm->N=n;
    pm->A=0;
    pm->solve=0;

    pm->maze=(PMazeN)malloc((m*n)*sizeof(MazeN));//��ͼԪ�ط���ռ�
    for(int i=0;i<pm->M;i++)
    {
        for(int j=0;j<pm->N;j++)
        {
            //ShowMazeGraph(stdout,pm);
            //printf("\n");
            int tmp;
            fscanf(fin,"%d",&tmp);
            if(pm->A >= (pm->M)*(pm->N))break;
            (pm->maze+pm->N*i+j)->wll=tmp;
            pm->A++;
            (pm->maze+pm->N*i+j)->x=i;
            (pm->maze+pm->N*i+j)->y=j;
            if((pm->maze+pm->N*i+j)->wll==2)
            {
                pm->xb=i;
                pm->yb=j;
            }
            if((pm->maze+pm->N*i+j)->wll==3)
            {
                pm->xe=i;
                pm->ye=j;
            }
            if((pm->maze+pm->N*i+j)->wll==1 || (pm->maze+pm->N*i+j)->wll==2)
                (pm->maze+pm->N*i+j)->been=1;//������¼������ʾ��ջ�У�0��ʾû����ջ��-1��ʾ���˹�ջ
            else (pm->maze+pm->N*i+j)->been=0;
            for(int k=0;k<4;k++)(pm->maze+pm->N*i+j)->dirc[k]=0;//0123�ֱ��ʾ����������0��ʾ���򶼻�û��̽����1��ʾ̽�����ˣ�-1��ʾ��ջ����
        }
        //ShowMazeGraph(stdout,pm);
        //printf("\n");
    }
    return pm;
}

void DeMazeGraph(PMazeG pm)
{
    free(pm->maze);
    free(pm);pm=NULL;
}

int ShowMazeGraph(FILE* fout, PMazeG pm)
{
    printf("--------------�Թ���Ϣ����ʾ-------------\n");
    printf("�Թ���Ϣ��\n    ����=%d      ����=%d\n    ���=b       �յ�=e\n\n",pm->M,pm->N);
    for(int i=0;i<pm->M;i++)
    {
        printf("    ");
        for(int j=0;j<pm->N;j++)
        {
            if((pm->maze+pm->N*i+j)->wll==1)printf("# ");
            else if((pm->maze+pm->N*i+j)->wll==0)printf("  ");
            else if((pm->maze+pm->N*i+j)->wll==2)printf("b ");
            else if((pm->maze+pm->N*i+j)->wll==3)printf("e ");
            else if((pm->maze+pm->N*i+j)->wll==9)printf("+ ");
            else printf("? ");//,(pm->maze+pm->N*i+j)->wll);
        }
        printf("\n");
    }
    printf("-----------------------------------------\n");
    if(pm->solve==1)return 1;
    else return 0;
}

int SurroundBeen(PMazeG pmg,PMazeN pmn, int i)//����һ������ĳ������Ľ��ռ�����
{
    if(i==0)
    {
        if((pmg->maze+pmg->N*pmn->x+pmn->y+1)->been==0)return 0;//0��ʾû���߹�
        else return 1;
    }
    if(i==1)
    {
        if((pmg->maze+pmg->N*(pmn->x+1)+pmn->y)->been==0)return 0;
        else return 1;
    }
    if(i==2)
    {
        if((pmg->maze+pmg->N*pmn->x+pmn->y-1)->been==0)return 0;
        else return 1;
    }
    if(i==3)
    {
        if((pmg->maze+pmg->N*(pmn->x-1)+pmn->y)->been==0)return 0;
        else return 1;
    }
    return 1;//????
}

int ShowMazeBeen(FILE* fout, PMazeG pm)
{
    printf("-------------�Թ�̽�����̸���------------\n");
    printf("�Թ���Ϣ��\n    ����=%d      ����=%d\n    ���=b       �յ�=e\n\n",pm->M,pm->N);
    for(int i=0;i<pm->M;i++)
    {
        printf("    ");
        for(int j=0;j<pm->N;j++)
        {
            if((pm->maze+pm->N*i+j)->wll==1) printf("# ");
            else if((pm->maze+pm->N*i+j)->wll==2) printf("b ");
            else if((pm->maze+pm->N*i+j)->wll==3) printf("# ");
            else if((pm->maze+pm->N*i+j)->been==1)printf("+ ");
            else if((pm->maze+pm->N*i+j)->been==0)printf("  ");
            else printf("? ");//,(pm->maze+pm->N*i+j)->been);
        }
        printf("\n");
    }
    printf("-----------------------------------------\n");
    if(pm->solve==1)return 1;
    else return 0;
}

int ShowMazePath(FILE* fin, PMazeG pmg)
{
    int x=pmg->xe;
    int y=pmg->ye;
    while(x!=pmg->xb || y!=pmg->yb)
    {
        int k=0;
        for(;k<4;k++)
        {
            if((pmg->maze+pmg->N*x+y)->dirc[k]<0)break;
        }
        if(k==0)y++;
        if(k==1)x++;
        if(k==2)y--;
        if(k==3)x--;
        (pmg->maze+pmg->N*x+y)->wll=9;
    }
    (pmg->maze+pmg->N*x+y)->wll=2;
    ShowMazeGraph(stdout,pmg);
    return 0;
}

int ShowMazeDircFrom(FILE* fout, PMazeG pmg)
{
    printf("M=%d, N=%d\n",pmg->M,pmg->N);
    for(int i=0;i<pmg->M;i++)
    {
        for(int j=0;j<pmg->N;j++)
        {
            int k=0;
            for(;k<4;k++)
            {
                if((pmg->maze+pmg->N*i+j)->dirc[k]<0)break;
            }
            if((pmg->maze+pmg->N*i+j)->wll!=1)printf("%d ",k);
            else printf("# ");
        }
        printf("\n");
    }
    return 0;
}
