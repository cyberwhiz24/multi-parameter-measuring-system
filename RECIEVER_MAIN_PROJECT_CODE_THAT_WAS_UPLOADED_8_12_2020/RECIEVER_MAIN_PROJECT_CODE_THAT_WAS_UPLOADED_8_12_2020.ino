//_____________THIS IS THE RECIEVER CODE, BUILT ON 8/12/2020_____________________________________________
#include "Arduino.h"
#include <SPI.h>
#include <RF24.h>
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_SPI.h> //Hardware-specific library
//_______________________________PIN Parameters definitions______________________________________________
#define MODEL ILI9225 // _
#define CS   A5       //  |
#define CD   A3       //  |
#define RST  A4       //  |___
#define SDA  A2       //  |---  PIN INITIALIZATION AND DEFINITION FOR THE TFT LCD
#define SCK  A1       //  |
#define LED -1       //  _|
//////////////////////
#define LED1 10
#define LED2 9
#define LED3 5
#define LED4 4
#define LED5 3
#define BUZZER 6
//______________________________________________________________________________________________________
float HOME =22.00;
 ////////////////////////////////////////////////////////////////////////////////////////////////////////
 void buzzer (void)
{
    digitalWrite (BUZZER, HIGH);
    delay (200);
    digitalWrite (BUZZER, LOW);
 }
 ///////////////////////////////////////////////////////////////////////////////////////////////////////
 
 
// This is just the way the RF24 library works:
// Hardware configuration: Set up nRF24L01 radio on SPI bus (pins 10, 11, 12, 13) plus pins 7 & 8
RF24 radio(7, 8);
struct package{
  int id;
  float temperature = 0.00;
  float humidity = 0.00;
  int TiltStatus;
  int PIRstatus;
};
typedef struct package Package;
Package data;

// ________________________create the pipe node for the connection of two or more arduino's____________________________
byte addresses[][6] = {"6Node", "1Node", "2Node", "3Node", "4Node", "5Node"};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LCDWIKI_SPI mylcd(MODEL,CS,CD,-1,SDA,RST,SCK,LED); //model,cs,dc,sdo,sda,reset,sck,led //FOR THE LCD SPI INITIALIZATION
//_____________________________________________________________________________________________________________________

//________________________________LCD COLOR HEX CODE DEFINITION________________________________________________________
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define PINK    0xF910
//_____________________________________________________________________________________________________________________

// --------------------------------------------------------------------------------------------------------------------
// SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP   SETUP  SETUP   SETUP   SETUP    SETUP   SETUP  SETUP
// --------------------------------------------------------------------------------------------------------------------
void setup() {
//_________________________BIO_DATA & LCD INITIALIZATION_______________________________________________________________
  mylcd.Init_LCD();
  mylcd.Set_Rotation(1);
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Rotation(3);
  //////////////////////////////////////////////////////////////////////////////////
       mylcd.Set_Draw_color(RED);
         int i = 0;
    for(i = mylcd.Get_Display_Width() -1; i>=0;i-=5)
    {
      mylcd.Draw_Line(mylcd.Get_Display_Width()-1, 0, i, mylcd.Get_Display_Height()-1);
     }
  /////////////////////////////////////////////////////////////////////////////////
  mylcd.Set_Text_Mode(1); 
  mylcd.Set_Text_colour(WHITE);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(1);
  mylcd.Print_String("NAME: OMOROH OVIE ", 0, 10); 
  mylcd.Print_String("REG NO: 2015/4210 ", 0, 30);
  mylcd.Print_String("BELLS UNIVERSITY OF TECHNOLOGY ", 0, 50); 
  mylcd.Print_String("DEPT: TELECOMMUNICATIONS ENGINEERING ", 0, 70);  
  mylcd.Print_String("DESIGN & IMPLEMENTATION OF A MULTI-", 0, 90); 
  mylcd.Print_String("PARAMETER WIRELESS SENSOR NETWORK", 0, 100); 
  mylcd.Print_String("SYSTEM ", 0, 110); 
  delay(6000);
  
  //_______________________________________________________________________________________________
  
//________________________PIN mode (output or input) for different components plugged into the Ardiuno I/O pin._________
pinMode (LED1, OUTPUT);
pinMode (LED2, OUTPUT);
pinMode (LED3, OUTPUT);
pinMode (LED4, OUTPUT);
pinMode (LED5, OUTPUT);
pinMode(BUZZER, OUTPUT);
//______________________________________________________________________________________________________________
/*
//________________________________LCD WILL DISPLAY  "STARTING UP..."____________________________________________
    mylcd.Fill_Screen(CYAN);
    mylcd.Set_Draw_color(BLUE);   
    for(i = 0; i< mylcd.Get_Display_Width();i+=5)
    {
       mylcd.Draw_Line(0, 0, i, mylcd.Get_Display_Height()-1);
     }
     for(i = mylcd.Get_Display_Height()-1; i>= 0;i-=5)
     {
       mylcd.Draw_Line(0, 0, mylcd.Get_Display_Width()-1, i);
     }
     
  mylcd.Set_Text_Mode(1); 
  mylcd.Set_Text_colour(BLACK);
  mylcd.Set_Text_Back_colour(CYAN);
  mylcd.Set_Text_Size(2);mylcd.Print_String("STARTING UP...", 40, 100); 
//______________________________________________________________________________________________________________
*/
//____________________________LED Start Up Sync_________________________________________________________________
  digitalWrite (LED1, HIGH);
  delay(300);
  digitalWrite (LED1, LOW); digitalWrite (LED2, HIGH);
  delay(300);
  digitalWrite (LED2, LOW); digitalWrite (LED3, HIGH);
  delay(300);
  digitalWrite (LED3, LOW); digitalWrite (LED4, HIGH);
  delay(300);
  digitalWrite (LED4, LOW); digitalWrite (LED5, HIGH);
  delay(300);
  digitalWrite (LED5, LOW); digitalWrite (LED4, HIGH);
  delay(300);
  digitalWrite (LED4, LOW); digitalWrite (LED3, HIGH);
  delay(300);
  digitalWrite (LED3, LOW); digitalWrite (LED2, HIGH);
  delay(300);
  digitalWrite (LED2, LOW); digitalWrite (LED1, HIGH);
  delay(300);
  digitalWrite (LED1, LOW);
  delay(200);
  //_______________________________ALL THE LED FLASHES_____________________________________________________________
  digitalWrite (LED1, HIGH); digitalWrite (LED1, HIGH); digitalWrite (LED2, HIGH); digitalWrite (LED3, HIGH); digitalWrite (LED4, HIGH); digitalWrite (LED5, HIGH);
  delay(200);
  digitalWrite (LED1, LOW); digitalWrite (LED1, LOW); digitalWrite (LED2, LOW); digitalWrite (LED3, LOW); digitalWrite (LED4, LOW); digitalWrite (LED5, LOW);
  delay(200);
  digitalWrite (LED1, HIGH); digitalWrite (LED1, HIGH); digitalWrite (LED2, HIGH); digitalWrite (LED3, HIGH); digitalWrite (LED4, HIGH); digitalWrite (LED5, HIGH);
  delay(100);
  digitalWrite (LED1, LOW); digitalWrite (LED1, LOW); digitalWrite (LED2, LOW); digitalWrite (LED3, LOW); digitalWrite (LED4, LOW); digitalWrite (LED5, LOW);
  delay(100);
  digitalWrite (LED1, HIGH); digitalWrite (LED1, HIGH); digitalWrite (LED2, HIGH); digitalWrite (LED3, HIGH); digitalWrite (LED4, HIGH); digitalWrite (LED5, HIGH);
  delay(70);
  digitalWrite (LED1, LOW); digitalWrite (LED1, LOW); digitalWrite (LED2, LOW); digitalWrite (LED3, LOW); digitalWrite (LED4, LOW); digitalWrite (LED5, LOW);
  delay(70);
  digitalWrite (LED1, HIGH); digitalWrite (LED1, HIGH); digitalWrite (LED2, HIGH); digitalWrite (LED3, HIGH); digitalWrite (LED4, HIGH); digitalWrite (LED5, HIGH);
  delay(50);
  digitalWrite (LED1, LOW); digitalWrite (LED1, LOW); digitalWrite (LED2, LOW); digitalWrite (LED3, LOW); digitalWrite (LED4, LOW); digitalWrite (LED5, LOW);
  delay(50);
  digitalWrite (LED1, HIGH); digitalWrite (LED1, HIGH); digitalWrite (LED2, HIGH); digitalWrite (LED3, HIGH); digitalWrite (LED4, HIGH); digitalWrite (LED5, HIGH);
  delay(50);
  digitalWrite (LED1, LOW); digitalWrite (LED1, LOW); digitalWrite (LED2, LOW); digitalWrite (LED3, LOW); digitalWrite (LED4, LOW); digitalWrite (LED5, LOW);
 //________________________________________________________________________________________________________________________________________________________________________
 
 //_______________________FILL UP THE SCREEN BLACK______________________________________________________________________________________________________________

  mylcd.Fill_Screen(BLACK);
 //________________________________________________________________________________________________________________________________________________________________________
 
  Serial.begin(9600);
  Serial.println("THIS IS THE RECEIVER CODE");

  // Initiate the radio object
  radio.begin();

  // Set the transmit power to lowest available to prevent power supply related issues
  radio.setPALevel(RF24_PA_MIN);

  // Set the speed of the transmission to the quickest available
  radio.setDataRate(RF24_2MBPS);

  // Use a channel unlikely to be used by Wifi, Microwave ovens etc
  radio.setChannel(124);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openReadingPipe(0, addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.openReadingPipe(2, addresses[2]);
  radio.openReadingPipe(3, addresses[3]);
  radio.openReadingPipe(4, addresses[4]);
  radio.openReadingPipe(5, addresses[5]);
  

  // Start the radio listening for data
  radio.startListening();
  display_Table(); //DISPLAY THE TABLE PARAMETERS.display_Table(); //DISPLAY THE TABLE PARAMETERS.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void display_Table(void)
 {
  //===============Lines============================================================================================================================================
    mylcd.Set_Draw_color(RED);
    mylcd.Draw_Line(40, 90,40, mylcd.Get_Display_Height()-1); //mylcd.Draw_Line(10, 50,40, mylcd.Get_Display_Height()-1);  //(x, +h, y, -h) FIRST VERRTICAL LINE
    mylcd.Draw_Line(80, 90,80, mylcd.Get_Display_Height()-1); //mylcd.Draw_Line(10, 50,40, mylcd.Get_Display_Height()-1);  //(x, +h, y, -h) SECOND VERTICAL LINE
    mylcd.Draw_Line(120, 90,120, mylcd.Get_Display_Height()-1); //mylcd.Draw_Line(10, 50,40, mylcd.Get_Display_Height()-1);  //(x, +h, y, -h) THIRD VERTICAL LINE
    mylcd.Draw_Line(160, 90,160, mylcd.Get_Display_Height()-1); //mylcd.Draw_Line(10, 50,40, mylcd.Get_Display_Height()-1);  //(x, +h, y, -h) FOURTH VERTICAL LINE
    mylcd.Draw_Line(219, 90,219, mylcd.Get_Display_Height()-1); //mylcd.Draw_Line(10, 50,40, mylcd.Get_Display_Height()-1);  //(x, +h, y, -h) FIFTH VERTICAL LINE
 //________________________________________________________________________________________________________________________________________________________________

 //_____________DESIGN ON THE TOP OF THE SCREEN______________________
     mylcd.Set_Draw_color(0xF910);
     int i;
    
     for(i = 0; i< mylcd.Get_Display_Width();i+=5)
    {
     mylcd.Draw_Line(0, 10, i, mylcd.Get_Display_Height()-100);
     }
     for(i = mylcd.Get_Display_Height()-100; i>= 0;i-=5)
     {
     mylcd.Draw_Line(0, 10, mylcd.Get_Display_Width()-1, i);
     }
 //___________________________________________________________________
 
//___________CREATE RECTANGLE AND PUT A TEXT IN IT_________________________________________________________________________________
  mylcd.Fill_Rect(0, 0, 250, 10, RED); //(x y w h) RECTANGLE AT THE TOP POSITOPN OF THE DISPLAY
  mylcd.Set_Text_colour(0xFFF0);
  mylcd.Set_Text_Back_colour(RED);
  mylcd.Set_Text_Size(1);
  mylcd.Print_String("     MULTIPARAMETER WSN SYSTEM", 0, 0);
  mylcd.Fill_Rect(0, 170, 250, 6, RED); //(x y w h) RECTANGLE AT THE BOTTOM POSITOPN OF THE DISPLAY
  mylcd.Fill_Rect(0, 104, 250, 1, RED); //(x y w h) RECTANGLE AT THE TOP POSITOPN OF THE TABLE
  mylcd.Fill_Rect(40, 90, 250, 1, RED); //(x y w h) RECTANGLE AT THE TOP POSITOPN OF THE TABLE COVER UP THE TABLE TITLE
  mylcd.Fill_Rect(0, 77, 250, 2, PINK); //(x y w h) HORIZONTAL PINK LINE AT THE TOP POSITOPN OF THE TABLE COVER UP THE TABLE TITLE
//================================================================================================================================


//_________________________________________________TABLE TEXTS____________________________________________________________________

  mylcd.Set_Text_Mode(1);

{  
  mylcd.Set_Text_colour(WHITE);
  mylcd.Set_Text_Back_colour(YELLOW);
  mylcd.Set_Text_Size(1);
  //____________FIRST COLLUMN_____________
  mylcd.Print_String("NODE 1", 0, 107);
  mylcd.Print_String("NODE 2", 0, 120);
  mylcd.Print_String("NODE 3", 0, 133);
  mylcd.Print_String("NODE 4", 0, 146);
  mylcd.Print_String("NODE 5", 0, 159);
  mylcd.Print_String("MOTION", 42, 96); //X, Y AXIS
  mylcd.Print_String("SHOCK", 85, 96);  //X, Y AXIS
  mylcd.Print_String("TEMP C", 123, 96);  //X, Y AXIS
  mylcd.Print_String("HUMIDITY%", 163, 96);  //X, Y AXIS
  //_______________________________________
 
//___________________TOP  OF THE TABLE_______________________ 
  mylcd.Set_Text_colour(BLUE);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Print_String("SENSOR PARAMETERS & CONDITION", 40,80 );
//___________________________________________________________
}
//_________________________________________________________________________________________________________________________
 }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//___________________________________TRIP ALERT__________________________________________________________________
void Trip_Alert (void) {
  mylcd.Set_Text_Mode(1); 
  mylcd.Set_Text_colour(RED);
  mylcd.Set_Text_Back_colour(BLACK);
 
  mylcd.Print_String("!!!", 0, 85); delay(100); mylcd.Set_Text_colour(BLACK); mylcd.Print_String("!!!", 0, 85); 
}
//_______________________________________________________________________________________________________________

//____________________________________________________________________________________________________________________
void loop() {
//____PUT YOUR CODES HERE TO RUN REPEATEDLY_________________________
  data.id=0;
  mylcd.Set_Text_colour(0xFFF0);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(1);

//__Is there any data for us to get?_________________________________
  if ( radio.available()) {
//___________________________________________________________________

//_____Go and read the data and put it into that variable____________
    radio.read( &data, sizeof(data));
    Serial.println(data.id);
    Serial.println ((float)data.humidity, 2);  
    Serial.println ((float)data.temperature, 2);
    Serial.println (data.TiltStatus);
    Serial.println (data.PIRstatus);
    Serial.print("\n");
  }
//______CONNECTION LED STATUS FOR NODES AND DISPLAY FOR TEMPERATURE AND HUMIDITY FOR EACH NODE________________________________________________________________________________________


//_____________________NODE 1_______________________________________________________________________________________________________________________________________________________
  if(data.id==1)
{
 mylcd.Fill_Rect(123, 107, 30, 8, BLACK);  mylcd.Fill_Rect(163, 107, 30, 8, BLACK);  mylcd.Fill_Rect(42, 107, 35, 10, BLACK);  mylcd.Fill_Rect(83, 107, 35, 10, BLACK); //(x y w h)
 mylcd.Print_Number_Float(data.temperature, 2, 123,107, '.', 0, ' '); //FOR NODE 1 TEMPERATURE
 mylcd.Print_Number_Float(data.humidity, 2, 163,107, '.', 0, ' '); //FOR NODE 1 HUMIDITY
 mylcd.Print_String("Normal", 42, 107); //FOR NODE 1 MOTION
 mylcd.Print_String("Normal", 83, 107); //FOR NODE 1 SHOCK
digitalWrite (LED1, HIGH); delay(50);
}
else 
digitalWrite (LED1, LOW);

//___________________NODE 2________________________________________________________________________________________________________________________________________________________

  if(data.id==2)
{
 
 mylcd.Fill_Rect(123, 120, 30, 8, BLACK);  mylcd.Fill_Rect(163, 120, 30, 8, BLACK);   mylcd.Fill_Rect(42, 120, 35, 10, BLACK); mylcd.Fill_Rect(83, 120, 35, 10, BLACK); //(x y w h)
 mylcd.Print_Number_Float(data.temperature, 2, 123,120, '.', 0, ' '); //FOR NODE 2 TEMPERATURE
 mylcd.Print_Number_Float(data.humidity, 2, 163,120, '.', 0, ' '); //FOR NODE 2 HUMIDITY
  mylcd.Print_String("Normal", 42, 120); //FOR NODE 2 MOTION
   mylcd.Print_String("Normal", 83, 120); //FOR NODE 2 SHOCK
digitalWrite (LED2, HIGH); delay(50);
}
else 
digitalWrite (LED2, LOW);

//_____________________NODE 3____________________________________________________________________________________________________________________________________________________
  if(data.id==3)
{
 mylcd.Fill_Rect(123, 133, 30, 8, BLACK);  mylcd.Fill_Rect(163, 133, 30, 8, BLACK); mylcd.Fill_Rect(42, 133, 35, 10, BLACK); mylcd.Fill_Rect(83, 133, 35, 10, BLACK);  //(x y w h)
 mylcd.Print_Number_Float(data.temperature, 2, 123,133, '.', 0, ' '); //FOR NODE 3 TEMPERATURE
 mylcd.Print_Number_Float(data.humidity, 2, 163,133, '.', 0, ' '); //FOR NODE 3 HUMIDITY
 mylcd.Print_String("Normal", 42, 133); //FOR NODE 3 MOTION
 mylcd.Print_String("Normal", 83, 133); //FOR NODE 3 SHOCK
 digitalWrite (LED3, HIGH); delay(50);
}
else 
digitalWrite (LED3, LOW); 

//_____________________NODE 4___________________________________________________________________________________________________________________________________________________
  if(data.id==4)
{ 
 mylcd.Fill_Rect(123, 146, 30, 8, BLACK);  mylcd.Fill_Rect(163, 146, 30, 8, BLACK); mylcd.Fill_Rect(42, 146, 35, 10, BLACK); mylcd.Fill_Rect(83, 146, 35, 10, BLACK);//(x y w h)
 mylcd.Print_Number_Float(data.temperature, 2, 123,146, '.', 0, ' '); //FOR NODE 4 TEMPERATURE
 mylcd.Print_Number_Float(data.humidity, 2, 163,146, '.', 0, ' '); //FOR NODE 4 HUMIDITY
 mylcd.Print_String("Normal", 42, 146); //FOR NODE 4 MOTION
 mylcd.Print_String("Normal", 83, 146); //FOR NODE 4 SHOCK
 digitalWrite (LED4, HIGH); delay(50);
}
else 
digitalWrite (LED4, LOW);


//_____________________NODE 5___________________________________________________________________________________________________________________________________________________
  if(data.id==5)
{
  
 mylcd.Fill_Rect(123, 159, 30, 8, BLACK);  mylcd.Fill_Rect(163, 159, 30, 8, BLACK); mylcd.Fill_Rect(42, 159, 35, 10, BLACK); mylcd.Fill_Rect(83, 159, 35, 10, BLACK);//(x y w h)
 mylcd.Print_Number_Float(data.temperature, 2, 123,159, '.', 0, ' '); //FOR NODE 5 TEMPERATURE
 mylcd.Print_Number_Float(data.humidity, 2, 163,159, '.', 0, ' '); //FOR NODE 5 HUMIDITY
 mylcd.Print_String("Normal", 42, 159); //FOR NODE 5 MOTION
 mylcd.Print_String("Normal", 83, 159); //FOR NODE 5 SHOCK
 digitalWrite (LED5, HIGH); delay(50);
}
else 
digitalWrite (LED5, LOW);

//________________________BUZZER ALERT FOR ALL NODES____________________________

if (data.PIRstatus==1 or data.TiltStatus==1)
{buzzer();  mylcd.Set_Text_Size(2); Trip_Alert();}
//___________________________________________________________________________________

//___________________________________________NODE DISPLAY AND ALERT FOR MOTION STATUS FOR EACH NODE_____________________________________________________________


//_____________________PIR 1_______________________________________________________________________________________________________________________________________________________________
if (data.id ==1 && data.PIRstatus==1){mylcd.Fill_Rect(42, 107, 35, 10, RED);  mylcd.Set_Text_Size(1); mylcd.Print_String("Alert!", 42, 107); }//buzzer(); Trip_Alert();}//FOR NODE 1 MOTION
//_________________________________________________________________________________________________________________________________________________________________________________________

//_____________________PIR 2_______________________________________________________________________________________________________________________________________________________________
if (data.id ==2 && data.PIRstatus==1){ mylcd.Fill_Rect(42, 120, 35, 10, RED); mylcd.Set_Text_Size(1); mylcd.Print_String("Alert!", 42, 120); }//buzzer(); Trip_Alert();}//FOR NODE 2 MOTION
//_________________________________________________________________________________________________________________________________________________________________________________________

//_____________________PIR 3_______________________________________________________________________________________________________________________________________________________________
if (data.id ==3 && data.PIRstatus==1){mylcd.Fill_Rect(42, 133, 35, 10, RED); mylcd.Set_Text_Size(1);  mylcd.Print_String("Alert!", 42, 133); buzzer(); }//Trip_Alert();}//FOR NODE 3 MOTION
//_________________________________________________________________________________________________________________________________________________________________________________________

//_____________________PIR 4______________________________________________________________________________________________________________________________________________________________
if (data.id ==4 && data.PIRstatus==1){mylcd.Fill_Rect(42, 146, 35, 10, RED); mylcd.Set_Text_Size(1); mylcd.Print_String("Alert!", 42, 146); buzzer(); }//Trip_Alert();}//FOR NODE 4 MOTION
//________________________________________________________________________________________________________________________________________________________________________________________

//_____________________PIR 5_______________________________________________________________________________________________________________________________________________________________
if (data.id ==5 && data.PIRstatus==1){mylcd.Fill_Rect(42, 159, 35, 10, RED); mylcd.Set_Text_Size(1); mylcd.Print_String("Alert!", 42, 159); buzzer(); }//Trip_Alert();} //FOR NODE 5 MOTION
//_________________________________________________________________________________________________________________________________________________________________________________________



//___________________________________________NODE DISPLAY AND ALERT FOR SHOCK STATUS FOR EACH NODE_____________________________________________________________


//_____________________PIR 1____________________________________________________________________________________________________________________________________
if (data.id ==1 && data.TiltStatus==1){mylcd.Fill_Rect(83, 107, 35, 10, RED); mylcd.Set_Text_Size(1); mylcd.Print_String("Alert!", 83, 107); }//buzzer(); Trip_Alert();}// FOR NODE 1 SHOCK
//______________________________________________________________________________________________________________________________________________________________

//_____________________PIR 2_____________________________________________________________________________________________________________________________________
if (data.id ==2 && data.TiltStatus==1){ mylcd.Fill_Rect(83, 120, 35, 10, RED); mylcd.Set_Text_Size(1); mylcd.Print_String("Alert!", 83, 120); }//buzzer(); Trip_Alert();}//FOR NODE 2 SHOCK
//_______________________________________________________________________________________________________________________________________________________________

//_____________________PIR 3____________________________________________________________________________________________________________________________________
if (data.id ==3 && data.TiltStatus==1){mylcd.Fill_Rect(83, 133, 35, 10, RED); mylcd.Set_Text_Size(1); mylcd.Print_String("Alert!", 83, 133); }//buzzer(); Trip_Alert();}//FOR NODE 3 SHOCK
//______________________________________________________________________________________________________________________________________________________________

//_____________________PIR 4___________________________________________________________________________________________________________________________________
if (data.id ==4 && data.TiltStatus==1){mylcd.Fill_Rect(83, 146, 35, 10, RED); mylcd.Set_Text_Size(1); mylcd.Print_String("Alert!", 83, 146); }//buzzer(); Trip_Alert();}//FOR NODE 4 SHOCK
//_____________________________________________________________________________________________________________________________________________________________

//_____________________PIR 5____________________________________________________________________________________________________________________________________
if (data.id ==5 && data.TiltStatus==1){mylcd.Fill_Rect(83, 159, 35, 10, RED); mylcd.Set_Text_Size(1); mylcd.Print_String("Alert!", 83, 159); }//buzzer(); Trip_Alert();} //FOR NODE 5 SHOCK
//______________________________________________________________________________________________________________________________________________________________

}
