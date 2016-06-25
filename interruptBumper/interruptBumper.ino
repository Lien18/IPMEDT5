// Install Pin change interrupt for a pin, can be called multiple times
 char dataString[50] = {0};
 int a =0; 
void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}
 
// Use one Routine to handle each group
 
ISR (PCINT0_vect) // handle pin change interrupt for D8 to D13 here
 {      
     digitalWrite(13,digitalRead(8) and digitalRead(9));
 }
 
ISR (PCINT1_vect) // handle pin change interrupt for A0 to A5 here
 {
//   a = 3;
//     Serial.println("3");   // send the data
//     a = 3;
     if(digitalRead(A3) == LOW)
    {
//     digitalWrite(13,LOW);
    Serial.println("3");   // send the data
    } 
    else
    {
//      digitalWrite(13,HIGH);

        
    }
    if(digitalRead(A4) == LOW)
    {
//     digitalWrite(13,LOW);
//      Serial.println("4");   // send the data
       Serial.println("4");   // send the data
    } 
    else
    {
     
//      digitalWrite(13,HIGH);
    }
    if(digitalRead(A5) == LOW)
    {
//     digitalWrite(13,LOW);
      Serial.println("5");   // send the data
    } 
    else
    {
      
//      digitalWrite(13,HIGH);
 }  
 delay(100);
 }
 
ISR (PCINT2_vect) // handle pin change interrupt for D0 to D7 here
 {
     digitalWrite(13,digitalRead(7));
 }  
 
void setup() {  
int i;
 
// set pullups, if necessary
//  for (i=0; i<=12; i++)
//      digitalWrite(i,HIGH);  // pinMode( ,INPUT) is default
 
  for (i=A0; i<=A5; i++)
      digitalWrite(i,HIGH);
 
  pinMode(13,OUTPUT);  // LED
 
// enable interrupt for pin...
//  pciSetup(7);
//  pciSetup(8);
//  pciSetup(9);
  pciSetup(A3);
  pciSetup(A4);
  pciSetup(A5);
  Serial.begin(9600);              //Starting serial communication
}
 
 
void loop() {
  // Nothing needed
//  sprintf(dataString,"%02X",a); // convert a value to hexa 
  Serial.println(a);   // send the data
  a = 0;
  delay(1000);                  // give the loop some break
}
