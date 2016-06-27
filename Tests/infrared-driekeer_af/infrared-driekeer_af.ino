int gameover = 0;

void setup() {
  Serial.begin(9600);
}
 
void loop() {
  //pin A1
  int sensorValue = analogRead(A1);
  //als value lager is, dan komt de bal langs
  if(sensorValue <= 1011){
    Serial.println("Bal");
    gameover = gameover + 1;
  }
  //Als je 3x af bent is het game over
  if(gameover == 3){
    Serial.println("Game Over");
    gameover = 0;
  }
  //delay voor nauwkeurige metingen
  delay(50);       
}
