#include<stdio.h>
#include"fields.h"
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include"jval.h"
#include"jrb.h"
#define MaxWord 2500
#define Len 20
typedef struct IndexWord
{
    char name[Len];
    int count;
    JRB Dong;
}Tudien;

int KiemTraDanhTu(char *TuTruoc,char *TuKT){
    // char dot ='.';
    //  printf("%c va %c\n",TuKT[0],TuTruoc[strlen(TuTruoc)-1]);
    if ('A'<=TuKT[0] && TuKT[0]<='Z')
    {
        if (TuTruoc[strlen(TuTruoc)-1]!='.')
        {
           return 1;
        }
    }
    return 0;
}

// Tra ve gia tri ki tu con lai sau khi loc tu
int LayTu(char *word){
    int i,n=strlen(word);
    for (i = 0; i < strlen(word); i++)
    {
         if ('A'<=word[i] && word[i]<='Z') {   
            word[i]+=32;
        }
    }
}

// 1 la co trung, 0 la khong trung
int KiemTraTu(char *word,char Stopw[][Len],int StopWordLine){
    for ( int i = 0; i < StopWordLine; i++)
    {
        if (strcmp(word,Stopw[i])==0)
        {
            return 1;
        }   
    }
    return 0;
}


// Ham nay se cung voi ham loc tu va ham kiem tra tu
int ThemTu(char *word,int lineword,Tudien *Danhsach,int soluongtu,char StopArr[][Len],int StopWordLine){
    if (KiemTraTu(word,StopArr,StopWordLine)==0)
    {
        // Kiem tra xem co trong danh sach chua
        for (int i = 0; i < soluongtu; i++)
        {
            if (strcmp(Danhsach[i].name,word)==0)
            {
                jrb_insert_int(Danhsach[i].Dong,lineword,JNULL);
                Danhsach[i].count++;
                return soluongtu;
            }
        }
        strcpy(Danhsach[soluongtu].name,word);
        jrb_insert_int(Danhsach[soluongtu].Dong,lineword,JNULL);
        Danhsach[soluongtu].count++;
        soluongtu++;
    }
    return soluongtu;
}

void sapxepdanhsach(Tudien *Danhsach,int soluongtu){
    for (int i = 0; i < soluongtu-1; i++)
    {
        for (int j = i+1; j < soluongtu; j++)
        {
            if (strcmp(Danhsach[i].name,Danhsach[j].name)>0)
            {
                Tudien tmp=Danhsach[i];
                Danhsach[i]=Danhsach[j];
                Danhsach[j]=tmp;
            }
            
        }
        
    }
    
}

void ThemKiTu(char *word,char c){
    word[strlen(word)]=c;
    word[strlen(word)+1]='\0';
}

void SetTmp(char *word){
    for (int i = 0; i < Len; i++)
    {
        word[i]='\0';
    }
}

void readfromfile(char *vanban,char *topw,Tudien *Danhsach,char StopArr[][Len]) {
    IS is=new_inputstruct(topw);
    int StopWordLine=0,i,soluongtu=0;
    while (get_line(is)>0)
    {
        strcpy(StopArr[StopWordLine],is->fields[0]);
        StopWordLine++;
    }
   jettison_inputstruct(is);
    FILE *file=fopen(vanban,"r");
    int dot=-1,N=0,line=1;
    char c;
    char tmp[Len];
    if (file==NULL)
    {
        printf("Cannot read file");
        exit(1);
    }
    c=fgetc(file);
    while (c!=EOF)
    {
        if (c=='\n'){
            line++;
        }
        if ('a'<=c && c <='z')
        {
            dot=0;
            ThemKiTu(tmp,c);
        }else if ('A'<= c && c <= 'Z')
        {
            if (dot==0)
            {
                N=1;
            }
            dot=0;
            ThemKiTu(tmp,c);
        }else if (c=='.')
        {
            dot=1;
            if(N==0 && strlen(tmp)!=0){
                LayTu(tmp);
                soluongtu = ThemTu(tmp,line,Danhsach,soluongtu,StopArr,StopWordLine);
            }
            N=0;
            SetTmp(tmp);
        }
        else{
            if(N==0 && strlen(tmp)!=0){
                LayTu(tmp);
                soluongtu = ThemTu(tmp,line,Danhsach,soluongtu,StopArr,StopWordLine);
            }
            N=0;
            SetTmp(tmp);
        }
        // printf("%c",c);
        c=fgetc(file);
    }
    fclose(file);
    JRB node;
    sapxepdanhsach(Danhsach,soluongtu);
    for (int i = 0; i < soluongtu; i++)
    {
        printf("->%s|%d|",Danhsach[i].name,Danhsach[i].count);
        jrb_traverse(node,Danhsach[i].Dong){
            printf("%d ",jval_i(node->key));
        }
        printf("\n");
    }
    printf("%d", soluongtu);
}

void main() {
    Tudien DanhSach[MaxWord];
    for (int i = 0; i < MaxWord; i++)
    {
        DanhSach[i].count=0;
        DanhSach[i].Dong=make_jrb();
    }
    char StopwArr[20][Len];
    readfromfile("alice30.txt","stopw.txt",DanhSach,StopwArr);
    // printf("%d",strcmp("acb","abb"));   
}
