#ifndef SOLVEMAZE_H_INCLUDED
#define SOLVEMAZE_H_INCLUDED

PCQ AddLevelSurround(PCQ que, PMazeG pmg, int rcd);
int AddNodeSurround(PCQ que,PMazeG pmg,PMazeN pmn,int i);//�����¼����һ�����ݽ���ͷָ�룬�����ض����Ƿ���ԣ�������������������������
PMazeN CheckOutLevel(PCQ que, int rcd, PMazeG pmg);
int Solve(PMazeG pmg);

#endif // SOLVEMAZE_H_INCLUDED
