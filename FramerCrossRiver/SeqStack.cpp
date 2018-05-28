#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "SepStack.h"
#include "CrossRiver.h"

PSS CreateEmptyStack()
{
	PSS pStk = (PSS)malloc(sizeof(struct CStack));
	if (pStk)
	{
		pStk->top=-1;
	}
	return pStk;
}

/////////////////////////////////
//ջ�п�
/////////////////////////////////
bool IsEmptyStack(PSS pStk)
{
	if (pStk && pStk->top == -1)
		return true;
	else
		return false;
}

/////////////////////////////////
//ջ����(��ջ)
/////////////////////////////////
bool InStack(PSS pStk, int x)
{
	if (pStk && (pStk->top+1) == 20)
	{
		printf("ջ����, �����ټ���!\n");
		return false;
	}
	pStk->top++;
	pStk->data[pStk->top] = x;
	return true;
}

/////////////////////////////////
//ջɾ��(��ջ)
/////////////////////////////////
bool OutStack(PSS pStk)
{
	if (IsEmptyStack(pStk))
	{
		printf("ջ�ѿ�, ������ɾ��!\n");
		return false;
	}
	pStk->top--;
	return true;
}

/////////////////////////////////
//��ȡջβԪ��
/////////////////////////////////
int Gettop(PSS pStk)
{
	return (pStk->data[pStk->top]);
}

void printStack(PSS pStk)
{
	printf("--��ǰջ����------------------\n");
	for (int i = pStk->top; i >= 0; i--)
	{
		int location = pStk->data[i];
        printf("  %1d   %1d   %1d   %1d\n",
				side(location, FARMER), side(location, WOLF),
				side(location, CABBAGE), side(location, GOAT));
	}
	printf("--ũ--��--��--��---------------\n");
}
