
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

void calibracao() {
}

void setup() {
  setupPin();
  calibracao();
}

unsigned int sensors[8];
void loop() {

  int position = readLine(sensors[8]);
}

int readLine(int *sensor_values) {
  sensor_values[0] = { analogRead(s0) };
  sensor_values[1] = { analogRead(s1) };
  sensor_values[2] = { analogRead(s2) };
  sensor_values[3] = { analogRead(s3) };
  sensor_values[4] = { analogRead(s4) };
  sensor_values[5] = { analogRead(s5) };
  sensor_values[6] = { analogRead(s6) };
  sensor_values[7] = { analogRead(s7) };
  int _position = 0;
  return _position;
}

void MotorsRight(int pwm) {

  if (pwm == 0) {
    digitalWrite(M1_M2_IN1, LOW);
    digitalWrite(M1_M2_IN2, LOW);
  } else if (pwm < 0) {
    analogWrite(PWM_M1_M2, -pwm);
    digitalWrite(M1_M2_IN1, HIGH);
    digitalWrite(M1_M2_IN2, LOW);
  } else {
    analogWrite(PWM_M1_M2, pwm);
    digitalWrite(M1_M2_IN1, LOW);
    digitalWrite(M1_M2_IN2, HIGH);
  }
}

void MotorsLeft(int pwm) {

  if (pwm == 0) {
    digitalWrite(M3_M4_IN1, LOW);
    digitalWrite(M3_M4_IN2, LOW);
  } else if (pwm < 0) {
    analogWrite(PWM_M3_M4, -pwm);
    digitalWrite(M3_M4_IN1, HIGH);
    digitalWrite(M3_M4_IN2, LOW);
  } else {
    analogWrite(PWM_M3_M4, pwm);
    digitalWrite(M3_M4_IN1, LOW);
    digitalWrite(M3_M4_IN2, HIGH);
  }
}
