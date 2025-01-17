#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

#define MAX_DESTINATIONS 5
#define LENGTH 100

struct Airport_t {
  char *name;
  char *destinations[MAX_DESTINATIONS];
  float flight_time[MAX_DESTINATIONS];
};

int find_airport(struct Airport_t *airports[], char *name){
    int index =-1;
    for(int i =0;i<MAX_DESTINATIONS;i++){
        if(airports[i]!=NULL && strcmp(airports[i]->name,name)==0){
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
    for(int i =0;i<MAX_DESTINATIONS;i++){
        if(airports[i]==NULL){
            airports[i] = malloc(sizeof(*airports[i]));
            if(airports[i]==NULL){
                printf("Malloc failed\n");
                return;
            }
            airports[i]->name=malloc((strlen(name)+1)*sizeof(*airports[i]->name));
            if(airports[i]->name==NULL){
                printf("Malloc failed\n");
                return;
            }
            strcpy(airports[i]->name, name);
            return;
            //리턴 여기에 들어감 
            //한번에 한단어만 추가하니까,,,,,
        }
    }
    
}


void print_airports(struct Airport_t *airports[]){
    printf("Airports:\n");
    for(int i =0;i<MAX_DESTINATIONS;i++){
        if(airports[i]!=NULL){
            printf(" %s\n", airports[i]->name);
            for(int j =0;j<MAX_DESTINATIONS;j++){
                if(airports[i]->destinations[j]!=NULL){
                    printf(" -%s: %.2f\n", airports[i]->destinations[j], airports[i]->flight_time[j]);
                }
            }
        }
    }
}


void add_destination(struct Airport_t *airports[], char* destination1, char* destination2, float time){
    int index1=find_airport(airports,destination1);
    int index2=find_airport(airports,destination2);
    if(index1 == -1|| index2==-1){
        printf("One of destinations does not exist\n");
        return;
    }
    
    for(int i =0;i<MAX_DESTINATIONS;i++){
        if(airports[index1]->destinations[i]==NULL){
            airports[index1]->destinations[i]=malloc((strlen(destination2)+1)*sizeof(*airports[index1]->destinations[i]));
            if(airports[index1]->destinations[i]==NULL){
                printf("Malloc failed\n");
                return;
            }
            strcpy(airports[index1]->destinations[i],destination2);
            airports[index1]->flight_time[i]=time;
            break;
        }
    }
    
    for(int i=0;i<MAX_DESTINATIONS;i++){
        if(airports[index2]->destinations[i]==NULL){
            airports[index2]->destinations[i]=malloc((strlen(destination1)+1)*sizeof(*airports[index2]->destinations[i]));
            if(airports[index2]->destinations[i]==NULL){
                printf("Malloc failed\n");
                return;
            }
            strcpy(airports[index2]->destinations[i],destination1);
            airports[index2]->flight_time[i]=time;
            break;
        }
    }
}

void remove_airport(struct Airport_t *airports[], char *name){
    int index = find_airport(airports,name);
    
    if(index == -1){
        return;
    }
    
    //index 안쓰는 이유
    //각각 공항 순회하면서 도착지로 설정된 이름도 지워야하기 떄문에
    
    for(int i =0;i<MAX_DESTINATIONS;i++){
        if(airports[i]==NULL){
            continue;
        }
        for(int j=0;j<MAX_DESTINATIONS;j++){
            if(airports[i]->destinations[j] != NULL && strcmp(airports[i]->destinations[j],name)==0){
                free(airports[i]->destinations[j]);
                airports[i]->destinations[j]=NULL;
                airports[i]->flight_time[j]=0;
            }
        }
    }
    free(airports[index]);
    airports[index]=NULL;
}



float is_connected(struct Airport_t *airports[], char *name1, char *name2, int hops){
    int index1=find_airport(airports,name1);
    int index2=find_airport(airports,name2);
    
    int index =0;
    float smallest_time = FLT_MAX;
    
    if(index1 == -1|| index2 == -1 ||hops < 0 ){
        //printf("One of destinations does not exist\n");
        //재귀함수이기 떄문에 경유지->도착지 확인할떄 도착지가 맞지 않으면
        //탐색중이라 -1여도 괜찮은데 중간에 오류메세지가 그냥 출력되어버림
        return -1;
    }
    
    if(index1 == index2){
        return 0;
    }
    
    for(int i =0;i<MAX_DESTINATIONS;i++){
        if(airports[index1]->destinations[i]==NULL){
            continue;
        }
        float time = is_connected(airports,airports[index1]->destinations[i],name2,hops-1);
        if(time >= 0){
            if(smallest_time>time){
                smallest_time = time;
                index =i;
            }
        }
        
    }
    
    //모든 forloop이 끝났는데도 경유지를 못찾아서 아직 
    //float smallest_time = FLT_MAX;라면
    if(smallest_time == FLT_MAX){
        return -1;
    }
    
    return airports[index1]->flight_time[index]+smallest_time;
}






int main(void){
    char cmd;
    char name[LENGTH] = {0};
    char dest1[LENGTH] ={0};
    char dest2[LENGTH] ={0};
    
    float time=0;
    
    struct Airport_t* airports[MAX_DESTINATIONS] = {0};
    
    
    printf("** Airports **\n");
    
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        
        switch (cmd){
            
            case 'c':
            printf("Destination1? ");
            scanf(" %s", dest1);
            printf("Destination2? ");
            scanf(" %s", dest2);
            
            float tottime = is_connected(airports, dest1,dest2,MAX_DESTINATIONS);
            
            if(tottime==-1){
                printf("Not connected\n");
            } else {
                printf("Flight time is %.2f\n", tottime);
            }
            
            break;
            
            case 'r':
            printf("Name? ");
            scanf(" %s", name);
            remove_airport(airports, name);
            break;
            
            case 'd':
            printf("Destination1? ");
            scanf(" %s", dest1);
            printf("Destination2? ");
            scanf(" %s", dest2);
            printf("Time? ");
            scanf(" %f", &time);
            add_destination(airports, dest1, dest2, time);
            break;
            
            case 'p':
            print_airports(airports);
            break;
            
            case 'a':
            printf("Name? ");
            scanf(" %s", name);
            add_airport(airports, name);
            break;
            
            case 'q':
            printf("Bye\n");
            break;
            
            default:
            printf("Unknown command\n");
            break;
        }
        
    } while (cmd != 'q');
    
    for(int i =0;i<MAX_DESTINATIONS;i++){
        if(airports[i]!=NULL){
        remove_airport(airports, airports[i]->name);
        }
    }
    
    return 0;
}
