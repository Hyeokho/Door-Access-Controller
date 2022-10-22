#include <mega128.h>
#include <delay.h>

void Port_set()
{
    DDRC = 0x0f; //상위 4bit 입력, 하위 4bit 출력
    DDRB = 0xff;
    PORTC = 0xf0;//PORTC의 상위 4bit 내부 풀업 설정
}
            
int Scan_Col(int row)  //Row 값(row = 0이면 첫번째 행, row = 3이면 네번째 행 선택)에 따라 Column 스캔 함수, 출력 Col1(1열) = 0x01, Col2(2열) = 0x02, Col3(3열) = 0x04
{
    int col_temp=0 , col_num =0;    //col_temp : column값 임시 저장 변수, col_num : column 값
                      
    PORTC = ~(1<<row);          //row 값에 따라 포트 C의 하위 비트 출력 선택  ex)3번째 줄(row = 2) 선택, PORTC = 0b11111011        
    delay_us(1);                //인식하기까지 시간이 걸리기 때문에 딜레이
    col_temp = PINC>>4;         //포트 C의 입력값 스캔(포트 C의 상위 4비트 입력값만 필요, 오른쪽으로 4비트 이동) ex)col_temp = 0b0000???? = 0x0?
    col_temp = ~col_temp;       //col_temp의 값 반전 ex)col_temp = 0b1111???? = 0xf?   
    col_num =  col_temp & 0x0f; //column 값은 하위 비트만 필요하므로 0x0f AND 연산 ex)col_num = 0b0000???? = 0x0?, 버튼이 눌렸다면  0x01, 0x02, 0x04로 출력
               
    return col_num; //Column 값 반환                  
}

int KeyNumScan(int row, int col_data) //row와 column 값에 따른 숫자 변환
{
    int sel_num = -1; //select number선택, 버튼에 따른 숫자 저장 변수, 초기값 -1 : 아무것도 누르지 않은 상태  
           
    switch(row)
    {
        case 0:               
            if(col_data == 0x01) sel_num = 1;
            if(col_data == 0x02) sel_num = 2;
            if(col_data == 0x04) sel_num = 3;
            break;
        case 1:               
            if(col_data == 0x01) sel_num = 4;
            if(col_data == 0x02) sel_num = 5;
            if(col_data == 0x04) sel_num = 6;
            break;
        case 2:               
            if(col_data == 0x01) sel_num = 7;
            if(col_data == 0x02) sel_num = 8;
            if(col_data == 0x04) sel_num = 9;
            break;
        case 3:               
            if(col_data == 0x01) sel_num = 10;  // *에 해당하는 값 10
            if(col_data == 0x02) sel_num = 0;   // 0에 해당하는 값 0
            if(col_data == 0x04) sel_num = 11;  // #에 해당하는 값 11
            break; 
        default:
            break;
    }
    
    return sel_num;     //선택된 숫자값 변환     
}

void main()
{
    int row_count = 0, col_count = 0;;
    int Num = 0;
    
    Port_set();
        
    while(1)
    {
        for(row_count = 0; row_count < 4; row_count++)
        {
            col_count = Scan_Col(row_count);        //column 스캔
            Num = KeyNumScan(row_count, col_count); //Number 스캔
            if(Num != -1)
            {
                PORTB = ~Num;       //선택된 숫자가 2진법으로 LED에 표기
            }
        }
    }    
}