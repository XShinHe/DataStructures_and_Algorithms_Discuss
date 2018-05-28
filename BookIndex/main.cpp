#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

char wordlist[][16]={"to","the","and","of","in","a","my","and","his","who","on","introduction"};
char seps[]=" ,\t\n";

typedef struct Book
{
    int No;
    Book* link;
}Bk, *PBk;

typedef struct Key
{
    char info[16];
    Bk head;//ͷ��㣬ͷ���Ŀռ��Ѿ����䣨ͷ��㲻��ָ�룬�����������̫�鷳��
}Key, *PK;

typedef struct KeyList
{
    Key klist[200];
    int tot;
    unsigned int maxlen;
}KL, *PKL;

PKL InputBook();
int FindWord(char** words, char* akey);
int FindKeyLoc(PKL pkl, char* akey);
int FindExist(PKL pkl, char* akey);
PKL ClrBk(PKL pkl, int loc);
int ClrKlist(PKL pkl);
PKL SetLoc(PKL pkl, int loc, char* akey, int num);
PKL CreatKey(PKL pkl, char* akey, int num);
PKL AddBook(PKL pkl, int id, int num);
PKL AddKey(PKL pkl, char* akey, int num);
int ShowIndexList(PKL pkl);
int KeyFindBook(PKL pkl, char* akey);


PKL InputBook()
{
    FILE* fin=fopen("d:\\codefile\\datafile\\booklist.txt","r");//���Ƚ�����Ӧ���ļ���

    PKL pklist=(PKL)malloc(sizeof(KL));
    pklist->tot=0;//��ʼ���ؼ��ʸ���Ϊ0
    pklist->maxlen=0;
    //for(int k=0;k<200;k++)pklist->klist[k].head.link=NULL;

    char Aline[100];//һ������
    char* token;//��ȡһ���е���
    int Num;//���
    while(fgets(Aline, 100, fin) && Aline != NULL)
    {
        token=strtok(Aline,seps);
        if(token==NULL)continue;//��ֹ���Ŀ���!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        sscanf(token,"%d",&Num);//��һ�������������
        token=strtok(NULL, seps);
        while(token!=NULL)
        {
            pklist=AddKey(pklist,token, Num);
            token=strtok(NULL, seps);
        }
    }
    return pklist;
}

int FindWord(char words[][16], char* akey)
{
    int nwrd=sizeof(wordlist)/sizeof(wordlist[0]);
    akey=_strlwr(akey);
    for(int i=0;i<nwrd; i++)
    {
        if(strcmp(words[i], akey)==0)return 1;
    }
    return 0;
}

int FindKeyLoc(PKL pkl, char* akey)//ʵ���۰���ң����ش���λ�û���Ӧ�ò����λ�ã��ر����λ������᷵��-1
{
    akey=_strlwr(akey);
    int m1=0;
    int m2=pkl->tot;//�����1��ע��tot==0��1�����
    int mid;

    if(strcmp(_strlwr( pkl->klist[m1].info ),akey)>0)return -1;//�˷���λ��������⣬-1��ʾ������λ����-1λ�ú���0����

    //ʣ���������akey�ܹ�����[m1,m2)��������
    while(m2-m1>1)//һ��������յ���m2-m1=1
    {
        mid=(m1+m2)/2;
        if(strcmp(_strlwr( pkl->klist[mid].info ),akey)>0)//�м�mid�п��ܵ���akey����ʱȫ��������m1��m2�����ܵ���akey
        {
            m2=mid;//m2���ִ���akey
        }
        else m1=mid;//m1����С�ڵ���akey
    }
    return  m1;//m1С�ڵ���akey������akeyҪ��m1�ĺ������
}

int FindExist(PKL pkl, char* akey)//��������FindKeyLoc�ж�Ԫ���Ƿ���ڣ������������𿪱���ģ�黯ʹ��
{
    int loc=FindKeyLoc(pkl, akey);
    if(loc!=-1 && strcmp(_strlwr( pkl->klist[loc].info ),_strlwr(akey))==0) return 1;
    else return 0;
}

PKL ClrBk(PKL pkl, int loc)//���booklist��¼
{
    PBk prepb=&pkl->klist[loc].head;//prepbʼ�ն���head
    PBk pb=prepb->link;
    while(pb!=NULL)
    {
        pb=pb->link;
        free(prepb);
        prepb->link=pb;
    }
    pkl->klist[loc].head.link=NULL;
    pkl->klist[loc].head.No=0;
    return pkl;
}

int ClrKlist(PKL pkl)
{
    for(int i=0;i<pkl->tot;i++)
    {
        pkl=ClrBk(pkl, i);
    }
    free(pkl);
    return 0;
}

PKL SetLoc(PKL pkl, int loc, char* akey, int num)//�������Ѿ��ƶ����˺�ʵ��ĳһλ�õĹؼ��ʸ��£�ע���������ݵ�����ͳ�ʼ��
{
    if(loc < pkl->tot) pkl=ClrBk(pkl, loc);//�������ֵ��˵��ǰ���ڳ���λ�������ڴ���Ҫ�ͷų�����

    strncpy(pkl->klist[loc].info, akey, 16);//����loc����key������&����Ҫ��Ҫ����������������������������������
    pkl->klist[loc].head.No=0;
    PBk bn=(PBk)malloc(sizeof(Bk));//����һ���µĽ���¼��Ϣ
    bn->No=num;
    bn->link=NULL;
    pkl->klist[loc].head.link=bn;//�����½ڵ㣬������Ϣbooklist��keylist
    pkl->klist[loc].head.No++;//keylist�ĸ���������������⣬��δ����
    return pkl;
}

PKL CreatKey(PKL pkl, char* akey, int num)
{
    if(pkl->tot >= 200)
    {
        printf("���\n");
        return pkl;
    }
    int loc=FindKeyLoc(pkl, akey);
    if(loc==-1)//��λ����
    {
        if(pkl->tot!=0)
        {
            for(int i=pkl->tot;i>0;i--)pkl->klist[i]=pkl->klist[i-1];//�ǿձ��ڳ���λ���ձ�ֱ�Ӳ�����λ����
        }
        pkl=SetLoc(pkl, 0, akey, num);//������λ
        pkl->tot++;
        pkl->maxlen=(strlen(akey) > pkl->maxlen)?strlen(akey):pkl->maxlen;
        return pkl;
    }
    for(int i=pkl->tot;i>loc+1;i--) pkl->klist[i]=pkl->klist[i-1];//���ڲ���loc֮���λ�ã�loc������0,1,...tot-1��������ƶ�������loc=tot-1ʱ�����ƶ�
    pkl=SetLoc(pkl, loc+1, akey, num);
    pkl->tot++;
    pkl->maxlen=(strlen(akey) > pkl->maxlen)?strlen(akey):pkl->maxlen;
    return pkl;
}

PKL AddBook(PKL pkl, int id, int num)//��key����ʱ��ֻ�����book
{
    PBk tail=&pkl->klist[id].head;//ע��ȡ��ַ����
    for(;tail->link!=NULL && tail->link->No <num ;tail=tail->link);//�ҵ�����˳��������ŵ�λ��
    PBk bn=(PBk)malloc(sizeof(Bk));//����һ���½ڵ�
    bn->No=num;
    bn->link=NULL;
    tail->link=bn;
    pkl->klist[id].head.No++;//����Ϣ���£��ｫͷ���head����Ϣ������¼�������Ԫ�������������
    return pkl;
}

PKL AddKey(PKL pkl, char* akey, int num)//pwl��wordlist���ɵı����ų����ã�
{
    int findinword=FindWord(wordlist, akey);
    if(findinword==1)return pkl;//���ôʲ����룬����ԭ�б�

    int findinkey=FindExist(pkl, akey);//�жϹؼ����Ƿ����
    if(findinkey==0)
    {
        pkl=CreatKey(pkl, akey, num);//�����ڣ��½��ؼ���
    }
    else
    {
        int loc=FindKeyLoc(pkl, akey);//���ڣ����ڹؼ���λ��loc���������ż���
        pkl=AddBook(pkl, loc, num);
    }
    return pkl;
}

int ShowIndexList(PKL pkl)
{
    printf("Keywords-Book's No. IndexList��\n");
    for(int i=0 ;i < pkl->tot;i++)
    {
        printf("    %-12.12s �� ",pkl->klist[i].info);
        PBk head=pkl->klist[i].head.link;
        for(;head!=NULL; head=head->link)
        {
            printf("  %d",head->No);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int KeyFindBook(PKL pkl, char* akey)
{
    akey=_strlwr(akey);
    if(FindExist(pkl, akey)==0)
    {
        printf("    �ؼ��ʲ����ڡ�\n");
        return -1;//�쳣
    }
    printf("Search word: \n    %-12.12s �� ",akey);
    int loc=FindKeyLoc(pkl, akey);
    PBk pb=pkl->klist[loc].head.link;
    while(pb!=NULL)
    {
        printf("  %d",pb->No);
        pb=pb->link;
    }
    printf("\n");
    return 0;
}

int main()
{
    //freopen("d:\\codefile\\datafile\\ShowIdxofBook.txt", "w", stdout);
    PKL keys=InputBook();
    ShowIndexList(keys);
    KeyFindBook(keys, "computer");
    ClrKlist(keys);
    return 0;
}
