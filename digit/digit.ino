// Arduino 7 segment display example software
// http://www.hacktronics.com/Tutorials/arduino-and-7-segment-led.html
// License: http://www.opensource.org/licenses/mit-license.php (Go crazy)
 
// Define the LED digit patters, from 0 - 9
// Note that these patterns are for common cathode displays
// For common anode displays, change the 1's to 0's and 0's to 1's
// 1 = LED on, 0 = LED off, in this order:
//                                    Arduino pin: 2,3,4,5,6,7,8
int score[4] = {0, 0, 0, 0};
int totalScore = 1740;
int theNumber[4]= {9, 10, 11, 12};
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

void setup() {                
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
  digitalWrite(9, 1);
  digitalWrite(10, 1);
  digitalWrite(11, 1);
  digitalWrite(12, 1);
  //writeDot(0);  // start with the "dot" off
}

//void writeDot(byte dot) {
//  digitalWrite(9, dot);
//}
    
void sevenSegWrite(byte digit, int number) {
  byte pin = 2;
  for(int i = 0; i<4; i++){
    if(i == number)
    {
    digitalWrite(theNumber[i],0);
    }
    else
    {
      digitalWrite(theNumber[i], 1);
    }
  }
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
  _delay_ms(1);
}
void calcScore()
{
  score[0] = totalScore /1000;
  score[1] = totalScore % 1000 / 100;
  score[2] = totalScore % 1000 % 100 / 10;
  score[3] = totalScore % 1000 % 100 % 10;
  
}
void loop() {
  totalScore = 9888;
  calcScore();
  for(int i = 0; i <4; i++){
    sevenSegWrite(score[i],i);
  }
  //Score + 7
  
//  for (byte count = 10; count > 0; --count) {
//   delay(1000);
//   sevenSegWrite(count - 1); 
 // }
  //delay(4000);
}
