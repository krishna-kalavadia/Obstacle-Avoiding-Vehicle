#include <Servo.h>
#include <NewPing.h>

// Set up ultrasonic sensor
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Set up servo
Servo servo1;
int servo1_pin = 10;

// Set up pin numbers of the DC motors
int front_motor1_forward = 3;
int front_motor1_backward = 2;
int front_motor2_forward = 5;
int front_motor2_backward = 4;

int rear_motor3_forward = 7;
int rear_motor3_backward = 6;
int rear_motor4_forward = 9;
int rear_motor4_backward = 8;

void setup() {
  servo1.attach(servo1_pin);

  // Make sure ultrasonic senor is looking forward
  servo1.write(90);
  delay(500);

  // Set the DC motor pins to output
  pinMode(front_motor1_forward, OUTPUT);
  pinMode(front_motor1_backward, OUTPUT);
  pinMode(front_motor2_forward, OUTPUT);
  pinMode(front_motor2_backward, OUTPUT);

  pinMode(rear_motor3_forward, OUTPUT);
  pinMode(rear_motor3_backward, OUTPUT);
  pinMode(rear_motor4_forward, OUTPUT);
  pinMode(rear_motor4_backward, OUTPUT);

}

void loop() {
  move_forward();

  int distance =  get_distance();
  // If a close object is detected find the direction that does not have obstacles
  if (distance < 25){
    stop_motors();
    int distance_left = look_left();
    int distance_right = look_right();

    if (distance_left > distance_right){
      turn_left();
    }
    else{
      turn_right();
    }
  }
}


int look_right()
{
  // Rotate servo to the right and ping to get distance
  delay(500);
  servo1.write(0);
  delay(1000);
  int distance = get_distance();
  servo1.write(90);
  return distance;
}


int look_left()
{
  // Rotate servo to the left and ping to get distance
  delay(500);
  servo1.write(180);
  delay(1000);
  int distance = get_distance();
  servo1.write(90);
  return distance;
}


int get_distance(){
  // Ping to get a distance value
  delay(50);
  int distance_cm = sonar.ping_cm();
  // Incorrect values of 0 can be returned, so set 0's to a large value
  if (distance_cm == 0){
    distance_cm = 999;
  }
  return distance_cm;
}


void turn_right(){
  // Rotate chassis to the right
  digitalWrite(front_motor1_forward, HIGH);
  digitalWrite(front_motor1_backward, LOW);

  digitalWrite(front_motor2_forward, LOW);
  digitalWrite(front_motor2_backward, HIGH);

  digitalWrite(rear_motor3_forward, HIGH);
  digitalWrite(rear_motor3_backward, LOW);

  digitalWrite(rear_motor4_forward, LOW);
  digitalWrite(rear_motor4_backward, HIGH);
  delay(950);

}


void turn_left(){
  // Rotate chassis to the left
  digitalWrite(front_motor1_forward, LOW);
  digitalWrite(front_motor1_backward, HIGH);

  digitalWrite(front_motor2_forward, HIGH);
  digitalWrite(front_motor2_backward, LOW);

  digitalWrite(rear_motor3_forward, LOW);
  digitalWrite(rear_motor3_backward, HIGH);

  digitalWrite(rear_motor4_forward, HIGH);
  digitalWrite(rear_motor4_backward, LOW);
  delay(950);

}

void stop_motors(){
  // Stop rotation of all 4 motors
  digitalWrite(front_motor1_forward, LOW);
  digitalWrite(front_motor1_backward, LOW);

  digitalWrite(front_motor2_forward, LOW);
  digitalWrite(front_motor2_backward, LOW);

  digitalWrite(rear_motor3_forward, LOW);
  digitalWrite(rear_motor3_backward, LOW);

  digitalWrite(rear_motor4_forward, LOW);
  digitalWrite(rear_motor4_backward, LOW);
}

void move_forward()
{
  // Rotate all 4 motors
  digitalWrite(front_motor1_forward, HIGH);
  digitalWrite(front_motor1_backward, LOW);

  digitalWrite(front_motor2_forward, HIGH);
  digitalWrite(front_motor2_backward, LOW);

  digitalWrite(rear_motor3_forward, HIGH);
  digitalWrite(rear_motor3_backward, LOW);

  digitalWrite(rear_motor4_forward, HIGH);
  digitalWrite(rear_motor4_backward, LOW);
}