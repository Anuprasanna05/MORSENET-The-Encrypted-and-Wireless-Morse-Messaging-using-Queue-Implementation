#include <WiFi.h>
#include <WiFiUdp.h>
#include <AESLib.h>

const char* ssid = "OPPO F21s Pro 5G";
const char* password = "K_i_r_u_b_a";
const char* receiverIP = "192.168.77.202";  // Replace with receiver ESP32's IP
const int udpPort = 1234;

WiFiUDP udp;
AESLib aesLib;

#define BUZZER_PIN 5  // Use GPIO5 for buzzer

// AES 128-bit key (16 bytes)
byte aes_key[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
                   0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00 };

// Initialization Vector (must be 16 bytes, same as receiver)
byte aes_iv[]  = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80,
                   0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0, 0x01 };

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  if (Serial.available()) {
    String plainText = Serial.readStringUntil('\n');
    plainText.trim();

    Serial.print("Plaintext: ");
    Serial.println(plainText);

    playBuzzer(plainText); // Beep based on message

    String encrypted = encryptAES(plainText);

    Serial.print("Encrypted (Base64): ");
    Serial.println(encrypted);

    udp.beginPacket(receiverIP, udpPort);
    udp.print(encrypted);
    udp.endPacket();
  }
}

// AES encryption function
String encryptAES(String plainText) {
  char encrypted[256];
  memset(encrypted, 0, sizeof(encrypted));

  aesLib.encrypt64((const byte*)plainText.c_str(), plainText.length(),
                   encrypted, aes_key, sizeof(aes_key), aes_iv);

  return String(encrypted);
}

// Buzzer function - short beep per character
void playBuzzer(String message) {
  for (int i = 0; i < message.length(); i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100); // Short beep
    digitalWrite(BUZZER_PIN, LOW);
    delay(100); // Pause between beeps
  }
}
