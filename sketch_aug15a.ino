#include <AFMotor.h> // library for DCMotor
#include <Servo.h>  // library for Servo motor

AF_DCMotor rWheel(4, MOTOR34_64KHZ); //initalize right wheel
AF_DCMotor lWheel(3, MOTOR34_64KHZ); // initalize left wheel
Servo ser; // initalize Servo

int trig = A0,echo=A1; // for ultrasonic sensor
long duration; 
int distance;

void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  ser.attach(9);
  ser.write(90); // looking ahead
  rWheel.setSpeed(190);
  lWheel.setSpeed(190); 
}

int dis(){
  // function for calculating distance
  digitalWrite(trig, LOW);
  delayMicroseconds(2); // turn trig off at the beginning
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); // turn trig on
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH); // calculate time 

  distance = duration * 0.034 / 2;  // measure distance
 
  return distance;
}

int look(){
  int ri,le; // values for both direction
  ser.write(0); // look right
  ri=dis();
  delay(1000);
  ser.write(180); // look left
  le=dis();
  delay(1000);
  ser.write(90); // straight ahead
  if(ri>=le) return 1; else return 0;
}

// 
void forward(){
  rWheel.run(FORWARD);
  lWheel.run(FORWARD);
}

void backward(){
  rWheel.run(BACKWARD);
  lWheel.run(BACKWARD);
}

void right(){
  rWheel.run(BACKWARD);
  lWheel.run(FORWARD);
}

void left(){
  rWheel.run(FORWARD);
  lWheel.run(BACKWARD);
}

// stops the car
void stopped(){
  rWheel.run(RELEASE);
  lWheel.run(RELEASE);
}

void loop() {
  int x= dis(); // get the distance ahead
  if(x>10){forward();}
  else{
  backward();
  delay(1000);
  stopped();
  delay(1000);
  int direction = look();
  if (direction == true){
    right();
    delay(500);
  } else {
    left();
    delay(500);
  }
}}
