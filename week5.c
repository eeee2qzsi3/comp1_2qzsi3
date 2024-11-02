#include <stdio.h>
#include <string.h>
#include <stdlib.h>



struct person {
  char *name;
  float height;
};


void removeAllPersons(struct person *persons, int nrPersons){
    //NULL일때 free시도하면 메모리 접근 오류 발생
    if(persons == NULL){
        return;//함수종료료
    }    
    for(int i =0; i<nrPersons;i++){
        free(persons[i].name);
    }
    free(persons);
}


void printPersons (struct person persons[], int nrPersons, int from, int to){
    int print = 0;
    printf("[");
    for (int i = 0; i<nrPersons; i++){
        if(!(persons[i].name  == NULL)){
            if (print > 0){
                printf(",(\"%s\",%.3f)",persons[i].name, persons[i].height);
            } else {
                printf("(\"%s\",%.3f)",persons[i].name, persons[i].height);
                print++;
            }
        }
    }
    printf("]\n");
}



void insertPerson(struct person persons[], int nrPersons, int newEntry, char *newName, float newHeight){
    if (persons[newEntry].height == 0.0 && persons[newEntry].name == NULL){
        //꼭 둘다 확ㅇ니해기 안하면 leak
        persons[newEntry].name = (char *)malloc((strlen(newName)+1)*sizeof(char));
        //주로 포인터나 문자열에 사용용
        strcpy(persons[newEntry].name,newName);
        persons[newEntry].height =newHeight;
    } else {
        printf("Entry %d is already occupied by (\"%s\",%.3f)\n",newEntry,persons[newEntry].name,persons[newEntry].height);
    }
}



void maxHeight (struct person persons[], int nrPersons, float *max){
    for (int i = 0;i<nrPersons;i++){
        if (persons[i].height > *max){
            *max = persons[i].height;
        }
    }
}

float minHeight (struct person persons[], int nrPersons){
    float min=0.0;
    for(int i =0; i<nrPersons; i++){
        if (min == 0){
            min = persons[i].height;
        }
        if(min > persons[i].height&& persons[i].height != 0){
            //persons[i].height != 0, 0일 경우 비어있는값으로 간주
            min = persons[i].height;
        }
    }
    return min;
    //float이라 return해야하는듯듯
}



void replacePerson(struct person persons[], int nrPersons, int newEntry, char *newName, float newHeight){
    free(persons[newEntry].name);
    persons[newEntry].name=(char *)malloc((strlen(newName)+1)*sizeof(char));
    strcpy(persons[newEntry].name, newName);
    persons[newEntry].height = newHeight;
}
//굿굿 ~~~~~




void bubbleSort(struct person persons[], int nrPersons, int *swapped){//❇️
//이름도 확인 해야됨
    *swapped =0;
    //함수가 호출된 후 swapped값을 함수 외부에서도 변경할수있도록 하기위해서 
    for(int i =0; i<nrPersons-1;i++){
        for(int j=0;j<nrPersons-1-i;j++){
            if(persons[j].height>persons[j+1].height||(persons[j].height==persons[j+1].height&&strcmp(persons[j].name,persons[j+1].name))){
                struct person temp = persons[j];
                //char temp와 struct person을 교환할수없음음
                persons[j] = persons[j+1];
                persons[j+1] = temp;
                (*swapped)++;
                
                printf("after swapping: ");
                printPersons (persons,nrPersons, 0,1);
            }
        }
    }
    printf("Swapped %d times\n", *swapped);
}


void merge(struct person persons[], int left, int mid, int right){
    //struct person n[right-left+1];
    //정렬하는중에 기존데이터가 덮어질수있어서순서가 꼬임
    int n1 = mid-left+1;
    int n2 = right - mid; 
    
    struct person *leftArray = (struct person *)malloc(n1*sizeof(struct person));
    struct person *rightArray = (struct person *)malloc(n2*sizeof(struct person));
    
    //copy data to temp arrays
    for(int i =0;i<n1;i++){
        leftArray[i]=persons[left+i];
    }
    
    for(int j=0;j<n2;j++){
        rightArray[j]=persons[mid+1+j];
    }
    
    
    
    
    int i = 0;
    int j = 0;
    int k=left;
    //본격적으로 이간질
    //한쪽이 전멸될때까지
    while(i<n1 &&j<n2){
        //n1,n2는 인덱스가 아니라 길이라서 그냥<
        if(leftArray[i].height<rightArray[j].height||(leftArray[i].height==rightArray[j].height&&strcmp(leftArray[i].name,rightArray[j].name)<0)){
            //뒤에 height가 같은경우를 따로 계산하니까
            //여기서는 구냥 <
            persons[k] = leftArray[i];
            k++;
            i++;
        } else {
            persons[k] = rightArray[j];
            j++;
            k++;
        }
    }
    
    //왼쪽이 살아있다면면
    while(i < n1){
        persons[k] = leftArray[i];
        k++;
        i++;
    }
    
    //오른쪽이전멸
    while(i < n2){
        persons[k] = rightArray[j];
        k++;
        j++;
    }
    free(leftArray);
    free(rightArray);
}
    

void mergeSort(struct person persons[],int left, int right){
    //exit condition
    if(left<right){
        int mid=left+(right-left)/2;
        //배열의 절대적인 중간위치를 구함
        //(right+left)/2: left가 아닌 0을 기준으로 계산산
        
        //left
        mergeSort(persons, left, mid);
        
        //right
        mergeSort(persons,mid+1,right);
        
        //fight
        merge(persons,left,mid,right);
        
    } else{
        return;
    }
}



int main(void)
{
    char cmd;
    
    struct person *persons = NULL;
    
    int nrPersons = 0;
    float max =0.0;
    
    
    do{
        printf("Command? ");
        scanf(" %c",&cmd);
        
        switch (cmd){
            case 'q':
            printf("Bye!\n");
            removeAllPersons(persons, nrPersons);
            break;
            
            case 'n':
            int newnrPersons=0;
            printf("Entries? ");
            scanf("%d", &newnrPersons);
            //&nrPersons 를 그냥 쓰면 이 값이 바로 변경돼버림림
            removeAllPersons(persons, nrPersons);
            nrPersons = newnrPersons;
            persons = (struct person *)malloc(nrPersons *sizeof(struct person));
            //float는 스택 메모리에 자동으로 저장됨
            //따라서 malloc으로 동적 메모리 할당 안해도됨
            if (persons == NULL){
                printf("malloc returned NULL\n");
                break;
            } else {
                for(int i =0; i<nrPersons ; i++){
                    persons[i].name = NULL;
                    persons[i].height = 0.0;
                }
            }
            break;
            
            case 'p':
            printPersons(persons,nrPersons,0,nrPersons);
            break;
            
            
            case 'h':
            printf("Min: %.3f\n",minHeight (persons, nrPersons));
            maxHeight(persons,nrPersons,&max);
            printf("Max: %.3f\n", max);
            //max주소가 아닌 값이 필요하니가 그냥 max
            printf("Range: %.3f\n", max-minHeight (persons, nrPersons));
            break;
            
            
            case 'i':
            int newEntry =0;
            char newName[80];//[]을 씀으로써 이미 첫번째 주소를 가르치고있음
            float newHeight = 0.0;
            printf("Index? ");
            scanf(" %d", &newEntry);
            printf("Name? ");
            scanf(" %s", newName);
            //&newName은 배열 전체 주소를 가르킴
            //scanf는 문자열의 첫칸 주소를 필요로 함
            //&newName을 쓰면 scanf가 예상하는 모양이 아니어서 경고가 뜸
            //newName=첫번째 칸의 주소
            printf("Height? ");
            scanf(" %f", &newHeight);
            if (newHeight <= 0){
                //newHeight <0 이렇게만 쓰면 음수만 해당돼서 안됨
                printf("Height must be larger than zero\n");
            } else {
                insertPerson(persons,nrPersons,newEntry,newName,newHeight);
            }
            //nerName을 char* 타입, 즉 문자열의 주소로 받으려고 함. 
            //&newName을 넘기면 배열의 전체 주소를 넘기는 것과 같아서 함수가 
            //원하는 타입이 아니게돰돰
            break;
            
            
            
            case 'b':
            int swapped =0;
            bubbleSort(persons,nrPersons, &swapped);
            //swapped define 해야ㅗ딤딤
            break;
            
            
            
            case 'r'://replace
            printf("Index? ");
            scanf(" %d",&newEntry);
            printf("Name? ");
            scanf(" %s",newName);
            printf("Height? ");
            scanf(" %f",&newHeight);
            if (newHeight <= 0){
                //newHeight <0 이렇게만 쓰면 음수만 해당돼서 안됨
                printf("Height must be larger than zero\n");
            } else {
                replacePerson(persons,nrPersons,newEntry,newName,newHeight);
            }
            break;
            //긋긋 ~~~~
            
            
            case 'm':
            mergeSort(persons, 0,nrPersons-1);
            break;
            
            
            
            default:
            printf("Unknown command '%c'\n", cmd);
            break;
            
        }
    }while (cmd != 'q');
    return 0;
}
