#ifndef MAZEGRAPH_H_INCLUDED
#define MAZEGRAPH_H_INCLUDED

typedef struct MazeNode
{
    int wll;//'0','1','b','e'
    int x,y;
    int been;//
    int dirc[4];//directions��0��ʾû���߹���1��ʾ�߹���-1��ʾ��һ�����ķ���
}MazeN, *PMazeN;

typedef struct MazeGraph
{
    int M;//����
    int N;//����
    int A;
    int xb,yb;//�Թ����
    int xe,ye;//�Թ��յ�
    int solve;
    PMazeN maze;
}MazeG, *PMazeG;

PMazeG CreatMazeGraph(FILE* fin);
void DeMazeGraph(PMazeG pm);
int ShowMazeGraph(FILE* fout, PMazeG pm);
int SurroundBeen(PMazeG pmg,PMazeN pmn, int i);
int ShowMazeBeen(FILE* fout, PMazeG pm);
int ShowMazePath(FILE* fin, PMazeG pmg);
int ShowMazeDircFrom(FILE* fout, PMazeG pmg);

#endif // MAZEGRAPH_H_INCLUDED
