#include <stdio.h>
#include <string.h>

#define LENGTH 100

void printString(char string[]){
    for(int i = 0; i<LENGTH; i++){
        if(string[i]!= '\0'){
            printf("%c", string[i]);
        }
        else {
            printf("\\0");
        }
    }
    printf("\n");
}


void insertName(char *startPos[], int *nrNames, char newName[]){
    int i =0;
    while(newName[i]!='\0'){
        startPos[*nrNames][i]=newName[i];
        i++;
    }
    startPos[*nrNames][i]='\0';
    startPos[*nrNames+1]=startPos[*nrNames]+i+1;
    (*nrNames)++;
}


void printNames(char names[], char *startPos[], int nrNames){
    for(int i =0; i<nrNames;i++){
        int startingposition=startPos[i]-names;
        //startPos는 각 배열의 주소를 갖고있음
        //startPos[0]=&names[0]
        int length = strlen(startPos[i])+1;
        //strlen 함수는 주어진 주소에서 \0이 나올때까지 문자의 갯수를 셈셈
        printf("startPos[%d]=%02d length=%02d string=\"%s\"\n", i, startingposition,length,startPos[i]);
        //%s를 사용하면 startPos[i] (주소)에있는 문자열이 출력됨
    }
}

int totalLength(char *startPos[], int nrNames){
    //누적 계산이 필요하므로 초기화 해야됨
    int totlength =0;
    for(int i =0;i<nrNames;i++){
        totlength += strlen(startPos[i])+1;
    }
    return totlength;
}

int lookupNamePos(char names[], char *startPos[], int nrNames, char name[]){
    int index = -1;
    for(int i =0; i<nrNames;i++){
        if(strcmp(startPos[i],name)==0){
            index = startPos[i]-names;
        }
    }
    return index;
}

void removeName(char *startPos[], int *nrNames, char remName[]){
    for(int i =0;i<*nrNames;i++){
        if(strcmp(startPos[i],remName)==0){
            startPos[i]=startPos[*nrNames-1];
            startPos[*nrNames-1]=startPos[*nrNames];//❇️
            //startPos[*nrNames]=NULL;
            (*nrNames)--;
            break;
        }
    }
}

void swapNames(char* startPos[],int i, int j){
    char *temp = startPos[i];
    startPos[i]=startPos[j];
    startPos[j]= temp;
}

void insertionSortNames(char *startPos[],int nrNames){
    for(int i =1;i<nrNames;i++){
        for(int j =i;j>0;j--){
            if(strcmp(startPos[j],startPos[j-1])<0){
                swapNames(startPos, j, j-1);
            }
        }
    }
}

/*void recoverNames(char names[], char *startPos[], int *nrNames){
    for(int j =0;j<*nrNames;j++){
        for(int i =0;i<LENGTH;i++){
            if(strcmp(startPos[j],&names[i]) ==0){
                printf("Name \"%s\" starts at %d and is not garbage\n",startPos[j],i);
            } else {
                printf("Name \"%s\" starts at %d and is garbage\n",startPos[j],i);
            }
            break;
        }
    }
}*/

void recoverNames(char names[], char *startPos[], int *nrNames){
    for(int i =0;i<LENGTH;i++){
        if(names[i]!='\0'){
            if(lookupNamePos(names, startPos, *nrNames, &names[i])==-1){
                printf("Name \"%s\" starts at %d and is garbage\n",&names[i],i);
                startPos[*nrNames]=&names[i];
                (*nrNames)++;
            } else {
                printf("Name \"%s\" starts at %d and is not garbage\n",&names[i],i);
            }
            i+=strlen(&names[i]);
        }
    }
}


int main(void)
{
    char cmd;
    char names[LENGTH]={0};
    char newName[LENGTH]={0};
    char name[LENGTH]={0};
    char remName[LENGTH]={0};
    
    char *startPos[LENGTH]={0};
    startPos[0]=&names[0];
    //startPos는 Length개의 포인터터를 저장할수있음
    //각포인터는 문자열의 시작주소를 저장할수있음음
    
    int nrNames =0;
    
    
    
    do {
        printf("Command? ");
        scanf(" %c", &cmd);
      
        switch (cmd){
            
            case 'v':
            recoverNames(names, startPos, &nrNames);
            break;
            
            case 'o':
            insertionSortNames(startPos,nrNames);
            break;
            
            case 's':
            int i;
            int j;
            printf("Indices? ");
            scanf(" %d %d", &i, &j);
            swapNames(startPos, i, j);
            break;
            
            case 'r':
            printf("Name? ");
            scanf(" %s", remName);
            removeName(startPos, &nrNames, remName);
            break;
            
            case 'l':
            printf("Name? ");
            scanf(" %s", name);
            int index=0;
            index = lookupNamePos(names, startPos, nrNames, name);
            printf("\"%s\" has index %d\n", name, index);
            break;
            
            case 'e':
            int totallength=0;
            totallength = totalLength(startPos,nrNames);
            printf("Total length is %d\n", totallength);
            break;
            
            case 'n':
            printNames(names, startPos, nrNames);
            break;
            
            case 'i':
            printf("Name? ");
            scanf(" %s", newName);
            insertName(startPos,&nrNames,newName);
            //nrNames=*nrNames=nrNames주소
            break;
            
            case 'p':
            printString(names);
            break;
            
            case 'q':
            printf("Bye!\n");
            break;
          
            default:
            printf("Unknown command '%c'\n", cmd);
            break;
        }
      
  } while (cmd != 'q');
  
  
  
  
  return 0;
}
