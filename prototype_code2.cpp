 #include <SoftwareSerial.h>
#include <Servo.h>
#include <NewPing.h>

#define irFL  8
#define irFR  9
#define irBL 10
#define irBR 11

#define ENA 7
#define ENB 2
#define IN1 6 
#define IN2 5
#define IN3 4
#define IN4 3

#define motor_speed 150
#define turning_speed 165

#define trig1 A0
#define echo1 A1
#define trig2 A2
#define echo2 A3

#define MAX_DmaxISTANCE 200
#define DETECTION_THRESHOLD 15
#define SERVO_PIN 9
#define min_ange 30
#define max_ange 150

SoftwareSerial mySerialBT(10, 11);

Servo myservo;
NewPing sonar1(trig1, echo1, max);
NewPing sonar2(trig2, echo2, max);

int k;

void setup() {
  Serial.begin(9600);

  while (!Serial) {}

  pinMode(irFL, OUTPUT);
  pinMode(irFR, OUTPUT);
  pinMode(irBL, OUTPUT);
  pinMode(irBR, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  myservo.attach(SERVO_PIN);
  myservo.write(min_ange);
  delay(500);

  mySerialBT.begin(9600);
  Serial.println("Waiting for connection");
  while (!mySerialBT) {
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connection Established!");
}

void loop() {
  if (mySerialBT.available()) {
    k = mySerialBT.read();
    if(k == 'F') {
      if(irFL == HIGH && irFR == HIGH) {
        forward(motor_speed, motor_speed);
      }
      if(irFL == LOW && irFR == HIGH) {
        fwd_left(-motor_speed, turning_speed);
      }
      if(irFL == HIGH && irFR == LOW) {
        fwd_right(turning_speed, -motor_speed);
      }
    }
    if(k == 'B') {
      if(irBL == HIGH && irBR == HIGH) {
        backward(motor_speed, motor_speed);
      }
      if(irBL == LOW && irBR == HIGH) {
        bkd_left(-motor_speed, turning_speed);
      }
      if(irBL == HIGH && irBR == LOW) {
        bkd_right(turning_speed, -motor_speed);
      }
    }
    if(k == 'S') {
      stopCar();
    }
  }

  for (int angle = min_ange; angle <= max_ange; angle += 2) {
    myservo.write(angle);
    delay(30);

    int distance1 = sonar1.ping_cm();
    int distance2 = sonar2.ping_cm();

    if (distance1 > 0 && distance1 <= DETECTION_THRESHOLD || distance2 > 0 && distance2 <= DETECTION_THRESHOLD) {
      moveBackward();
      delay(500);
      stopCar();
    }
  }

  for (int angle = max_ange; angle >= min_ange; angle -= 2) {
    myservo.write(angle);
    delay(30);

    int distance1 = sonar1.ping_cm();
    int distance2 = sonar2.ping_cm();

    if (distance1 > 0 && distance1 <= DETECTION_THRESHOLD || distance2 > 0 && distance2 <= DETECTION_THRESHOLD) {
      moveBackward();
      delay(500);
      stopCar();
    }
  }
}

void forward(int speed1, int speed2) {
  analogWrite(ENA, speed1);
  analogWrite(ENB, speed2);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void fwd_left(int speed1, int speed2) {
  analogWrite(ENA, speed1);
  analogWrite(ENB, speed2);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void fwd_right(int speed1, int speed2) {
  analogWrite(ENA, speed1);
  analogWrite(ENB, speed2);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward(int speed1, int speed2) {
  analogWrite(ENA, speed1);
  analogWrite(ENB, speed2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void bkd_left(int speed1, int speed2) {
  analogWrite(ENA, speed1);
  analogWrite(ENB, speed2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void bkd_right(int speed1, int speed2) {
  analogWrite(ENA, speed1);
  analogWrite(ENB, speed2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopCar() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

void moveBackward() {
  backward(motor_speed, motor_speed);
}
