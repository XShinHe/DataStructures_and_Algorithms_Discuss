#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "SepStack.h"
#include "CrossRiver.h"
bool side(int location, int movers)
{
    return ((location & movers) != 0);
}

bool safe(int location)
{
	//��԰ײ�
    if (side(location, GOAT) == side(location, CABBAGE) &&
		side(location, GOAT) != side(location, FARMER))
		return false;
	//�ǳ���
    if (side(location, GOAT) == side(location, WOLF) &&
		side(location, GOAT) != side(location, FARMER))
		return false;
	//����Ϊ��ȫ״̬
	return true;
}

void TakeSolution(int location2, int location1, char *pstr)
{
	//�����ж��Ĳ���
	int location = location2 ^ location1;
	if (side(location, FARMER))
	{
		//ũ����ж�
		char obj_action[20] = "";
		if (side(location, WOLF))
            strcat(obj_action, "��");
		if (side(location, CABBAGE))
            strcat(obj_action, "�ײ�");
		if (side(location, GOAT))
            strcat(obj_action, "��");
		if (obj_action[0])
		{
			sprintf(pstr, "ũ���%s��", obj_action);
			strcat(pstr, side(location2, FARMER) ? "�ϱ�" : "����");
		}
		else
			sprintf(pstr, "ũ���Լ��ص�%s", side(location2, FARMER) ? "�ϱ�" : "����");
	}
}
