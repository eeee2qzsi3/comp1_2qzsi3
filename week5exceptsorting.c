#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 80

struct person {
  char *name;
  float height;
};



void freePersons(struct person* persons, int nrPersons){
    if(persons == NULL){
        //nrPersons==0
        //조건으로 넣지말기
        //free가 제대로 안된 상태로 종료 될수있음 
        return;
    }
    for(int i =0;i<nrPersons;i++){
         //if(persons[i].name ==NULL){
           //  return;
         //} 왜 이걸 없애면 메모리 릭크가 안뜨지 
            free(persons[i].name);
            persons[i].name = NULL;
            persons[i].height =0.0;
        }
    free(persons);
    persons = NULL;
}

void printPersons(struct person persons[], int nrPersons, int from, int to){
    int print =0;
    printf("[");
    for(int i =0;i<nrPersons;i++){
        if(persons[i].name != NULL){
            if(print!=0){
                printf(",");
            }
            printf("(\"%s\",%.3f)",persons[i].name,persons[i].height);
            print++;
        }
    }
    printf("]\n");
}

void insertPerson(struct person persons[], int nrPersons,int newEntry, char *newName, float newHeight){
    if(newHeight <= 0){
        printf("Height must be larger than zero\n");
        return;
    }    
    if(persons[newEntry].name != NULL){
        printf("Entry %d is already occupied by (\"%s\",%.3f)\n", newEntry, persons[newEntry].name, persons[newEntry].height);
        return;
    }
    if(persons[newEntry].name == NULL){
        persons[newEntry].name = malloc((strlen(newName)+1)*sizeof(persons[newEntry].name));
        if(persons[newEntry].name == NULL){
            printf("Malloc failed\n");
            return;
        }
        strcpy(persons[newEntry].name, newName);
        persons[newEntry].height = newHeight;
    }
}

void maxHeight (struct person persons[], int nrPersons, float *max){
    if(persons == NULL){
        *max =0.0;
        return;
    }
    for(int i=0;i<nrPersons;i++){
        if(persons[i].height>*max){
            *max = persons[i].height;
        }
    }
}

float minHeight(struct person persons[], int nrPersons){
    float min =0.0;
    if(persons == NULL){
        min = 0.0;
    }
    for(int i =0; i<nrPersons;i++){
        if(min == 0.0){
            min = persons[i].height;
        }
        if(persons[i].height<min && persons[i].height !=0){
            min = persons[i].height;            
        }
    }
    return min;
}

void replacePerson(struct person persons[], int nrPersons, int newEntry, char *newName, float newHeight){
    if(newHeight<=0){
        printf("Height must be larger than zero\n");
        return;
    }
    if(persons[newEntry].name == NULL){
    persons[newEntry].name = malloc(sizeof(persons[newEntry].name)*(strlen(newName)+1));
    strcpy(persons[newEntry].name, newName);
    persons[newEntry].height=newHeight;
    return;
    }
    free(persons[newEntry].name);
    persons[newEntry].name = malloc(sizeof(persons[newEntry].name)*(strlen(newName)+1));
    strcpy(persons[newEntry].name, newName);
    persons[newEntry].height=newHeight;
    //덮어씌울때 free한후 다시 동적할당해야됨 
}





int main(void)
{
    char cmd;
    char name[LENGTH] ={0};
    
    int nrPersons=0;
    int index =0;
    
    float height =0.0;
    
    struct person* persons= NULL;
    
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        
        switch (cmd){
            
            case 'r':
            printf("Index? ");
            scanf(" %d", &index);
            printf("Name? ");
            scanf(" %s", name);
            printf("Height? ");
            scanf(" %f", &height);
            replacePerson(persons, nrPersons, index, name, height);
            break;
            
            case 'h':
            float max =0;
            maxHeight (persons, nrPersons, &max);
            float min=minHeight(persons, nrPersons);
            printf("Min: %.3f\n", min);
            printf("Max: %.3f\n", max);
            printf("Range: %.3f\n", max-min);
            break;

            case 'n':
            int newnr=0;
            printf("Entries? ");
            scanf(" %d", &newnr);
            freePersons(persons, nrPersons);
            //persons = malloc(sizeof(*persons)*newnr);
            persons = malloc(sizeof(*persons)* newnr);
            //persons = (struct person*)malloc(sizeof(struct person)*newnr);
            if(persons == NULL){
                printf("Malloc failed\n");
                break;
            }else{
            for(int i =0;i<newnr;i++){
                persons[i].name = NULL;
                persons[i].height = 0.0;
            }
            }
            nrPersons = newnr;
            //printf("%d",nrPersons);
            break;
                
            case 'p':
            printPersons(persons, nrPersons, 0, nrPersons);
            break;
            
            case 'i':
            printf("Index? ");
            scanf(" %d", &index);
            printf("Name? ");
            scanf(" %s", name);
            printf("Height? ");
            scanf(" %f", &height);
            insertPerson(persons, nrPersons, index, name, height);
            break;
            
            case 'q':
            //freePersons(persons, nrPersons);
            printf("Bye!\n");
            break;
            
            default:
            printf("Unknown command '%c'\n", cmd);
            break;
                
        }
        
    } while (cmd != 'q');
    
    freePersons(persons, nrPersons);
    
    return 0;
}
