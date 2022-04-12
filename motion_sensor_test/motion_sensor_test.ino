#define PIR 2
#define RAD 5
#define SND 4

int previous_pir = LOW, previous_rad = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  pinMode(RAD, INPUT);
  pinMode(SND, OUTPUT);
  digitalWrite(SND, LOW);
}

void loop() {
  int pir = LOW;//digitalRead(PIR);
  int rad = digitalRead(RAD);
  
  if (previous_pir != pir && pir == HIGH) {
    Serial.println("PIR");
  }

  if (previous_rad != rad && rad == HIGH) {
    Serial.println("RAD");
  }

  previous_pir = pir;
  previous_rad = rad;
}
