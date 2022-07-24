#include <Arduino_FreeRTOS.h>
#include <Wire.h>
#include <semphr.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20,4);

#define pinSensor1 5
#define pinSensor2 6
#define pinSensor3 7
int a=0;
int b=0;
int c=0;
SemaphoreHandle_t xSerialSemaphore;

void BacaSensor1(void *pvParameters);
void BacaSensor2(void *pvParameters);
void BacaSensor3(void *pvParameters);
void Menampilkan(void *pvParameters);

void setup(){
  Serial.begin(9600);
  if(xSerialSemaphore == NULL){
       xSerialSemaphore = xSemaphoreCreateMutex();
        if((xSerialSemaphore)!= NULL)
            xSemaphoreGive((xSerialSemaphore));
  }
  lcd.init();
  lcd.backlight();
  lcd.begin(20,4);
  while (!Serial) {
    ;
  }
 
 // Now set up two Tasks to run independently.
  xTaskCreate(
    BacaSensor1
    ,  "BacaSensor1"          // A name just for humans
    ,  128                    // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL                   // Parameters for the task
    ,  3                      // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );                // Task Handle

  xTaskCreate(
    BacaSensor2
    ,  "BacaSensor2"          // A name just for humans
    ,  128                    // Stack size
    ,  NULL                   // Parameters for the task
    ,  2                      // Priority
    ,  NULL );                // Task Handle
   xTaskCreate(
    BacaSensor3
    ,  "BacaSensor3"          // A name just for humans
    ,  128                    // Stack size
    ,  NULL                   // Parameters for the task
    ,  1                      // Priority
    ,  NULL );                // Task Handle
  xTaskCreate(
    Menampilkan
    ,  "Menampilkan"          // A name just for humans
    ,  128                    // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL                   // Parameters for the task
    ,  0                      // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );                // Task Handle

  // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.
}

void loop(){
}

void BacaSensor1( void *pvParameters __attribute__((unused)) ){
  pinMode(pinSensor1, INPUT);
  
  for (;;){
    int sensorValue1 = digitalRead(5);
      //Serial.print("Sensor 1 : ");
      //Serial.println(sensorValue1);
        if(sensorValue1==0){
          a++;
        } 
    vTaskDelay(45/portTICK_PERIOD_MS); 
  }
}

void BacaSensor2( void *pvParameters __attribute__((unused)) ){
  pinMode(pinSensor2, INPUT);
  
  for (;;){
    int sensorValue2 = digitalRead(6);
      //Serial.print("Sensor 2 : ");
      //Serial.println(sensorValue2);
         if(sensorValue2==0){
          b++;
        }
    vTaskDelay(50/portTICK_PERIOD_MS);  
  }
}

void BacaSensor3( void *pvParameters __attribute__((unused)) ){
  pinMode(pinSensor3, INPUT);

  for (;;){
    int sensorValue3 = digitalRead(7);
      //Serial.print("Sensor 3 : ");
      //Serial.println(sensorValue3);
       if(sensorValue3==0){
          c++;
        }
     
    vTaskDelay(55/portTICK_PERIOD_MS);  
  }
}

void Menampilkan( void *pvParameters __attribute__((unused)) ){
 int d=0;
  for (;;){
      lcd.setCursor(0,0);
      lcd.print("Sensor 1 : ");
      lcd.println(a);
      lcd.setCursor(0,1);
      lcd.print("Sensor 2 : ");
      lcd.println(b);
      lcd.setCursor(0,2);
      lcd.print("Sensor 3 : ");
      lcd.println(c);
      d=a+b+c;
      lcd.setCursor(0,3);
      lcd.print("Total Benih : ");
      lcd.println(d);
      Serial.print("Total Benih : ");
      Serial.println(d);
    vTaskDelay(50/portTICK_PERIOD_MS); 
  }
}
