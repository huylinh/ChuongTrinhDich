#include<stdio.h>
#include"fields.h"
#include<string.h>
#include<ctype.h>
#define MaxWord 100
typedef struct IndexWord
{
    char name[100];
    int count;
    int Dong[100];
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
    int i,j,n=strlen(word);
    for (i = 0; i < n; i++)
    {
        if ('a'<=word[i] && word[i]<='z')
        {
            continue;
        }else if ('A'<=word[i] && word[i]<='Z') {   
            word[i]+=32;
        }
        else {
            for (j = i; j < strlen(word); j++)
            {
                word[j]=word[j+1];
            }
            i--;
            n--;
        }
    }
    return n;
}

// 1 la co trung, 0 la khong trung
int KiemTraTu(char *word,char Stopw[][100],int StopWordLine){
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
int ThemTu(char *word,int lineword,Tudien *Danhsach,int soluongtu,char StopArr[][100],int StopWordLine){
    if (LayTu(word)!=0 && KiemTraTu(word,StopArr,StopWordLine)==0)
    {
        // Kiem tra xem co trong danh sach chua
        for (int i = 0; i < soluongtu; i++)
        {
            if (strcmp(Danhsach[i].name,word)==0)
            {
                Danhsach[i].Dong[Danhsach[i].count]=lineword;
                Danhsach[i].count++;
                return soluongtu;
            }
        }
        strcpy(Danhsach[soluongtu].name,word);
        int tmp=Danhsach[soluongtu].count;
        Danhsach[soluongtu].Dong[tmp]=lineword;
        Danhsach[soluongtu].count++;
        soluongtu++;
        return soluongtu;
    }
    return soluongtu;
}

void sapxepdanhsach(Tudien *Danhsach,int soluongtu){
    for (int i = 0; i < soluongtu; i++)
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

void readfromfile(char *vanban,char *topw,Tudien *Danhsach,char StopArr[][100]) {
    // Doc file stopw.txt
    IS is=new_inputstruct("stopw.txt");
    int StopWordLine=0,i,soluongtu=0;
    char tmp[100];
    while (get_line(is)>0)
    {
        strcpy(StopArr[StopWordLine],is->fields[0]);
        StopWordLine++;
    }
   jettison_inputstruct(is);
    //Doc file vanban.txt 
    is=new_inputstruct("vanban.txt");
    while (get_line(is)>0)
    {
        strcpy(tmp,is->fields[is->NF-1]);
            for ( i = 0; i < is->NF; i++)
            {
                if (i==0 && is->line==1)
                {
                    soluongtu = ThemTu(is->fields[i],is->line,Danhsach,soluongtu,StopArr,StopWordLine);
                }
                else if (i==0 && is->line!=1)
                {
                    if(KiemTraDanhTu(tmp,is->fields[i])==0){
                        soluongtu = ThemTu(is->fields[i],is->line,Danhsach,soluongtu,StopArr,StopWordLine);
                    }
                }else {
                    if (KiemTraDanhTu(is->fields[i-1],is->fields[i])==0)
                    {
                       soluongtu = ThemTu(is->fields[i],is->line,Danhsach,soluongtu,StopArr,StopWordLine);
                    }
                    }
            }
        // printf("\n");
    }
    sapxepdanhsach(Danhsach,soluongtu);
    for (int i = 0; i < soluongtu; i++)
    {
        printf("%s %d ",Danhsach[i].name,Danhsach[i].count);
        for (int k = 0; k < Danhsach[i].count; k++)
        {
            printf("%d ",Danhsach[i].Dong[k]);
        }
        printf("\n");
    }    
}

void main() {
    Tudien DanhSach[MaxWord];
    for (int i = 0; i < MaxWord; i++)
    {
        DanhSach[i].count=0;
    }
    char StopwArr[MaxWord][100];
    readfromfile("vanban.txt","stopw.txt",DanhSach,StopwArr);
    // printf("%d",strcmp("acb","abb"));

    
}