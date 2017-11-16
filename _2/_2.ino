#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
int sound = 250;
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);
//#include <Servo.h> //communicates to program to refer to the Servo library in the Arduino files
//These servos control the movement of the robot
//Servo myservo; // create servo object named myservo to control a servo
//Servo myservo1; //create servo object named myservo1 to control a servo
//int pos = 0; // variable to store the servo position
//Sets the Arduino Digital Ports for the Ultrasonic Sensor
const int trigPin = 7; //sets output pin for ultrasonic sensor 1 to digital port 7
const int echoPin = 8; //sets    input pin for ultrasonic sensor 1 to digital port 7
const int trigPin1 = 12; //sets output pin for ultrasonic sensor 2 to digital port 7
const int echoPin1 = 13; //sets input pin for ultrasonic sensor 2 to digital port 7
void setup() {
  Serial.begin(9600); //establishes a communication rate and BAUD number'
  AFMS.begin();
  pinMode(trigPin, OUTPUT); //initializes the digital port 7 trigPin as an output port
  pinMode(trigPin1, OUTPUT); //initializes the digital port 12 trigPin1 as an output port
  pinMode(echoPin, INPUT); //initializes the digital port 8 recieverPin as an input port
  pinMode(echoPin1, INPUT); //initializes the digital port 13 recieverPin1 as an input port
  motor1->setSpeed(50);
  motor2->setSpeed(50);
  motor3->setSpeed(50);
  motor4->setSpeed(50);

  motor1->run(RELEASE);
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);


}
void loop()
{
  long duration, inches, cm; //establishes three objects that can hold large numbers called duration, inches, and cm
  long duration1, inches1, cm1; //establishes three objects that can hold large numbers called duration1, inches1, and cm1
  //Triggers the first ultrasonic sensor to gather distances
  digitalWrite(trigPin, LOW); //turns on the output to a low power (not as many ultrasonic waves)
  delayMicroseconds(2); //waits for two milliseconds
  digitalWrite(trigPin, HIGH); //moves the output ultrasonic to high power
  delayMicroseconds(2); //waits five milliseconds
  digitalWrite(trigPin, LOW); //drops ultrasonic output back to low
  duration = pulseIn(echoPin, HIGH); //turns the input on ultrasonic sensor 1 to high so it can recieve the ultrasonic
  //waves that were emitted and sets duration to this time value
  // convert the time from the first ultrasonic sensor into a distance
  inches = microsecondsToInches(duration); //sets the inches object to the value of the duration converted to inches
  cm = microsecondsToCentimeters(duration); //sets the cm object to the value of the duration converted to centimeters

  //Triggers the second ultrasonic sensor to gather distances
  digitalWrite(trigPin1, LOW); //turns on the output to a low power (not as many ultrasonic waves)
  delayMicroseconds(2); //waits for two milliseconds
  digitalWrite(trigPin1, HIGH); //moves the output ultrasonic to high power
  delayMicroseconds(5); //waits five milliseconds
  digitalWrite(trigPin1, LOW); //drops ultrasonic output back to low
  duration1 = pulseIn(echoPin1, HIGH); //turns the input on ultrasonic sensor 2 on to high so it can recieve the ultrasonic
  //waves that were emitted and sets duration1 to this time value**

  // convert the time from the second ultrasonic sensor into a distance
  inches1 = microsecondsToInches(duration1); //sets the inches1 object to the value of the duration converted to inches
  cm1 = microsecondsToCentimeters(duration1); //sets the cm1 object to the value of the duration converted to centimeters
  //Serial Moniter Control
  Serial.print(inches); //prints the number of inches read by the first ultrasonic sensor
  Serial.print("in, "); //prints "in" after the number of inches to give a measurement to the value
  Serial.print(cm); //prints the number of centimeters read by the first ultrasonic sensor
  Serial.print("cm"); //prints "cm" after the number of centimeters to give a measurement to the value
  Serial.println(); //goes to next line in serial moniter

  Serial.print(inches1); //prints the number of inches read by the second ultrasonic sensor
  Serial.print("in1, "); //prints "in" after the number of inches to give a measurement to the value
  Serial.print(cm1); //prints the number of centimeters read by the second ultrasonic sensor
  Serial.print("cm1"); //prints "cm" after the number of centimeters to give a measurement to the value
  Serial.println(); //goes to next line in serial moniter

  delay(200); //waits 200 milliseconds before continuing
  //Robot Control Code based on distance read from ultrasonic sensors
  //Motors operate on a range of 0 to 200 where 90 is braking
  if (cm1 > 20 && cm > 20) //if both sensors read more than 20 cm, brake both motors
  {
    motor1->run(BACKWARD);
    motor2->run(BACKWARD);
    motor3->run(BACKWARD);
    motor4->run(BACKWARD);
  }
  if (cm1 < 20 && cm < 20) //if both sensors read less than 100 cm, go forward
  {
    motor1->run(FORWARD);
    motor2->run(FORWARD);
    motor3->run(FORWARD);
    motor4->run(FORWARD);
  }
  if (cm<20 & cm1>20) //if only something is in front of the left ultrasonic sensor, turn left
  {
    motor1->run(FORWARD);
    motor2->run(BACKWARD);
    motor3->run(RELEASE);
    motor4->run(RELEASE);
  }
  if (cm > 20 & cm1 < 20) //if only something is in front of the right ultrasonic sensor, turn right
  {
    motor1->run(BACKWARD);
    motor2->run(FORWARD);
    motor3->run(RELEASE);
    motor4->run(RELEASE);
  }
}
long microsecondsToInches(long microseconds) //store value for microseconds converted to inches
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second). This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2; //divide microseconds to get inches
}
long microsecondsToCentimeters(long microseconds) //store value for microseconds converted to centimeters
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds /19 / 2; //divide microseconds to get centimeters
}
