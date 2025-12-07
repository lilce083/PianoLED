# PianoLED

PianoLED là một dự án kết hợp hiển thị LED strip với piano, cho phép các hiệu ứng ánh sáng chạy theo thời gian thực dựa trên dữ liệu MIDI. Dự án này đã được thử nghiệm trên Arduino Uno R3 (Tahoe 26).

# Tính năng
- LED phản hồi theo thời gian thực với các nốt MIDI
- Hỗ trợ nhiều chế độ LED thông qua ứng dụng đi kèm:
  - Chế độ chọn màu thủ công – chọn màu LED theo ý muốn
  - Chế độ màu ngẫu nhiên – LED hiển thị màu tự động
  - Điều chỉnh độ sáng – thay đổi cường độ sáng LED
  - Chế độ học – hiển thị nốt khi học piano
  - Quản lý file MIDI – quản lý các file MIDI cho chế độ học
  - Đồng bộ Baudrate – cấu hình tốc độ giao tiếp giữa Arduino và ứng dụng

# Phần cứng
- LED Strip: WS2812b (144 LED/mét) hoặc các LED strip có thể địa chỉ hóa tương tự
- Vi điều khiển: Arduino Uno R3 (đã thử nghiệm)
- Nguồn: Khuyến nghị dùng nguồn ngoài 5V cho LED strip
- MIDI Input: MIDI chuẩn từ piano hoặc controller

# Phần mềm
- Arduino IDE để nạp firmware
- Ứng dụng đi kèm với các chế độ trên để điều khiển LED

# Cài đặt
1. Kết nối:
   - Kết nối Arduino Uno R3 với máy Mac qua cổng USB
   - Kết nối LED strip với Arduino Uno R3 bằng 2 dây jumper (Gnd, data_pin 5) (hình 1)
   - Kết nối LED strip với nguồn 5V ngoài
2. Nạp sketch `PianoLED.ino` vào Arduino
3. Chạy ứng dụng, cấu hình các cài đặt (baud rate, thiết bị MIDI, cổng Serial), nhấn nút kết nối, chọn chế độ và điều khiển LED (hình 2)
4. Chơi thiết bị MIDI của bạn và quan sát LED sáng theo nốt nhạc

# Hình ảnh

1. ![1](images/unor3.jpg)
2. ![2](images/UIApp.png)

# Cách sử dụng
- Cấu hình ánh xạ LED trong code (`PianoLED.ino`)
- Chọn chế độ ứng dụng (Manual Picker, Random Colors, Learning, v.v.)
- Điều chỉnh độ sáng và các cài đặt khác

# Đóng góp
Chào đón mọi đóng góp! Hãy mở issue hoặc gửi pull request để cải thiện dự án.

# Giấy phép
Dự án này được cấp phép theo MIT License. Xem file LICENSE để biết chi tiết.
