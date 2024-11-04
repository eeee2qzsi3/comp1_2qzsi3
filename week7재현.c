#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "predefined.h"

/*
#define MAXWORDS 60
#define MAXINDEX 10
typedef struct _entry_t{
    char *word;
    int indices[MAXINDEX];
} entry_t;
*/

void addWord(entry_t concordance[], char *word){
    int complete;
    entry_t temp;
    for(int i=0; i<MAXWORDS; i++){
        if(concordance[i].word != NULL && strcmp(concordance[i].word, word) == 0){
            return;
        }
        else if(concordance[i].word == NULL){
            concordance[i].word = (char*)malloc((strlen(word)+1)*sizeof(char));
            if(concordance[i].word == NULL){
                printf("Malloc failed\n");
                return;
            }
            strcpy(concordance[i].word, word);
            for(int j = 0; j<MAXINDEX; j++){
                concordance[i].indices[j] = -1;
            }
            do{
                complete = 0;
                for(int i = 0; i<MAXWORDS; i++){
                    if(concordance[i].word != NULL && concordance[i+1].word != NULL && strcmp(concordance[i].word, concordance[i+1].word)>0){
                        temp = concordance[i];
                        concordance[i] = concordance[i+1];
                        concordance[i+1] = temp;
                        complete = 1;
                        break;
                    }
                }
            }while(complete == 1);
            return;
        }
    }
}

void printConcordance(entry_t concordance[]){
    if(concordance[0].word == NULL){
        printf("The concordance is empty\n");
        return;
    }
    else{
        printf("Concordance\n");
        for(int i=0; i<MAXWORDS; i++){
            if(concordance[i].word != NULL){
                printf("%10s:", concordance[i].word);
                for(int j = 0; j<MAXINDEX; j++){
                    if(concordance[i].indices[j] != -1)
                    printf(" %d", concordance[i].indices[j]);
                }
                printf("\n");
            }
        }
    }
}

void addIndex(entry_t concordance[], char *word, int index){
    int n = 1;
    for(int i = 0; i<MAXWORDS; i++){
        if(concordance[i].word != NULL && strcmp(concordance[i].word, word)==0){
            for(int j = 0; j<MAXINDEX; j++){
                if(concordance[i].indices[j] == -1){
                    concordance[i].indices[j] = index;
                    n = 0;
                    break;
                }
            }
        }
    }
    if(n==1) printf("Word %s not found\n", word);
}

void readFile(entry_t concordance[], char *filename, int *index){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Cannot open file %s\n", filename);
        return;
    }
    
    char word[100];
    int wordCount = 0;
    
    while(fscanf(file, "%s", word) != EOF){
        addWord(concordance, word);
        addIndex(concordance, word, *index);
        (*index)++;
        wordCount++;
    }
    printf("Inserted %d words\n", wordCount);
    fclose(file);
}

void removeWord(entry_t concordance[], char *word){
    for(int i = 0; i<MAXWORDS; i++){
        if(concordance[i].word != NULL && strcmp(concordance[i].word, word)==0){
            free(concordance[i].word);
            concordance[i].word = NULL;
            for(int j = i; j<MAXWORDS-1; j++){
                concordance[j].word = concordance[j+1].word;
                for(int k=0; k<MAXINDEX; k++){
                    concordance[j].indices[k] = concordance[j+1].indices[k];
                }
            }
            return;
            /*concordance[MAXWORDS-1].word = NULL;
            for(int k = 0; k<MAXINDEX; k++){
                concordance[MAXWORDS - 1].indices[k] = -1;
            }
            return;*/
        }
    }
    printf("Word %s not found\n", word);
}

char *findWordAtIndex(entry_t concordance[], int index){
    //char temp[50] = "";
    for(int i = 0; i<MAXWORDS; i++){
        if(concordance[i].word != NULL){
            for(int j = 0; j<MAXINDEX; j++){
                if(concordance[i].indices[j] == index){
                    //strcpy(temp, concordance[i].word);
                    //return temp;
                    return concordance[i].word;
                } 
            }
        }
    }
    return NULL;
}

void sortConcordance(entry_t concordance[]){
    
}

int main(void){
    char cmd;
    
    entry_t concordance[MAXWORDS] ={0};
    for(int i = 0; i<MAXWORDS; i++){
        concordance[i].word = NULL;
    }
    
    char word[100] = "";
    int index= 0;
    char filename[100] = "";
    
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        
        switch(cmd){
            case 'w':
            printf("Word? ");
            scanf("%s", word);
            addWord(concordance, word);
            break;
            case 'p':
                printConcordance(concordance);
                break;
            case 'i':
                printf("Word index? ");
                scanf("%s %d", word, &index);
                addIndex(concordance, word, index);
                break;
            case 'r':
                printf("File name? ");
                scanf("%s", filename);
                readFile(concordance, filename, &index);
                break;
            case 'W':
                printf("Word? ");
                scanf("%s", word);
                removeWord(concordance, word);
                break;
            case 'f':
                printf("Index? ");
                scanf("%d", &index);
                if(findWordAtIndex(concordance, index) == NULL){
                    printf("There is no word at index %d\n", index);
                }
                else{
                    printf("The word at index %d is %s\n", index, findWordAtIndex(concordance,index));
                }
                break;
            case 'q':
                printf("Bye!\n");
                break;
            default:
                printf("Unknown command '%c'\n", cmd);
                break;
        }
    } while(cmd != 'q');
    
    for(int i = 0; i<MAXWORDS; i++){
        if(concordance[i].word != NULL)
        free(concordance[i].word);
    }
    
}
