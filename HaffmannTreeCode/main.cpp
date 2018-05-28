#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "CodeStack.h"
#include "HaffmannTree.h"
#include "Translate.h"

using namespace std;

int main()
{
    RandFormText();//�������һ����ĸ��Ӧ��Ƶ�ʱ�����Ϊ�ļ��������������Haffmann��
    FILE* fin=fopen("d:\\codefile\\datafile\\coderand.txt","r");
    //freopen("d:\\codefile\\datafile\\HaffmannTree_outpot.txt","w",stdout);

    //////////////////////����Haffmann��//////////////////////////////////////
    int n;
    fscanf(fin,"%d",&n);
    PHT ht=CreatHtTree(n);
    InitHtTree(ht,fin);
    BuildHtTree(ht);//��ɻ��������Ĺ���
    ShowHt(ht);
    ShowHtCode(ht);
    //////////////////////////////////////////////////////////////////////////


    /////////ʵ�ֿ���̨���������ı�����Haffmann��ת��Ϊ��Ӧ�Ĵ��벢����////////
    char* text=(char*)malloc(100*sizeof(char));
    while(fgets(text,99,stdin)!=NULL)
    {
        if(*text=='\n')break;

        printf("the text is\n   %s\n",text);
        char* lock=TransTextToCode(text,ht);//����ռ䲢��ԭ�ַ���������01����
        printf("translate it to code:\n   %s\n",lock);

        char* unlock=TransCodeToText(lock,ht);//��01�����ٴ�ת����ԭ�ַ���
        printf("translate the code to text again:\n   %s\n",unlock);

        free(lock);lock=NULL;
        free(unlock);unlock=NULL;
    }
    free(text);
    //////////////////////////////////////////////////////////////////////////



    //////////////////ʵ�ֵ����ļ����ļ��ı�����01��������///////////////////
    FILE* ftext=fopen("d:\\codefile\\datafile\\CarData.txt","r");
    FILE* fcode_in=fopen("d:\\codefile\\datafile\\CarData_haff.txt","w");
    FILE* fcode_out=fopen("d:\\codefile\\datafile\\CarData_haff.txt","r");
    FILE* ftext_re=fopen("d:\\codefile\\datafile\\CarData_re.txt","w");

    TransTextToCode_byFile(ftext,fcode_in,ht);
    TransCodeToText_byFile(fcode_out,ftext_re,ht);
    ////////////////////////////////////////////////////////////////////////////

    return 0;
}
