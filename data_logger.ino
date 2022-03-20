#include <SPI.h>
#include <SD.h>

#define LED A7
#define PIR 2
#define MAN 6
#define CS 4

File file;
int file_num = -1;
String file_name;
String dir_path = "data";

int pir_p = LOW;
int man_p = LOW;
int time_p = 0;

void setup() {
  Serial.begin(9600);

  if (!SD.begin(CS)) {
    Serial.println("Error 1");
    while (1);
  }

  if (!SD.exists(dir_path)) {
    Serial.println("Making directory: " + dir_path);
    SD.mkdir(dir_path);
  }

  File dir = SD.open("/" + dir_path);
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;

    String entry_name = entry.name();
    Serial.println(entry_name);
    int l = entry_name.indexOf('_'), r = entry_name.indexOf('.');
    file_num =  max(file_num, entry_name.substring(l + 1, r).toInt());
  }
  file_num++;
  file_name = dir_path + "/log_" + (String)file_num + ".csv";

  Serial.println("Current log: " + (String)file_num);

  file = SD.open(file_name, FILE_WRITE);
  if (file) {
    file.println("time,sensor,value");
    file.close();
  }

  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(MAN, INPUT);
}

void loop() {
  int pir = digitalRead(PIR);  
  if (pir != pir_p) {
    if (pir) {
      log_data("PIR", pir);
    }
    pir_p = pir;
  }

  int man = digitalRead(MAN);
  if (man != man_p) {
    if (man) {
      log_data("MANUAL", man);
    }
    man_p = man;
  }
}

void log_data(String sensor, int value) {
  unsigned long time_n = millis();

  if (time_n - time_p >= 1000) {
    file = SD.open(file_name, FILE_WRITE);
    if (file) {
      // Serial.println((String)time + ",MANUAL" + "," + (String)in);
      file.println((String)time_n + "," + sensor + "," + (String)value);
      file.close();
    }
    time_p = time_n;
  }

  read_data();
}

void read_data() {
  file = SD.open(file_name);
  if (file) {
    Serial.println("Data: ");

    while (file.available()) {
      Serial.write(file.read());
    }

    file.close();
  }
  else {
    Serial.println("Error 2");
  }
}
