// Install Pin change interrupt for a pin, can be called multiple times
char dataString[50] = {0};
 int a =0; 
 byte pinSelected = 0;
 byte pinA3 = 11;
 byte pinA4 = 12;
 byte pinA5 = 13;
void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}
void ledPWM(byte pin)
{
  for(int i = 0; i<= 25; i++)
  {
    if(pin != 0)
   {
    digitalWrite(pinA3, LOW);
    digitalWrite(pinA4, LOW);
    digitalWrite(pinA5, LOW);
    delay(1);
    digitalWrite(pinA3, HIGH);
    digitalWrite(pinA4, HIGH);
    digitalWrite(pinA5, HIGH);
    digitalWrite(pin, LOW);
    delay(10); 
    if(i == 25)
    {
      pinSelected =0; 
    }
  }
  else
  {
    digitalWrite(pinA3, LOW);
    digitalWrite(pinA4, LOW);
    digitalWrite(pinA5, LOW);
    delay(1);
    digitalWrite(pinA3, HIGH);
    digitalWrite(pinA4, HIGH);
    digitalWrite(pinA5, HIGH);
    delay(10);
  }
  
}
}

// Use one Routine to handle each group
 
ISR (PCINT1_vect) // handle pin change interrupt for A0 to A5 here
 {
     if(digitalRead(A3) == LOW)
    {
//      pinSelected = pinA3;
//      a =2;
    } 
    else
    {
//      digitalWrite(13,HIGH);
//        a=1;
        pinSelected = pinA3;
    }
    if(digitalRead(A4) == LOW)
    {
        pinSelected = pinA4;
    } 
//    else
//    {
//     
////      digitalWrite(13,HIGH);
//    }
    if(digitalRead(A5) == LOW)
    {
       pinSelected = pinA5  ;
    } 
//    else
//    {
//      
////      digitalWrite(13,HIGH);
// }  
// delay(100);
 a = 2;
 }
 
ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
 {
     digitalWrite(13,digitalRead(7));
 }  
 
void setup() {  
int i;
 
// set pullups, if necessary

  for (i=A0; i<=A5; i++)
      digitalWrite(i,HIGH);
 
  pinMode(pinA3,OUTPUT);  // LEDs
  pinMode(pinA4,OUTPUT);
  pinMode(pinA5,OUTPUT);
// enable interrupt for pin...
  pciSetup(A3);
  pciSetup(A4);
  pciSetup(A5);
  Serial.begin(9600);              //Starting serial communication
}
 
 
void loop() {
  // Nothing needed
//  sprintf(dataString,"%02X",a); // convert a value to hexa 
  ledPWM(pinSelected);
//  ledPWM(14,2);
//  ledPWM(15,2);
  sprintf(dataString,"%02X",a); // convert a value to hexa 
  Serial.println(dataString);   // send the data
  a = 0;
  delay(10);                  // give the loop some break
}
