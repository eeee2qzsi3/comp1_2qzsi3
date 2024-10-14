#include <stdio.h>
#include <string.h>
#define LENGTH 30
//int LENGTH = 20은 실행중에 값이 바뀔수있음

  
  char input [LENGTH] = {0};
  char inputOcurrence [LENGTH] = {0};
  char inputString [LENGTH] = {0};
  char inputChar [LENGTH] = {0};
  char fromString [LENGTH] = {0};
  char toChar [LENGTH] = {0};
  
  int index1 = 0;
  int index2 = 0;
  
  
void printArray(char a[], int length){
    printf("[");
    for (int i = 0; i<length; i++){
        if (a[i] == '\0'){
            printf("\\0");
        } else if (a[i] == '\n'){
            printf("\\n");
        } else {
            printf("%c", a[i]);
        }
        if (i< length -1){
            printf(",");
        }
    }
    printf("]\n");
}
    
    
    
    
void printString(char str[]){
    printf("\"");
    int i = 0;
    for(i = 0; str[i] != '\0'; i++){
        putchar(str[i]);
    }
    printf("\"\n");
}






void readLine(char str[], int length){
    //char c;
    int i = 0;
    char c;
    //for loop 밖에서도 i가 필여해서
    while ((c=getchar()) != '\n' && i<length-1){
        ////getchar을 이용해서 문자를 읽어온후 str[]에 저장
        //i<length-1 마지막자리에 NULL을 넣을자리를 남겨놓음음
        str[i] = c;
        i++;
    }
    str[i] = '\0';
    if(c!= '\n' && i ==length -1){
        //배열이 꽉 찬 후에 실행됨
        //남은 입력을 배열에 넣을수 없으므로 버퍼를 비우는 용도
        while(getchar() != '\n');
        //아무것도 하지않음, 입력버퍼를 비우기 위한 루프프
    }
}



int readInt(char str[], int length){
    int i = 0;
    int n = 0;
    while(str[i] != '\0'){
        if(str[i] >= '0' && str[i] <= '9'){
            n = 10 * n + (str[i] - '0');
            //str[i]-'0': '3'-'0'은 51-48=3 이되어 3으로 변환됨.
            //'0' = 48, '1' = 49, '2' = 50 ...
            //10*n: 숫자를 자리 수에 맞게 계산하기 위해 이전결과를 10으로 곱해줌줌
        }
        else{
            break;
        }
        i++;
    }
    return n;
}


void insertChar(char str[], char aChar, int index){
    int i = 0;
    while (str[i] != '\0'){
        //문자열의 끝을 찾는 루프
        i++;
    } while (i >= index){
        //문자를 삽입할 공간을 만들기위해
        //앞에서 문자열 끝으로 갔으니 문자열 끝에서부터 시작해서 삽입할 위치로 아동
        //각문자를 한칸 오른쪽으로 이동시키고 인덱스를 줄여가며 진행
        //예) abc이고 index=1에 x를 삽입하려면 abcc->abbc->axbc
        str[i+1]=str[i];
        i--;
    }
    str[index] = aChar;
    //인덱스 위치에 aChar을 삽입
}






int findFirstOccurrence(char str[], char aChar){
    for (int i = 0; i<strlen(str); i++){
        //strlen: 문자열의 길이를 계산해서 반환해주는 함수
        // 문자열에서 \0을 만나기 전까지의 문자길이를 세어서 반환함 
        
        //() 함수호출
        //[] 각요소의 위치치
        if (aChar == str[i]){
         return i;
         //함수가 실행을 마친후에 i 변수의 값을 호출한 곳으로 돌려줌 
        }
    }
    return -1;
    // 찾고자하는 문자가 문자열에 없을때 왜냐면 문자열의 인덱스는 0부터 시작하니까까
}






void replaceChars(char str[], char fromString[], char toChar){
    for (int i = 0; str[i] != '\0'; i++){
        //\n 대신 \0을 쓰는 이유: \0은 문자열의 끝을 표시 \n은 중간에 나타날수있으며 문자열의 끝을 의미하지 않음
        for(int l = 0; fromString[l] != '\0'; l++){
            if (str[i] == fromString[l]){
                str[i] = toChar;
                break;
            }
        }
    }
}




void stringReorder(char str[], int index1, int index2){
    char sub1 [LENGTH];
    char sub2 [LENGTH];
    char sub3 [LENGTH];
    
    strncpy(sub1, str, index1);
    //sub1 복사된 문자열이 여기에 저장됨
    //str 여기서 데이터를 복사
    //index1 복사할 최대 문자 수수
    sub1 [index1] ='\0';
    //널 문자가 나타나는 위치부터 문자열은 더 이상 유효하지 않다고 c는 판단함
    
    
    strncpy(sub2, str+index1, index2-index1);
    //str+index1: 복사할 원본 문자열의 시작 위치
    //str[]의 index1 번째 위치를 가르킴
    //index1 위치부터 복사를 시작함함
    sub2 [index2-index1] ='\0';
    //index2-index1번째 위치에 널 문자 추가가
    
    strcpy(sub3, str+index2);
    //str에서 index2이후의 모든 문자를 sub3배열에 복사
    //str+index2: str문자열의 index2 위치를 가르킴.
    //즉 str배열의 index2번째 위치에서 시작하는 문자열을 sub3에 복사
    
    strcpy(str,sub3);//str에 sub3복사
    strcat(str,sub2);//str에 sub2 추가
    strcat(str,sub1);
}




int main(void)
{
  //char string1[12] = "hello";
  //char string2[12] = "hello\n";
  //char string3[12] = "hello\n\0you\n";
  //char string4[13] = {'0','1','2','3','4','5','6','7','8','9','A','B','\0'};
  
  //printArray(string1, 12);
  //printArray(string2, 12);
  //printArray(string3, 12);
  //printArray(string4, 13);
  
  //printString(string1);
  //printString(string2);
  //printString(string3);
  //printString(string4);
  
  //char input [LENGTH] = {0};
  //char inpurArray [LENGTH] = {0};
  //char currString [LENGTH] = {0};
  //char currArray [LENGTH] = {0};
  
  do {
      printf("Command? ");
      readLine(input, LENGTH);
      
      switch (input[0]){
          
          case 'q':
          printf("Bye!\n");
          break;
          
          case 'p':
          printf("The current string is: ");
          printString(inputString);
          break;
          
          case 'a':
          printf("The current array is: ");
          printArray(inputString, LENGTH);
          break;
          
          case 's':
          printf("Please enter a string? ");
          readLine(inputString, LENGTH);
          //strcpy(currString,input);
          //strcpy(currArray,input);
          break;
          
          case 'o':
          printf("Find first occurrence of which character? ");
          readLine(inputOcurrence, LENGTH);
          int index = findFirstOccurrence(inputString, inputOcurrence[0]); //s 써서 받은 input을 curr_String에 저장하니까까
          printf("The first occurrence of '%c' is at index %d\n", inputOcurrence[0], index);
          break;
          
          case 'i':
          printf("Insert which character? ");
          readLine(inputChar, LENGTH); //inputString 하면안됨 덮혀씌여진대대
          char aChar = inputChar[0];
          printf("At what index? ");
          readLine(input, LENGTH);
          int finalIndex = readInt(input, LENGTH);
          //readLine이랑 readInt같이 쓰는 이유:
          //readLine: 사용자의 입력을 문자열로 받아옴 -> "6\0"
          //readInt: "6" 이라는 문자열을 실제숫자인 정수6으로 변환.
          insertChar(inputString, aChar, finalIndex);
          break;
          
          case 'r':
          printf("Replace which characters? ");
          readLine(fromString, LENGTH);
          // readLine은 입력된값을 직접 fromString배열에 저장하므로 char fromString = readLine()처럼 사용할수 없음음
          printf("with which character? ");
          readLine(toChar, LENGTH);
          replaceChars(inputString, fromString, toChar[0]);
          break;
          
          case 'R':
          printf("Please enter index 1? ");
          readLine(input, LENGTH);
          index1 = readInt(input, LENGTH);
          printf("Please enter index 2? ");
          readLine(input, LENGTH);
          index2 = readInt(input, LENGTH);
          stringReorder(inputString, index1, index2);
          break;
          
          default:
          printf("Unknown command '%c'\n", input[0]);
          break;
      }
  } while (input[0] != 'q');
  
  
  return 0;
}








