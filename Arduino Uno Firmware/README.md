# PianoLED Firmware (Arduino Uno R3)

Firmware for Arduino Uno R3 controlling WS2812b LED strips via MIDI. Tested on Arduino Uno R3 (Tahoe 26).

## Hardware
- LED Strip: WS2812b, 176 LEDs
- Data Pin: `#define DATA_PIN 5`
- Microcontroller: Arduino Uno R3
- Power: External 5V for LED strip

## Note Mapping
- Uses `noteMap[88]` to map MIDI keys 21–108 to LEDs


Focus this code :
<pre>

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

</pre>

## Serial & Baud Rate
- EEPROM stores last used baud code
- On first run, ensure Serial baud matches firmware default
- Changing baud updates EEPROM; firmware reads baud on startup

Focus this code :
<pre>
// DEBUG log
    //Serial.begin(9600); // Manual Picker Baud for first time
    /*
    Serial.print("DEBUG: EEPROM read baudCode=");
    Serial.println(baudCode);
    Serial.print("DEBUG: decoded baud=");
    Serial.println(decodedBaud);
    */ // Print and check at IDE/Tools/Serial Monitor
    Serial.begin(decodedBaud); // Sync Baud ( its not for first time )
</pre>

## Installation
1. Connect Arduino Uno R3 via USB and attach LED strip
2. Provide 5V power to LED strip
3. Upload `PianoLED.ino` via Arduino IDE
4. Play MIDI piano; LEDs will light according to keys

## Usage
- Adjust `noteMap[88]` for correct LED alignment
- Ensure baud rate matches EEPROM settings on first run
