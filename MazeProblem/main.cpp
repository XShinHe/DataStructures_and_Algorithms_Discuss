#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "MazeGraph.h"
#include "Queue.h"
#include "SolveMaze.h"
#include "SolveMazeByQueue.h"

using namespace std;
int main()
{
    freopen("d:\\codefile\\datafile\\datainMaze.txt","r",stdin);
    //freopen("d:\\codefile\\datafile\\ShowMazeGraph.txt","w",stdout);
    PMazeG pm;
    pm=CreatMazeGraph(stdin);
    ShowMazeGraph(stdout,pm);

    printf("    ��ʼ����    (xb,yb):(%d,%d)\n",pm->xb,pm->yb);
    printf("    �յ�����    (xe,ye):(%d,%d)\n\n",pm->xe,pm->ye);

    if(SolveByQue(pm)==1)
    {
        ShowMazePath(stdout,pm);
    }
    else printf("    �Թ������޽⣡\n");

    DeMazeGraph(pm);

    fclose(stdout);
    return 0;
}
