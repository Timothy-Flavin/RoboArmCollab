#include <Servo.h>
Servo base;
Servo lowArm;
Servo upArm;
Servo hand;
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  base.attach(6);  // attaches the servo on pin 9 to the servo object
  lowArm.attach(9);
  upArm.attach(10);
  hand.attach(11);
}

void loop() {
  for (pos = 0; pos <= 30; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    base.write(pos);   
    lowArm.write(pos+30);  
    upArm.write(pos+120);  
    hand.write(pos);  // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 30; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    base.write(pos);   
    lowArm.write(pos+30);  
    upArm.write(pos+120);  
    hand.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
}
