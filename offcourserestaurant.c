#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 16
#define MAX_BOOKINGS 10
#define LENGTH 20


struct Booking_t{
    int hour;
    char *name;
    int people;
};

void free_malloc(struct Booking_t *bookings[]){
    for(int i =0;i<MAX_BOOKINGS;i++){
        if(bookings[i]!=NULL){
            free(bookings[i]->name);
            bookings[i]->name=NULL;
            bookings[i]->hour=0;
            bookings[i]->people=0;
            free(bookings[i]);
            bookings[i]=NULL;
        }
    }
}

int free_seats(struct Booking_t *bookings[], int hour){
    int seats=MAX_SEATS;
    for(int i =0;i<MAX_BOOKINGS;i++){
        if(bookings[i]!=NULL&& bookings[i]->hour == hour){
            seats -= bookings[i]->people;
        }
    }
    return seats;
}


void print_bookings(struct Booking_t *bookings[]){
    for(int i =0;i<MAX_BOOKINGS;i++){
        if(bookings[i]!=NULL){
            printf("Name: %s\n", bookings[i]->name);
            printf(" Hour: %d\n", bookings[i]->hour);
            printf(" Number of people: %d\n", bookings[i]->people);
        }
    }
}

//시발 왜 안되는거야 맞는지 확인 부탁탁
/*void add_booking(struct Booking_t *bookings[], int hour, char *name, int people){
    int seats = free_seats(bookings, hour);
    if(people >= seats){
        printf("Could not add reservation\n");
        return;
    }
    if(name[0]!='\0'){
        for(int i =0;i<MAX_BOOKINGS;i++){
            if(bookings[i]==NULL){
                bookings[i]=malloc(sizeof(*bookings[i]));
                if(bookings[i]==NULL){
                    printf("Malloc failed\n");
                    return;
                }
                bookings[i]->name=malloc((strlen(name)+1)*sizeof(*bookings[i]->name));
                if(bookings[i]->name ==NULL){
                    printf("Malloc failed\n");
                    return;
                }
                strcpy(bookings[i]->name,name);
                bookings[i]->hour = hour;
                bookings[i]->people = people;
                return;
            }
        }
    }
}*/

void add_booking(struct Booking_t *bookings[], int hour, char *name, int people) {
  int free_index = -1;

  for (size_t i = 0; i < MAX_BOOKINGS; ++i) {
    if (bookings[i] == NULL) {
      free_index = i;
      break;
    }
  }

  if (free_seats(bookings, hour) >= people && free_index > -1) {
    bookings[free_index] = malloc(sizeof(*bookings[free_index]));
    if (bookings[free_index] == NULL) {
      fprintf(stderr, "Buy more RAM\n");
      return;
    }
    bookings[free_index]->name = malloc((strlen(name) + 1) * sizeof(*bookings[free_index]->name));
    if (bookings[free_index]->name == NULL) {
      fprintf(stderr, "Buy more RAM\n");
      return;
    }

    bookings[free_index]->hour = hour;
    strcpy(bookings[free_index]->name, name);
    bookings[free_index]->people = people;
    return;
  }
 
  printf("Could not add reservation\n");
}

void change_booking_hour(struct Booking_t *bookings[], char *name, int new_hour){
    int seats = free_seats(bookings, new_hour);
    for(int i =0;i<MAX_BOOKINGS;i++){
        if(bookings[i]!=NULL){
            if(bookings[i]->people>seats){
                printf("Could not resit %s, because at %d there are not enough seats\n", name, new_hour);
                return;
            }
            if(strcmp(bookings[i]->name,name)==0){
                int temp = bookings[i]->hour;
                bookings[i]->hour = new_hour;
                printf("Reseated %s from %d to %d\n", name, temp, bookings[i]->hour);
                return;
            }
        }
    }
}


void remove_booking(struct Booking_t *bookings[], char *name){
    for(int i=0;i<MAX_BOOKINGS;i++){
        if(bookings[i]!=NULL){
            if(bookings[i]->name !=NULL){
        if(strcmp(bookings[i]->name,name)==0){
            free(bookings[i]->name);
            bookings[i]->name=NULL;
            bookings[i]->people=0;
            bookings[i]->hour=0;
            free(bookings[i]);
            bookings[i]=NULL;
            return;
        }
        }
        }
    }
}

//❇️d일어나서 다시보기기
void sort_bookings(struct Booking_t *bookings[]){
    for(int i =0;i<MAX_BOOKINGS-1;i++){
        if(bookings[i]!=NULL){
            for(int j=i+1;j<MAX_BOOKINGS-1;j++){
                if(bookings[j]!=NULL){
                    if(bookings[i]->hour>bookings[j]->hour){
                        struct Booking_t *temp;
                        temp=bookings[i];
                        bookings[i]=bookings[j];
                        bookings[j]=temp;
                    }
                }
            }
        }
    }
}



int main(void){
    
    char cmd;
    
    int hour =0;
    int people=0;
    
    char name[LENGTH]={0};
    
    struct Booking_t* bookings[MAX_BOOKINGS]={0};
    
    printf("Welcome to restaurants booking system\n");
    
    do{
        printf("Command? ");
        scanf(" %c", &cmd);
        
        switch (cmd){
            
            case 'o':
            sort_bookings(bookings);
            break;
            
            case 'r':
            printf("Name? ");
            scanf(" %[^\n]", name);
            remove_booking(bookings, name);
            break;
            
            case 's':
            printf("Name? ");
            scanf(" %[^\n]", name);
            printf("New hour? ");
            scanf(" %d", &hour);
            change_booking_hour(bookings,name,hour);
            break;
            
            case 'a':
            printf("Hour? ");
            scanf(" %d", &hour);
            printf("Name? ");
            scanf(" %[^\n]", name);
            printf("Number of people? ");
            scanf(" %d", &people);
            add_booking(bookings, hour, name, people);
            break;
            
            case 'p':
            print_bookings(bookings);
            break;
            
            case 'q':
            break;
            
            default:
            printf("Unknown command\n");
            break;
        }
    } while(cmd != 'q');
    
    free_malloc(bookings);
    
    return 0;
}
