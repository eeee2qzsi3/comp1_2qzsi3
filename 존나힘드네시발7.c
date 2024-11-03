#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORDS 60
#define MAXINDEX 10

typedef struct _entry_t{
    char *word;
    int indices [MAXINDEX];
    //단어가 나타나는 위치를 기록
} entry_t;

void addWord(entry_t concordance[], char *word){
    
    // 같은단어가 있는지 탐색 
    for(int i =0; i<MAXWORDS;i++){
        //strcmp: 0=두 문자열이 같음
        // 음수: 첫번째 문자열이 두번째보다 앞에 있음(안바꿔도됨됨)
        //양수: 첫번째 문자열이 두번째보다 뒤에있음
        if(concordance[i].word != NULL){
            //이미 단어가 존재하는 경우만 비교를 수행함함
            if(strcmp(concordance[i].word, word)==0){
                //같은 단어가 있는 지 확인후 있으면 함수종료료
                return;
            }
        }
    }
    
    
    //단ㄴ어 복붙하고 사용 안됐다고 표시
    for(int i =0; i<MAXWORDS;i++){
        if(concordance[i].word == NULL){
            //동적할당후
            concordance[i].word=(char *)malloc(sizeof(char)*strlen(word)+1);
            //word복사 붙혀넣기
            strcpy(concordance[i].word, word);
            for (int j =0; j<MAXINDEX; j++){
                concordance[i].indices[j] = -1;
                //방금 단어를 넣었기 떄문에 그 단어가 어디에서도 
                //사용되지 않았음을 표시하는거임
            }
            break;
        }
    }
    
    //알파벳정렬렬
    for(int i =0; i< MAXWORDS-1; i++){
        for(int j =0; j<MAXWORDS-1-i;j++){
            //bubblesort
            if(concordance[j].word !=NULL && concordance[j+1].word != NULL){
                //두 단어 모두 NULL이 아닌 경우에만 비교함
                if(strcmp(concordance[j].word, concordance[j+1].word)>0){
                    entry_t temp = concordance[j];
                    concordance[j] = concordance[j+1];
                    concordance[j+1] = temp;
                }
            }
        }
    }
    
        
}






void printConcordance(entry_t concordance[]){
    printf("Concordance\n");
    for(int i =0; i<MAXWORDS;i++){
        if(concordance[i].word != NULL){
            printf("%10s:", concordance[i].word);
            for(int j =0; j<MAXINDEX;j++){
                if(concordance[i].indices[j]!= -1){
                    //그자리에 index가 있으면
                    printf(" %i", concordance[i].indices[j]);
                    //앞에 뛰어쓰기 하려면 %i
                }
            } printf("\n");
        }
    }
}




void addIndex(entry_t concordance[], char *word, int index){
    //입력된 단어가 있는지 확인
    int wordnumber =-1;
    for(int i =0; i<MAXWORDS;i++){
        if(concordance[i].word != NULL){
            if(strcmp(concordance[i].word, word)==0){
                wordnumber=i;
                break;
            }
        } else{
            printf("Word %s not found\n", word);
            return;
        }
    }
    
    for(int i =0; i<MAXINDEX; i++){
        if(concordance[wordnumber].indices[i] == -1){
            //해당 단어의 인덱스 배열중 첫번째 빈공간을 찾고, 그 위치에 새로운 index를 추가가
            concordance[wordnumber].indices[i] = index;
            break;
        }
    }
    
    
}


//주어진 파일을 열고 파일의 내용을 읽어 concordance배열에 단어 추가하며 인덱스 기록
void readFile(entry_t concordance[], char *filename, int *index){
    for(int i = 0; i<MAXWORDS;i++){
        for(int j =0; j<MAXINDEX;j++){
            if(concordance[i].word!=NULL){
                //빈값에 indices값을 넣으려고 하지 않게 하기 위해해
                if(concordance[i].indices[j]>*index){
                    //현재 indices값이 *index 보다 크면 갱신함
                    //concordance 배열의 각 단어에 기록된 인덱스 값 중 가장 큰 값을 찾기 위한 것
                    *index = concordance[i].indices[j];
                }
            } else {
                break;
            }
        }
    }
    
    // 새로운 단어의 시작 인덱스를 설정하는 역할
    //*index가 0 보다 크면:
    //기본에 단어들이 추가외어있다는 의미
    //새로운 단어는 기존단어의 마지막 인덱스보다 하나 더 큰 위치에 추가되어야 하기 때문에
    //*index를 1만큼 증가 시킴
    if(*index != 0){
        *index = *index+1;
    }
    
    char wordfile[100];
    //파일에서 단어를 하나씩 읽어올때 사용됨
    //파일에서 읽은 단어를 저장하는 임시 공간
    
    int counter =0;
    //파일에서 읽어온 단어의 개수를 세기위해 초기화됨
    //몇개의 단어가 파일에서 추가되었는지를 추적함
    
    //파일 존재유무 확인
    FILE *fp;
    //fp는 파일을 가리키는 포인터
    //FILE은 C 언어에서 파일을 처리하기 위한 표준 라이브러리 타입
    
    
    fp = fopen(filename, "r");
    //fopen: 파일을 염
    //그 파일의 포인터를 fp에 저장함.
    //r: 읽기모드로 파일을 염
    //파일이 존재하지 않거나 열 수 없는 경우 fp는NULL을 반환
    
    if(fp==NULL){
        printf("Cannot open file %s\n", filename);
        return;
        //실행 종료 후 호출한 곳으로 돌아감
    }
        
        
        while (fscanf(fp, "%s", wordfile) != EOF){
        //fscanf: 파일 fp에서 단어를 읽어와 wordFile배열에 자장
        //파일의 끝(EOF)에 도달하면 EOF를 반환함
        //즉 파일이 끝날때까지 단어를 계속 읽음
        addWord(concordance, wordfile);
        //concordance배열에 wordFile에 저장된 단어를 추가함
        //새로운 단어는 배열에 추가되며, 중복된 단어는 추가 되지 않음
        addIndex(concordance,wordfile,*index+counter);
        //concordance배열의 해당 단어에 인덱스를 추가함.
        //*index+counter는 현재 단어의 위피를 나타냄
        //읽은 단어가 concordance배열의 몇번째 위치에 나타났는지 인덱스를 기록함
        //*index는 시작 인덱스를 나타내고
        //counter는 현재 읽은 단어의 개수만큼 더해져서 각 단어의 고유 인덱스를 지정함
        counter++;
        }
    printf("Inserted %i words\n", counter);
}


//concordance 배열에서 특정 단어를 제거하고 빈공간을 없애기 위해 
//배열의 나머지 부분을 앞으로 당김김
void removeWord(entry_t concordance[], char *word){
    int foundIndex =0;
    //제거할 단어의 인덱스를 저장함
    
    for(int i =0;i<MAXWORDS;i++){
    //concordance 배열의 모든 단어를 탐색함
        if (concordance[i].word != NULL){
        //현재 위치에 단어가 있는지 확인
            if(strcmp(concordance[i].word, word) == 0){
                //찾고자하는 단어와 일치하면
                free(concordance[i].word);
                //할당된메모리 해제
                concordance[i].word = NULL;
                //NULL로 설정하여 단어 제거
                foundIndex = i;
                //foundIndex에 현재 인덱스를 저장하고 루프종료료
                break;
            } 
        } else {
                printf("Word %s not found\n", word);
                //NULL이 발견되면 word가 배열에 존재하지 않음을 알리고 함수 종료 
                //같은 단어가 나올때까지 계속  if (concordance[i].word != NULL){ 여기로
                //돌아가서 확인하니까 else까지 왔다는건 문자열 끝까지 돌았는데도
                //같은단어를 못찾은거임임
                return;
            }
        }
    //배열 재정렬렬
    //foundIndex 이후의 모든 단어를 한칸 앞으로 이동시켜 배열 내의 빈공간을 제거 
    //마지막에 이동된 위치는 NULL로 설정됨됨
    for(int i = foundIndex +1;i<MAXWORDS;i++){
        if(concordance[i].word != NULL){
            concordance[i-1] = concordance[i];
            concordance[i].word =NULL;
        }
    }
}




char *findWordAtIndex(entry_t concordance[], int index){
    char *foundWord = "none";
    //founword는 함수내에서 반환할 값을 저장하는 변수
    //이는 인덱스에 해당하는 단어를 찾지 못할경우 반환됨
    
    for(int i =0; i<MAXWORDS; i++){
        //배열을 순회하여 각 단어를 검사
        if(concordance[i].word != NULL){
            //배열의 현재위치에 단어가 있을떄만 검사함
            for(int j =0;j<MAXINDEX;j++){
                //현재 단어의 indices배열을 순회하여 인덱스를 찾음
                if(concordance[i].indices[j]==index){
                    //해당인덱스가 index와 같으면 founWord에 현재 단어를 저장함 
                    foundWord = concordance[i].word;
                }
            }
        } else{
            break;
        }
    }
    if(strcmp(foundWord, "none")==0){
    //foundWord가 여전히 "none"이면 인덱스단어가 없다는 뜻
        printf("There is no word at index %i\n", index);
    } else {
        printf("The word at index %i is %s\n", index, foundWord);
    }
    return foundWord;
    //foundWord나 none을 반환함
}





void printOriginalText(entry_t concordance[]){
    int largestIndex =-1;
    //concordance에서 가장 큰 인덱스를 저장하는 변수
    
    //출력범위를 결정하기위해
    //NULL을 만나서 출력을 멈추지 않도록 출력범위를 미리 설정하는거임 
    //concordance배열을 순회하면서 각 단어의 indices값을 검사하여 가장 큰 인덱스를 찾음 
    //first 1, fourth 4, third 3 -> ? first ? third fourth according to index no.
    for(int i =0; i<MAXWORDS;i++){
        if(concordance[i].word != NULL){
            //배열의 현재위치에 단어가 있는 경우에만 인덱스를 검사함
            for(int j =0; j<MAXINDEX; j++){
                if(concordance[i].indices[j] > largestIndex) {
                    //현재 인덱스 값이 largestIndex보다 크면 largestIndex를 업데이트함 
                    largestIndex = concordance[i].indices[j];
                }
            }
        } else{
            break;
            //단어가 없는 곳에서 루프 중단
        }
    }
    
    if(largestIndex == -1){
        return;
        //concordance에 단어가 없다는 뜻 함수 종료
    }
    
    
    //단어 출력 루프
    int found =0;
    //현재 인덱스에 단어가 있는지 여부를 추적
    
    
    for(int k =0; k<largestIndex +1;k++){
        //순회하여 인덱스별로 단어를 찾음
        
        //largestIndex+1인 이유: 인덱스의 범위가 0 부터 시작하기 때문에 
        //예) largestIndex =4
        //0 1 2 3 4 까지 실행되어야 함 근데
        //for(int k =0; k<largestIndex;k++) 이렇게 하면
        // 0 1 2 3 까지만 실행됨
        for(int i =0; i<MAXWORDS; i++){
            if(concordance[i].word != NULL){
                //단어가 존재하는지확인인
                for(int j =0; j<MAXINDEX;j++){
                    //현재 단어의 indices 배열을 순회하여 인덱스 k가 포함되어있는지 확인 
                    if(concordance[i].indices[j] == k){
                        //해당 인덱스에서 단어가 발견됨됨
                        printf("%s", concordance[i].word);
                        //단어 출력후
                        found=1;
                        //단어 찾았따고 1로 바
                    }
                }
            }
        }
        
        if(found == 0){
            //해당 인덱스k에서 단어가 발견되지 않았으면 ?를 출력
            printf("?");
        }
        found =0;
        //found를 다시 0으로 초기화하여 다음 인덱스 k에 대해 새롭게 검사할 준비를 함    
        if(k!=largestIndex){
            //k가 마지막 인덱스가 아닐경우, 공백입력
            printf(" ");
        }
    }
    printf("\n");
    
}




void sortConcordance(entry_t concordance[]){
    for(int i =0;i<MAXWORDS-1;i++){
        //i 바깥쪽 루프 반복횟수
        for(int j = 0; j<MAXWORDS-1-i;j++){
        //배열의 인접한 두 요소를 비교하는 내부 루프의 인덱스스
            if(concordance[j].word !=NULL && concordance[j+1].word !=NULL){
            //배열내에 단어가 존재하는 경우에만 정렬을 수행함
                if(concordance[j].indices[0]>concordance[j+1].indices[0]||(concordance[j].indices[0] == concordance[j+1].indices[0]&&strcmp(concordance[j].word, concordance[j+1].word)>0)){
                //첫번째[j] 인덱스를 기준으로 오름차순으로 정렬
                entry_t temp = concordance[j];
                concordance[j]=concordance[j+1];
                concordance[j+1] =temp;
                //concordance[j] 와 concordance[j+1] 자리교환환
                }
            }
        }
    }
}



int main(void)
{
    char cmd;
    entry_t concordance[MAXWORDS];
    char word[100];
    int index;
    
    //초기화
    for(int i =0; i<MAXWORDS;i++){
        concordance[i].word = NULL;
    }
    
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        
        switch (cmd){
            
            case 'q':
            printf("Bye!\n");
            for (int i=0; i<MAXWORDS;i++){
                if(concordance[i].word !=NULL){
                    free(concordance[i].word);
                }
            }
            break;
            
            case 'w':
            printf("Word? ");
            scanf(" %s", word);
            addWord(concordance,word);
            break;
            
            case 'p':
            if (concordance[0].word == NULL){
                printf("The concordance is empty\n");
            } else{
                printConcordance(concordance);
            }
            break;
            
            case 'i':
            printf("Word index? ");
            scanf(" %s %d",word , &index);
            addIndex(concordance,word,index);
            break;
            
            case 'r':
            char filename[100];
            int fileindex =0;
            printf("File name? ");
            scanf(" %s", filename);
            readFile(concordance,filename, &fileindex);
            //fileindex는 int라 포인터로 콜되면 &fileindex로 씀 
            break;
            
            case 'W':
            printf("Word? ");
            scanf(" %s", word);
            removeWord(concordance, word);
            //word는스트링이라 포인터로 콜되지만 그냥 word이렇게 씀
            break;
            
            case 'f':
            printf("Index? ");
            scanf(" %i", &index);
            //%i는 int에 사용
            /*char *foundWord=*/findWordAtIndex(concordance, index);
            //findWordAtIndex를 호출하여 주어진indx에 해당하는 단어를
            //concordacne배열에서 찾고, 그 결과를 foundWord포인터에 저장
            //단어를 찾으면 반환하고 찾지 못하면 none을 반환
            
            //그냥 findWordAtIndex(concordance, index);만 쓰지 않는 이유
            //함수가 반환한 값을 사용할수 없음
            //반환된 값이 있지만, 이를 저장하거나 출력하지 않으면 프로그램이 그 값을 잃어버림
            break;
            
            case 's':
            sortConcordance(concordance);
            break;
            
            
            case 'o':
            printOriginalText(concordance);
            break;
            
            default:
            printf("Unknown command '%c'\n", cmd);
            break;
        }
    } while(cmd != 'q');
    return 0;
}
