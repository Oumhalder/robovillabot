<SoftwareSerial.h>

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

SoftwareSerial mySerialBT(10, 11); // RX, TX

int k;

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

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

  
  mySerialBT.begin(9600);
  Serial.println("Waiting for connection")
  while (!mySerialBT)
  {
    Serial.print(".")
  }
  Serial.println();
  Serial.println("Connection Established!");
  
}

void loop() {
  if (mySerialBT.available())
  {
    k = mySerialBT.read();
    if(k == 'F')
    {
      if(irFL == HIGH && irFR == HIGH)
      {
        forward(motor_speed, motor_speed);
      }
      if(irFL == LOW && irFR == HIGH)
      {
        fwd_left(-motor_speed, turning_speed);
      }
      if(irFL == HIGH && irFR == LOW)
      {
        fwd_right(turning_speed, -motor_speed);
      }
    }
    if(k == 'B')
    {
      if(irBL == HIGH && irBR == HIGH)
      {
        backward(motor_speed, motor_speed);
      }
      if(irBL == LOW && irBR == HIGH)
      {
        bkd_left(-motor_speed, turning_speed);
      }
      if(irBL == HIGH && irBR == LOW)
      {
        bkd_right(turing_speed, -motor_speed);
      }
    }
    if(k == 'S')
    {
      stop();
    }
  }
}

forward(speed1, speed2) 
{
  analogWrite(ENA, speed1);
  analogWrite(ENB, speed2);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

fwd_left(speed1, speed2) 
{
  analogWrite(ENA, speed1);
  analogWrite(ENB, speed2);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

fwd_right(speed1, speed2)  
{
  analogWrite(ENA, speed1);
  analogWrite(ENB, speed2);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

backward(speed1, speed2) 
{
  analogWrite(ENA, speed1);
  analogWrite(ENB, speed2);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

bkd_left(speed1, speed2) 
{
  analogWrite(ENA, speed1);
  analogWrite(ENB, speed2);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

bkd_right(speed1, speed2) 
{
  analogWrite(ENA, speed1);
  analogWrite(ENB, speed2);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

stop()
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}
