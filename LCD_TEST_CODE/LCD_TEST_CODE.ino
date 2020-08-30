#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_SPI.h> //Hardware-specific library

//paramters define
#define MODEL ILI9225
#define CS   A5
#define CD   A3
#define RST  A4
#define SDA  A2
#define SCK  A1
#define LED -1 
float HOME=2.0;
LCDWIKI_SPI mylcd(MODEL,CS,CD,-1,SDA,RST,SCK,LED); //model,cs,dc,sdo,sda,reset,sck,led

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
void setup() 
{
  mylcd.Init_LCD();
  mylcd.Fill_Screen(RED);
  mylcd.Set_Rotation(3);
}
void loop() 
{
  mylcd.Set_Text_Mode(1); mylcd.Fill_Screen(BLACK); mylcd.Set_Text_colour(WHITE); mylcd.Set_Text_Back_colour(BLACK); mylcd.Set_Text_Size(1);mylcd.Print_String("Hello World! how have you been?", 7, 100); mylcd.Set_Text_Size(2); mylcd.Print_Number_Float(HOME, 2, 0, 8, '.', 0, ' ');  
    delay(3000);
    }
  //mylcd.Print_Number_Float(HOME, 0,28);
  //mylcd.Print_Number_Int(0xDEADBEF, 0, 16, 0, ' ',16);
