#include <mega128.h>
#include <delay.h>

/*


아두이노 4x4 키패드 사용 

아두이노 핀은 위에서부터 1번

회로도핀  // 아두이노 핀
ROW1     //  8
ROW2     //  7
ROW3     //  6
ROW4     //  5

COL1     //  4
COL2     //  3
COL3     //  2
COL4     //  1

우리가 지금 진행하고 있는 코드에서
int Scan_Col(int row) 함수 부분

col_temp = PINC>>4; 이거 다음에

col_temp = ~col_temp; 추가만 하면 됨


*/


void Port_set()
{
    DDRC = 0x0f; // 상위 4bit 입력, 하위 4bit 출력
  //DDRB = 0xff;  fnd 안씀
    PORTC = 0xf0;// PORTC의 상위 4bit 내부 풀업 설정
  //DDRE = 0xf0;  fnd 안씀
}
            
int Scan_Col(int row)  //Row 값(row = 3 이면 첫번째 행, row = 0 이면 네번째 행 선택)에 따라 Column 스캔 함수, 출력 Col1(1열) = 0x01, Col2(2열) = 0x02, Col3(3열) = 0x04, Col4(4열) = 0x08
{
    int col_temp = 0 , col_num = 0;    //col_temp : column값 임시 저장 변수, col_num : column 값
                      
    PORTC = ~(1<<row);          // row 값에 따라 포트 C의 하위 비트 출력 선택  ex)3번째 줄(row = 1) 선택, PORTC = 0b1111_1101        
    delay_us(1);                // 인식하기 까지 시간이 걸리기 때문에 딜레이
    col_temp = PINC>>4;
    col_temp = ~col_temp;         // ================= 이 거 추 가 해 ==========================
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


void main()
{
    int row_count;
    int col_count;
    int Num;

    Port_set();     
    DDRB=0xff;
     
    while(1)     
    {
        for(row_count = 0; row_count < 4; row_count++)
        {
            col_count = Scan_Col(row_count);        //column 스캔
            Num = KeyNumScan(row_count, col_count);
            
            if(Num!=-1)
            {
                if(Num==0) PORTB=0b11111111;
                else if(Num==1) PORTB=0b11111110;
                else if(Num==2) PORTB=0b11111101;
                else if(Num==3) PORTB=0b11111011;
                else if(Num==4) PORTB=0b11110111;
                else if(Num==5) PORTB=0b11101111;
                else if(Num==6) PORTB=0b11011111;
                else if(Num==7) PORTB=0b10111111;
                else if(Num==8) PORTB=0b01111111;
                else if(Num==9) PORTB=0b00111111;
                else if(Num==10) PORTB=0b00011111;
                else if(Num==11) PORTB=0b00001111;
                else if(Num==12) PORTB=0b00000111;
                else if(Num==13) PORTB=0b00000011;
                else if(Num==14) PORTB=0b00000001;
                else if(Num==15) PORTB=0b00000000;
               
            }        

        }      
               
    }
     
}