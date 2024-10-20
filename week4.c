#include <stdio.h>
#include <string.h>
#define LENGTH 100


void printString(char string[]){
    for(int i = 0; i<LENGTH; i++){
        if(string[i] != '\0'){
            printf("%c", string[i]);
        } else {
        printf("\\0");
        }
    }
    printf("\n");
}



//❇️❇️❇️❇️
void insertName(char *startPos[], int *nrNames, char newName[]){
    
    int i = 0;
    while (newName[i] != '\0'){
        startPos[*nrNames][i] = newName[i];
        //예) startPos[3][2]: 네번째 이름의 세번째 글자를 가르킴
        //예) newName의 첫 글자를 startPos[4][0]에 저장하고,
        // 두번째 글자를 startPos[4][1] 에 저장하는 식으로 진행.
        i++;
    }
    //마지막에도 i++가 행해 졌으니 입력한 이름의 다음 칸에 위치해있음음
    startPos[*nrNames][i] = '\0';
    startPos[*nrNames+1] = startPos[*nrNames] + i +1;
    
    (*nrNames)++;
    
    
    
    
    
    
    
    
    
    
    
    
    //char* currentPos = startPos[*nrNames];
    //if((currentPos+strlen(newName)) < (startPos[0] + LENGTH)){
    //strcpy(currentPos, newName);//복사할위치 startPos[*nrNames]
    //startPos[*nrNames+1] = currentPos + strlen(newName)+1;
    
    //}
    //다음에 이름을 적을 빈칸이 어디인지 알기위해
    // startPos[*nrNames]: 지금까지 적은 이름 중 마지막 이름이 시작하는 위치
    //예) yerin -> 'y'
    
    //strlen(newName): 새로 적을 이름이 몇글자인지 세는것
    
    //+1: 이름을 적고 난 뒤에 마침표 '\0' 를 위해 한칸 더 띄어주는것
    //*nrNames++;: 메모리 주소를 증가시키려는 의미로 해석될수있어서 오류남
    //(*nrNames)++; 
    //마지막으로 이름을 몇개 적었는지 숫자를 하나 늘리는거임임
}



void printNames(char names[], char *startPos[], int nrNames){
    for(int i = 0; i<nrNames; i++){
        int startIndex = startPos[i] - names;
        //startPos[i]: 이름이 시작하는 곳을 가르킴킴
        //names: 전체 상자의 시작을 가르킴킴
        //두개의 차이를 계싼해서 이름이 배열의 몇번째 자리에서 시작하는지 알아내는 거임
        
        
        //int length = startPos[i]-startPos[i-1];
        //^ 이거 쓰면 안됨: 이러면 첫번쨰 이르미랑 비교할 전 이름이 없음
        
        int length = strlen(startPos[i])+1;
        
        printf("startPos[%d]=%02d length=%02d string=\"%s\"\n", i, startIndex, length, startPos[i]);
        //%02d: 02->두자리숫자, 숫자가 한 자리일 경우 앞에 0을 채워줌줌
    }
}







void swapNames(char *startPos[], int i, int j){
    
    //char *temp: 문자열이 있는위치를 기억하는 포인터
    // 문자열을 다룸
    
    //char temp: 한글자만 담을수있음
    //주소를 넣으려하면 문제가 생김김
    
    char *temp = {0};
    //char temp: 그냥 하나의 문자를 저장하는 변수
    //char *temp: 문자열이 저장되어 있는지 가리키는 역할할
    temp = startPos[i];
    // *temp를 사용하면 주소에 지정된 실제값(문자열)을 가져오게됨
    //하지만 문자열 자체가 아닌 그 문자열에 어디이 어디에 있는지를 알고싶은거임임
    //temp(지도), *temp(상자속 내용용)
    startPos[i] = startPos[j];
    startPos[j] = temp;
    
}







//❇️❇️뭐야사발️//❇️❇️
void removeName(char *startPos[], int *nrNames, char remName[]){
    int index= 0;
    //배열에서 이름을 찾았을때 그 이름이 위치한 자리를 저장하는 변수 0으로 시작
    
    int flag =0;
    //이름을 찾았는지 여부부
    
    
    for(int i = 0; i< *nrNames; i++){
        //차례로 배열의 이름을 하나씩 확인함 마지막까지지
        if(strcmp(startPos[i], remName) == 0){
            //그뒤에 또 같은 이름이 나오면 덮혀씌여짐짐
            flag = 1;
            //찾았으면 깃발들기기
            break;
        }
        index++;
        //이름을 찾지 못했으면 index를 하나 늘려서 다음 이름을 확인할준비비
    }
    
    if(flag == 1){
        //이름을 찾았으면 그 배열에서 그 이름을 제거하는 작업을 시작함함
            startPos[index] = startPos[*nrNames - 1];
            //배열에서 찾은 이름을 배열의 마지막 이름으로 덮어씌움움
            //예) 철수(0), 영희(1), 민수(2), 수지(3)->영희 x
            //nrNames = 4 -> 그래서 *nrNames - 1
            // 철수 수지 민수
            //문제에서: 'move the last name to the position of the name that you want to remove'
           startPos[*nrNames - 1] = startPos[*nrNames];
            //마지막 빈칸을 한칸 땡김김
            
            startPos[*nrNames] = NULL;
            //마지막 자리에는 아무것도 없으니까 NULL로 표시시
            (*nrNames)--;
            //이름을 하나 지웠으니 배열에있는 이름 개수를 1개 줄임임
    }
}




void insertionSortNames(char *startPos[], int nrNames){
    //>0: if the first non-matching character in str1 is greater than that of str2
    //<0: if the first non-matching character in str1 is lower than that of str2
    for(int i = 1; i<nrNames; i++){
        for(int j = i; j>0; j--){//i부터 0까지지
            //j=i-1: 첫번째 요소와 비교할수있는 조건을 놓칠수있음음
            if(strcmp(startPos[j],startPos[j-1])<0){
                swapNames(startPos, j, j-1);
                //세번째 친구를 두 번째 친구와 비교해. 만약 세번째 친구가 두번째
                //친구보다 키가 작으면 자리를 바꾸고, 또 첫번째 친구와도 비교해
                //계속 자리를 바꾸면서 제자리를 찾아감
            }
        }
    }
}




int totalLength(char *startPos[], int nrNames){
    int totlength=0;
    for(int i = 0; i<nrNames; i++){
        totlength+=strlen(startPos[i])+1;
    }
    return totlength;
}



int lookupNamePos(char names[], char *startPos[], int nrNames, char name[]){
    int index = -1; //찾지 못하면 -1을 반환환
    
    for(int i = 0; i<nrNames ;i++){
        if(strcmp(startPos[i], name) == 0){//이름이 일치하면
        //startPos[i]는 예를들어 names 배열의 "Getafix"라는 문자열의 시작주소를 가르킴 'G'
        //name은 사용자가 입력한 문자열을 가르킴
        //두 문자열의 내용을 하나씩 비교함함
        
        //이르미 일치하는 경우 현재위치를 계속 기록하고, 마지막으로 일치한 위치가 
        //최종적으로 반환됨됨
        index = startPos[i] - names; // 아름의 시작위차-names 배열 시작위치
        }
    }
    return index;
}





void recoverNames(char names[], char *startPos[], int *nrNames){
    for(int i = 0; i<LENGTH; i++){
        if(names[i] != '\0'){
            //names가 비어있는지 확인 안비어있고이름이 있다면 실행
            if(lookupNamePos(names, startPos, *nrNames, &names[i]) == -1){
                printf("Name \"%s\" starts at %d and is garbage\n", &names[i], i);
                //&names[i]:이름이 어디있는지 정확하게 기억하고, 그걸 필요할때 찾아갈수
                //있도록 만듬
                //names[i]:문자열이 아닌 문자 하나만 가져옴옴
                
                startPos[*nrNames] = &names[i];
                //startPos에 다시 추가
                (*nrNames)++;
            } else {
                 printf("Name \"%s\" starts at %d and is not garbage\n", &names[i], i);
            }
            i += strlen(&names[i]);
        }
    }
}






int main(void)
{
    char names [LENGTH] = {'\0'};
    char name [LENGTH] = {'\0'};
    char cmd;
    int nrNames = 0;
    int totlength=0;
    int index = 0;
    
    int i = 0;
    int j = 0;
    
    char *startPos[LENGTH] = {0};
    //char* startPos[LENGTH] = {&names[0]};
    startPos[0] = &names[0];
    
    
    
    do {
        printf("Command? ");
        scanf(" %c", &cmd);
        switch (cmd){
            
            case 'p':
                printString(names);
                //strcpy(names, "Asterix");
                //printString(names);
            break;
            
            case 'i':
                printf("Name? ");
                scanf("%s", name);
                insertName(startPos, &nrNames, name);
                //startPos는 이미 포인ㅌㅓ로 nrNames는 아직 아니니까
            break;
            
            case 'n':
                if (nrNames>0){
                    printNames(names, startPos, nrNames);
                }
            break;
            
            case 'l':
                printf("Name? ");
                scanf(" %s",name);
                index = lookupNamePos(names,startPos,nrNames,name);
                printf("\"%s\" has index %d\n", name, index);
            break;
            
            
            case 'r':
                printf("Name? ");
                scanf(" %s", name);
                //배열 자체가 그 배열의 첫번째 원소의 주소를 가리키는 포인터처럼 동직
                //remName은 이미 주소를 의미함함
                removeName(startPos, &nrNames, name);
            break;
            
            
            case 'e':
                totlength=totalLength(startPos, nrNames);
                printf("Total length is %d\n", totlength);
            break;
            
            
            case 's':
                printf("Indices? ");
                scanf(" %d %d", &i, &j);
                swapNames(startPos, i, j);
            break;
            
            
            case 'o':
                insertionSortNames(startPos, nrNames);
            break;
            
            
            case 'v':
                recoverNames(names, startPos, &nrNames);
            break;
            
            
            case 'q':
                printf("Bye!\n");
            break;
            
            default:
                printf("Unknown command '%c'\n", cmd);
            break;
        }
    } while (cmd != 'q');
    
}
