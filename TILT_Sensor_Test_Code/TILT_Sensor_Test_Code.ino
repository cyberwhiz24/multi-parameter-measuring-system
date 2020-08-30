#define tiltPin 3
#define  LED 10
bool TILT=0;
int TILTstatus=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(tiltPin, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(57600);

}

void loop() {
  // put your main code here, to run repeatedly:
  TILT= digitalRead(tiltPin);
  if (TILT==LOW)
{
  TILTstatus=1;
    Serial.print("TILT ");
   Serial.print (TILTstatus);
     Serial.print("\n");
      digitalWrite(LED, HIGH);
     }
else 
if (TILT==HIGH)
    TILTstatus=0;
    Serial.print("TILT ");
    Serial.print (TILTstatus);
    Serial.print("\n");
    digitalWrite(LED, LOW);
}
