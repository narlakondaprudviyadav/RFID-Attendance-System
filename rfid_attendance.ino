#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

#define GREEN_LED 5
#define RED_LED 6
#define BUZZER 4

MFRC522 rfid(SS_PIN, RST_PIN);

// UIDs
String card1 = "9A 04 02 35"; // Shivani
String card2 = "0C F3 12 07"; // Prudvi
String card3 = "1A E8 54 30"; // Vikram

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("RFID Attendance System");
  Serial.println("Scan your card...");
}

void loop() {

  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  String uid = "";

  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uid += "0";
    uid += String(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) uid += " ";
  }

  uid.toUpperCase();

  Serial.print("UID: ");
  Serial.println(uid);

  // MATCHING WITH NAMES
  if (uid == card1) {
    Serial.println("Shivani Present ✅");

    digitalWrite(GREEN_LED, HIGH);
    tone(BUZZER, 1000);
  }
  else if (uid == card2) {
    Serial.println("Prudvi Present ✅");

    digitalWrite(GREEN_LED, HIGH);
    tone(BUZZER, 1000);
  }
  else if (uid == card3) {
    Serial.println("Vikram Present ✅");

    digitalWrite(GREEN_LED, HIGH);
    tone(BUZZER, 1000);
  }
  else {
    Serial.println("Unknown Card ❌");

    digitalWrite(RED_LED, HIGH);
    tone(BUZZER, 200);
  }

  delay(1500);

  // RESET OUTPUTS
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  noTone(BUZZER);

  Serial.println("----------------------");

  delay(500);
}