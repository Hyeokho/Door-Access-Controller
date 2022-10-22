#include <mega128.h>
#include <delay.h>

//음계 주파수에 따른 주기(time) 계산, On-Off로 만들어야 하기 때문에 (음계 주기/2)
#define Do4 1908 // 262Hz = (3817us) 1908us
#define Re4 1700 // 294Hz (3401us) 1701us
#define Mi4 1515 // 330Hz (3030us) 1515us
#define Fa4 1432 // 349Hz (2865us) 1433us
#define FaS4 1351
#define Sol4 1275 // 370Hz (2703us) 1351us
#define La4 1136 // 440Hz (2273us) 1136us
#define Si4 1012 // 494Hz (2024us) 1012us


#define Do3 3822 
#define DoS3 3610 
#define Re3 3405
#define ReS3 3214  
#define Mi3 3033  
#define Fa3 2863
#define FaS3 2702
#define Sol3 2551
#define SolS3 2407
#define La3 2272
#define LaS3 2145
#define Si3 20024

#define Do5 955 
#define DoS5 901 
#define Re5 851 
#define ReS5 803 
#define Mi5 758 
#define Fa5 715 
#define FaS5 675 
#define Sol5 637 
#define SolS5 602 
#define La5 568 
#define LaS5 536 
#define Si5 506

#define Do6 478 
#define DoS6 451 
#define Re6 425 
#define ReS6 401 
#define Mi6 379 
#define Fa6 357 
#define FaS6 337 
#define Sol6 318 
#define SolS6 301 
#define La6 284 
#define LaS6 268 
#define Si6 253

#define Do7 238

// 새로운 delay 함수 생성, 기존의 delay_us() 함수는 인자로
// 상수만 받기 때문에 새로운 딜레이 함수 생성
// 음계 시간 La(1136)가 들어오면 delay_us(1)을 1136번 반복하여
// 시간 생성
void myDelay_us(unsigned int delay)
{
    int i;
    for(i=0; i<delay; i++)
    {
        delay_us(1);
    }
}

// 해당 음계의 주파수를 만들어주는 함수 ex)262Hz=3817us
// 이기 때문에 1908us on, 1908us off 동작 반복
void SSound(int time)
{
    int i, tim;
    
    // tim값을 조절해서 시간을 조절할 수 있음
    tim = 45000/time;
    
    //음계마다 같은 시간동안 울리도록 tim 변수 사용
    for(i=0; i<tim; i++)
    {
        PORTG |= 1<<4;
    
        //buzzer on, PORTG의 4번 핀 on(out 1)
        myDelay_us(time);
        PORTG &= ~(1<<4);
    
        //buzzer off, PORTG의 4번 핀 off(out 0)
        myDelay_us(time);
    }
}

/*
void timescale(double sec, int time)
{
    int i,tim;
     
    // tim값을 조절해서 시간을 조절할 수 있음
    tim = (250000/time)*sec;
    
    //음계마다 같은 시간동안 울리도록 tim 변수 사용
    for(i=0; i<tim; i++)
    {
        PORTG |= 1<<4;
    
        //buzzer on, PORTG의 4번 핀 on(out 1)
        myDelay_us(time);
        PORTG &= ~(1<<4);
    
        //buzzer off, PORTG의 4번 핀 off(out 0)
        myDelay_us(time);
    }
}
*/

void Melody_Elise()
{
DDRG |= (1<<4); //부저 사용을 위한 출력 설정(PORTG 4번)
    SSound(Mi6);
    SSound(ReS6);
    SSound(Mi6);
    SSound(ReS6);
    SSound(Mi6);
    SSound(Si5);
    SSound(DoS6);
    SSound(Do6);
    SSound(La5);
                 
    delay_ms(500);
    
    SSound(Do5);
    SSound(Mi5);
    SSound(La5);
    SSound(Si5);
                
    delay_ms(500); 
                       
    SSound(Mi5);
    SSound(SolS5);
    SSound(Si5);
    SSound(Do6);
}

void Melody_We_are()
{
     DDRG |= (1<<4); //부저 사용을 위한 출력 설정(PORTG 4번)
        SSound(La5);
          SSound(Si5);
          SSound(Re6);
          SSound(FaS6);
          
          delay_ms(200);
          
           
          SSound(Re6);
          
          delay_ms(200);
          
          SSound(Mi6);
          
          delay_ms(200);
          
          SSound(Mi6);
          SSound(Re6);
          SSound(Mi6);
          
          
          delay_ms(400);
      
          SSound(La5);
          SSound(Si5);
          SSound(Re6);
          SSound(FaS6);
          
          delay_ms(200);
           
          SSound(Re6);
          
          delay_ms(200);
          
          SSound(Mi6);
          
          delay_ms(200);
          
          SSound(Mi6);
          SSound(Re6);
          SSound(Mi6);
          
     
          delay_ms(400); 
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          
          SSound(Do6);
          delay_ms(20);
          
          SSound(Do6);
          delay_ms(20);
          
          SSound(Do6);
          delay_ms(20);
          
          SSound(Do6);
          delay_ms(20);
          
          SSound(Do6);
          delay_ms(20);
          
          SSound(Do6);
          delay_ms(20); 
             
          
          
          SSound(Si5);
          delay_ms(10); 
          
          SSound(Si5);
          
          delay_ms(200); 
          
          SSound(Si5);
          delay_ms(20); 
          
          SSound(Si5);
          delay_ms(20); 
          
          SSound(Si5);
          delay_ms(20); 
          
          SSound(Si5);
          delay_ms(20); 
          
          SSound(Si5);
          delay_ms(20); 
          
          SSound(Si5);
          delay_ms(20); 
          
          SSound(Si5);
          delay_ms(20); 
          
          SSound(Si5);
          delay_ms(20); 
          
          SSound(Si5);
          delay_ms(20); 
          
          SSound(Si5);
          delay_ms(20); 
          
          SSound(Si5);
          delay_ms(20); 
          
          SSound(Si5);
          delay_ms(20); 
          
          
          
          SSound(Re6);
          delay_ms(20); 
          
          SSound(Re6);
          delay_ms(20); 
          
          SSound(Re6);
          delay_ms(20); 
          
          SSound(Re6);
          delay_ms(20); 
          
          SSound(Re6);
          delay_ms(20); 
          
          SSound(Re6);
          delay_ms(20); 
          
          SSound(Re6);
          delay_ms(20); 
          
          SSound(Re6);
          delay_ms(20); 
          
          
          
          
          SSound(Do6);
          delay_ms(20); 
          
          SSound(Do6);
          delay_ms(20); 
          
          
          SSound(Do6);
          delay_ms(20); 
          
          
          SSound(Do6);
          delay_ms(20); 
          
          SSound(Do6);
          delay_ms(20); 
          
          SSound(Do6);
          delay_ms(20); 
          
          SSound(Do6);
          delay_ms(20); 
          
          SSound(Do6);
          delay_ms(20); 
          
          
          
          
          
           SSound(Si5);
          delay_ms(20); 
          
           SSound(Si5);
          delay_ms(20); 
          
           SSound(Si5);
          delay_ms(20); 
          
           SSound(Si5);
          delay_ms(20); 
          
           SSound(Si5);
          delay_ms(20); 
          
           SSound(Si5);
          delay_ms(20); 
          
           SSound(Si5);
          delay_ms(20); 
          
           SSound(Si5);
          delay_ms(20); 
          
           SSound(Si5);
          delay_ms(20); 
          
           SSound(Si5);
          delay_ms(20); 
          
           SSound(Si5);
          delay_ms(20); 
          
           SSound(Si5);
          delay_ms(20); 
          
          
          
           SSound(Si5);
          
          delay_ms(100);
          
           
          
          SSound(Si5);
          delay_ms(20); 
          
          SSound(Si5);
          delay_ms(20); 
          
          SSound(Re6);
          delay_ms(10);
          SSound(Re6);
          
          delay_ms(200);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          
          
          SSound(Mi6);
          delay_ms(20);
          
          SSound(Mi6);
          delay_ms(200);
          
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
         SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(200);
                              
          
            
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          SSound(Si5);
          delay_ms(20);
          
          
          SSound(Re6);
          delay_ms(20);
          
          
          SSound(Si5);
          delay_ms(20);
          
          
          SSound(Re6);
          delay_ms(20);
          
          SSound(Re6);
          delay_ms(20);
          
}
 
void Beep(void)
{
    // buzzer on
    PORTG |= 1<<4;
    delay_us(200); // 200usec 지연
    
    // buzzer off
    PORTG &= ~(1<<4);
    delay_us(200); // 200usec 지연
}
