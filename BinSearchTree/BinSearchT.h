#ifndef BINSEARCHT_H_INCLUDED
#define BINSEARCHT_H_INCLUDED

typedef struct TNode
{
    int key;
    int data;
    TNode* llink;
    TNode* rlink;
}TN,*PTN;

typedef struct BinTree
{
    TNode* ptree;
}BT,*PBT;

typedef struct QNode
{
    PTN ptn;
    QNode* qlink;
}QN,*PQN;

typedef struct TQueue//
{
    PQN f;//head���
    PQN r;//ָ���βԪ��
}Q,*PQ;

PQ CreatEm(void);
int IsEmpty(PQ pq);
int InQueue(PQ pq, PQN pqn);
PQN OutQueue(PQ pq);
PQN GetHQueue(PQ pq);
int ShowQue(PQ pq);

int SearchBT(PBT pbt,int key,PTN* pploc);//���ز���ڵ�ĸ��ڵ�
int InsertBT(PBT pbt,PTN ptn);
int DelBTNode(PBT pbt,int key);
PBT CreatBT(FILE* fp);
int BinRound(PTN ptree);//�ݹ鶨��
int BinHeight(PTN ptree, int *ph, int* phmax);//�ݹ飬������������
int ShowTree(PBT pbt);
int InNode(PQ pq,PTN ptn);
int InLevel(PQ pq,int cnt);
int OutLevel(PQ pq, int cnt, int ht);

#endif // BINSEARCHT_H_INCLUDED
