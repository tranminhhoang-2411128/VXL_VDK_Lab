# **CO3010 - Vi xử lý - Vi điều khiển - HK261**
Tổng quan về nội dung của từng thư mục

## Lab 1-LED Animations
### Exercise 1,2
Mô phỏng đèn giao thông  
Mã nguồn có sẵn trong Report Lab 1
#### Schematic
Chân PA4, PA5, PA6 điều khiển 3 đèn LED: Đỏ, Vàng, Xanh

### Exercise 3,4,5
Nâng cấp thành đèn giao thông cho ngã tư, tích hợp thêm LED 7 đoạn
#### Source
Mã nguồn để chạy Exercise 5
#### Schematic
Hướng Bắc-Nam: chân PA4-PA6 điều khiển đèn, chân PB0-PB6 điều khiển LED 7 đoạn  
Hướng Đông-Tây: chân PA7-PA9 điều khiển đèn, chân PB7-PB13 điều khiển LED 7 đoạn

### Exercise 6-10
Mô phỏng Analog Clock
#### Source
Mã nguồn để chạy Exercise 10
#### Schematic
Chân PA4-PA15 điều khiển LED tượng trưng cho hướng 1-12h

---

## Lab 2-Timer Interrupt and LED Scanning
### Source
main.c: Mã nguồn để chạy Exercise 8, Exercise 10  
software_timer.c: quản lý các ngắt sử dụng software timer
### Schematic
Digital clock gồm 4 LED 7 đoạn scan với tần số 1Hz  
LED Matrix hiển thị chữ A di chuyển hướng lên trên, chu kỳ 8s
