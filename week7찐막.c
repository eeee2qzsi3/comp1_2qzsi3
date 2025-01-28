#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORDS 60
#define MAXINDEX 10

typedef struct _entry_t{
    char *word;
    int indices[MAXINDEX];
} entry_t;



void freeconcordance(entry_t concordance[]){
    for(int i =0;i<MAXWORDS;i++){
        if(concordance[i].word != NULL){
            free(concordance[i].word);
            concordance[i].word = NULL;
            for(int j=0;j<MAXINDEX;j++){
                concordance[i].indices[j]=-1;
            }
        }
    }
}


void addWord(entry_t concordance[], char *word){
    for(int i =0;i<MAXWORDS;i++){
        if(concordance[i].word != NULL && strcmp(concordance[i].word,word)==0){
            //접근전에 null인지 항시 확인 
            return;
        }
    }
    for(int i =0;i<MAXWORDS;i++){
        if(concordance[i].word == NULL){
            concordance[i].word = malloc(sizeof(char)*(strlen(word)+1));
            //이 문자길이만큼의 문자 크기가 필요함함
            if(concordance[i].word == NULL){
                printf("Malloc failed\n");
                return;
            }
            strcpy(concordance[i].word, word);
            //조건 안에서 초기화하기기
            for(int j=0;j<MAXINDEX;j++){
            concordance[i].indices[j]=-1;
            }
            break;
            //더이상 반복할필요없으니 탈출
        }
    }
    
    for(int i =0;i<MAXWORDS;i++){
        for(int j=i+1;j<MAXWORDS;j++){
            //비교전 NULL인지 확인인
            if(concordance[i].word!=NULL && concordance[j].word!=NULL){
                if(strcmp(concordance[i].word,concordance[j].word)>0){
                    char* temp;
                    temp = concordance[i].word;
                    concordance[i].word = concordance[j].word;
                    concordance[j].word = temp;
                    //indices도 같이 스ㅡ왑해줘야지지
                    for(int x=0;x<MAXINDEX;x++){
                        int temp_;
                        temp_=concordance[i].indices[x];
                        concordance[i].indices[x]=concordance[j].indices[x];
                        concordance[j].indices[x]=temp_;
                    }
                }
            }
        }
    }
}


void printConcordance(entry_t concordance[]){
    if(concordance[0].word == NULL){
        printf("The concordance is empty\n");
        return;
    }
    printf("Concordance\n");
    for(int i =0;i<MAXWORDS;i++){
        if(concordance[i].word != NULL){
            printf("%10s:", concordance[i].word);
            for(int j=0;j<MAXINDEX;j++){
                if(concordance[i].indices[j] != -1){
                    printf(" %d", concordance[i].indices[j]);
                }else {
                    break;
                }
            }
            printf("\n");
        }
    }
}

void addIndex(entry_t concordance[], char *word, int index){
    int exist =0;
    
    for(int i =0;i<MAXWORDS;i++){
        if(concordance[i].word != NULL && strcmp(concordance[i].word,word)==0){
            for(int j=0;j<MAXINDEX;j++){
                if(concordance[i].indices[j] == -1){
                    concordance[i].indices[j] =index;
                    exist=1;
                    break;
                }
            }
        }
    }
    if(exist ==0){
        printf("Word %s not found\n", word);
        return;
    }
}


void readFile(entry_t concordance[], char *filename, int *index){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Cannot open file %s\n", filename);
        return;
    }
    char fileword[100];
    int wordcount = 0;
    while(fscanf(file, "%s", fileword)!= EOF){
        addWord(concordance, fileword);
        addIndex(concordance, fileword, *index);
        (*index)++;
        wordcount++;
    }
    printf("Inserted %d words\n", wordcount);
    fclose(file);
    
}


void removeWord(entry_t concordance[], char *word){
    int wechi=-1;
    for(int i = 0; i < MAXWORDS; i++){
        if(concordance[i].word != NULL && strcmp(concordance[i].word, word)==0){
            free(concordance[i].word);
            concordance[i].word = NULL;
            for(int j=0;j<MAXINDEX;j++){
                concordance[i].indices[j] =-1;
            }
            wechi=i;
            break;
        }
    }
    
    if(wechi == -1){
        printf("Word %s not found\n", word);
        return;
    }
    
    for(int i =wechi+1; i<MAXWORDS;i++){
        if(concordance[i].word != NULL ){
            concordance[i-1]=concordance[i];
            concordance[i].word=NULL;
        }
    }
    
}

char *findWordAtIndex(entry_t concordance[], int index){
    int found=-1;
    for(int i =0;i<MAXWORDS;i++){
        if(concordance[i].word!=NULL){
            for(int j=0;j<MAXINDEX;j++){
                if(concordance[i].indices[j]==index){
                    found = i;
                }
            }
        }
    }
    if(found == -1){
        return NULL;
    } else{
    return concordance[found].word;
    }
}

/*void printOriginalText(entry_t concordance[]){
    //index순으로 나열 
    int largestindex =-1;
    int printt=0;
    for(int i =0;i<MAXWORDS;i++){
        if(concordance[i].word != NULL){
            for(int j=0;j<MAXINDEX;j++){
                if(concordance[i].indices[j]>largestindex){
                    largestindex = concordance[i].indices[j];
                }
            }
            
        }
    }
    
    if(largestindex == -1){
        return;
    }
    for(int k =0;k<largestindex+1;k++){
        for(int i =0;i<MAXWORDS;i++){
            if(concordance[i].word != NULL){
                for(int j =0;j<MAXINDEX;j++){
                    if(concordance[i].word != NULL){
                        if(concordance[i].indices[j]==k){
                            if(printt != 0){
                            printf(" ");
                            }
                            printf("%s",concordance[i].word);
                            printt++;
                            break;
                        }
                    }
                }
            } else if(concordance[i].word == NULL){
                    if(printt != 0){
                        printf(" ");
                    }
                    printf("?");
                    break;
            }
        }
    }
    printf("\n");
    return;
}*/




int main(void)
{
    int index=0;
    
    char cmd;
    
    char word[100]={0};
    //너무 적게 설정해서 overflow생김
    char filename[100]={0};
    entry_t concordance[MAXWORDS]={0};
    //크기가 고정된 배열로 선언되어있음 
    //이미 크기 MAXWORDS만큼 메모리가 할당된 정적배열
    //각 배열의 각 요소 concordance[i]는 구조체 entry_t타입으로
    //이미 크기가 고정된 배열로 메모리가 자동으로 할당됨 
    //따라서 각 요소를 추가로 malloc으로 동적 할당할 필요가 없음
    //정해진 크기의 책꽂이
    //이미 책을 꽂을 공간이 있기 떄문에 책꽂이를 추가로 만들 필요가 없음
    
    
    //struct person* persons=NULL
    //persons는 포인터변수로 선언되어있음
    //포인터는 메모리를 직접 차지하지 않고 메모리의 주소만을 저장함
    //persons는 초기에는 아무것도 가리키지 않는 NULL포인터로 설정됨
    //메모리를 사용하려면 필요한 크기만큼 동적 메모리를 명시적으로 할당해야함
    // 테이블만 있는 상태
    //테이블은 사람들이 앉을 의자의 위치(주소)를 저장할 공간만 마련되어있지만
    //의자 자체는 없음
    //사람들이 앉을 의자를 제공하려면, 의자를 만들어(메모리 할당) 테이블과 연결해야합니다.
    
    
    for(int i =0;i<MAXWORDS;i++){
        concordance[i].word = NULL;
    }
    //구조체 안에 있는 포인터 초기화 시켜줘야함 
    
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        
        switch (cmd){
            
            /*case 'o':
            printOriginalText(concordance);
            break;*/
            
            case 'f':
            printf("Index? ");
            scanf(" %d", &index);
            char *fword = findWordAtIndex(concordance, index);
            if(fword != NULL){
                printf("The word at index %d is %s\n", index, fword);
            } else{
                printf("There is no word at index %d\n", index);
            }
            break;
            
            case 'W':
            printf("Word? ");
            scanf(" %s", word);
            removeWord(concordance, word);
            break;
            
            case 'r':
            printf("File name? ");
            scanf(" %s", filename);
            readFile(concordance, filename, &index);
            break;
            
            case 'i':
            printf("Word index? ");
            scanf(" %s %d", word, &index);
            addIndex(concordance, word, index);
            break;
            
            case 'p':
            printConcordance(concordance);
            break;
            
            case 'w':
            printf("Word? ");
            scanf(" %s", word);
            addWord(concordance, word);
            break;
            
            case 'q':
            printf("Bye!\n");
            break;
            
            default:
            printf("Unknown command '%c'\n", cmd);
            break;
            
        }
        
    } while (cmd != 'q');
    
    freeconcordance(concordance);
    
    return 0;
}
