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
#define PWM_M3_M4 6

int minValues[8] = { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000 };
int maxValues[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int sensor_values[8];
int lastError = 0;
const int MAX_SPEED = 250;
const int HALF_SPEED = 200;

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

int getPosition() {
  return (3 * sensorNormalization(1) + 2 * sensorNormalization(2) + 1 * sensorNormalization(3) + 1 * sensorNormalization(4) + 2 * sensorNormalization(5) + 3 * sensorNormalization(6));
}

int sensorNormalization(int position) {
  float result = ((((sensor_values[position] - minValues[position])* 1.0) / (maxValues[position] - minValues[position]))*1000);
  return result;
}

void getMinAndMaxValues() {
  //editar esse valor depois
  for (int i = 0; i < 15000; i++) {  //editar esse valor depois
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
  return (position - 3000);
}


void setup() {
  Serial.begin(9600);
  setupPin();
  getMinAndMaxValues();
  for (int i = 0; i < 8; i++) {
    Serial.println("Min value $i:     ");
    Serial.println(minValues[i]);
  }
  for (int i = 0; i < 8; i++) {
    Serial.println("Max value $i:     ");
    Serial.println(maxValues[i]);
  }
  Serial.println();
}

void loop() {

  readSensors();
  int position = getPosition();
  int error = calculateError(position);
  int speedDifference = error / 500 + 2 * (error - lastError);
  lastError = error;
  int m1Speed = HALF_SPEED + speedDifference;
  int m2Speed = HALF_SPEED - speedDifference;

  Serial.println("POSICAO:               ");
  Serial.println(position);
  Serial.println("ERROR:               ");
  Serial.println(error);
  Serial.println("SPEEDDIFFERENCE:               ");
  Serial.println(speedDifference);
  Serial.println("M1SPEED:               ");
  Serial.println(m1Speed);
  Serial.println("M2SPEED:               ");
  Serial.println(m2Speed);


  // MotorsRight(200);
  // MotorsLeft(200);
  delay(5000);
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