#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "SepStack.h"
#include "CrossRiver.h"
//��������
#define FARMER	0x08
#define WOLF	0x04
#define CABBAGE 0x02
#define GOAT	0x01

int main(int argc, char* argv[])
{
    int movers, location, newlocation;
    int route[16];            //��¼�Ѿ����ǵ�״̬·��

    //��ʼ׼��
    PSS pstk = CreateEmptyStack();
    InStack(pstk, 0x00);//
	int i;
    route[0] = 0;
    for (i = 1; i < 16; i++)  route[i] = -1;

    //��ʼ�ƶ�
    while (!IsEmptyStack(pstk) && route[15] < 0)
    {
		//��ӡ��ǰջ����
		printStack(pstk);
		getchar();

		//�õ����ڵ�״̬
        location = Gettop(pstk);
		int cnt = 0;
        for (movers = GOAT; movers <= FARMER; movers <<= 1)
        {
            //ũ���������ƶ�����ũ���ƶ��Ķ���������ũ����ͬ��
            if (side(location, FARMER) == side(location, movers))
            {
                //��λ�ã�ũ����Ҫ�ƶ��Ķ���ͬʱ����[״̬�ı�]
                newlocation = location ^(FARMER | movers);
                if (safe(newlocation) && route[newlocation] < 0)
                {
                    //��ȫ����δ���ʹ���״̬(������һ��)
                    route[newlocation] = location;
                    InStack(pstk, newlocation);
					cnt++;
					break;
                }
            }
        }

		//�����״̬�޷�����, ��ջ(�ص���һ��)
		if (!cnt)
		{
			printf("--״̬: %1d  %1d  %1d  %1d �޷�����\n",
					side(location, FARMER), side(location, WOLF),
					side(location, CABBAGE), side(location, GOAT));
			OutStack(pstk);
		}
		else
		{
			printf("++����: %1d  %1d  %1d  %1d ��״̬\n",
					side(newlocation, FARMER), side(newlocation, WOLF),
					side(newlocation, CABBAGE), side(newlocation, GOAT));
		}
    }

    //�����ӡ·��
    if (route[15] >= 0)
    {
		printf("=============ũ�����������岽��================\n");
		printf("      ũ��  ��    �ײ�   �� \n");
		printf("-------------------------------------------------\n");
        for (location = 15; location >= 0; location = route[location])
        {
			char str[32] = "��ʼ״̬";
			if (location != 0)
			{
				TakeSolution(location, route[location], str);
			}
            printf("״̬:   %1d     %1d     %1d     %1d      %s\n",
					side(location, FARMER), side(location, WOLF),
					side(location, CABBAGE), side(location, GOAT), str);
            if (location == 0)   break;
        }
    }
	getchar();

	return 0;
}
