#ifndef SOLVEMAZEBYQUEUE_H_INCLUDED
#define SOLVEMAZEBYQUEUE_H_INCLUDED
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "MazeGraph.h"
#include "Queue.h"

int AppendHeadSur(PCQ que,PMazeG pmg);//�����¼����һ�����ݽ���ͷָ�룬�����ض����Ƿ���ԣ�������������������������
PMazeN CheckQueHead(PCQ que, PMazeG pmg);
int SolveByQue(PMazeG pmg);


#endif // SOLVEMAZEBYQUEUE_H_INCLUDED
