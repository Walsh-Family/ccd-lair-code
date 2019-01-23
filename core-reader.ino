#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include "deprecated.h"
#include "MFRC522.h"
#include "MFRC522Extended.h"
#include "require_cpp11.h"


#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define htonl(x) __builtin_bswap32((uint32_t) (x))

void setup() {
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("Scan card to see identification number");
    lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
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
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Card Number: ");
    lcd.setCursor(0,1);
    lcd.print(x);
    delay(2000);
    lcd.clear();

    if(x == 10087) 
    {
      lcd.print("Welcome!");
    }
    else
    {
      lcd.print("Go away!");
    }
}
