#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct person {
    char *name;
    float height;
};

void removeall(struct person *persons, int nrPersons){
    if(persons ==NULL){
        return;
    } else{
        for(int i =0; i<nrPersons; i++){
        free(persons[i].name);
        persons[i].height =0.0;
        }
    }
    free(persons);
}


void printPersons(struct person persons[], int nrPersons, int from, int to){
    int print =0;
    printf("[");
    for(int i =0; i<nrPersons;i++){
        if(persons[i].name != NULL){
            if(print==0){
                printf("(\"%s\",%.3f)", persons[i].name, persons[i].height);
                print++;
            } else {
                printf(",(\"%s\",%.3f)",persons[i].name, persons[i].height);
            }
        }
    }
    printf("]\n");
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
/*    int print = 0;
    printf("[");
    for(int i =0; i<nrPersons; i++){
        if(persons[i].name == NULL || persons[i].height == 0.0){
            break;
        } else 
        if(persons[i].name != NULL){
        if( print > 0){
            printf(",(\"%s\",%f)", persons[i].name, persons[i].height);
        }else if (print == 0){
            printf("(\"%s\",%f)", persons[i].name, persons[i].height);
            print++;
        }
    }
    }
    printf("]\n");*/
}



void insertPerson(struct person persons[], int nrPersons, int newEntry, char *newName, float newHeight){
    if(newHeight<=0){
        
        printf("Height must be larger than zero\n");
        
    } else if (persons[newEntry].name != NULL || persons[newEntry].height != 0.0){
        
        printf("Entry %d is already occupied by (\"%s\",%.3f)\n", newEntry, persons[newEntry].name,persons[newEntry].height);
    
        
    } else if (persons[newEntry].name == NULL || persons[newEntry].height == 0.0){
        //저는 바보입니다.
        
        persons[newEntry].name = (char *)malloc(sizeof(char)*(strlen(newName)+1));
        strcpy(persons[newEntry].name, newName);
        persons[newEntry].height = newHeight;
        
    }
}




void maxHeight(struct person persons[], int nrPersons, float *max){
    *max=0.0;
    for(int i=0; i<nrPersons; i++){
        if(*max<persons[i].height){
            *max = persons[i].height;
        }
    }
}

float minHeight(struct person persons[], int nrPersons){
    float min =0.0;
    for(int i=0; i<nrPersons; i++){
        if(persons[i].name !=NULL){
        if(min ==0.0){
            min = persons[i].height;
        } else if(min>persons[i].height){
            min = persons[i].height;
        }
    }
    }
    return min;
}



void replacePerson(struct person persons[], int nrPersons, int newEntry, char *newName, float newHeight){
    if(newHeight<=0){
        
        printf("Height must be larger than zero\n");
        
    } else{
        free(persons[newEntry].name);
        persons[newEntry].name = (char *)malloc(sizeof(char)*(strlen(newName)+1));
        strcpy(persons[newEntry].name, newName);
        persons[newEntry].height = newHeight;
        
    }
}


int main(void)
{
    char cmd;
    struct person *persons = NULL;
    int nrPersons=0;
    
    int newEntry =0;
    char newName[80] = "";
    float newHeight =0.0;

    do{
        printf("Command? ");
        scanf(" %c",&cmd);
        
        switch(cmd){
            
            case 'q':
            printf("Bye!\n");
            removeall(persons, nrPersons);
            break;
            
            case 'n':
            removeall(persons, nrPersons);
            printf("Entries? ");
            scanf(" %d", &nrPersons);
            persons = (struct person *)malloc(nrPersons*(sizeof(struct person)));
            
            if(persons ==NULL){
                printf("malloc returned NULL\n");
                break;
            } else{
                for(int i =0; i<nrPersons; i++){
                    persons[i].name = NULL;
                    persons[i].height =0.0;
                }
            }
            break;
            
            case 'p':
            printPersons(persons, nrPersons, 0, nrPersons);
            break;
            
            case 'i':
            printf("Index? ");
            scanf(" %d", &newEntry);
            printf("Name? ");
            scanf(" %s", newName);
            printf("Height? ");
            scanf(" %f", &newHeight);
            insertPerson(persons, nrPersons, newEntry, newName, newHeight);
            break;
            
            
            case 'h':
            float max =0.0;
            printf("Min: %.3f\n",minHeight(persons, nrPersons));
            maxHeight(persons, nrPersons, &max);
            printf("Max: %.3f\n", max);
            printf("Range: %.3f\n", max-minHeight(persons, nrPersons));
            break;
            
            case 'r':
            printf("Index? ");
            scanf(" %d", &newEntry);
            printf("Name? ");
            scanf(" %s", newName);
            printf("Height? ");
            scanf(" %f", &newHeight);
            replacePerson(persons, nrPersons, newEntry, newName, newHeight);
            break;
            
            default:
            printf("Unknown command '%c'\n", cmd);
            break;
            
            
        }
        
        
    } while (cmd != 'q');
    return 0;
}
