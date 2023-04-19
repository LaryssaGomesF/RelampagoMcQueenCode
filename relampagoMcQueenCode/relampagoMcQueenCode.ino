
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
#define PWM_M1 3
#define PWM_M2 5

//MOTOR LEFT
#define M3_M4_IN1 7
#define M3_M4_IN2 8
#define PWM_M3 6
#define PWM_M4 9


void setupPin(){
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
  pinMode(PWM_M1, OUTPUT);
  pinMode(PWM_M2, OUTPUT);
  pinMode(PWM_M3, OUTPUT);
  pinMode(PWM_M4, OUTPUT);
}

void calibracao(){

}

void setup() {
  setupPin();
  calibracao();

}




void loop() {
  // put your main code here, to run repeatedly:
}

void readLine(){

}

void MotorRight(int pwm){
 
  if(pwm==0){
    digitalWrite(M1_M2_IN1, LOW);
    digitalWrite(M1_M2_IN2, LOW);
  }
  else if(pwm<0)
  {
    analogWrite(PWM_M1, -pwm);
    digitalWrite(M1_M2_IN1, HIGH);
    digitalWrite(M1_M2_IN2, LOW);
  }
  else
  {
    analogWrite(PWM_M1, pwm);
    digitalWrite(M1_M2_IN1, LOW);
    digitalWrite(M1_M2_IN2, HIGH);
  }
}

