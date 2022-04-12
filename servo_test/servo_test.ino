#include <Servo.h>

#define PIR 3
#define SERVO A0

Servo servo;
int previous_pir = LOW;
int servo_pos = 0;

void setup() {
  pinMode(PIR, INPUT);
  servo.attach(SERVO);
}

void loop() {
  int pir = digitalRead(PIR);

  if (previous_pir != pir && pir == HIGH) {
    servo.write(servo_pos);
    if (servo_pos == 0) servo_pos = 180;
    else servo_pos = 0;
    delay(500);
  }

  previous_pir = pir;
}
