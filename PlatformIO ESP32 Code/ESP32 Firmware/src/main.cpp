#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"

//#include <Arduino.h>
#include "TOF.h"

#define BOARD_LED GPIO_NUM_13

uint32_t timeout_millis = 1000;

void test_task(void *arg0) {
    gpio_pad_select_gpio(BOARD_LED);
    gpio_set_direction(BOARD_LED, GPIO_MODE_OUTPUT);

    while (true) {
        gpio_set_level(BOARD_LED, 0);
        vTaskDelay(timeout_millis / portTICK_RATE_MS);
        gpio_set_level(BOARD_LED, 1);
        vTaskDelay(timeout_millis / portTICK_PERIOD_MS);
    }
}

void app_main() {
    xTaskCreate(&test_task, "test", 512, NULL, 5, NULL);
}

void setup(){}
void loop(){}



// // volatile int state = -1;

// // void task0() {
// //   for (int i = 1; i < 1000; i++) {
// //     sqrt(i * i);
// //   }
// // }

// // void task1() {
// //   for (int i = 0; i < 1000; i++) {
// //     delayMicroseconds(1);
// //   }
// // }


// // void core0Task(void * pvParameters) {
// //   while (true) {
// //     // unsigned long start = micros();
// //     // task0();
// //     // unsigned long delta = micros() - start;

// //     // Serial.print("Task 0 completed on Core ");
// //     // Serial.print(xPortGetCoreID());
// //     // Serial.print(" in ");
// //     // Serial.print(delta);
// //     // Serial.println("us");
// //     //state = 0;
// //     //Serial.println(state);
// //     vTaskDelay(10/portTICK_PERIOD_MS);
// //   }
  
// // }

// // void core1Task(void * pvParameters) {
// //   while (true) {
// //     // unsigned long start = micros();
// //     // task1();
// //     // unsigned long delta = micros() - start;
// //     // Serial.print("Task 1 completed on Core ");
// //     // Serial.print(xPortGetCoreID());
// //     // Serial.print(" in ");
// //     // Serial.print(delta);
// //     // Serial.println("us");
// //     //state = 1;
// //     //Serial.println(state);
// //     vTaskDelay(10/portTICK_PERIOD_MS);
    
// //   }
  
// // }


// // hw_timer_t* timer = NULL;
// // portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// // uint32_t coreNum[500];
// // volatile int count = 0;
// // volatile bool ready = false;

// // void IRAM_ATTR onTimer() {
// //   if (count < 500) {
// //     coreNum[count] = xPortGetCoreID(); 
// //     count++;
// //   } else {
// //     portENTER_CRITICAL_ISR(&timerMux);
// //     ready = true;
// //     portEXIT_CRITICAL_ISR(&timerMux);
// //     count = 0;
// //   }

// // }

// // void setup() {
// //   Serial.begin(112500);
// //   delay(1000);

// //   // xTaskCreatePinnedToCore(
// //   //                   core0Task,   /* Function to implement the task */
// //   //                   "core0Task", /* Name of the task */
// //   //                   10000,      /* Stack size in words */
// //   //                   NULL,       /* Task input parameter */
// //   //                   3,          /* Priority of the task */
// //   //                   NULL,       /* Task handle. */
// //   //                   0);  /* Core where the task should run */

// //   // xTaskCreatePinnedToCore(
// //   //                   core1Task,   /* Function to implement the task */
// //   //                   "core1Task", /* Name of the task */
// //   //                   10000,      /* Stack size in words */
// //   //                   NULL,       /* Task input parameter */
// //   //                   2,          /* Priority of the task */
// //   //                   NULL,       /* Task handle. */
// //   //                   1);  /* Core where the task should run */
// //   timer = timerBegin(0, 80, true);
// //   timerAttachInterrupt(timer, &onTimer, true);
// //   timerAlarmWrite(timer, 1000000, true);
// //   timerAlarmEnable(timer);
// // }

// // void loop() {
// //   if (ready) {
// //     for (int i = 0; i < 500; i++) {
// //       Serial.print(coreNum[i]);
// //     }
// //     portENTER_CRITICAL(&timerMux);
// //     ready = false;
// //     portEXIT_CRITICAL(&timerMux);
// //   }
// // }


// volatile uint32_t coreNum[500];
// volatile int interruptCounter;
// int totalInterruptCounter;
// volatile int Coreindex = 0;


// hw_timer_t * timer = NULL;
// portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
 
// void IRAM_ATTR onTimer() {
//   portENTER_CRITICAL_ISR(&timerMux);
//   interruptCounter++;
//   if (Coreindex < 500) coreNum[Coreindex++] = xPortGetCoreID();
//   portEXIT_CRITICAL_ISR(&timerMux);
 
// }
 
// void setup() {
 
//   Serial.begin(115200);
 
//   // timer = timerBegin(0, 80, true);
//   // timerAttachInterrupt(timer, &onTimer, true);
//   // timerAlarmWrite(timer, 10000, true);
//   // timerAlarmEnable(timer);
 
// }
 
// void loop() {
//   Serial.println(portTICK_PERIOD_MS);
//   Serial.println(configTICK_RATE_HZ);
//   Serial.println(CONFIG_FREERTOS_HZ);
//   delay(2000);
//   // if (interruptCounter > 0) {
 
//   //   portENTER_CRITICAL(&timerMux);
//   //   interruptCounter--;
//   //   portEXIT_CRITICAL(&timerMux);
//   //   Serial.print('.');
//   //   if (Coreindex >= 499) {
//   //     for (int i = 0; i < 500; i++) {
//   //       Serial.print(coreNum[i]);
//   //     }
//   //     Coreindex = 0;
//   //     Serial.println("\n\n");
//   //   }
//   // }
// }