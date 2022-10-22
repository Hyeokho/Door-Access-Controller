#include <mega128.h>
#include <delay.h>

unsigned int Font_Num[] ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90, 0x88, 0x83, 0xA7, 0xA1, 0x86, 0x8E, 0xFF}; //FND 표기될 문자표 정리 0~F, 이 코드에서는 0~9의 숫자만 사용

void display_segment(int num)//0000~9999 디스플레이를 위한 함수, 함수 처리시간 약 4ms
{
    int num_1, num_10, num_100, num_1000;
    
    num_1000 = (num/1000)%10;       //1000의 자리수 
    num_100  = (num/100)%10;        //100의 자리수
    num_10   = (num/10)%10;         //10의 자리수
    num_1    = (num)%10;            //1의 자리수
    
    PORTE = 0x10;                   //FND0 선택(1의 자리)
    PORTB = Font_Num[num_1]; 
    delay_ms(1);
    PORTE = 0x00;
    
    PORTE = 0x20;                   //FND1 선택(10의 자리)            
    PORTB = Font_Num[num_10];
    delay_ms(1);
    PORTE = 0x00;
    
    PORTE = 0x40;                   //FND2 선택(100의 자리)
    PORTB = Font_Num[num_100];
    delay_ms(1);
    PORTE = 0x00;
    
    PORTE = 0x80;                   //FND3 선택(1000의 자리)
    PORTB = Font_Num[num_1000];
    delay_ms(1);
    PORTE = 0x00;    
}

void Port_set()
{
    DDRB = 0xff; //FND의 a~g 값 출력을 위한 출력 설정
    DDRE = 0xf0; //FND0~FND3 선택(전원 공급)을 위한 출력 설정, PINE.4~7
}

void main()
{
    int count_num;      //1~9999 계수를 위한 변수
    int delay;          //화면 표시 시간을 위한 변수                    
    Port_set();
    
    while(1)
    {   
        for(count_num=0; count_num<10000; count_num++)  //0~9999를 표시하기 위한 변수 
        {
            for(delay=0; delay<100; delay++) //delay를 위한 for문(숫자 증가 시간 설정), 함수 처리시간이 4ms이므로 100번 반복시 4ms*100 = 400ms(0.4초), 즉 0.4초마다 1씩 증가
            {
                display_segment(count_num);
            }
        }
    }
}