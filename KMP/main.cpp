#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int* CalNext(char* mode)
{
    int modetot=strlen(mode);//��¼mode�ĳ���
    int* next=(int*)malloc(modetot*sizeof(int));//����һ����������
    //
    int i =0;
    int k=-1;
    next[i]=k;//��ʼ��next[0]=-1��next�����¼i֮ǰ(ע���ǲ�����i֮ǰ�ģ�����)��������Ӽ��ظ�ǰ��׺���ȼ�Ϊk��������һ��j���k=-1
                //nextҲ�������k��i�ԱȲ��ɹ���ʹ�õ���һ��k�ĶԱȵ�ַ
    while(i<modetot-1)//��Ȼi<modetot-1����һ��ѭ���������next[i+1],�������
    {
        //����next[i]���Ѿ�������ˣ�i-1ǰ�����ظ�ǰ��׺����k���ٽ��mode[i]�����ʼ���mode[i+1]
        while(k>=0 && mode[i]!=mode[k]) k=next[k];//k<=i-1����ָ��i����Ŀ�꣬k����ģʽ
        //k=-1��next��˵����һ�����j��ƽ�ƣ�i++��k=0��Ϊ��������һ�����
        //mode[i]=mode[k],��ômode[i+1]֮ǰ��������Ӽ��ظ�ǰ��׺������mode[i]+1��next���Ҳ��ֱ�ӵõ���
        //����mode[i]ǰֻ��k����ͬ������mode[i+1]��ģʽָ���ַ��1��Ŀ��ָ���ַ��1����ʵ�ǵ�mode[i]����mode[i+1]ǰ�����һ��Ԫ�أ����Ա�
        //�����ƥ�䣬��Ծģʽָ���ַk������ֱ��mode[k]=mode[i]��
        //����k�ǵ�ַ��֮ǰһ���Ѿ���k��ǰ׺��ͬ����������mode[i+1]��˵һ����k+1��ǰ׺,
        i++;k++;
        if(mode[i]==mode[k]) next[i]=next[k];
        //�������Ѿ��������next[i]=k��������j��i����ʱ,����next[i]=k�Ƚϣ����mode[i]==mode[k]��ô��Ȼ��Ҫ�ٻ�k�ĵ�ַ��������ǰ����
        else next[i]=k;//�������next[i]=k;
    }
    return next;
}

int Strfindstr(char* target, char* mode)
{
    int targettot=strlen(target);int modetot=strlen(mode);
    int* Next=CalNext(mode);
    printf("next����Ϊ��\n");
    for(int k=0;k<modetot;k++)printf("%d  ",Next[k]);//��ʾnext���������
    int j=0;//ָ��Ŀ��
    int i=0;//ָ��ģʽ
    while(j < targettot && i < modetot)
    {
        if(i==-1 || target[j]==mode[i])//ƥ��ɹ������¿�ʼʱ
        {
            j++;
            i++;
        }
        else i=Next[i];//ijƥ�䲻�ɹ���iָ�뻻��ַ����ַ֮ǰ���Ѿ���֤ƥ�䣩
    }
    if(i >= modetot)//�յ�Ӧ����jָ��û�е�ͷ����iָ��ָ����mode�е�"\0"��ע�����������j��ָ���Ӧmode�е�"\0"
    {
        printf("\n\n�Ӵ�λ�ôӵ�%d���ַ�����ʼ:\n",j-i+1);//��������Ӵ���λ��ĸ������ţ���1��ʼ��������������㿪ʼ������Ӧ�÷���j-1
        return j-modetot+1;
    }
    else
    {
        printf("None\n");
        return  -1;//û���ҵ�
    }
}

int main()
{
    char a[]="aabcbabcaabcaababc";
    char mode[]="abcaababc";
    int i=Strfindstr(a,mode);
    printf("%s\n",a);
    for(int j=0;j<i-1;j++)printf(" ");
    printf("%s\n",mode);
    return 0;
}
