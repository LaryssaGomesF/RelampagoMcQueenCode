//SENSORES
#define s0 A0
#define s1 A1
#define s2 A2
#define s3 A3
#define s4 A4
#define s5 A5
#define s6 A6
#define s7 A7

//MOTOR RIGHT
#define M1_M2_IN1 2
#define M1_M2_IN2 4
#define PWM_M1_M2 3

//MOTOR LEFT
#define M3_M4_IN2 7
#define M3_M4_IN1 8
#define PWM_M3_M4 9



int minValues[8] = { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000 };
int maxValues[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int sensor_values[8];
int lastError = 0;
int integral = 0;
const int MAX_SPEED = 255;
int HALF_SPEED = 150;
int MIN_SPEED = 120;
const float KP = 8.0;
const float KD = 30.0;
const float C1 = 1.0;
const float C2 = 2.0;
const float C3 = 3.0;

void setupPin() {
  Serial.begin(9600);
  pinMode(s0, INPUT);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(s6, INPUT);
  pinMode(s7, INPUT);
  pinMode(M1_M2_IN1, OUTPUT);
  pinMode(M1_M2_IN2, OUTPUT);
  pinMode(M3_M4_IN1, OUTPUT);
  pinMode(M3_M4_IN2, OUTPUT);
  pinMode(PWM_M1_M2, OUTPUT);
  pinMode(PWM_M3_M4, OUTPUT);
}

void getMinAndMaxValues() {

  MotorsLeft(-HALF_SPEED);
  MotorsRight(HALF_SPEED);
  for (int i = 0; i < 3000; i++) {
    readSensors();
    for (int i = 0; i < 8; i++) {
      if (sensor_values[i] < minValues[i]) {
        minValues[i] = sensor_values[i];
      }
      if (sensor_values[i] > maxValues[i]) {
        maxValues[i] = sensor_values[i];
      }
    }
  }
  MotorsLeft(HALF_SPEED);
  MotorsRight(-HALF_SPEED);
  for (int i = 0; i < 3000; i++) {
    readSensors();
    for (int i = 0; i < 8; i++) {
      if (sensor_values[i] < minValues[i]) {
        minValues[i] = sensor_values[i];
      }
      if (sensor_values[i] > maxValues[i]) {
        maxValues[i] = sensor_values[i];
      }
    }
  }
  MotorsLeft(0);
  MotorsRight(0);
}

float getPosition() {
  return (C3 * (sensorNormalization(1)) + C2 * (sensorNormalization(2)) + C1 * (sensorNormalization(3)) + -C1 * (sensorNormalization(4)) + -C2 * (sensorNormalization(5)) + -C3 * (sensorNormalization(6)));
}

float sensorNormalization(int pos) {
  float result = ((sensor_values[pos] - minValues[pos]) / (1.0 * (maxValues[pos] - minValues[pos])));
  return 1.0 - result;
}

void readSensors() {
  sensor_values[0] = analogRead(s0);
  sensor_values[1] = analogRead(s1);
  sensor_values[2] = analogRead(s2);
  sensor_values[3] = analogRead(s3);
  sensor_values[4] = analogRead(s4);
  sensor_values[5] = analogRead(s5);
  sensor_values[6] = analogRead(s6);
  sensor_values[7] = analogRead(s7);
}

int calculateError(float pos) {
  return 10 * pos;
}


void setup() {
  Serial.begin(9600);
  setupPin();
  getMinAndMaxValues();
  Serial.print("Ready");
  Serial.println();
  delay(3000);
}

int flag = 0;
int contD = 0;

void loop() {

  readSensors();

  float pos = getPosition();
  int error = calculateError(pos);
  int speedDifference = KP * error + KD *(error - lastError); //+ 0*integral;
  lastError = error;
  integral += error;

  int m1Speed = HALF_SPEED + speedDifference;
  int m2Speed = HALF_SPEED - speedDifference;


  MotorsRight(m1Speed);
  MotorsLeft(m2Speed);

  /*Serial.print("sensor  1    :");
  Serial.print(sensor_values[1]);
  Serial.println();

  Serial.print("sensor  2    :");
  Serial.print(sensor_values[2]);
  Serial.println();

  Serial.print("sensor  3    :");
  Serial.print(sensor_values[3]);
  Serial.println();

  Serial.print("sensor  4    :");
  Serial.print(sensor_values[4]);
  Serial.println();

  Serial.print("sensor  5   :");
  Serial.print(sensor_values[5]);
  Serial.println();

  Serial.print("sensor  6   :");
  Serial.print(sensor_values[6]);
  Serial.println();
  Serial.println();
  Serial.println();
  delay(5000);*/


  /*
  Serial.print("P:");
  Serial.print(pos);
  Serial.print(" E:");
  Serial.print(error);
  Serial.print(" D:");
  Serial.print(speedDifference);
  Serial.print(" M1:");
  Serial.print(m1Speed);
  Serial.print(" M2:");
  Serial.print(m2Speed);
  Serial.println();

 */

}

void MotorsRight(int pwm) {

  if (pwm < 0) {
    digitalWrite(M1_M2_IN1, LOW);
    digitalWrite(M1_M2_IN2, HIGH);
  } else {
    digitalWrite(M1_M2_IN1, HIGH);
    digitalWrite(M1_M2_IN2, LOW);
  }
  if (abs(pwm) > MAX_SPEED) {
    analogWrite(PWM_M1_M2, MAX_SPEED);
  } else if (abs(pwm) < MIN_SPEED) {
    analogWrite(PWM_M1_M2, abs(MIN_SPEED));
  } else {
    analogWrite(PWM_M1_M2, abs(pwm));
  }
}

void MotorsLeft(int pwm) {

  if (pwm < 0) {
    digitalWrite(M3_M4_IN1, LOW);
    digitalWrite(M3_M4_IN2, HIGH);
  } else {
    digitalWrite(M3_M4_IN1, HIGH);
    digitalWrite(M3_M4_IN2, LOW);
  }
  if (abs(pwm) > MAX_SPEED) {
    analogWrite(PWM_M3_M4, MAX_SPEED);
  } else if (abs(pwm) < MIN_SPEED) {
    analogWrite(PWM_M3_M4, abs(MIN_SPEED));
  } else {
    analogWrite(PWM_M3_M4, abs(pwm));
  }
}
