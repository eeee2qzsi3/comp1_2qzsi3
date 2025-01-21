#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 80

struct person {
  char *name;
  float height;
};

void new(struct person** persons, int nrPersons){

    *persons = malloc(nrPersons * sizeof(**persons));
    //dereference
    if (*persons == NULL) {
        printf("Malloc failed\n");
        return;
    }
    for (int i = 0; i < nrPersons; ++i) {
         (*persons)[i].name = NULL;
         (*persons)[i].height=0.0f;
    }
    //void는 이걸 리턴 할수없음
    //고로 struct person* new(int nrPersons)
    // 써야됨
}


void freePersons(struct person** persons, int nrPersons){
    if(*persons==NULL || nrPersons <= 0){
        return;
    }
    // for(int i =0;i<nrPersons;i++){
    //     if (persons[i] != NULL && persons[i]->name != NULL) {
    //         free(persons[i]->name);
    //         persons[i]->name = NULL;
    //         persons[i]->height=0.0;
    //     }
    // }
    free(*persons);
    *persons=NULL;
}

/*
void printPersons(struct person persons[], int nrPersons, int from, int to){
    printf("[");
    for(int i =0;i<nrPersons;i++){
        if(persons[i].name != NULL){
            printf("(\"%s\",%.3f)", persons[i].name, persons[i].height);
            if(persons[i+1].name==NULL){
                break;
            }
            printf(",");
        }
    }
    printf("]\n");
}

void insertPerson(struct person persons[], int nrPersons, int newEntry, char *newName, float newHeight){
    if(newName !=NULL){
        if(persons[newEntry].name==NULL){
            persons[newEntry].name=malloc((strlen(newName)+1)*sizeof(char));
            strcpy(persons[newEntry].name,newName);
            persons[newEntry].height = newHeight;
            nrPersons++;
        }else {
            printf("Entry %d is already occupied by (\"%s\",%.3f)\n",newEntry, newName, newHeight);
            return;
        }
    }
}

*/



int main(void)
{
    char cmd;
    char name[LENGTH] ={0};
    
    int nrPersons=0;
    int newnr=0;
    int index =0;
    
    float height =0.0;
    
    struct person* persons= NULL;
    
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        
        switch (cmd){
            
            case 'i':
                printf("Index? ");
                scanf(" %d", &index);
                printf("Name? ");
                scanf(" %s", name);
                printf("Height? ");
                scanf(" %f", &height);
                
                if(height < 1){
                    printf("Height must be larger than zero\n");
                    break;
                } else{
                    // insertPerson(persons,nrPersons,index, name, height);
                }
                break;
                
            case 'p':
                // printPersons(persons, nrPersons, 0, nrPersons);
                break;
            
            case 'n':
                printf("Entries? ");
                scanf(" %d", &newnr);
                freePersons(&persons, nrPersons);
                new(&persons, newnr);
                nrPersons = newnr;
                break;
            
            case 'q':
                printf("Bye!\n");
                break;
            
            default:
                printf("Unknown command '%c'\n", cmd);
                
        }
        
    } while (cmd != 'q');
    
    freePersons(&persons, nrPersons);
    
    return 0;
}
