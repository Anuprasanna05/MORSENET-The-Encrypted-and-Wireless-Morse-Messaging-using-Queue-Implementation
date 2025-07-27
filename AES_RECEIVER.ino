#include <WiFi.h>
#include <WiFiUdp.h>
#include <AESLib.h>
#include <LiquidCrystal.h>

// WiFi credentials
const char* ssid = "OPPO F21s Pro 5G";
const char* password = "K_i_r_u_b_a";
const int udpPort = 1234;

WiFiUDP udp;
AESLib aesLib;

// AES key and IV (must match transmitter)
byte aes_key[] = {
  0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
  0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00
};

byte aes_iv[] = {
  0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80,
  0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0, 0x01
};

char incomingPacket[512];

// LCD pin config: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(23, 22, 21, 19, 18, 5);

void setup() {
  Serial.begin(115200);

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);  // Blue LED off

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
    digitalWrite(2, HIGH); // LED ON
  } else {
    Serial.println("\nWiFi FAILED");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Failed");
    digitalWrite(2, LOW);
    return;
  }

  udp.begin(udpPort);
  Serial.print("Listening on UDP port ");
  Serial.println(udpPort);

  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting Msg...");
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);

    int len = udp.read(incomingPacket, sizeof(incomingPacket) - 1);
    if (len > 0) {
      incomingPacket[len] = 0;
    }

    Serial.print("Encrypted (Base64): ");
    Serial.println(incomingPacket);

    String decryptedMessage = decryptAES(String(incomingPacket));

    Serial.print("Decrypted: ");
    Serial.println(decryptedMessage);
    Serial.print("Length: ");
    Serial.println(decryptedMessage.length());

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Received:");
    lcd.setCursor(0, 1);
    if (decryptedMessage.length() > 0) {
      lcd.print(decryptedMessage.substring(0, 16));
    } else {
      lcd.print("Decryption Failed");
    }
  }
}

String decryptAES(String encryptedBase64) {
  byte decrypted[256];
  memset(decrypted, 0, sizeof(decrypted));

  aesLib.decrypt64((char*)encryptedBase64.c_str(), encryptedBase64.length(),
                   decrypted, aes_key, sizeof(aes_key), aes_iv);

  return String((char*)decrypted);
}
