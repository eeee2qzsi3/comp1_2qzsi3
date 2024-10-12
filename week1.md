#include <stdio.h>



void currentvalue(float curr_re, float curr_im){
    if (curr_im<0){
          printf("Current value is %f%fi\n", curr_re, curr_im);
          } else {
              printf("Current value is %f+%fi\n", curr_re, curr_im);
          }
}


int main(void)
{
    char cmd;
    float curr_re=0.0;
    float curr_im=0.0;
    float new_re=0.0;
    float new_im=0.0;
    int num;
    
  printf("** Complex Calculator **\n");
  
  do {
      printf("Operation [0+-*crpq]? ");
      scanf(" %c", &cmd);
      
      switch(cmd){
          case ('+'):
          printf("Complex operand? ");
          scanf(" %f %f\n",  &new_re, &new_im);
          //각각 새로운 값만큼 증가시킴
          curr_re+=new_re;
          curr_im+=new_im;
          currentvalue(curr_re,curr_im);
          break;
          
          case ('-'):
          printf("Complex operand? ");
          scanf(" %f %f\n",  &new_re, &new_im);
          //각각 새로운 값만큼 감소시킴
          curr_re-=new_re;
          curr_im-=new_im;
          currentvalue(curr_re,curr_im);
          break;
          
          case '*':
          printf("Complex operand? ");
          scanf(" %f %f\n",  &new_re, &new_im);
          float im_re = curr_re;
          float im_im = curr_im;
          //그대로 curr_re, curr_im을 쓰면 첫번째 식에서 이미 새로운 값으로 업데이트 되기때문에 임시변수를 써야됨
          curr_re=im_re*new_re-im_im*new_im;
          curr_im=im_re*new_im+im_im*new_re;
          currentvalue(curr_re,curr_im);
          break;
          
          case('0'):
          curr_re=0.0;
          curr_im=0.0;
          currentvalue(curr_re,curr_im);
          //break안넣으면 다음 case나 default 블록, 끝까지지 실행되버림
          break;
          
          case 'r':
          printf("Natural operand? ");
          scanf(" %d", &num);
          float mul_re=curr_re;
          float mul_im=curr_im;
          for(int i = 1; i < num; i++ ){
              float temp_re = 0.0;
              float temp_im = 0.0;
              temp_re=mul_re*curr_re-mul_im*curr_im;
              temp_im=mul_re*curr_im+mul_im*curr_re;
              //그냥 currvule를 쓰면 계속 갱신되니까 다른 변수를 써야됨
              //안그러면 너무 커짐 
              //예) (2+i)^3=(2+i)(2+i)(2+i)
              //           =(3+4i)(2+i)  이렇게 되야하는데데
              //           =(3+4i)(3+4i) 이렇게 돼버림
              curr_re = temp_re;
              curr_im = temp_im;
          } if (num == 0){
              curr_re = 1;
              curr_im = 0;
          }
          currentvalue(curr_re,curr_im);
          break;
          
          case 'p':
          for(int l = 10; l>-11; l--){
          for(int i =-10; i<11; i++){
              if ((curr_re >= i && curr_re < i+1) && (curr_im >= l && curr_im<l+1)){
                  printf("*");
              } else if (i == 0 && l == 0){
                  printf("+");
                  }else if (i == 0 && l != 0){
                      printf("|");
                      } else if (i != 0 && l == 0){
                          printf("-");
                      }
                      else {
                  printf(".");
              }
          }
          printf("\n");
          }
          currentvalue(curr_re,curr_im);
          break;
          
          case('c'):
          curr_re=curr_re;
          curr_im*=-1.0;
          currentvalue(curr_re,curr_im);
          break;
          
          case ('q'):
          currentvalue(curr_re,curr_im);
          printf("Bye!\n");
          break;
          
          default:
          printf("Invalid command '%c'\n", cmd);
          currentvalue(curr_re,curr_im);
          break;
          
      }
    
  } while(cmd != 'q');
  return 0;
    
}
