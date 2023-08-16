#include <microDS3231.h>
MicroDS3231 rtc;

int PIN_LED = 13;

uint8_t minute;
uint8_t hour;
uint8_t second;

bool status_led = false;

void setup() {
  
//  rtc.setTime(COMPILE_TIME);
  
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);
  
  // проверка наличия модуля на линии i2c
  if (!rtc.begin()) {
    Serial.println("DS3231 not found");
    for(;;);
  }
  if (rtc.lostPower()) {            // выполнится при сбросе батарейки
    Serial.println("Батарея не найдена");
   
  }

  
}

void loop() {
  
  updateTime();
  print_time();
  // Указывам премя включения и сколько по времяни она должна быть запущена
  
  turn_on_for_time(21, 8, 0, 0, 1);  // пример квлючится в 23 часа 9 минут 0 сек, и будет работать 0 часов, 1 минута.
  turn_on_for_time(21, 16, 0, 0, 1);
  turn_on_for_time(21, 20, 0, 0, 1);
  turn_on_for_time(21, 30, 0, 0, 1);
  
  
  delay(500);
}

void turn_on_for_time(uint8_t _hour, uint8_t _minute, uint8_t _second, uint8_t duration_hour, uint8_t duration_minute){
  /*
  Включить на определенное количество времени
  Во сколько влючиить
  uint8_t _hour 
  uint8_t _minute
  uint8_t _second
  через сколько часов и минут отключить
  uint8_t duration_hour
  uint8_t duration_minute
  */
  if (time_check(_hour, _minute, _second))
    on_led();
  
  if (time_check(_hour+duration_hour, _minute+duration_minute, _second))
    off_led();
}

void on_led(){
  //включаем ленту
  if (status_led==false){
//     Serial.println("on_led");
     digitalWrite(PIN_LED, LOW);
     status_led = true;
    }

}

void off_led(){
  //Выключаем ленту
  if (status_led==true){
//    Serial.println("off_led");
    digitalWrite(PIN_LED, HIGH);
    status_led = false;
  }
}

bool time_check(uint8_t _hour, uint8_t _minute, uint8_t _second){
  // Проверка времяни
  if ((hour >= _hour) && (minute>=_minute) && (second>=_second))
    return true;
  else
    return false;
}

void updateTime(){
  //Обновляем время
  hour = rtc.getHours();
  minute = rtc.getMinutes();
  second = rtc.getSeconds();
}

void print_time(){
  // Отображения времени
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.print(second);
  Serial.print(" status_led:");
  Serial.println(status_led);
}
