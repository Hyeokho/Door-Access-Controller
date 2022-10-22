#include <mega128.h>
#include <delay.h>
#define LCD_WDATA PORTA
#define LCD_WINST PORTA
#define LCD_CTRL PORTG //LCD 제어 포트 정의
#define LCD_EN 0
#define LCD_RW 1
#define LCD_RS 2

#define RIGHT 1
#define LEFT 0

#define Byte unsigned char

#define ON 1  //불리언 상수 정의
#define OFF 0

#define blink 0x0F // 커서 위치에 있는 문자 점멸
#asm("sei")

void PortInit(void)
{
    DDRA=0xff; //PORTA를 출력으로
    DDRG=0x0f; //PORTG의 하위 4비트를 출력으로
}

void LCD_Data(Byte ch)
{
    LCD_CTRL |= (1<<LCD_RS); //RS=1, 데이터 레지스터 seletion
    LCD_CTRL &= ~(1<<LCD_RW); // RW=0, write
    LCD_CTRL |= (1<<LCD_EN); // LCD Enable
    delay_us(50); // 시간 지연
    LCD_WDATA=ch; // 데이터 출력
    delay_us(50);
    LCD_CTRL &= ~(1<<LCD_EN); // LCD disable
}

void LCD_Comm(Byte ch)
{
    LCD_CTRL &= ~(1<<LCD_RS); //명령어 RS=0
    LCD_CTRL &= ~(1<<LCD_RW); //쓰기 RW=0
    LCD_CTRL |= (1<<LCD_EN); // LCD Enable
    delay_us(50);
    LCD_WINST =ch; //명령어 쓰기
    delay_us(50);
    LCD_CTRL &= ~(1<<LCD_EN);
}

void LCD_delay(Byte ms)
{
    delay_ms(ms);
}

void LCD_CHAR(Byte c) //한 문자 출력
{
    LCD_Data(c);
    delay_ms(1);
}

void LCD_STR(Byte *str) //문자열 출력
{
    while(*str!=0 ){
        LCD_CHAR(*str);
        str++;
    }
}

void LCD_pos(Byte col,Byte row) //LCD 포지션 설정
{
    LCD_Comm(0x80|(row+col*0x40));
}

void LCD_Clear(void) //화면 클리어
{
    LCD_Comm(0x01);
    LCD_delay(2);
}

void LCD_Init(void) //LCD 초기화
{
    LCD_Comm(0x38); // DDRAM,데이터 8비트 사용, LCD 2열로 사용
    LCD_delay(2);
    LCD_Comm(0x38); // DDRAM,데이터 8비트 사용, LCD 2열로 사용
    LCD_delay(2);
    LCD_Comm(0x38); // DDRAM,데이터 8비트 사용, LCD 2열로 사용
    LCD_delay(2);
    LCD_Comm(0x0e); // display on/off
    LCD_delay(2);
    LCD_Comm(0x06); // 주소 +1, 커서를 우측 이동(3)
    LCD_delay(2);
    LCD_Clear(); // 화면 클리어
}

void blink_OnOff(unsigned char a)      //1 이면 블링크on , 0이면 블링크 off
{
    if(a==1)
        LCD_Comm(blink);
    else
        LCD_Comm(0x06);
}

void LCD_Shift(Byte p) // 디스플레이 시프트 (5)
{
    // 표시 화면 전체를 오른쪽으로 이동
    if(p == RIGHT)
     {
        LCD_Comm(0x1C); // * A에서 C로 바꿈
        LCD_delay(1); // 시간 지연
    }

    // 표시 화면 전체를 왼쪽으로 이동
    else if(p == LEFT)
    {
        LCD_Comm(0x18);
        LCD_delay(1);
    }
}

void Cursor_Home(void)
{
        LCD_Comm(0x02); // Cursor Home
        LCD_delay(2); // 2ms 시간지연
}

void Cursor_Shift(Byte p)
{
    if(p == RIGHT)
    {
        LCD_Comm(0x14);
        LCD_delay(1);
    }
    else if(p == LEFT)
    {
        LCD_Comm(0x10);
        LCD_delay(1);
    }
}

void LCD_Num(int c) //한 숫자 출력
{
    if( c==0 ) LCD_CHAR(0x30);
    if( c==1 ) LCD_CHAR(0x31);
    if( c==2 ) LCD_CHAR(0x32);
    if( c==3 ) LCD_CHAR(0x33);
    if( c==4 ) LCD_CHAR(0x34);
    if( c==5 ) LCD_CHAR(0x35);
    if( c==6 ) LCD_CHAR(0x36);
    if( c==7 ) LCD_CHAR(0x37);
    if( c==8 ) LCD_CHAR(0x38);
    if( c==9 ) LCD_CHAR(0x39);        
}

void Left_Erase()
{
    Cursor_Shift(LEFT);
    LCD_CHAR(0x90);
    Cursor_Shift(LEFT);                                          
 }