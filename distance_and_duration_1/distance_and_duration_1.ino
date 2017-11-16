const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}
void loop() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  if(distance>=100 || distance <= 2){
    Serial.print("Distance = ");
    Serial.print("Out of range");
    Serial.println("Duration = ");
    Serial.print(duration);
    
    delay(2000); //slows down printout break in program
  }
  else{
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println("cm");
    Serial.print("Duration = ");
    Serial.println(duration);
    
    delay(2000); //slows down printout break in program
 
  }
}
