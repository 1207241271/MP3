//
//  main.c
//  MP3
//
//  Created by yangxu on 15/10/24.
//  Copyright (c) 2015年 yangxu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define StringLength 20

struct Node{
    int numb;
    char name[20];
    struct Node *next;
    struct Node *pre;
}*head,*temp,*body,*tail;
    FILE *FileOut;

void ADD(char name[20]);
void DELETE(char name[20]);
void SHOW();
void PLAY(int sum);
int check(char string[20]);
char *getMp3Name(int check,char string[20]);
void deleteChar(int length,char string[20]);
char *numbToString(int numb);


int main(int argc, const char * argv[]) {
    head=(struct Node *)malloc(sizeof(struct Node));
    tail=(struct Node *)malloc(sizeof(struct Node));
    head->numb=0;
    head->pre=NULL;
    head->next=tail;
    tail->pre=head;
    tail->next=NULL;
    
    
    
    FILE *FileIn;

    
    char mystring[100];
    
    FileIn=fopen("/Users/yangxu/Documents/c/c/MP3/MP3/MP3_in.txt", "r");
    FileOut=fopen("/Users/yangxu/Documents/c/c/MP3/MP3/MP3_out.txt", "w");
    if (FileIn==NULL) {
        perror("error opening file");
    }
    else{
        while (fgets(mystring, 100, FileIn)) {
            switch (check(mystring)) {
                case 1:
                    ADD(getMp3Name(1, mystring));
                    break;
                case 2:
                    DELETE(getMp3Name(2, mystring));
                    break;
                case 3:
                    SHOW();
                    break;
                case 4:
                    PLAY(tail->pre->numb);
                default:
                    break;
            }
        }
    }
    fclose(FileIn);
    fclose(FileOut);
}

void ADD(char name[20]){
    temp=(struct Node *)malloc(sizeof(struct Node));
    temp->pre=tail->pre;
    temp->next=tail;
    tail->pre->next=temp;
    tail->pre=temp;
    strcpy(temp->name, name);
    temp->numb=temp->pre->numb+1;
}

void DELETE(char name[20]){
    temp=(struct Node *)malloc(sizeof(struct Node));
    temp=head->next;
    if (strcmp(temp->name,name)==0) {
        temp->pre->next=temp->next;
        temp->next->pre=temp->pre;
    }
    while (temp->next!=NULL) {
        if (strcmp(temp->name,name)==0) {
            temp->pre->next=temp->next;
            temp->next->pre=temp->pre;
            break;
        }
        else{
            temp=temp->next;
        }
    }
    while (temp->next!=NULL) {
        temp->numb--;
        temp=temp->next;
    }
}

void SHOW(){
    temp=(struct Node *)malloc(sizeof(struct Node));
    temp=head->next;
    char result[100]="";
    char* num=numbToString(tail->pre->numb);
    int i=0;
    for (int j=0; j<strlen(num)-5; j++) {
        result[i]=num[j];
        i++;
    }
    result[i]=' ';
    i++;
    while (temp->next!=NULL) {
        for (int j=0; j<strlen(temp->name); j++) {
            result[i]=temp->name[j];
            i++;
        }
        result[i]=' ';
        i++;
        temp=temp->next;
    }
    result[i]=10;
    if(FileOut!=NULL){
        fprintf(FileOut,result);
    }
}

void PLAY(int sum){
    temp=(struct Node *)malloc(sizeof(struct Node));
    temp=head->next;
    
    int num[100]={0};
    for (int i=1; i<=sum; i++) {
        num[i]=i;
    }
    srand((unsigned)time(NULL));
    for (int i=0; i<sum; i++) {
        int mark=1;
        temp=head->next;
        while (mark) {
            
        
        int randomNum=rand()%(sum)+1;
        while (temp->next!=NULL&&num[randomNum]!=0) {
            if (temp->numb==num[randomNum]) {
                fprintf(FileOut,"%s\n",temp->name);
                num[randomNum]=0;
                mark=0;
                break;
            }
            temp=temp->next;
        }
        
        }
        
    }
    
    
    
    
    
    
    
}



int check(char string[20]){
    char add[4]="ADD";
    char delete[7]="DELETE";
    char show[5]="SHOW";
    char play[5]="PLAY";
    int mark=1;
    for (int i=0; i<3; i++) {
        if (string[i]!=add[i]) {
            mark=0;
            break;
        }
    }
    if (mark==1) {
        return 1;
    }
    mark=1;
    for (int i=0; i<6; i++) {
        if (string[i]!=delete[i]) {
            mark=0;
            break;
        }
    }
    if (mark==1) {
        return 2;
    }
    
    mark=1;
    for (int i=0; i<4; i++) {
        if (string[i]!=show[i]) {
            mark=0;
            break;
        }
    }
    if (mark==1) {
        return 3;
    }
    mark=1;
    for (int i=0; i<4; i++) {
        if (string[i]!=play[i]) {
            mark=0;
            break;
        }
    }
    if (mark==1) {
        return 4;
    }
    return 0;
}

char *getMp3Name(int check,char string[20]){
    char name[20]="";
    int j=0;
    if (check==1) {
        for (int i=4; i<=sizeof((char*)string); i++) {
            if (string[i]==10) {
                break;
            }
            name[j]=string[i];
            j++;
        }
    }else if (check==2){
        j=0;
        for (int i=7; i<=strlen(string); i++) {
            if (string[i]==10) {
                break;
            }
            name[j]=string[i];
            j++;
        }
    }
    char* result =(char*)calloc(20,sizeof(char*));
    strcpy(result,name);
    return result;
}

char *numbToString(int numb){

    int i=0;
    int n=0;
    char str[20], tmp[20];
    n = numb % 10;
    while (n>0)
    {
        tmp[i++] = n + '0';
        numb = (numb - n) / 10;
        n = numb % 10;
    }
    tmp[i] = '\0';
    for (i=0; i<=strlen(tmp)-1; i++)
    {
        str[i] = tmp[strlen(tmp)-i-1];
    }
    char* result =(char*)calloc(20,sizeof(char*));
    strcpy(result,str);
    return result;
}


