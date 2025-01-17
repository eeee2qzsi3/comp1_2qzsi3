#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_DESTINATIONS 5
#define LENGTH 100

struct Airport_t {
  char *name;
  char *destinations[MAX_DESTINATIONS];
  float flight_time[MAX_DESTINATIONS];
};

int find_airport(struct Airport_t *airports[], char *name){
    int index = -1;
    for(int i =0;i<MAX_DESTINATIONS;i++){
        if(airports[i] != NULL && strcmp(airports[i]->name,name)==0){
            return i;
        }
    }
    return index;
}

void add_airport(struct Airport_t *airports[], char *name){
    int index = find_airport(airports,name);
    if(index != -1){
        printf("Airport '%s' exists\n", name);
        return;
    }
    
    if(name[0] != '\0'){
    //이름이 비어있지 않은 경우에만 실행
        for(int i =0;i<MAX_DESTINATIONS;i++){
            if(airports[i]==NULL){
            //빈슬롯확인
                airports[i]=malloc(sizeof(*airports[i]));//할당 후
                if(airports[i]==NULL){
                //할당이 잘됐는지 확인해야됨
                    printf("Malloc failed\n");
                    return;
                }
                airports[i]->name=malloc((strlen(name)+1)*sizeof(airports[i]->name));
                if(airports[i]->name==NULL){
                    printf("Malloc failed\n");
                    return;
                }
                strcpy(airports[i]->name, name);
                return;
            }
        }
    }
    
}


void print_airports(struct Airport_t *airports[]){
    printf("Airports:\n");
    for(int i=0;i<MAX_DESTINATIONS;i++){
        if(airports[i]!=NULL){
            printf("%s\n", airports[i]->name);
            for(int j=0;j<MAX_DESTINATIONS;j++){
                if(airports[i]->destinations[j]!=NULL){
                    printf(" -%s: %.2f\n", airports[i]->destinations[j], airports[i]->flight_time[j]);
                }
            }
        }
    }
}

void add_destination(struct Airport_t *airports[], char* destination1, char* destination2, float time){
    int index1=find_airport(airports, destination1);
    int index2=find_airport(airports, destination2);
    //서로의 공항을 서로의 도착지로 지정정
    if(index1==-1||index2==-1){
        printf("One of destinations does not exist\n");
        return;
    }
    
    for(int i =0;i<MAX_DESTINATIONS;i++){
        if(airports[index1]->destinations[i] == NULL){
            airports[index1]->destinations[i] = malloc((strlen(destination2)+1)*sizeof(airports[index1]->destinations[i]));
            if(airports[index1]->destinations[i] == NULL){
                printf("Malloc failed\n");
                return;
            }
            strcpy(airports[index1]->destinations[i],destination2);
            airports[index1]->flight_time[i] =time;
            break;
        }
    }
    
    for(int i =0; i<MAX_DESTINATIONS;i++){
        if(airports[index2]->destinations[i] == NULL){
            airports[index2]->destinations[i] =malloc((strlen(destination1)+1)*sizeof(airports[index2]->destinations[i]));
            if(airports[index2]->destinations[i] == NULL){
                printf("Malloc failed\n");
                return;
            }
            strcpy(airports[index2]->destinations[i],destination1);
            airports[index2]->flight_time[i] =time;
            break;
        }
    }
}

void remove_airport(struct Airport_t *airports[], char *name){
    int index = find_airport(airports, name);
    if(index == -1){
    //입력된 공항이 있는지 없는지부터 확인
        return;
    }
    //있으면
    //각각 공항의 destination에 입력된 name이 있는지확인 후
    //그 데스티네이션 삭제 ↓↓↓↓
    for(int i =0;i<MAX_DESTINATIONS; i++){
    //값이 있는 공항 찾기기
        if(airports[i]==NULL){
            continue;
        }
        for(int j=0;j<MAX_DESTINATIONS; j++){
            if(airports[i]->destinations[j] != NULL && strcmp(airports[i]->destinations[j],name)==0){
                free(airports[i]->destinations[j]);
                airports[i]->destinations[j] =NULL;
                airports[i]->flight_time[j] = 0;
            }
        }
    }
    free(airports[index]);
    airports[index]=NULL;
}

float is_connected(struct Airport_t *airports[], char *name1, char *name2, int hops){
    int index1=find_airport(airports, name1);
    int index2=find_airport(airports, name2);
    
    float smallest_time = FLT_MAX;
    int index =0;
    float time=0;
    
    if(index1 == -1|| index2 == -1 || hops < 0){
        return -1;
    }
    
    if(index1 == index2){
        return 0;
    }
    
    for(int i =0; i< MAX_DESTINATIONS; i++){
        if(airports[index1]->destinations[i]==NULL){
            continue;
        }
        
        time = is_connected(airports, airports[index1]->destinations[i], name2, hops-1);
        if(time>=0){
            if(time<smallest_time){
                smallest_time=time;
                index=i;
            }
        }
    }
    
    if(smallest_time == FLT_MAX){
        return -1;
    }
    
    return smallest_time + airports[index1]->flight_time[index];
}







int main(void){
    char cmd;
    char name[LENGTH]={0};
    char destination1[LENGTH]={0};
    char destination2[LENGTH]={0};
    
    float time;
    
    
    struct Airport_t *airports[MAX_DESTINATIONS]={0};
    
    printf("** Airports **\n");
    do{
    
    printf("Command? ");
    scanf(" %c", &cmd);
    
        switch (cmd){
            case 'q':
            printf("Bye\n");
            break;
            
            case 'a':
            printf("Name? ");
            scanf(" %s", name);
            add_airport(airports, name);
            break;
            
            case 'p':
            print_airports(airports);
            break;
            
            case 'd':
            printf("Destination1? ");
            scanf(" %s", destination1);
            printf("Destination2? ");
            scanf(" %s", destination2);
            printf("Time? ");
            scanf(" %f", &time);
            add_destination(airports,destination1,destination2,time);
            break;
            
            case 'r':
            printf("Name? ");
            scanf(" %s", name);
            remove_airport(airports, name);
            break;
            
            case 'c':
            printf("Destination1? ");
            scanf(" %s", destination1);
            printf("Destination2? ");
            scanf(" %s", destination2);
            float tottime= is_connected(airports, destination1, destination2, MAX_DESTINATIONS);
            
            if(tottime == -1){
                printf("Not connected\n");
            } else{
                printf("Flight time is %.2f\n", tottime);
            }
            break;
            
            default:
            printf("Unknown command\n");
            break;
        
        }
    }while(cmd != 'q');
    return 0;
}
