int score = 0;

void setup() {

  Serial.begin(9600);
}
 

void loop() {
  // aangesloten op pin A0
  int sensorValue = analogRead(A0);
  // als de bal voorbij rolt, is de value lager dan 800
  if(sensorValue <= 800){
    Serial.println("Bal");
    score = score +7 ;
    Serial.println(score);
  }
  // delay voor nauwkeurige metingen
  delay(50);        
}
