#include <SPI.h>

#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

#define htonl(x) __builtin_bswap32((uint32_t) (x))

void setup() {
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("Scan card to see identification number");
}

void loop() {
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;
    }

    if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    unsigned int x = *(int *) mfrc522.uid.uidByte;
    Serial.print("Card #: ");
    Serial.println(x); 
    mfrc522.PICC_HaltA();
    Serial.println("Scan PICC to see UID and type...");
}
