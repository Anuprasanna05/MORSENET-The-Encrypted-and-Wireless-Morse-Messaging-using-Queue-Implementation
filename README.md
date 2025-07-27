# MORSENET-The-Encrypted-and-Wireless-Morse-Messaging-using-Queue-Implementation


🔐 A secure, real-time Morse code communication system built on ESP32, using embedded C and Queue concepts for efficient messaging.

---

## 📖 Overview

**MORSENET** revives Morse code for modern use by combining embedded systems, encryption, and queue-based message handling. It enables wireless transmission of Morse-encoded messages between ESP32 boards over Wi-Fi using the UDP protocol. The system encrypts data using AES and decodes it on the receiver side for display on an I2C LCD.

---

## 🧠 Key Features (Implemented)

- Morse code input via push button (DOT / DASH).
- Message construction using queue logic (`enqueue`, `dequeue`).
- AES encryption on the transmitter side.
- UDP communication over Wi-Fi between ESP32 modules.
- AES decryption on the receiver side.
- Real-time decoded output on a 16x2 I2C LCD display.

---

## 🛠️ Tech Stack

- **Microcontroller**: ESP32-WROOM-32
- **Language**: Embedded C (Arduino IDE)
- **Communication**: Wi-Fi (UDP)
- **Encryption**: AES (using AESLib)
- **Display**: 16x2 I2C LCD
- **Data Structure**: Queue (manually implemented)

---

## 🔧 Setup Instructions

### ✅ Hardware Required

- 2× ESP32 Boards  
- 1× Push Button  
- 1× 16x2 I2C LCD Display  
- Jumper Wires, Breadboard, Power Supply

### 📦 Code Files

- `AES_TRANSMITTER1.ino` – Morse code input, AES encryption, and UDP transmission.
- `AES_RECEIVER.ino` – UDP reception, AES decryption, LCD display output.

### ⚙️ Upload Instructions

1. Open Arduino IDE.
2. Install the required libraries:
   - `AESLib.h`
   - `WiFi.h`
   - `Wire.h`
   - `LiquidCrystal_I2C.h`
3. Configure your **Wi-Fi SSID** and **password** in both files.
4. Upload `AES_TRANSMITTER1.ino` to the transmitter ESP32.
5. Upload `AES_RECEIVER.ino` to the receiver ESP32.
6. Power both boards and observe communication over serial monitor and LCD.

---

## 📸 Output Preview

- Transmitter: Serial monitor shows Morse code character conversion and AES-encrypted packets.
- Receiver: Decoded message is shown on I2C LCD after decryption.

---


