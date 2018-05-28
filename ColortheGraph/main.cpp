#include <cstdio>
#include <cstdlib>


using namespace std;
//���й�ͼ��ɫ�����ݱ�����txt�ļ��У���һ�и���ͼ�Ķ������
//����n�и�����n������Ĺ�ϵ�������ּ�ͨ���ո����
//Ĭ�ϵ�����·����d:\\codefile\\datafile\\datain1.txt
//Ĭ�ϵ����·����d:\\codefile\\datafile\\dataou1.txt

typedef struct Node//������Ļ�������
{
   int clr; //������ɫ
} Node,*PNode;

typedef struct Graphtype//����һ��ͼ�Ļ������ԣ��ɽ������ڽӾ��󹹳�
{
    int Nver;//ͼ�Ķ�����
    int NBeenColored;//�Ѿ���Ϳɫ�Ķ����������ܳ�ʼ��
    PNode Ver;//ͼ�Ķ��㣬��Ϊһ��ָ��
    int* Adjmtx;//�ڽӾ�����Ϊһ��ָ��
}Graph, *PGraph;

bool CanColor(PGraph PG, int clr, int j , int i)//�ж�PG��Ӧ��ͼ�ĵ�j��Ԫ���ܷ�ʹ��clr��ɫ����Ϊ�ǰ���˳��ģ�����ֻ�ö�i֮��j֮ǰ��Ԫ�ؽ����жϼ���
{
    bool CanClr=true;//��ʼ��Ϊ������ɫ

    for(int k=i ; k < j ; k++)
    {
        if(*(PG->Adjmtx+k*PG->Nver+j) && (PG->Ver+k)->clr==clr)//���Ԫ��k��j�ڽӲ����Ѿ�����ɫΪclr������ɫ�����pnode������clr�Ƚ�
            {
                CanClr=false;
                break;//����ѭ��
            }
    }
    return CanClr;
}

int Color(PGraph PG,FILE* fout){
    int color = 0;//k����Ⱦ�ڼ�����ɫ
    int init=0;//��¼����Ⱦɫ����㣬��ʼ��Ϊ0
    while (PG->NBeenColored < PG->Nver) {//��ͼ���е�δ��Ⱦɫʱ������ִ��
        color++;
        fprintf(fout,"��ɫ����%d:",color);

        //�ҵ���һ��δ��ɫ�Ľڵ㣬������ɫȾɫ
        int i;
        for (i = init; i < PG->Nver; i++)
        {
           if ((PG->Ver+i)->clr == 0)
           {
               (PG->Ver+i)->clr = color;
               PG->NBeenColored++;//��ɫ��+1
               fprintf(fout," ����%02d",i+1);
               init=i+1;//˵��֮ǰ�ĵ㶼�Ѿ�Ⱦɫ���´�����ֱ�Ӵ����￪ʼ
               break;
           }
        }

        //�ٰ��������в��͸���Ⱦɫ�����ڵĶ�������ͬ����ɫ
        //����i������ɫ�ĵ�һ�����㣬ʣ�µĶ���Ӧ�ô���������
        for(int j=i+1; j<PG->Nver; j++)
        {
           if((PG->Ver+j)->clr ==0 && CanColor(PG,color,j,i) )//�����ǽ��jδ����ɫ,��������֮ǰ�ı�color��ɫ��㲻��ͻ
           {
               (PG->Ver+j)->clr = color;
               PG->NBeenColored++;//��ɫ��+1
               fprintf(fout," ����%02d",j+1);
           }
        }
        fprintf(fout,"\n");
     }
     return color;
}

int main() {
    FILE *fin, *fout;
    fin = fopen("d:\\codefile\\datafile\\datain1.txt","r");
    fout = fopen("d:\\codefile\\datafile\\dataout1.txt","w");
    //���϶����ض�����ļ�ָ��
    //datain1.txt�Ǵ�����ݵ��ļ���
    //dataout1.txt�Ǵ��������ݵ��ļ���
    if(fin==NULL)
    {
        fprintf(fout,"The file d:\\codefile\\datafile\\datain1.txt is not existing!\n");
        exit(0);
    }
    //�ж��ļ�ָ���Ƿ���ȷָ��


    int n=0;
    fscanf(fin,"%d",&n);//����ͼ�Ķ������
    PGraph PG=(PGraph)malloc(sizeof(Graph));//Ϊͼ����ռ�
    PG->Nver=n;//ͼ�Ķ�����Ŀ��ֵ
    PG->NBeenColored=0;//ͼ��Ⱦɫ���ʼ��Ϊ0

    PG->Ver=(PNode)malloc(n*sizeof(struct Node));//Ϊͼ��n��������ռ䣨�㼯��
    PG->Adjmtx=(int*)malloc(n*n*sizeof(int));//Ϊͼ��n*n��ϵ�������ռ䣨��ϵ����

    //��ʼ����ϵ���󣬳�ʼ��0��ʾû��Ϳɫ
    for (int i = 0; i < n; i++)
    {
         for (int j = 0; j < n; j++) {
            fscanf(fin,"%d",PG->Adjmtx+i*n+j);
         }
         (PG->Ver+i)->clr = 0;
    }


    int clrneed = Color(PG,fout);//ִ�ж�ͼ��Ⱦɫ����
    fprintf(fout,"һ����Ҫ%d����ɫ��",clrneed);

    free(PG->Ver);
    free(PG->Adjmtx);
    free(PG);
    //�ͷſռ�
    //ע��codeblock�ƺ�û��Ұָ�����⣬VC�д���Ұָ������

    return 0;
}

