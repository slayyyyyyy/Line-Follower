#include <QTRSensors.h>

const int m11Pin = 7;
const int m12Pin = 6;
const int m21Pin = 5;
const int m22Pin = 4;
const int m1Enable = 11;
const int m2Enable = 10;

int m1Speed = 0; //motor 1 speed
int m2Speed = 0; //motor 2 speed

// gain values
float kp = 14;
float ki = 0.65;
float kd = 2;

// passed to the pid controller
int p = 1;
int i = 0;
int d = 0;

int error = 0;
int lastError = 0;
float pidValue = 0;
const int maxNeglectableError = 45;

const int maxSpeed = 255;
const int minSpeed = -255;
const int baseSpeed = 255;
const int noSpeed = 0;
const int calibrationSpeed = 140;

QTRSensors qtr;
const int sensorCount = 6;
int sensorValues[sensorCount];
int sensors[sensorCount] = {0, 0, 0, 0, 0, 0};
const int minSensorValue = 0;
const int maxSensorValue = 5000;
const int minSensorError = -50;
const int maxSensorError = 50;

const int calibrationTime = 100;

// negative values represent the motor speed in reverse.
void setMotorSpeed(int motor1Speed, int motor2Speed) {
  if (motor1Speed == noSpeed) {
    digitalWrite(m11Pin, LOW);
    digitalWrite(m12Pin, LOW);
    analogWrite(m1Enable, motor1Speed);
  }
  else {
    if (motor1Speed > noSpeed) {
      digitalWrite(m11Pin, HIGH);
      digitalWrite(m12Pin, LOW);
      analogWrite(m1Enable, motor1Speed);
    }
    if (motor1Speed < noSpeed) {
      digitalWrite(m11Pin, LOW);
      digitalWrite(m12Pin, HIGH);
      analogWrite(m1Enable, -motor1Speed);
    }
  }
  if (motor2Speed == noSpeed) {
    digitalWrite(m21Pin, LOW);
    digitalWrite(m22Pin, LOW);
    analogWrite(m2Enable, motor2Speed);
  }
  else {
    if (motor2Speed > noSpeed) {
      digitalWrite(m21Pin, HIGH);
      digitalWrite(m22Pin, LOW);
      analogWrite(m2Enable, motor2Speed);
    }
    if (motor2Speed < noSpeed) {
      digitalWrite(m21Pin, LOW);
      digitalWrite(m22Pin, HIGH);
      analogWrite(m2Enable, -motor2Speed);
    }
  }
}

void moveLeftInPlace() {
  setMotorSpeed(noSpeed, calibrationSpeed);
}

void moveRightInPlace() {
  setMotorSpeed(calibrationSpeed, noSpeed);
}

void calibrateSensors(){
   for (uint16_t i = 0; i < calibrationTime; i++)
  {
    moveLeftInPlace();
    moveRightInPlace();
    qtr.calibrate();
  }
}

void setup() {
  pinMode(m11Pin, OUTPUT);
  pinMode(m12Pin, OUTPUT);
  pinMode(m21Pin, OUTPUT);
  pinMode(m22Pin, OUTPUT);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5}, sensorCount);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode
  calibrateSensors();
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  pidControl(kp, ki, kd);
  calculateMotorsSpeed();
  setMotorSpeed(m2Speed, m1Speed);
}

// calculate PID value based on error, kp, kd, ki, p, i and d.
void pidControl(float kp, float ki, float kd) {
  error = map(qtr.readLineBlack(sensorValues), minSensorValue, maxSensorValue, minSensorError, maxSensorError);

  if(abs(error) < maxNeglectableError){
    error = 0;
  }
  p = error;
  i = i + error;
  d = error - lastError;
  lastError = error;

  pidValue = kp * p + ki * i + kd * d;
}

// calculates the motor speeds based on the speed provided by pid controller
void calculateMotorsSpeed() {
  m1Speed = baseSpeed;
  m2Speed = baseSpeed;

  if (error < 0) {
    m1Speed += pidValue;
  } else if (error > 0) {
    m2Speed -= pidValue;
  }

  m1Speed = constrain(m1Speed, minSpeed, maxSpeed);
  m2Speed = constrain(m2Speed, minSpeed, maxSpeed);
}