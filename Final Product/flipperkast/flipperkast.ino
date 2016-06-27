// Install Pin change interrupt for a pin, can be called multiple times
char dataString[50] = {0};
int bumperEnGang[5] = {0,0,0,0,0};
 int a =0; 
 int sendPoints =0;
 byte pinSelected = 0;
 byte pinA3 = 14;
 byte pinA4 = 15;
 byte pinA5 = 16;
 byte pinSend = 3;
 int levens = 0;
 int addScore = 0;
 int beginGame = 0;
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

void checkGang(){
   // aangesloten op pin A0 & pin A1
  int sensorValueScore = analogRead(A1);
  int sensorValueLevens = analogRead(A0);
  // als de bal voorbij rolt, is de value lager dan 800
  if(bumperEnGang[3] == 0){
  if(sensorValueScore <= 800){
    totalScore += 7 ;
    a=3;
    bumperEnGang[3] = 1;
  }

  //als value lager is, dan komt de bal langs
  if(bumperEnGang[4] == 0){
  if(sensorValueLevens <= 1011){
    levens -= 1;
    if(levens ==0)
    {
      a = 4;
      sprintf(dataString,"%02X",a); // convert a value to hexa 
      Serial.println(dataString);   // send the data
      Serial.println(dataString); 
      Serial.println(dataString); 
      Serial.println(dataString); 
    }
    else{
    bumperEnGang[4] = 1;
    }
  }
  }
}
}
// Use one Routine to handle each group
void interruptButton()
 {
   if(beginGame == 0)
   {
    beginGame = 1; 
   }
   else
   {
     a = 1;
     levens = 3;
     sprintf(dataString,"%02X",a); // convert a value to hexa
     
      Serial.println(dataString);   // send the data 
      Serial.println(dataString);   // send the data
   }
 }
void interruptBumper()
 {
   if(levens != 0){
    
   
   if(digitalRead(19) == LOW && bumperEnGang[0] == 0)
   {
      a =2;
      pinSelected = pinA3;
      sendPoints = 1;
      bumperEnGang[0] = 1;
      totalScore +=7;
   } 
   if(digitalRead(20) == LOW && bumperEnGang[1] == 0)
   {
      a=2;
      pinSelected = pinA4;
      sendPoints = 1;
      bumperEnGang[1] = 1;
      totalScore+=7;
   } 
   if(digitalRead(21) == LOW && bumperEnGang[2] == 0)
   {
      a=2;
      pinSelected = pinA5;
      sendPoints = 1;
      bumperEnGang[2] = 1;
      totalScore+=7;
   } 
 }
 }

void boardPWM(int state)
{

    digitalWrite(22, state);
    digitalWrite(23, state);
    digitalWrite(24, state);
    digitalWrite(25, state);
    digitalWrite(26, state);
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
   for(int i = 0; i<5; i++)
  {
   if(bumperEnGang[i] > 0)
   {
    bumperEnGang[i]++; 
   }
   if(bumperEnGang[i] ==25)
    {
     bumperEnGang[i] = 0;
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

  //Leds from the Board
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
    pinMode(18, INPUT_PULLUP);
    pinMode(19, INPUT_PULLUP);
    pinMode(20, INPUT_PULLUP);
    pinMode(21, INPUT_PULLUP);
   digitalWrite(9, 1);
  digitalWrite(10, 1);
  digitalWrite(11, 1);
  digitalWrite(12, 1);
  digitalWrite(13, 1);
//  digitalWrite(28,
 
// set pullups, if necessary


  attachInterrupt(digitalPinToInterrupt(18), interruptButton, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), interruptBumper, CHANGE);
  attachInterrupt(digitalPinToInterrupt(20), interruptBumper, CHANGE);
  attachInterrupt(digitalPinToInterrupt(21), interruptBumper, CHANGE);
  Serial.begin(9600);              //Starting serial communication
}
 
 
void loop() {
//  sprintf(dataString,"%02X",a); // convert a value to hexa 
  if(levens > 0)
  {
  ledPWM(pinSelected);
//  checkGang();
  boardPWM(1);
 sprintf(dataString,"%02X",a); // convert a value to hexa 
  Serial.println(dataString);   // send the data
//  delay(20);
  a = 0;
  setValue();
  ledPWM(pinSelected);
  boardPWM(0);
   calcScore();
   for(int i = 0; i <5; i++){
     sevenSegWrite(score[i],i);
   }
  delay(10);                  // give the loop some break
  }
  else
  {
    digitalWrite(26, HIGH);
    delay(1000);
    digitalWrite(26, LOW);
    delay(1000);
  }
  
}
