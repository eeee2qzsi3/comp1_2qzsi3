#include <stdio.h>
#include <stdlib.h>


#define START 'S'
#define DESTINATION 'D'
#define PATH '+'
#define WALL '#'
#define UNSEEN '.'
#define SEEN '~'


/*❇️*/

typedef struct{
    char *grid;
    int maxX;
    int maxY;
} navigation_t;



void newGrid(navigation_t *nav){//여기선 nav가구조체 포인터임임
    //*nav는 navigation_t 전체를 가리키는 포인터임
    //nav포인터를 통해 navigation_t구조체 안에있는 모든 멤버들에 접근가능
    
    //이미 존재하는 그리드가 있을 때 해제하기
    if(nav->grid != NULL){
        free(nav->grid);
        //이미 할당된 메모리를 해제하여 메모리누수를 방지
        nav->grid = NULL;
        //포인터를 NULL로 설정해 다음에 사용할때 오류를 방지
        nav->maxX = 0;
        nav->maxY = 0;
        //nav는 구조체를 직접 담고있는 변수가 아니라 그 구조체를 가르키는 포인터
        //포인터를 통해 구조체의 멤버에 접근할때는 ->을 사용
        //만약 .을 사용하려면 (*nav).maxX라고 써야하니 더 간단하게 쓰기위해 ->를 사용용
        
    }
    
    printf("Number of rows? ");
    scanf(" %d", &nav->maxY);
    printf("Number of columns? ");
    scanf(" %d", &nav->maxX);
    
    if(nav->maxX<2||nav->maxY<2){
        printf("The number of rows and columns must be at least two\n");
        return; //함수종료
    }
    
    //2보다 작지 않다면
    //grid에 입력된 만큼 공간을 만들기위에 동적할당 해야됨
    nav->grid = (char *)malloc(sizeof(char) * nav->maxX * nav->maxY);
    //동적할당이 그리드에 연결됨
}







void inputGrid(navigation_t nav){//여기선nav가 구조체 변수임임
    int startcount = 0;
    //입력받은 그리드에서 시작점이 몇개인지 세기
    for(int j=0; j<nav.maxY; j++){
        //첫번째줄
        printf("Input row %d: ", j);
        for(int i =0; i<nav.maxX;i++){
            //nav.maxX안됨
            /*❇️ struct 변수이면 nav.maxX
                struct포인터이면 nav->maxX*/
            //한칸한칸
            scanf(" %c", &nav.grid[j*nav.maxX+i]);
            //그리드 칸에 한글자씩 입력받기위해해
            
            /*❇️ nav.grid는 1차원 배열처럼 선언됨*/
            //프로그램에서 2차원 그리드 처럼 사용하려면 2차원 위치를 1차원 인덱스로 변환해야됨
            /*❇️ y*nav.maxX+x 는 그리드에서 2차원위치 (x,y))를
            1차원 배열의 인덱스로 변환한것
            ❇️ 공식 j*가로크기 +i*/
            if(nav.grid[j*nav.maxX+i]=='S'){
                //첫번째 값을 원하기 때문에 주소 안씀씀
                startcount++;
                //startpoint 세기기
                if(startcount>1){
                    //startpoint가 한개 이상일때때
                    printf("Extra starting point\n");
                    //wall로 replace]함함
                    nav.grid[j*nav.maxX+i] = '#';
                }
            }
        }
    }
}




void printGrid(navigation_t nav){
    for(int j =0;j<nav.maxY;j++){
        for(int i=0; i<nav.maxX;i++){
            printf("%c", nav.grid[j*nav.maxX+i]);
            //printf니까 %c앞에 공백 필요없음
        }
        printf("\n");
    }
}




typedef struct{
    int x;
    int y;
} position_t;



position_t findStart(navigation_t nav){
    position_t start;
    //start라는potition_t타입의 변수를 선언하여 시작위치를 저장할 준비 
    int startp =0;
    int destp=0;
    
    
    for(int j=0; j<nav.maxY;j++){
        for(int i=0;i<nav.maxX;i++){
            if(nav.grid[j*nav.maxX+i] == 'S'){
                startp++;
                start.x=i;
                start.y=j;
            }
            if(nav.grid[j*nav.maxX+i] == 'D'){
                destp++;
            }
        }
    }
    if(startp<1){
        printf("Grid contains no starting point\n");
        start.x=-1;
    }
    if (destp<1){
        printf("Grid contains no destination\n");
        start.x=-1;
        //함수의 반환타입이 position_t이기 떄문에
        //position_t 타입의 변수를 반환해야됨됨
        return start;
        //탈출시키기기
    }
    return start;
    //없으면 안됨
}





int findPath(navigation_t nav, int x, int y, int length){
    int lengthn=0;
    int lengthe=0;
    int lengths=0;
    int lengthw=0;
    //미로에서 벗어났는지 확인
    //maxX, maxY0부터 시작하니까 이상으로 표현해야됨됨
    if(nav.maxX<=x || x<0 || nav.maxY<=y || y<0){
        return 0;
    }
    
    //탐색불가능한경우
    else if(nav.grid[y*nav.maxX+x]==WALL||nav.grid[y*nav.maxX+x]==SEEN||nav.grid[y*nav.maxX+x]==PATH||(nav.grid[y*nav.maxX+x]==START && length>0)){
    //nav.grid[y*nav.maxX+x]==PATH: 이미 탐색중인 길을 다시 탐색하지 않도록 방지
    //nav.grid[y*nav.maxX+x]==START && length>0: 탐색경로가 시작덤으로 돌아오는 경우를 방지 
        return 0;
    }
    
    //목적지 도달
    else if(nav.grid[y*nav.maxX+x]==DESTINATION){
        return length;
    }
    
    //경로표시
    /*위에 모두가 해당사항이 아니고 시작점이 아니라면
    움직일수있는 조건이 성립되기 때문에 PATH*/
    else if (nav.grid[y*nav.maxX+x]!=START){
        nav.grid[y*nav.maxX+x]=PATH;
        //헌재위치가 시작점이 아닌경우 경로 표시시
    }
    
    
    //lengthn이 0이 아닌경우에 참으로 평가되어 조건이 실행됨
    //❇️double bracket 해야됨됨
    //findPath()는 경로 탐색중 목적지를 찾았을깨 길이를 반환함함
    //North
    if((lengthn=findPath(nav,x,y-1,length+1))){
        return lengthn;
    }
    //East
    if((lengthe=findPath(nav,x+1,y,length+1))){
        return lengthe;
    }
    //South
    if((lengths=findPath(nav,x,y+1,length+1))){
        return lengths;
    }
    //West
    if((lengthw=findPath(nav,x-1,y,length+1))){
        return lengthw;
    }
    
    /*탐색경로에서 더이상 진행할수없을때, 그 위치를 다시 돌아오지
    돌아오지 않도록 표시하는 역할*/
    if(nav.grid[y*nav.maxX+x]==UNSEEN||nav.grid[y*nav.maxX+x]==PATH){
        nav.grid[y*nav.maxX+x]=SEEN;
    }
    return 0;
    /*탐색이 실패하거나 진행할수없는경우, 함수는 0을 반환하여 현재경로
    에서는 유효한 결과가 없음을 나타*/
}


void resetPath(navigation_t nav){
    for(int y =0; y<nav.maxY; y++){
        for(int x =0; x<nav.maxX; x++){
            if (nav.grid[y*nav.maxX+x]==SEEN || nav.grid[y*nav.maxX+x]==PATH){
            nav.grid[y*nav.maxX+x]=UNSEEN;
            }
        }
    }
}



int max(int a, int b){
    if(a>b){
        return a;
    } else {
        return b;
    }
    
}

int longestPath(navigation_t nav, int x, int y, int length){
    int lengthn=0;
    int lengthe=0;
    int lengths=0;
    int lengthw=0;
    
    if(nav.maxX<=x || x<0 ||nav.maxY<=y || y<0){
        return 0;
    } else
    
    if(nav.grid[y*nav.maxX+x]==WALL||nav.grid[y*nav.maxX+x]==SEEN||nav.grid[y*nav.maxX+x]==PATH||(nav.grid[y*nav.maxX+x]==START && length>0)){
        return 0;
    } else
    if(nav.grid[y*nav.maxX+x]==DESTINATION){
        printf("Found a path of length %d\n",length);
        return length;
    } else
    if(nav.grid[y*nav.maxX+x]!=START){
        nav.grid[y*nav.maxX+x]= PATH;
    }
    
    lengthn=longestPath(nav,x,y-1,length+1);
    lengthe=longestPath(nav,x+1,y,length+1);
    lengths=longestPath(nav,x,y+1,length+1);
    lengthw=longestPath(nav,x-1,y,length+1);
    
    
    if(nav.grid[y*nav.maxX+x]== PATH){
        nav.grid[y*nav.maxX+x]= UNSEEN;
    }//❇️
    
    return max(max(lengthn,lengthe),max(lengths,lengthw));
    
}







int main(void)
{
    char cmd;
    position_t start;
    /*❇️*/navigation_t nav = {NULL};
    int pathlength=0;
    //nav구조체의 모든 멤버를 초기화하는 코드
    
    
    
    /*
    printf("Command? ");
    scanf(" %c",&cmd);
    */
    do{
        printf("Command? ");
        scanf(" %c",&cmd);
        
        switch (cmd){
            case 'q':
                printf("Bye!\n");
                free(nav.grid);
                //int main 에선 변수로 콜됨
            break;
            
            case 'i':
                newGrid(&nav);
                //초기화, 그리드 삭제후 새로운 그리드의 메모리할당당
                if(nav.maxX>=2&&nav.maxY>=2){
                //조건에 해당되면 insert하기기
                    inputGrid(nav);
                }
            break;
            
            case 'p':
            printGrid(nav);
            break;
            
            
            //쉬발발
            case 's':
            start=findStart(nav);
            if(start.x != -1){
                printf("The start is at x=%d and y=%d\n", start.x,start.y);
            }
            break;
            
            case 'f':
            pathlength=0;
            //시작점 위치 불러오기기
            start=findStart(nav);
            pathlength=findPath(nav, start.x,start.y,pathlength);
            if(pathlength==0){
                printf("No path found\n");
            } else if (pathlength >0){
                printf("Found a path of length %d\n",pathlength);
            }
            printGrid(nav);
            break;
            
            
            case 'r':
            resetPath(nav);
            break;
            
            
            case 'l':
            pathlength=0;
            start=findStart(nav);
            pathlength=longestPath(nav, start.x,start.y,pathlength);
            if(pathlength==0){
                printf("No path found\n");
            } else if (pathlength >0){
                printf("The length of the longest path is %d\n",pathlength);
            }
            break;
            
            default:
                printf("Unknown command '%c'\n", cmd);
            break;
        }
    }while(cmd != 'q');
    return 0;
}
