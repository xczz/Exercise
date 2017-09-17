#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 20

struct GeneralAddress
{
    char address[LEN+1];
    char name[LEN+1];
    long pnum;
};
struct GroupAddress
{
    char address[LEN+1];
    char name[LEN+1];
    char AddressList[LEN+1][LEN+1];
    int genum;

};
int InputInfo (void);
int OutputInfo (void);
int SeekInfo (void);
int AddAddress (void);
int DeleteAddress (void);
void menu (void);

int Genum,Grnum; // 在输入邮件信息时获得的General和group的邮件地址的数量
FILE *fpp; // 文件指针
struct GeneralAddress generalAddress[500];
struct GroupAddress groupAddress[200];
char ch1; // 用于处理字符
int ch2; // 用于菜单中的选择


int main() {
    menu();
    return 0;
}

int InputInfo (void)
{
    if((fpp=fopen("/Users/zzy/Desktop/address.txt","r"))==NULL)
    {
        printf("Can't open this file.\n");
        exit(0);
    }
    do
    {
        fscanf(fpp,"%c",&ch1);
        switch(ch1)
        {
            case '#':
            {
                fscanf(fpp,"%d",&Genum);
                fscanf(fpp,"%s %s %ld",generalAddress[Genum].address,generalAddress[Genum].name,&generalAddress[Genum].pnum);
                while(fgetc(fpp)!='\n')
                    continue;
            }
                break;
            case 'G':
            {
                fscanf(fpp,"%d",&Grnum);
                fscanf(fpp,"%s %s %d",groupAddress[Grnum].address,groupAddress[Grnum].name,&groupAddress[Grnum].genum);
                for(int i=0;i<groupAddress[Grnum].genum;i++)
                {
                    fscanf(fpp,"%s",groupAddress[Grnum].AddressList[i]);
                }
                while(fgetc(fpp)!='\n')
                    continue;
            }
                break;
            default:
                break;
        }
    }while(ch1=='#'||ch1=='G');
    fclose(fpp);
    return 1;
}
int OutputInfo (void)
{
    if((fpp=fopen("/Users/zzy/Desktop/Info.txt","w"))==NULL)
    {
        printf("Can't open this file.\n");
        exit(0);
    }
    for(int i=0;i<Genum+1;i++)
    {
        fprintf(fpp,"#%d\n%s\n%s\n%ld\n\n\n",i,generalAddress[i].address,generalAddress[i].name,generalAddress[i].pnum);
    }
    for(int i=0;i<Grnum+1;i++)
    {
        fprintf(fpp,"G%d\n%s\n%s\n",i,groupAddress[i].address,groupAddress[i].name);
        for (int j = 0; j <groupAddress[i].genum ; ++j) {
            fprintf(fpp,"#%d\n%s\n",j,groupAddress[i].AddressList[j]);
        }
        fprintf(fpp,"\n\n\n");
    }
    fclose(fpp);
    return 1;
}
int SeekInfo (void)
{
    char address[LEN+1];
    int signal=0;
    printf("Please input an address.\n");
    scanf("%s",address);
    for (int i = 0; i <Genum+1; ++i) {
        if(strcmp(address,generalAddress[i].address)==0)
        {
            printf("#%d\n%s\n%s\n%ld\n",i,generalAddress[i].address,generalAddress[i].name,generalAddress[i].pnum);
            signal=1;
        }
        if(signal)
            break;
    }
    if(!signal)
    {
        for (int i = 0; i <Grnum+1 ; ++i) {
            if(strcmp(address,groupAddress[i].address)==0)
            {
                printf("G%d\n%s\n%s\n",i,groupAddress[i].address,groupAddress[i].name);
                for (int j = 0; j <groupAddress[i].genum ; ++j) {
                    printf("%s\n",groupAddress[i].AddressList[j]);
                }
            }
        }
    }
    return 1;
}
int AddAddress (void)
{
    printf("What kind of address would you like to add?\n");
    printf("1.General address.\n");
    printf("2.Group address.\n");
    printf("3.Back to the main menu.\n");
    scanf("%d",&ch2);
    switch (ch2) {
        case 1: {
            Genum++;
            printf("Please input the address.\n");
            scanf("%s", generalAddress[Genum].address);
            printf("Please input the name.\n");
            scanf("%s", generalAddress[Genum].name);
            printf("Please input the phone number.\n");
            scanf("%ld", &generalAddress[Genum].pnum);
        }
            break;
        case 2: {
            Grnum++;
            printf("Please input the address.\n");
            scanf("%s", groupAddress[Grnum].address);
            printf("Please input the name.\n");
            scanf("%s", groupAddress[Grnum].name);
            printf("Please input the number of the address of the list.\n");
            scanf("%d", &groupAddress[Grnum].genum);
            for (int i = 0; i < groupAddress[Grnum].genum; ++i) {
                printf("Please input a address of the list.\n");
                scanf("%s", groupAddress[Grnum].AddressList[i]);
            }
        }
            break;
        case 3:
            return 1;
        default:
            break;
    }
    return 1;
}
int DeleteAddress (void)
{
    char address[LEN+1];
    int signal=0;
    printf("What kind of address would you like to delete?\n");
    printf("1.General address.\n");
    printf("2.Group address.\n");
    printf("3.Back to the main menu.\n");
    scanf("%d",&ch2);
    switch (ch2)
    {
        case 1:
        {
            printf("Please input the address.\n");
            scanf("%s",address);
            for (int i = 0; i <Genum+1 ; ++i) {
                if(strcmp(address,generalAddress[i].address)==0)
                {
                    for (int j = i; j <Genum+1 ; ++j) {
                        generalAddress[j]=generalAddress[j+1];
                    }
                }
            }
            Genum--;
            printf("Delete successfully.\n");
        }
            break;
        case 2:
        {
            printf("Please input the address.\n");
            scanf("%s",address);
            for (int i = 0; i <Grnum+1 ; ++i) {
                if(strcmp(address,groupAddress[i].address)==0)
                {
                    for (int j = i; j <Grnum+1 ; ++j) {
                        groupAddress[j]=groupAddress[j+1];
                    }
                }
            }
            Grnum--;
            printf("Delete successfully.\n");
        }
            break;
        case 3:
            return 1;
        default:
            break;
    }
    return 1;
}
void menu (void)
{
    printf("Welcome!\n");
    printf("1.find  information.\n");
    printf("2.Add an address.\n");
    printf("3.Remove an address.\n");
    printf("4.Read email address book.\n");
    printf("5.Save email address book.\n");
    scanf("%d",&ch2);
    switch (ch2)
    {
        case 1:
        {
            if(SeekInfo()==1)
                menu();
        }
            break;
        case 2:
        {
            if(AddAddress()==1)
                menu();
        }
            break;
        case 3:
        {
            if(DeleteAddress()==1)
                menu();
        }
            break;
        case 4:
        {
            if(InputInfo()==1)
            {
                printf("Read email address book successfully.\n");
                menu();
            }
        }
            break;
        case 5:
        {
            if(OutputInfo()==1)
            {
                printf("Save email address book successfully.\n");
                menu();
            }
        }
            break;
        default:
            break;
    }
}