// Install Pin change interrupt for a pin, can be called multiple times
char dataString[50] = {0};
int bumper[3] = {0,0,0};
 int a =0; 
 int sendPoints =0;
 byte pinSelected = 0;
 byte pinA3 = 15;
 byte pinA4 = 16;
 byte pinA5 = 17;
 byte pinSend = 3;
 int levens = 0;
 int addScore = 0;
int score[4] = {0, 0, 0, 0};
int totalScore = 0;
int theNumber[5]= {9, 10, 11, 12, 13};

byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0 klopt
                                                           { 1,0,0,1,0,0,0 },  // = 1 klopt
                                                           { 1,1,1,0,0,1,1 },  // = 2 klopt
                                                           { 1,0,1,1,0,1,1 },  // = 3 klopt
                                                           { 1,0,0,1,1,0,1 },  // = 4 klopt
                                                           { 0,0,1,1,1,1,1 },  // = 5 klopt
                                                           { 0,1,1,1,1,1,1 },  // = 6 klopt
                                                           { 1,0,0,1,0,1,0 },  // = 7 klopt
                                                           { 1,1,1,1,1,1,1 },  // = 8 klopt
                                                           { 1,0,1,1,1,1,1 }   // = 9 klopt
                                                           };


void sevenSegWrite(byte digit, int number) {
  byte pin = 2;
  for(int i = 0; i<5; i++){
    if(i == number)
    {
    digitalWrite(theNumber[i],0);
    }
    else
    {
      digitalWrite(theNumber[i], 1);
    }
  }
  if(number ==4)
  {
    for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[levens][segCount]);
    ++pin;
  }
  _delay_ms(1);
  }
  else{
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
  _delay_ms(1);
  }
}

void calcScore()
{
  score[0] = totalScore /1000;
  score[1] = totalScore % 1000 / 100;
  score[2] = totalScore % 1000 % 100 / 10;
  score[3] = totalScore % 1000 % 100 % 10;
  
}
void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}
// Use one Routine to handle each group
 
ISR (PCINT1_vect) // handle pin change interrupt for A0 to A5 here
 {
   if(digitalRead(A2) == LOW)
   {
     a = 1;
     levens = 3;
     sprintf(dataString,"%02X",a); // convert a value to hexa
     
      Serial.println(dataString);   // send the data 
      Serial.println(dataString);   // send the data
   }
   if(digitalRead(A3) == LOW && bumper[0] == 0)
   {
      a =2;
      pinSelected = pinA3;
      sendPoints = 1;
      bumper[0] = 1;
      totalScore +=7;
   } 
   if(digitalRead(A4) == LOW && bumper[1] == 0)
   {
      a=2;
      pinSelected = pinA4;
      sendPoints = 1;
      bumper[1] = 1;
      totalScore+=7;
   } 
   if(digitalRead(A5) == LOW && bumper[2] == 0)
   {
      a=2;
      pinSelected = pinA5;
      sendPoints = 1;
      bumper[2] = 1;
      totalScore+=7;
   } 
 }
  
void ledPWM(byte pin)
{
//  for(int i = 0; i<= 25; i++)
//  {
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
//    if(i == 25)
//    {
//      pinSelected =0; 
//    }
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
  
//}
}
void setValue()
{
   for(int i = 0; i<3; i++)
  {
   if(bumper[i] > 0)
   {
    bumper[i]++; 
   }
   if(bumper[i] ==25)
    {
     bumper[i] = 0;
     pinSelected =0;
 
    } 
  } 
}

 
void setup() {  
int i;
 
  pinMode(2, OUTPUT);   
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  //Which number
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);//levens
  
   digitalWrite(9, 1);
  digitalWrite(10, 1);
  digitalWrite(11, 1);
  digitalWrite(12, 1);
  digitalWrite(13, 1);
 
// set pullups, if necessary

  for (i=A0; i<=A5; i++)
      digitalWrite(i,HIGH);
  //sevenSegment segments
 
  pinMode(pinSend, OUTPUT); //outputq
  pinMode(pinA3,OUTPUT);
  pinMode(pinA4,OUTPUT);
  pinMode(pinA5,OUTPUT);
// enable interrupt for pin...
  pciSetup(A2);//start button A2 = start buttons, A3 to A5 are bumpers
  pciSetup(A3);
  pciSetup(A4);
  pciSetup(A5);
  
  Serial.begin(9600);              //Starting serial communication
}
 
 
void loop() {
//  sprintf(dataString,"%02X",a); // convert a value to hexa 
  if(levens > 0)
  {
  ledPWM(pinSelected);
 sprintf(dataString,"%02X",a); // convert a value to hexa 
  Serial.println(dataString);   // send the data
//  delay(20);
  a = 0;
  setValue();
  ledPWM(pinSelected);
   calcScore();
   for(int i = 0; i <5; i++){
     sevenSegWrite(score[i],i);
   }
  delay(10);                  // give the loop some break
  }
}