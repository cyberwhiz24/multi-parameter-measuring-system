#define pirPin 5
#define  LED 10
int PIR=0;
int PIRstatus=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(pirPin, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(57600);

}

void loop() {
  // put your main code here, to run repeatedly:
  PIR = digitalRead(pirPin);
  if (PIR==HIGH)
{
  PIRstatus=1;
    Serial.print("PIR");
   Serial.print (PIRstatus);
     Serial.print("\n");
      digitalWrite(LED, HIGH);
     }
else 
if (PIR==LOW)
    PIRstatus=0;
    Serial.print("PIR");
    Serial.print (PIRstatus);
    Serial.print("\n");
    digitalWrite(LED, LOW);
}
