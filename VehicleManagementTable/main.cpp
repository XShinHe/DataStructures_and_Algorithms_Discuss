#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

//�������������ݽṹ��Υ�¼�¼��㣬Υ�¼�¼����������Ϣ��㣬�����������Ա�
typedef struct RecordNode//����һ��Υ�¼�¼
{
    int idx;
    int Time;//ʱ���������Ϊ��������
    char Place[6];//�ص����5λ
    char Code[12];//
    char Treat[3];//Y��N
    RecordNode* link;
}RN, *PRN;

typedef struct RecordList//����һ������Υ�¼�¼��
{
    //int car_id;//��ʾ��¼�ĳ���
    int rcd_total;//��ʾһ����Υ�´���
    PRN rcd_head;//�ٴη��˽ṹ���ڵ�ָ��ҲӦ�ö�̬��������⣡����
}RL, *PRL;

typedef struct CarInfor//����һ��������Ϣ��¼
{
    char Car_idnum[3];
    char Car_type[6];
    int Car_buytime;
    int Car_price;
    char Car_owner[13];
    PRL Car_rlist;
}Car, *PCar;

typedef struct CarList//����һ�ų�����Ϣ��¼�����100����
{
    int cartotal;
    Car cars[100];
}CList, *PCL;

PCL InitRcd_Lst(PCL pcl, const char* id, int ridx, int time, const char* place, const char* code, const char* treat);
PCL InputRcdInfo(PCL pcl);//ʵ��Υ�¼�¼������
PCL InputCarInfo();//ʵ�ֹ�����������

PCar FindCar(PCL pcl, const char* id);//������Ҹ������ŵĳ�������ָ��
PCar FindOwnr(PCL pcl, const char* owner);
int FindIdx(PCL pcl, const char* id);//������Ҹ������ŵĳ������������е�λ��
int BeenAllTreated(PCL pcl, Car car);//�ж�Υ���Ƿ������

int ShowRcdInfo(PRL rlist);//ʵ��Υ�¼�¼�����
int ShowCarInfo(PCL pcl);//ʵ�����г������
int ShowIdRcdInfo(PCL pcl, const char* id);//ʵ�ָ�����������Υ�¼�¼�����
int ShowOwnrRcdInfo(PCL pcl, const char* owner);

//���º���ʵ��ͳ�ƹ���
int StatCarRecord(PCL pcl, const char* id);//ͳ�Ƹ������ŵ�Υ�¼�¼
int MarchTime(PRL prl, int t1, int t2);//ͳ��ʱ����Ƿ�Υ�£�����Υ�´���
int StatTimeRecord(PCL pcl, int t1, int t2);
int MarchPlace(PRL prl, const char* place);//ͳ�Ƶص��Ƿ�Υ�£�����Υ�´���
int StatPlaceRecord(PCL pcl, const char* place);
int MarchCode(PRL prl, const char* code);//ͳ��ĳһ�����Υ�£�����Υ�´���
int StatCodeRecord(PCL pcl, const char* code);

//��Ӹ���ɾ��������Ϣ�Ĳ���
PCar Init_ZeroRcd(PCar car);//Ϊ�³�����Υ�¼�¼�ĳ�ʼ���ڴ�
PCL AddCarInfo(PCL pcl, const char* carid ,const char* Owner, const char* type, int btime, int bprice);
PCL AddCar_Lst(PCL pcl, const char* carid);//�¼ӳ���
PCL AlertCarInfo_Lst(PCL pcl, const char* id, const char* carowner, const char* cartype, int buytime, int buyprice);//���ĳ��������ڽ��Զ�����
PCL DelCar_Lst(PCL pcl, const char* carid);//ɾ������

//��Ӹ���ɾ��Υ����Ϣ�Ĳ���
Car AddRcd_Car(Car car,int ridx, int time, const char* place, const char* code, const char* treat);//��Ҫһ��idx
PCL AddRcd_Lst(PCL pcl, const char* id, int time, const char* place, const char* code, const char* treat);//����Ҫһ��idx

Car AlertRcd_Car(Car car, int ridx, int time, const char* place, const char* code, const char* treat);//��Ҫһ��idx
PCL AlertRcd_Lst(PCL pcl, const char* id, int time, const char* place, const char* code, const char* treat);//�������ݲ����ڽ��Զ�����
Car DelRcd_Car(Car car, int time, const char* place);
PCL DelRcd_Lst(PCL pcl, const char* id, int time, const char* place);

//�ͷ����ڴ�ռ�
int DelLst(PCL pcl);

int main(void)
{
    //ʵ���ļ��������

    freopen("d:\\codefile\\datafile\\dataout2.txt", "w", stdout);

    //��������ʵ����������
    PCL pcarlist=InputCarInfo();
    pcarlist=InputRcdInfo(pcarlist);
    ShowCarInfo(pcarlist);//������峵������Ϣ

    //ʵ��Υ�¼�¼��ͳ�ƹ���
    ShowOwnrRcdInfo(pcarlist, "hans");
    ShowOwnrRcdInfo(pcarlist, "jojo");
    StatCarRecord(pcarlist,"20");//�������2��Υ����Ϣ
    StatTimeRecord(pcarlist,20170105,20170106);//ͳ��5-10ʱ��ε�Υ�¼�¼
    StatPlaceRecord(pcarlist,"Rd_7");//ͳ��100022�ص��Υ�¼�¼
    StatCodeRecord(pcarlist,"Accident");//ͳ�ƴ���Υ�¼�¼


    //ʵ�ֳ�������ӡ����ĺ�ɾ��
    pcarlist=AddCarInfo(pcarlist, "0", "wang","BENZ",20170306,220000);//0��ʾ���ƺ��Զ����

    pcarlist=DelCar_Lst(pcarlist,"13");
    pcarlist=DelCar_Lst(pcarlist,"36");
    ShowCarInfo(pcarlist);


    //ʵ��Υ�¼�¼����ӡ����ĺ�ɾ��
    pcarlist=AddRcd_Lst(pcarlist, "29", 20170307, "Rd_10", "Accident", "N");//���һ��Υ�¼�¼���������Ա�

    //�ͷ��ڴ�ռ�
    DelLst(pcarlist);

    return 0;
}

PCL InputRcdInfo(PCL pcl)
{
    freopen("d:\\codefile\\datafile\\accident.txt", "r", stdin);
    char tmpid[3]="1";//��ʼ��
    char id[3]="00";
    int i=0;
    while( i < pcl->cartotal)
    {
        scanf("%s",tmpid);
        if(strcmp(tmpid, "0")!=0)
        {
            strncpy(id,tmpid,3);
            i++;
        }

        int ridx;scanf("%d",&ridx);
        if(ridx==0)continue;
        char place[6];scanf("%s",place);
        int time;scanf("%d", &time);
        char code[12];scanf("%s",code);
        char treat[3];scanf("%s",treat);
        pcl=InitRcd_Lst(pcl, id, ridx, time, place, code, treat);
    }

    return pcl;//��Ϊ��Ȼ��ָ��ָ���ڴ棬���Գ����ս�rlist������ڴ�û��й¶��
}

PCL InputCarInfo()//ʵ�ֳ�����Ϣ������
{
    FILE* fin=fopen("d:\\codefile\\datafile\\CarData.txt", "r");
    PCL carlist=(PCL)malloc(sizeof(CList));//����һ��������������
    carlist->cartotal=0;

    int i=0;
    while(fscanf(fin,"%s",(carlist->cars[i].Car_idnum))!=EOF && carlist->cartotal < 100)//��ÿһ������һ������Ϣ����
    {
        carlist->cartotal++;
        //��Ϣ����
        fscanf(fin,"%s",(carlist->cars[i].Car_type));
        fscanf(fin,"%d",&(carlist->cars[i].Car_buytime));
        fscanf(fin,"%d",&(carlist->cars[i].Car_price));
        fscanf(fin,"%s",(carlist->cars[i].Car_owner));//s����ָ�룬����char���鱾��ָ�룬�����ٴ�ȡַ
        carlist->cars[i].Car_rlist=(PRL)malloc(sizeof(RL));
        carlist->cars[i].Car_rlist->rcd_total=0;
        carlist->cars[i].Car_rlist->rcd_head=(PRN)malloc(sizeof(RN));
        carlist->cars[i].Car_rlist->rcd_head->link=NULL;
        i++;//һ��Ҫ�ź���Ŷ�
    }
    return carlist;//ֻ�ǽ��ù����û�е���Υ�¼�¼
}

PCL InitRcd_Lst(PCL pcl, const char* id, int ridx, int time, const char* place, const char* code, const char* treat)//���ڴ�Υ�±�ŵĳ�ʼ��
{
    int idx=FindIdx(pcl, id);
    if(idx==-1)
    {
        pcl=AddCar_Lst(pcl,id);//��������ڣ����б�����¼�һ����
        Car tmp=pcl->cars[pcl->cartotal-1];
        pcl->cars[pcl->cartotal-1]=AddRcd_Car(tmp, tmp.Car_rlist->rcd_total+1, time, place, code, treat);
        printf("    ����%s�����ڣ��Ѿ���������Ӽ�¼��\n", id);
        return pcl;
    }
    pcl->cars[idx]=AddRcd_Car(pcl->cars[idx], ridx, time, place, code, treat);
    return pcl;
}

PCar FindCar(PCL pcl, const char* id)//����һ�����ţ��Ӻ���ǰ�ҵ�������������ָ��
{
    PCar findcar=pcl->cars+(pcl->cartotal-1);//�����һ��������
    for(int i=pcl->cartotal; strcmp(findcar->Car_idnum, id)!=0 && findcar!=pcl->cars && i>0;findcar--,i--);//������Ҹ�������ӵ����
    if(findcar==pcl->cars && strcmp(findcar->Car_idnum, id)!=0)
    {
        return NULL;//��ʾ�����쳣
    }
    else return findcar;
}

int FindIdx(PCL pcl, const char* id)//����һ�����ţ��ҳ����������б��е�λ��idx�����idx��0��ʼ����
{
    int i=0;
    while(strcmp(pcl->cars[i].Car_idnum, id)!=0 && i < (pcl->cartotal)-1)//cartotal-1ע��Ҫ��1
    {
        i++;
    }
    if(i==pcl->cartotal-1 && strcmp(pcl->cars[i].Car_idnum, id)!=0)
    {
        return -1;//��ʾû�в鵽
    }
    else return i;
}

PCar FindOwnr(PCL pcl, const char* owner)//����һ�����ţ��ҳ����������б��е�λ��idx�����idx��0��ʼ����
{
    int i=0;
    while(strcmp(pcl->cars[i].Car_owner, owner)!=0 && i < (pcl->cartotal)-1)//cartotal-1ע��Ҫ��1
    {
        i++;
    }
    if(i==pcl->cartotal-1 && strcmp(pcl->cars[i].Car_idnum, owner)!=0)
    {
        return NULL;//��ʾû�в鵽��ע�⵽���ؿ�ָ��
    }
    else return pcl->cars+i;
}

int ShowRcdInfo(PRL rlist)//ʵ��һ����������Υ�¼�¼�����
{
    PRN head=rlist->rcd_head->link;
    if(head==NULL)
    {
        printf("    û��Υ��\n\n");
        return 1;
    }
    for(int i=0;i<(rlist->rcd_total)&&(head!=NULL);i++)//???
    {
        printf("    Υ�±��%-3d:     Υ��ʱ��:%-11d  Υ�µص�:%-9.6s  Υ�´���:%-12.10s  Υ�´���:%-2s\n",head->idx,head->Time,head->Place,head->Code,head->Treat);
        head=head->link;
    }
    printf("\n");
    return 0;
}

int ShowCarInfo(PCL pcl)//ʵ�����г���Υ�¼�¼�����
{
    printf("��¼�ĳ���һ��%d����\n",pcl->cartotal);

    for(int i = 0;i < pcl->cartotal;i++)
    {
        printf("��������:%-10.2s",pcl->cars[i].Car_idnum);
        printf("��������:%-9.6s",pcl->cars[i].Car_type);
        printf("��������ʱ��:%-11d",pcl->cars[i].Car_buytime);
        printf("�����۸�:%d        ",pcl->cars[i].Car_price);
        printf("��������:%-12.12s\n",pcl->cars[i].Car_owner);
        ShowRcdInfo(pcl->cars[i].Car_rlist);
    }
    printf("\n");
    return 0;
}

int ShowIdRcdInfo(PCL pcl, const char* id)//ʵ��ĳһ������Υ�¼�¼�����
{
    printf("��ѯ��������Ϊ %-3.2s ��Υ�¼�¼��\n",id);
    PCar findcar=FindCar(pcl, id);
    if(findcar==NULL)
    {
        printf("    �������������ĳ��ţ���ȷ�ϣ�\n\n");
        return 1;//��ʾ�����쳣
    }
    if(findcar->Car_rlist->rcd_head->link==NULL)
    {
        printf("    ����Ϊ%-3.2s�ĳ���û��Υ�¼�¼��\n\n",id);
        return 0;
    }
    ShowRcdInfo(findcar->Car_rlist);
    return 0;
}

int ShowOwnrRcdInfo(PCL pcl, const char* owner)//ʵ��ĳһ������Υ�¼�¼�����
{
    printf("��ѯ��������Ϊ  %-5.5s ��Υ�¼�¼��\n",owner);
    PCar findownr=FindOwnr(pcl, owner);
    if(findownr==NULL)
    {
        printf("    �����������������ȷ�ϣ�\n\n");
        return 1;//��ʾ�����쳣
    }
    if(findownr->Car_rlist->rcd_head->link==NULL)
    {
        printf("    ����  %-5.5s�ĳ���û��Υ�¼�¼��\n\n",owner);
        return 0;
    }
    ShowRcdInfo(findownr->Car_rlist);
    return 0;
}

int StatCarRecord(PCL pcl, const char* id)//Ѱ��һ����������Υ�¼�¼
{
    printf("���ҳ���Ϊ%-5.2s������Υ�¼�¼��\n",id);
    PCar findcar=FindCar(pcl, id);
    if(findcar==NULL)
    {
        printf("    ����Ϊ%s�ĳ�����Ϣ�����ڣ����ʵ��\n\n",id);
        return 1;//1��ʾѰ���쳣
    }
    printf("    ��������:%-10.2s",findcar->Car_idnum);
    printf("��������:%-9.6s",findcar->Car_type);
    printf("��������ʱ��:%-11d",findcar->Car_buytime);
    printf("�����۸�:%d        ",findcar->Car_price);
    printf("��������:%-12.12s\n",findcar->Car_owner);

    printf("    �ó���һ��Υ��%d�Σ�\n",findcar->Car_rlist->rcd_total);
    ShowRcdInfo(findcar->Car_rlist);
    return 0;
}

int MarchTime(PRL prl, int t1, int t2)//ͳ��ʱ����Ƿ�Υ�£�����Υ�´���
{
    PRN head=prl->rcd_head->link;
    int cnt=0;
    while(head!=NULL)
    {
        if((head->Time)>=t1 && (head->Time) < t2)
        {
            cnt++;
        }
        head=head->link;
    }
    return cnt;
}

int StatTimeRecord(PCL pcl, int t1, int t2)
{
    printf("����Υ��ʱ�����%d--%d�ڵ�Υ�³�����\n",t1,t2);
    int haveone=0;
    for(int i=0;i<pcl->cartotal;i++)//iû�г�ʼ��
    {
        int sum=MarchTime(pcl->cars[i].Car_rlist,t1, t2);
        if(sum)
        {
            printf("    ��������%-3.2s��    Υ��%d��\n",pcl->cars[i].Car_idnum,sum);
            haveone=1;
        }
    }
    if(!haveone)printf("    ���ʱ�����û��Υ�³�����\n");
    printf("\n");
    return 0;
}

int MarchPlace(PRL prl, const char* place)
{
    PRN head=prl->rcd_head->link;
    int cnt=0;
    while(head!=NULL)
    {
        if(*(head->Place) ==*place)
        {
            cnt++;
        }
        head=head->link;
    }
    return cnt;
}

int StatPlaceRecord(PCL pcl, const char* place)
{
    printf("����Υ�µص���%s��Υ�³�����\n",place);
    int haveone=0;
    for(int i=0;i<pcl->cartotal;i++)
    {
        int sum=MarchPlace(pcl->cars[i].Car_rlist,place);
        if(sum)
        {
            printf("    ��������%-3.2s��    Υ��%d��\n",pcl->cars[i].Car_idnum,sum);
            haveone=1;
        }
    }
    if(!haveone)printf("    ����ص���û��Υ�¼�¼��\n");
    printf("\n");
    return 0;
}

int MarchCode(PRL prl, const char* code)
{
    PRN head=prl->rcd_head->link;
    int cnt=0;
    while(head!=NULL)
    {
        if(strcmp(head->Code, code)==0)
        {
            cnt++;
        }
        head=head->link;
    }
    return cnt;
}

int StatCodeRecord(PCL pcl, const char* code)
{
    printf("����Υ�´���%s��Ӧ��Υ�³�����\n",code);
    int haveone=0;
    for(int i=0;i<pcl->cartotal;i++)
    {
        int sum=MarchCode(pcl->cars[i].Car_rlist,code);
        if(sum)
        {
            printf("    ��������%-3.2s��    Υ��%d��\n",pcl->cars[i].Car_idnum,sum);
            haveone=1;
        }
    }
    if(!haveone)
    {
        printf("    ���Υ�´���û��Υ�¼�¼��\n\n");//ʹ��sum�������⣬����haveone
        return 1;
    }
    printf("\n");
    return 0;
}

PCar Init_ZeroRcd(PCar car)
{
    car->Car_rlist=(PRL)malloc(sizeof(RL));
    car->Car_rlist->rcd_total=0;
    car->Car_rlist->rcd_head=(PRN)malloc(sizeof(RN));
    car->Car_rlist->rcd_head->link=NULL;
    return car;
}

PCL AddCar_Lst(PCL pcl, const char* carid)//���ǵ�������ٸ�ֵ�����߲���д��̫��
{
    printf("��ӳ�������%s���б��У�\n",carid);
    if(FindCar(pcl, carid)!=NULL)
    {
        printf("    �����Ѿ����ڣ��޷���ӡ�\n");
        return pcl;
    }
    if((pcl->cartotal+1)>100)
    {
        printf("    ������޷���ӣ�\n\n");
        return pcl;
    }
    PCar findcar=pcl->cars+pcl->cartotal;
    strncpy(pcl->cars[pcl->cartotal].Car_idnum,carid,3);
    strncpy(pcl->cars[pcl->cartotal].Car_type,"----",4);//type��ʼ��
    pcl->cars[pcl->cartotal].Car_buytime=-1;
    pcl->cars[pcl->cartotal].Car_price=-1;
    strncpy(pcl->cars[pcl->cartotal].Car_owner,"------",4);//owner��ʼ��
    findcar=Init_ZeroRcd(findcar);

    pcl->cartotal++;
    return pcl;
}

PCL AddCarInfo(PCL pcl, const char* carid, const char* owner, const char* type, int btime, int bprice)
{
    PCar findcar;
    if(strcmp(carid, "0")==0)
    {
        char sid[3];
        findcar=pcl->cars+pcl->cartotal;//
        sprintf(sid, "%d", pcl->cartotal+1);
        strncpy(findcar->Car_idnum,sid,3);
        strncpy(findcar->Car_owner,owner,12);
        strncpy(findcar->Car_type,type,6);
        findcar->Car_buytime=btime;
        findcar->Car_price=bprice;
        pcl->cartotal++;
        findcar=Init_ZeroRcd(findcar);
        return pcl;
    }
    else findcar=FindCar(pcl, carid);
    if(findcar!=NULL )
    {
        printf("    �ó����Ѿ����ڣ��޷��ٴ���ӣ�\n");
        return pcl;
    }
    strncpy(findcar->Car_idnum,carid,3);
    strncpy(findcar->Car_owner,owner,12);
    strncpy(findcar->Car_type,type,6);
    findcar->Car_buytime=btime;
    findcar->Car_price=bprice;
    pcl->cartotal++;
    return pcl;
}

PCL AlertCarInfo_Lst(PCL pcl, const char* id, const char* carowner, const char* cartype, int buytime, int buyprice)//�޸Ļ򲹳䳵����Ϣ����ʱû��̫��Ĺ��ܡ�������������������������������������������
{
    printf("���� ����%s �ĳ�����Ϣ��", id);
    PCar findcar=pcl->cars+pcl->cartotal-1;//�����һ��������
    for(int i=pcl->cartotal; *(findcar->Car_idnum) != *id && findcar!=pcl->cars;findcar--,i--);//������Ҹ�������ӵ����
    if(findcar==pcl->cars && *(findcar->Car_idnum)!=*id)
    {
        pcl=AddCar_Lst(pcl,id);//��������ڣ����б�����¼�һ����
        pcl=AlertCarInfo_Lst(pcl, id, carowner, cartype, buytime, buyprice);//�¼Ӻ��ٽ���Ϣ����
        printf("    �ó��������ڲ����´�����\n");
        return pcl;//���return����ʡ�ԣ���
    }
    findcar->Car_buytime=buytime;
    strncpy(findcar->Car_owner,carowner,10);
    findcar->Car_price=buyprice;
    strncpy(findcar->Car_type,cartype,5);
    printf("    ���������鿴��\n");
    return pcl;
}

int BeenAllTreated(PCL pcl, Car car)
{
    PRN head=car.Car_rlist->rcd_head;
    while(head->link!=NULL)
    {
        head=head->link;
        if(strcmp(head->Treat,"N")==0)return 0;//�����û�д����Υ�£�����0
    }
    return 1;//Υ��ȫ������
}

PCL DelCar_Lst(PCL pcl, const char* carid)
{
    printf("������ɾ������%s�ĳ�����\n",carid);
    int idx=FindIdx(pcl, carid);
    if(idx==-1)
    {
        printf("    ɾ������û���ҵ���\n\n");
        return pcl;
    }
    if(BeenAllTreated(pcl, pcl->cars[idx])==0)
    {
        printf("    ����Υ��û�д����޷�ɾ����\n\n");
        return pcl;
    }
    for(;idx<(pcl->cartotal-1);idx++)
    {
        pcl->cars[idx]=pcl->cars[idx+1];
    }
    strncpy(pcl->cars[pcl->cartotal-1].Car_idnum,"none",4);//none��ʾ�ÿղ����ڳ���???
    pcl->cartotal--;
    printf("    ɾ����ɣ�\n\n");
    return pcl;
}

Car AddRcd_Car(Car car,int ridx, int time, const char* place, const char* code, const char* treat)//���ĳ����֪������һ��Υ��
{
    //AddRcd_Car(pcl->cars[idx], ridx, time, place, code, treat);
    PRN newrcd=(PRN)malloc(sizeof(RN));
    newrcd->idx=ridx;
    newrcd->Time=time;
    strncpy(newrcd->Place,place,6);
    strncpy(newrcd->Code,code, 12);
    strncpy(newrcd->Treat,treat,3);
    PRN tail=car.Car_rlist->rcd_head;
    while(tail->link!=NULL)tail=tail->link;//tail������for���������¼�¼����Υ�¼�¼��ĩβ
    tail->link=newrcd;
    newrcd->link=NULL;
    car.Car_rlist->rcd_total++;//ע������
    return car;
}

PCL AddRcd_Lst(PCL pcl, const char* id, int time, const char* place, const char* code, const char* treat)//���ĳ���������ŵ�һ��Υ�£����������ڽ��Զ��������������б�
{
    printf("��� ����%s ��һ��Υ�¼�¼��\n", id);
    int idx=FindIdx(pcl, id);
    if(idx==-1)
    {
        pcl=AddCar_Lst(pcl,id);//��������ڣ����б�����¼�һ����
        Car tmp=pcl->cars[pcl->cartotal-1];
        pcl->cars[pcl->cartotal-1]=AddRcd_Car(tmp, (tmp.Car_rlist->rcd_total+1), time, place, code, treat);
        printf("    �ĳ��Ų����ڣ��Ѿ���������Ӽ�¼��\n\n");
        return pcl;
    }
    pcl->cars[idx]=AddRcd_Car(pcl->cars[idx], pcl->cars[idx].Car_rlist->rcd_total+1, time, place, code, treat);
    printf("    ��������鿴��\n\n");
    return pcl;
}

Car AlertRcd_Car(Car car, int ridx, int time, const char* place, const char* code, const char* treat)
{
    PRN head=car.Car_rlist->rcd_head;
    int haveone=0;
    while(head->link!=NULL)
    {
        head=head->link;
        if(head->idx==ridx && head->Time==time && strcmp(head->Place, place)==0 && strcmp(head->Code, code)==0)
        {
            strncpy(head->Treat, treat, 3);
            haveone=1;
        }
    }
    if(!haveone)
    {
        car=AddRcd_Car(car, car.Car_rlist->rcd_total+1, time, place, code, treat);//���û���ҵ�����Ŀ�꣬���Զ���Υ�¼�¼��ĩβ����
    }
    return car;
}

PCL AlertRcd_Lst(PCL pcl, const char* id, int time, const char* place, const char* code, const char* treat)
{
    printf("��ӳ���Ϊ%s�ĵ�һ��Υ�¼�¼��\n", id);
    int idx=FindIdx(pcl, id);
    if(idx==-1)
    {
        printf("    ���������ڣ����Զ��������������ݣ�\n\n");
        pcl=AddCar_Lst(pcl, id);
        int tmprtot=pcl->cars[pcl->cartotal-1].Car_rlist->rcd_total;
        pcl->cars[pcl->cartotal-1]=AlertRcd_Car(pcl->cars[pcl->cartotal-1], tmprtot+1, time, place, code, treat);
        return pcl;
    }
    int tmprtot=pcl->cars[pcl->cartotal-1].Car_rlist->rcd_total;
    pcl->cars[idx]=AlertRcd_Car(pcl->cars[idx], tmprtot, time, place, code, treat);
    printf("    �����ɣ�\n\n");
    return pcl;
}

Car DelRcd_Car(Car car, int time, const char* place)//ɾ��ĳʱ��ص��Υ�¼�¼
{
    PRN head=car.Car_rlist->rcd_head;
    PRN prehead=head;
    int OriRLTol=car.Car_rlist->rcd_total;
    while(head->link!=NULL)
    {
        head=head->link;
        if(head->Time==time && strcmp(head->Place, place)==0)
        {
            if(head->link!=NULL)
            {
                head=head->link;//һ������ؿ�������ɾ���ڵ�ķ���
                free(prehead->link);
                prehead->link=head;
                head=prehead;
                car.Car_rlist->rcd_total--;
            }
            else
            {
                free(head);
                prehead->link=NULL;
                car.Car_rlist->rcd_total--;
            }
        }
        else prehead=prehead->link;
    }
    if(car.Car_rlist->rcd_total==OriRLTol)
        printf("    �ó��������ڸ���Ҫ���Υ����Ϣ��\n");
    return car;
}

PCL DelRcd_Lst(PCL pcl, const char* id, int time, const char* place)
{
    printf("ɾ�� ����%s ʱ��%d �ص�%s �ڵ�Υ����Ϣ��\n", id, time, place);
    int idx=FindIdx(pcl, id);
    if(idx==-1)
    {
        printf("    �ó��������ڣ�\n\n");
        return pcl;
    }
    pcl->cars[idx]=DelRcd_Car(pcl->cars[idx], time, place);
    printf("\n");
    return pcl;
}


int DelLst(PCL pcl)
{
    PRN head;
    PRN p;
    for(int i=0;i<pcl->cartotal;i++)
    {
        head=pcl->cars[i].Car_rlist->rcd_head;
        p=head->link;
        while(p!=NULL)
        {
            free(head);
            head=p;
            p=head->link;
        }
        free(head);
    }
    free(pcl);
    return 0;//free˳���ƺ��ֲ�Ӱ��
}

