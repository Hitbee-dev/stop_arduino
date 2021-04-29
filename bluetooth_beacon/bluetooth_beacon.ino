/*  
 *   Title. HNU Capstone :: STOP - Bluetooth Beacon
 *   Autor. K9714
 *   Date.  21. 04. 28
 */ 


#include <SoftwareSerial.h>

SoftwareSerial HM10(2,3); // RX, TX

// Check Sec
#define SLEEP_TIME 15 // (5, 10, 15) ms
#define MAX_COUNT 20

// Check MAC
String CHECK_UUID = "2E234454CF6D4A0FADF2F4911BA9FFA6";

// Parse Buffer
char buff[255] = {0};
char buff_idx = 0;

// counting
int success = 0, fail = 0;
int count = MAX_COUNT;
bool check = false;
bool start = false;


void setup() {
  //기본 통신속도는 9600입니다.
  Serial.begin(9600);
  HM10.begin(9600);
  Serial.println("Arduino UNO Start!");
}

void loop() {
  // Buffer check
  while (HM10.available()) {
    char data = HM10.read();
    buff[buff_idx++] = data;
    if (data == '\n') {
      buff[buff_idx] = '\0';
      parse_buffer();
    }
  }
  if (count > 0 && !start) {
    delay(SLEEP_TIME);
    count--;
    Serial.print("MSG COUNT : ");
    Serial.println(MAX_COUNT - count);
    HM10.println("AT+DISI?");
    start = true;
  }
  else if (count == 0 && !start) {
    count--;
    Serial.print("SUCCESS : ");
    Serial.println(success);
    Serial.print("Fail : ");
    Serial.println(fail);
  }
  
  while (Serial.available()) {
    byte data = Serial.read();
    HM10.write(data);
  }
}


void parse_buffer() {
  String line = buff;
  //Serial.println();
  if (line.substring(0, 8).equals("OK+DISC:")) {
    String mac = line.substring(17, 49);
    //Serial.println(mac);
    if (mac.equals(CHECK_UUID)) {
      check = true;
    }
  }
  if (line.substring(0, 8).equals("OK+DISCE")) {
    check ? success++ : fail++;
    check = false;
    start = false;
  }
  buff_idx = 0;
}
