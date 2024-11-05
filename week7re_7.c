#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORDS 60
#define MAXINDEX 10

typedef struct _entry_t{
    char *word;
    int indices [MAXINDEX];
} entry_t;






void addWord(entry_t concordance[], char *word){
    int done =0;
    entry_t temp;
    for(int i =0; i<MAXWORDS;i++){
        if(concordance[i].word != NULL && strcmp(concordance[i].word,word)==0){
            return;
        } else if(concordance[i].word == NULL){
            concordance[i].word =(char *)malloc(sizeof(char)*(strlen(word)+1));
            //메모리할당을 실패하면 concordance[i].word은 NULL
            if(concordance[i].word == NULL){
                printf("Malloc failed\n");
                return;
            }
                strcpy(concordance[i].word,word);
                for(int j=0;j<MAXINDEX;j++){
                    concordance[i].indices[j] =-1;
                }
                
                
                //순서 정렬
                do{
                    done=0;
                    for(int k=0;k<MAXWORDS-1;k++){
                        if(concordance[k].word !=NULL && concordance[k+1].word !=NULL && strcmp(concordance[k].word,concordance[k+1].word)>0){
                            temp = concordance[k];
                            concordance[k] =concordance[k+1];
                            concordance[k+1]=temp;
                            done =1;
                            break;
                        }
                    }
                } while(done ==1);
                return;
        }
    }
}



void printConcordance(entry_t concordance[]){
    if(concordance[0].word == NULL){
        printf("The concordance is empty\n");
        return;
    } else if(concordance[0].word != NULL){
        printf("Concordance\n");
        for(int i =0; i<MAXWORDS && concordance[i].word != NULL;i++){
            printf("%10s:",concordance[i].word);
            for(int j=0;j<MAXINDEX;j++){
                if(concordance[i].indices[j] != -1){
                    printf(" %i", concordance[i].indices[j]);
                }
            }
            printf("\n");
        }
    }
}




void addIndex(entry_t concordance[], char *word, int index){
    int wordnumber= -1;
    for(int i=0;i<MAXWORDS;i++){
        if(concordance[i].word != NULL){
            if(strcmp(concordance[i].word,word)==0){
                wordnumber =i;
                break;
            }
            } else {
                printf("Word %s not found\n", word);
                return;
            }
    }
    
    
    for(int i=0;i<MAXINDEX;i++){
        if(concordance[wordnumber].indices[i] == -1){
            concordance[wordnumber].indices[i] = index;
            break;
        }
    }
}



void readFile(entry_t concordance[], char *filename, int *index){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Cannot open file %s\n", filename);
        return;
    }
    
    char fileword [100];
    int wordcount=0;
    
    while(fscanf(file,"%s", fileword) != EOF){
        addWord(concordance, fileword);
        addIndex(concordance, fileword, *index);
        (*index)++;
        wordcount++;
    }
    printf("Inserted %d words\n", wordcount);
    fclose(file);
}



void removeWord(entry_t concordance[], char *word){
    int foundindex=0;
    for(int i =0; i<MAXWORDS;i++){
        if(concordance[i].word!=NULL){
            if(strcmp(concordance[i].word,word)==0){
                free(concordance[i].word);
                concordance[i].word=NULL;
                foundindex=i;
                break;
            } 
        }else{
            printf("Word %s not found\n", word);
            return;
        }
    }
    for(int i=foundindex+1;i<MAXWORDS;i++){
        if(concordance[i].word !=NULL){
            concordance[i-1]=concordance[i];
            concordance[i].word=NULL;
        }
    }
}


int main(void)
{
    char cmd;
    entry_t concordance[MAXWORDS];
    
    char word[100] ="";
    int index =0;
    
    for(int i =0;i<MAXWORDS;i++){
            concordance[i].word=NULL;
    }

    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        
        switch (cmd){
            
            case 'q':
            printf("Bye!\n");
            for(int i=0; i<MAXWORDS;i++){
                if(concordance[i].word !=NULL){
                    free(concordance[i].word);
                }
            }
            //removeall(concordance);
            break;
            
            case 'w':
            printf("Word? ");
            scanf(" %s", word);
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
            scanf(" %s", word);
            readFile(concordance, word, &index);
            break;
            
            case 'W':
            printf("Word? ");
            scanf(" %s",word);
            removeWord(concordance,word);
            break;


            default:
            printf("Unknown command '%c'\n", cmd);
            break;
        }
    } while(cmd != 'q');
    return 0;
}
