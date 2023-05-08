
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
#define M3_M4_IN1 7
#define M3_M4_IN2 8
#define PWM_M3_M4 6

int minValues[8] = { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000 };
int maxValues[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int sensor_values[8];
int lastError = 0;
const int MAX_SPEED = 255;
const int HALF_SPEED = 150;

void setupPin() {
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

int getPosition() {
  return (3 * sensorNormalization(1) + 2 * sensorNormalization(2) + 1 * sensorNormalization(3) - 1 * sensorNormalization(4) - 2 * sensorNormalization(5) - 3 * sensorNormalization(6));
}

int sensorNormalization(int position) {
  int result = (((sensor_values[position] - minValues[position]) / (maxValues[position] - minValues[position])) * 1000);
  return result;
}

void getMinAndMaxValues() {

  MotorsRight(255);                  //editar esse valor depois
  MotorsLeft(0);                     //editar esse valor depois
  for (int i = 0; i < 80000; i++) {  //editar esse valor depois
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

  MotorsRight(0);                    //editar esse valor depois
  MotorsLeft(255);                   //editar esse valor depois
  for (int i = 0; i < 80000; i++) {  //editar esse valor depois
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
}

void readSensors() {
  sensor_values[0] = { analogRead(s0) };
  sensor_values[1] = { analogRead(s1) };
  sensor_values[2] = { analogRead(s2) };
  sensor_values[3] = { analogRead(s3) };
  sensor_values[4] = { analogRead(s4) };
  sensor_values[5] = { analogRead(s5) };
  sensor_values[6] = { analogRead(s6) };
  sensor_values[7] = { analogRead(s7) };
}

int calculateError(int position) {
  return position - 3000;
}


void setup() {
  setupPin();
  getMinAndMaxValues();
  delay(10000);
}

void loop() {
  readSensors();
  int position = getPosition();
  int error = calculateError(position);
  int speedDifference = error / 2 + 8 * (error - lastError);
  lastError = error;
  int m1Speed = HALF_SPEED + speedDifference;
  int m2Speed = HALF_SPEED - speedDifference;

  MotorsRight(m1Speed);
  MotorsLeft(m2Speed);
}


void MotorsRight(int pwm) {
  digitalWrite(M1_M2_IN1, HIGH);
  digitalWrite(M1_M2_IN2, LOW);
  if (pwm < 0) {
    analogWrite(PWM_M1_M2, HALF_SPEED);
  } else if (pwm > 255) {
    analogWrite(PWM_M1_M2, MAX_SPEED);
  } else {
    analogWrite(PWM_M1_M2, pwm);
  }
}

void MotorsLeft(int pwm) {
  digitalWrite(M3_M4_IN1, HIGH);
  digitalWrite(M3_M4_IN2, LOW);
  if (pwm < 0) {
    analogWrite(PWM_M3_M4, HALF_SPEED);
  } else if (pwm > 255) {
    analogWrite(PWM_M3_M4, MAX_SPEED);
  } else {
    analogWrite(PWM_M3_M4, pwm);
  }
}
