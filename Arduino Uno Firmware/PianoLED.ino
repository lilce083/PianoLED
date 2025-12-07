#include <FastLED.h>
#include <EEPROM.h>
#include <avr/wdt.h>

#define NUM_LEDS 176
#define DATA_PIN 5

uint8_t baudCode = 2;
CRGB leds[NUM_LEDS];

// --------- Note mapping ---------
struct NoteMap {
  uint8_t idx, count;
};
NoteMap noteMap[88] = {
  { 174, 3 }, { 172, 2 }, { 170, 2 }, { 167, 3 }, { 166, 1 }, { 163, 3 }, { 162, 1 }, { 160, 2 }, 
  { 157, 3 }, { 156, 1 }, { 153, 3 }, { 152, 1 }, { 150, 2 }, { 148, 2 }, { 146, 2 }, { 144, 2 }, 
  { 143, 1 }, { 140, 3 }, { 139, 1 }, { 136, 3 }, { 134, 2 }, { 133, 1 }, { 130, 3 }, { 129, 1 }, 
  { 126, 3 }, { 125, 1 }, { 123, 2 }, { 120, 3 }, { 119, 1 }, { 116, 3 }, { 115, 1 }, { 112, 3 }, 
  { 110, 2 }, { 109, 1 }, { 106, 3 }, { 105, 1 }, { 102, 3 }, { 101, 1 }, { 99, 2 }, { 96, 3 }, 
  { 95, 1 }, { 92, 3 }, { 91, 1 }, { 89, 2 }, { 86, 3 }, { 85, 1 }, { 82, 3 }, { 81, 1 }, 
  { 79, 2 }, { 77, 2 }, { 75, 2 }, { 73, 2 }, { 72, 1 }, { 69, 3 }, { 68, 1 }, { 65, 3 }, 
  { 63, 2 }, { 62, 1 }, { 59, 3 }, { 58, 1 }, { 55, 3 }, { 54, 1 }, { 52, 2 }, { 49, 3 }, 
  { 48, 1 }, { 45, 3 }, { 44, 1 }, { 41, 3 }, { 39, 2 }, { 38, 1 }, { 35, 3 }, { 34, 1 }, 
  { 31, 3 }, { 30, 1 }, { 28, 2 }, { 25, 3 }, { 24, 1 }, { 21, 3 }, { 20, 1 }, { 18, 2 }, 
  { 15, 3 }, { 14, 1 }, { 12, 2 }, { 10, 2 }, { 8, 2 }, { 6, 2 }, { 4, 2 }, { 2, 2 }
};

// --------- Global state ---------
bool learningMode = false;
bool randomMode = false;
uint8_t brightnessVal = 200;
CRGB currentColor = CRGB::Cyan;
//Baud
int newBaud;
// Giải mã baudCode → baud thực
uint32_t decodeBaud(uint8_t code) {
  switch (code) {
    case 0: return 9600;
    case 1: return 19200;
    case 2: return 28800;
    case 3: return 38400;
    case 4: return 57600;
    case 5: return 115200;
    case 6: return 230400;
    default: return 115200;
  }
}
// Track blue notes for green/red logic
bool isBlue[88] = { false };  // 21..108
uint8_t fifoKB[32];
int kbCount = 0;
// --------- Helpers ---------
void setNoteColor(uint8_t note, const CRGB &c) {
  if (note < 21 || note > 108) return;
  NoteMap m = noteMap[note - 21];
  int start = m.idx - 1;
  for (uint8_t i = 0; i < m.count; ++i) {
    int idx = start + i;
    if (idx >= 0 && idx < NUM_LEDS) leds[idx] = c;
  }
}
void setManualColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB(r, g, b);
  FastLED.show();
}
// --------- Setup ---------
void setup() {
    // Đọc baudCode từ EEPROM
    uint8_t baudCode = EEPROM.read(0);
    if (baudCode == 0xFF) baudCode = 5; // default 115200
    uint32_t decodedBaud = decodeBaud(baudCode);

    // DEBUG log
    //Serial.begin(9600);
    /*
    Serial.print("DEBUG: EEPROM read baudCode=");
    Serial.println(baudCode);
    Serial.print("DEBUG: decoded baud=");
    Serial.println(decodedBaud);
    */
    // Bắt đầu Serial với baud cuối cùng
    Serial.begin(decodedBaud);
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(brightnessVal);
    FastLED.clear();
    FastLED.show();

    delay(50);
    Serial.write('R'); // báo app UNO sẵn sàng
}




// --------- Loop ---------
void loop() {
  while (Serial.available()) {
    uint8_t b = Serial.read();

    // 1) Learning packet [240 ... 240]
    if (b == 240) {
      while (Serial.available() < 4) delay(1);
      uint8_t mode = Serial.read();
      Serial.read();
      Serial.read();
      uint8_t end = Serial.read();
      if (end == 240) {
        learningMode = (mode == 1);
        FastLED.clear();
        FastLED.show();
        Serial.write('N');  // ACK Learning Mode
      }
      continue;
    }

    // 2) MIDI NOTE immediate [241, note] → bật blue LED liền
    if (b == 241) {
      while (Serial.available() == 0) delay(1);
      uint8_t note = Serial.read();
      uint8_t idx = note - 21;
      isBlue[idx] = true;  // mark blue
      setNoteColor(note, CRGB::Blue);
      FastLED.show();
      Serial.write('L');  // ACK MIDI Note
      continue;
    }

    // 3) Manual color [250,R,G,B,250]
    // 0) Manual Color packet [250, R, G, B, 250]
    if (b == 250) {
      while (Serial.available() < 4) delay(1);

      uint8_t r = Serial.read();
      uint8_t g = Serial.read();
      uint8_t b2 = Serial.read();
      uint8_t end = Serial.read();

      if (end == 250) {
        currentColor = CRGB(r, g, b2);
        FastLED.show();
        Serial.write('N');  // ACK for normal mode
      }
      continue;
    }

    // 4) Random mode ON/OFF [251]/[252]
    if (b == 251) {
      randomMode = true;
      Serial.write('N');

      continue;
    }
    if (b == 252) {
      randomMode = false;
      Serial.write('N');

      continue;
    }
    // 5) Brightness packet [253, level, 253]
    if (b == 253) {
      while (Serial.available() < 2) delay(1);  // đợi đủ level + end byte
      uint8_t level = Serial.read();
      uint8_t end = Serial.read();
      if (end == 253) {  // kiểm tra byte kết thúc
        brightnessVal = level;
        FastLED.setBrightness(brightnessVal);
        FastLED.show();
        Serial.write('N');  // ACK brightness
      }
      continue;
    }
    // 7) Clear LED [254, 254]
    if (b == 254) {
      while (Serial.available() == 0) delay(1);
      uint8_t end = Serial.read();
      if (end == 254) {
        FastLED.clear();
        FastLED.show();
        Serial.write('C');  // ACK Normal
      }
      continue;
    }
    // --- Baud rate change packet [255, newBaudCode, 255] ---
    if (b == 255) {
      while (Serial.available() < 2) delay(1); // đợi đủ 2 byte
      uint8_t newBaudCode = Serial.read();
      uint8_t end = Serial.read();
      if (end == 255) {
        EEPROM.update(0, newBaudCode); // lưu vào EEPROM
        Serial.write('B'); // ACK lại cho app
        //Serial.println(F("DEBUG: BaudCode updated, UNO will reset"));
        delay(50);
        wdt_enable(WDTO_15MS); // watchdog reset UNO
        while (true) {} // đợi reset
      }
      return;
    }

    // 6) KEYBOARD 2-byte [144/128 note]
    if (b == 144 || b == 128) {
      fifoKB[kbCount++] = b;
      while (Serial.available() == 0) delay(1);
      fifoKB[kbCount++] = Serial.read();

      if (kbCount >= 2) {
        uint8_t status = fifoKB[0];
        uint8_t note = fifoKB[1];
        uint8_t idx = note - 21;

        if (!learningMode) {
          // NORMAL MODE
          if (status == 144) {
            CRGB col = randomMode ? CRGB(CHSV(random(0, 255), 255, 255)) : currentColor;
            setNoteColor(note, col);
          } else {
            setNoteColor(note, CRGB::Black);
          }
          FastLED.show();
          Serial.write('N');  // ACK Normal Mode
          kbCount = 0;
          continue;
        }

        // LEARNING MODE
        if (status == 144) {
          CRGB col = isBlue[idx] ? CRGB::Green : CRGB::Red;
          setNoteColor(note, col);
          //Serial.write('K');  // ACK Learning Mode Keyboard
        } else {
          setNoteColor(note, CRGB::Black);
          isBlue[idx] = false;
          //Serial.write('M');  // ACK Learning Mode Keyboard
        }
        FastLED.show();
        Serial.write('L');  // ACK Learning Mode Keyboard
        kbCount = 0;
      }
      continue;
    }
  }
}