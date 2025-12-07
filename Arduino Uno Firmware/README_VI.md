# PianoLED Firmware (Arduino Uno R3)

Firmware cho Arduino Uno R3 điều khiển LED strip WS2812b qua MIDI. Đã thử nghiệm trên Arduino Uno R3 (Tahoe 26).

## Phần cứng
- LED Strip: WS2812b, 176 LED
- Data Pin: `#define DATA_PIN 5`
- Vi điều khiển: Arduino Uno R3
- Nguồn: Dùng nguồn ngoài 5V cho LED strip

## Ánh xạ nốt nhạc
- Sử dụng `noteMap[88]` để ánh xạ các phím MIDI 21–108 sang LED

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

## Serial & Tốc độ Baud
- EEPROM lưu mã baud cuối cùng sử dụng
- Lần đầu chạy, đảm bảo tốc độ Serial khớp firmware mặc định
- Thay đổi baud sẽ cập nhật EEPROM; firmware đọc baud khi khởi động

Focus this code :
<pre>
// DEBUG log
    //Serial.begin(9600); // Baud Manual Picker lần đầu
    /*
    Serial.print("DEBUG: EEPROM read baudCode=");
    Serial.println(baudCode);
    Serial.print("DEBUG: decoded baud=");
    Serial.println(decodedBaud);
    */ // In ra và kiểm tra trên IDE/Tools/Serial Monitor
    Serial.begin(decodedBaud); // Đồng bộ Baud (không phải lần đầu)
</pre>

## Cài đặt
1. Kết nối Arduino Uno R3 qua USB và gắn LED strip
2. Cung cấp nguồn 5V cho LED strip
3. Nạp `PianoLED.ino` qua Arduino IDE
4. Chơi piano MIDI; LED sẽ sáng theo phím

## Sử dụng
- Điều chỉnh `noteMap[88]` để ánh xạ LED đúng
- Đảm bảo tốc độ baud khớp EEPROM khi chạy lần đầu
