/*

텀프로젝트 2번

8조 2013146005 권혁호, 2013146034 임준호
  

*/

#include "lcd.h"

#include "buzzer.h"

unsigned int c_cnt=0;
int count=0;// 타이머를 위한 변수

void Init_Timer2(void);
int KeyNumScan(int row, int col_data) ;
int Scan_Col(int row);
interrupt [TIM2_OVF] void timer2_out_comp(void);
void Port_set();

void main()
{
    int i;
    int Num;       
                                                    
    
    int row_count;
    int col_count;
     
    int room_count=0;
    int pw_count=0;

    int room_pw[10][10] = {0};
    int Room_Num = 0; 
    
    int room[5] = {0};
    int password[5] = {0};
                           
    char Press[] = "Press";
    char PW[] = "PW";
    
    char RE[] = "RE ";
    char ENTER_ROOM[] = "ENTER ROOM";
    char NUMBER[] = "NUMBER:";  
                              
    char WELCOME[] = "WELCOME";
    char HAPPY_HOUSE[] = "HAPPY HOUSE";
    
  
    
     // 방과 비밀번호를 똑같이 맞춰줌 ex)1000호 = 1000 / 1000호 부터 1009호 까지  
    for(i=0; i<10; i++)
    {
        room_pw[i][0] = 1;
        room_pw[i][4] = 1;
        
        room_pw[i][3] = i;
        room_pw[i][7] = i;
     }
    
    Port_set();
    PortInit();
     
    LCD_Init();
    LCD_pos(0,2);
    LCD_STR(WELCOME);
    LCD_pos(1,2);
    LCD_STR(HAPPY_HOUSE); 
    
    
    while(1)
    {    
        
        Init_Timer2();   
        
        for(row_count = 0; row_count < 4; row_count++)
        {
            col_count = Scan_Col(row_count);        //column 스캔
            Num = KeyNumScan(row_count, col_count);
            delay_ms(30);
        
        
            if(Num == 11)
            {    
                count=0;
                LCD_Clear();       
                LCD_pos(0,1); 
            
                B:
                LCD_STR(ENTER_ROOM); // 문자열 출력
                LCD_pos(1,1);
                LCD_STR(NUMBER); 
                delay_ms(100);
                          
                room_count = 0; // 방 번호 4자리를 받기 위한 변수
                pw_count = 0; // 비밀  번호 4자리를 받기 위한 변수
                       
                // 몇호실인지 받음
                while(room_count != 4)
                {
                    
                    for(row_count = 0; row_count < 4; row_count++)
                    {
                        col_count = Scan_Col(row_count);        //column 스캔
                        Num = KeyNumScan(row_count, col_count);
                        delay_ms(35);
                        
                        if( 0 <= Num && Num <= 9) // 0~9 까지만 받음
                        {             
                            delay_ms(1);
                            room[room_count] = Num;
                            LCD_Num( room[room_count] ); // 숫자 출력 함수
                            room_count = room_count + 1;
                            delay_ms(100);
                        }
                        
                        else if(Num == 15)
                        {
                            if(room_count > 0)
                            {
                                Left_Erase();
                                room_count = room_count - 1;
                            }
                        } 

                        blink_OnOff(1); // 블링크 함수
                        
                        if(Num == -1 ) //버튼을 아무것도 누르지 않았을때 타이머작동
                        {
                            //256분주비 설정
                            if(count==10)     //8초동안 아무입력이 없을때
                            {
                                count=0;
                                LCD_Clear();                
                                LCD_pos(0,1);
                                LCD_STR(RE);
                                goto B;
                            }        
                        }                
                    }                
                }
            
                delay_ms(500); // 4자리 입력을 확인하기 위한 변수
            
            
                // Room_Num는 방 번호를 저장하기 위한 변수로써 1000~1009번 사이
                Room_Num = (1000 * room[0]) + (100 * room[1]) + (10 * room[2]) + room[3];
                                            
            
                // 방 번호가 1000~1009 일 때, 즉 호수가 제대로 입력 되었을 때
                if ( 1000 <= Room_Num && Room_Num <= 1009)
                {   
                    C:   
                    pw_count = 0;
                    LCD_Clear();
                    LCD_pos(0,1);
                    LCD_CHAR(0x52); // R
                 
                    // 방 번호 출력
                    LCD_Num( room[0] );
                    LCD_Num( room[1] );
                    LCD_Num( room[2] );
                    LCD_Num( room[3] );
                 
                    Cursor_Shift(RIGHT);
                    LCD_STR(Press); // 문자열 출력
                    Cursor_Shift(RIGHT);
                    LCD_STR(PW); // 문자열 출력
                    LCD_CHAR(0x21); // !
                    LCD_pos(1,1);
                    LCD_STR(PW); // 문자열 출력
                    LCD_CHAR(0x3A); // : 
                         
                    // 비밀번호를 받음
                    while(pw_count != 4)
                    {
                        for(row_count = 0; row_count < 4; row_count++)
                        {
                            col_count = Scan_Col(row_count);        //column 스캔
                            Num = KeyNumScan(row_count, col_count);
                            delay_ms(35);

                            if( 0 <= Num && Num <= 9 ) // 0~9 까지만 받음
                            {
                                password[pw_count] = Num;
                                LCD_CHAR(0x2A); // *
                                pw_count = pw_count + 1;
                                delay_ms(100);
                            }
                           
                            blink_OnOff(1); // 블링크 함수
                             
                            if(Num == 15)
                            {
                              if(pw_count > 0)
                              {
                                Left_Erase();
                                pw_count = pw_count - 1;
                              }
                            }

                        }                    
                    }
                    
                }
            
                // 방 번호가 잘못 입력 되었으면
                else
                {
                    LCD_Clear();
                    LCD_pos(0,1);
                    LCD_STR(RE);
                    goto B;
                }             
               
            }            
        
        
            // 메뉴1
            else if(Num == 12)
            {
                LCD_Clear();             
                LCD_pos(0,1); 
                A:
                LCD_STR(ENTER_ROOM); // 문자열 출력
                LCD_pos(1,1);
                LCD_STR(NUMBER); 
                delay_ms(100);
                room_count = 0; // 방 번호 4자리를 받기 위한 변수
                pw_count = 0; // 방 번호 4자리를 받기 위한 변수
                  
                // 몇호실인지 받음
                while(room_count != 4)
                {
                    for(row_count = 0; row_count < 4; row_count++)
                    {
                        col_count = Scan_Col(row_count);        //column 스캔
                        Num = KeyNumScan(row_count, col_count);
                        delay_ms(30);
                        
                        if( 0 <= Num && Num <= 9 ) // 0~9 까지만 받음
                        {
                            room[room_count] = Num;
                            LCD_Num( room[room_count] ); // 숫자 출력 함수
                            room_count = room_count + 1;
                            delay_ms(100);
                        } 
                        blink_OnOff(1); // 블링크 함수
                        
                        if(Num == 15)
                        {
                            if(room_count > 0)
                            {
                                Left_Erase();
                                room_count = room_count - 1;
                            }
                        }
                    }                 
                }
            
                delay_ms(500); // 4자리 입력을 확인하기 위한 변수

                // Room_Num는 방 번호를 저장하기 위한 변수로써 1000~1009번 사이
                Room_Num = (1000 * room[0]) + (100 * room[1]) + (10 * room[2]) + room[3];             
            
                // 방 번호가 1000~1009 일 때, 즉 호수가 제대로 입력 되었을 때
                if ( 1000 <= Room_Num && Room_Num <= 1009)
                {

                    LCD_Clear();
                    LCD_pos(0,1);
                    LCD_CHAR(0x52); // R
                    
                    // 방 번호 출력
                    LCD_Num( room[0] );
                    LCD_Num( room[1] );
                    LCD_Num( room[2] );
                    LCD_Num( room[3] );
                    LCD_CHAR(0x3A); // :

                    // 방-비밀번호 배열의 0행부터 9행까지 순회하면서 방 번호가 매칭되면 비밀번호 출력
                    for(i=0; i<10; i++)
                    {   
                        if(room_pw[i][0] == room[0] && room_pw[i][1] == room[1] && room_pw[i][2] == room[2] && room_pw[i][3] == room[3])
                        {
                            LCD_Num( room_pw[i][4] );
                            LCD_Num( room_pw[i][5] );
                            LCD_Num( room_pw[i][6] );
                            LCD_Num( room_pw[i][7] );
                        }                    
                    }
             
                    Cursor_Shift(RIGHT);
                    Cursor_Shift(RIGHT);

                    LCD_CHAR(0x28); // (
                    LCD_CHAR(0x43); // C
                    LCD_CHAR(0x29); // )
                
                    LCD_pos(1,1);
                    LCD_CHAR(0x52); // R
                 
                
                    // 방 번호 순서대로 출력
                    LCD_Num( room[0] );  
                    LCD_Num( room[1] );   
                    LCD_Num( room[2] ); 
                    LCD_Num( room[3] );
                
                    LCD_CHAR(0x3A); // :
                                  
                
                    // 방-비밀번호 배열의 0행부터 9행까지 순회하면서 방 번호가 매칭되면 입력한 비밀번호 저장
                    for(i=0; i<10; i++)
                    {
                        // 입력한 방 번호가 존재하면
                        if(room_pw[i][0] == room[0] && room_pw[i][1] == room[1] && room_pw[i][2] == room[2] && room_pw[i][3] == room[3])
                        {  
                        
                            // 변경하고자 하는 4자리 비밀번호를 받는다.
                            while(pw_count != 4)
                            {
                                for(row_count = 0; row_count < 4; row_count++)
                                {
                                    col_count = Scan_Col(row_count);        //column 스캔
                                    Num = KeyNumScan(row_count, col_count);
                                    delay_ms(35);

                                    if( 0<=Num && Num<=9 ) // 0~9 까지만 받음
                                    {
                                        room_pw[i][pw_count+4]  =  Num;
                                        LCD_CHAR(0x2A); // *
                                        pw_count = pw_count + 1;
                                        delay_ms(100);
                                    }
                            
                                    blink_OnOff(1); //1 이면 블링크on , 0이면 블링크 off
                                    
                                    if(Num == 15)
                                   {
                                        if(pw_count > 0)
                                        {
                                             Left_Erase();
                                             pw_count = pw_count - 1;
                                             delay_ms(35);
                                        }
                                   }
                                }         
                            }
                        }
                    }

                    Cursor_Shift(RIGHT);
                    Cursor_Shift(RIGHT);

                    LCD_CHAR(0x28); // (
                    LCD_CHAR(0x55); // U
                    LCD_CHAR(0x29); // )

                }
            
                // 비밀번호가 틀리면
                else
                {
                    LCD_Clear();
                    LCD_pos(0,1);
                    LCD_STR(RE);
                    goto A;
                }          
            }
        
            // 메뉴 2 = 기본 화면 출력
            else if(Num == 13)
            {   
                LCD_Init();
                LCD_pos(0,2);
                LCD_STR(WELCOME);
                LCD_pos(1,2);
                LCD_STR(HAPPY_HOUSE); 
            
                room[0] = 0;
                room[1] = 0;
                room[2] = 0;
                room[3] = 0;
            }
        
            // 메뉴 3
            else if(Num == 14)
            {
                // 방-비밀번호 배열의 0행부터 9행까지 순회하면서 방 번호가 매칭되면 입력한 비밀번호 확인
                for(i=0; i<10; i++)
                {
                    // 입력한 방 번호가 매칭 되며
                    if(room_pw[i][0] == room[0] && room_pw[i][1] == room[1] && room_pw[i][2] == room[2] && room_pw[i][3] == room[3])
                    {  
                        
                        // 입력한 4자리의 비밀번호와 매칭한다.
                        if(room_pw[i][4] == password[0] && room_pw[i][5] == password[1] && room_pw[i][6] == password[2] && room_pw[i][7] == password[3])
                        {
                            // 매칭되면 짧은 성공음 출력한다.
                            DDRG |= (1<<4); //부저 사용을 위한 출력 설정(PORTG 4번)
                            SSound(Do6);    // 딩
                            SSound(Mi6);    // 동
                            SSound(Sol6);   // 댕
                            SSound(Do7);    // 동 
                           
                            delay_ms(500);
                            
                            Melody_We_are(); // 시차 연주
                            //Melody_Elise(); // 엘리제를 위하여 연주
                        }
                        
                        // 입력한 4자리의 비밀번호와 다르면 비밀번호를 재입력한다
                        else
                        {    
                            DDRG |= (1<<4); //부저 사용을 위한 출력 설정(PORTG 4번)
                            SSound(La6);   // 땡
                            goto C;
                        }
                        
                    }
                }
             
            }
        
        }       

    }
}


void Port_set()
{
    DDRC = 0x0f; // 상위 4bit 입력, 하위 4bit 출력
  //DDRB = 0xff;  fnd 안씀
    PORTC = 0xf0;// PORTC의 상위 4bit 내부 풀업 설정
  //DDRE = 0xf0;  fnd 안씀  
}

void Init_Timer2(void)
{
    TCCR2 = 0x00;
    TIMSK |=(1<<TOIE2);
    TCCR2 |= (1<<CS22);
    SREG |=0X80;
}

/* 

1/16M[Hz] = 0.0625u[s] 이것이 1 클럭 

256분주 = 256클럭을 1클럭으로 만들어줌

설정하면  256 * 0.0625u = 16u [s] 가 1클럭이 됨



TCNT0 란?
TCNT0은 항상 상향 카운터로(증가형 0,1,2,3,4,...형태)로만 동작
TCNT0의 값이 0xFF에서 0x00으로 바뀌는 순간(0,1,2,3,,....255 -> 0으로 바뀌는 순간)에 TIFR 레지스터의 TOV0비트가 1로 세트 되면서 오버플로우 인터럽트가 발생하며 인터럽트 서비스 루틴을 수행한다. 자동으로 TOV0비트는 0으로 리셋

*/
interrupt [TIM2_OVF] void timer2_out_comp(void)
{
    c_cnt++;
    if(c_cnt==1000)
    {
        c_cnt=0; 
        count++;
    }
    TCNT2=200;
}
          
int Scan_Col(int row)  //Row 값(row = 3 이면 첫번째 행, row = 0 이면 네번째 행 선택)에 따라 Column 스캔 함수, 출력 Col1(1열) = 0x01, Col2(2열) = 0x02, Col3(3열) = 0x04, Col4(4열) = 0x08
{
    int col_temp = 0 , col_num = 0;    //col_temp : column값 임시 저장 변수, col_num : column 값
                      
    PORTC = ~(1<<row);          // row 값에 따라 포트 C의 하위 비트 출력 선택  ex)3번째 줄(row = 1) 선택, PORTC = 0b1111_1101        
    delay_us(1);                // 인식하기 까지 시간이 걸리기 때문에 딜레이
    col_temp = PINC>>4;
    //col_temp = ~col_temp;         // ================= 이 거 추 가 해 ==========================
    col_num  = col_temp & 0x0f; // column 값은 하위 비트만 필요하므로 0x0f AND 연산 ex)col_num = 0b0000???? = 0x0?, 버튼이 눌렸다면  0x01, 0x02, 0x04로 출력
               
    return col_num; // column 값 반환                  
}

int KeyNumScan(int row, int col_data) //row와 column 값에 따른 숫자 변환
{
    int sel_num = -1; //select number선택, 버튼에 따른 숫자 저장 변수, 초기값 -1 : 아무것도 누르지 않은 상태  
    
    delay_ms(5); 
      
    switch(row)
    {
        case 3:               
            if(col_data == 0x01) sel_num = 1;
            if(col_data == 0x02) sel_num = 2;
            if(col_data == 0x04) sel_num = 3;
            if(col_data == 0x08) sel_num = 12;  // M1 = A
            break;
        case 2:               
            if(col_data == 0x01) sel_num = 4;
            if(col_data == 0x02) sel_num = 5;
            if(col_data == 0x04) sel_num = 6;
            if(col_data == 0x08) sel_num = 13;  // M2 = S
            break;
        case 1:               
            if(col_data == 0x01) sel_num = 7;
            if(col_data == 0x02) sel_num = 8;
            if(col_data == 0x04) sel_num = 9;     
            if(col_data == 0x08) sel_num = 14;  // M3 = D
            break;
        case 0:               
            if(col_data == 0x01) sel_num = 10;  // *에 해당하는 값 10
            if(col_data == 0x02) sel_num = 0;   // 0에 해당하는 값 0
            if(col_data == 0x04) sel_num = 11;  // #에 해당하는 값 11
            if(col_data == 0x08) sel_num = 15;  // M4 = F
            break; 
        default:
            break;
    }
    
    return sel_num;     //선택된 숫자값 변환     
}