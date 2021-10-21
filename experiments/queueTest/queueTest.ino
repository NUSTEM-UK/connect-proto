#include <Arduino.h>
#include "ArduinoQueue.h"

#define QUEUE_SIZE_ITEMS 250

typedef struct {
    String target;
    int param1;
    int param2;
} servoQueue;

ArduinoQueue<servoQueue> myServoQueue1(QUEUE_SIZE_ITEMS);
servoQueue myTempServoQueue;

void printQueueStats() {
  Serial.println("");
  Serial.printf("Size of each element:    %u bytes\r\n", myServoQueue1.item_size());
  Serial.printf("Items in queue now:      %u items\r\n", myServoQueue1.item_count());
  Serial.printf("Queue actual max items:  %u items\r\n",
                myServoQueue1.maxQueueSize());
  Serial.printf("Queue actual max memory: %u bytes\r\n",
                myServoQueue1.maxMemorySize());
  Serial.println("");
}

void setup() {
    Serial.begin(115200);
    Serial.println(">>> STARTING...");
    printQueueStats();


}

void loop() {

    // Add some elements
    // for (int i = 1 ; i < 5 ; i++) {
    //     if (!myServoQueue1.isFull())
    //     {
    //         Serial.println("Adding values");
    //         myTempServoQueue.target = "Test value";
    //         myTempServoQueue.param1 = 11;
    //         myTempServoQueue.param2 = 22;
    //         myServoQueue1.enqueue(myTempServoQueue);
    //     } else {
    //         Serial.println("Queue is full");
    //     }
    // }
    myTempServoQueue = {"Test Value A", 11, 22};
    myServoQueue1.enqueue(myTempServoQueue);
    myTempServoQueue = {"Test Value B", 33, 44};
    myServoQueue1.enqueue(myTempServoQueue);
    myTempServoQueue = {"Test Value C", 55, 66};
    myServoQueue1.enqueue(myTempServoQueue);
    myTempServoQueue = {"Test Value D", 77, 88};
    myServoQueue1.enqueue(myTempServoQueue);
    myTempServoQueue = {"Test Value E", 99, 255};
    myServoQueue1.enqueue(myTempServoQueue);


    printQueueStats();

    // Remove elements

    while (!myServoQueue1.isEmpty()) {
        servoQueue myTemp2 = myServoQueue1.dequeue();
        Serial.printf("Popped: ");
        Serial.print(myTemp2.target);
        Serial.printf(" %i %i\r\n", myTemp2.param1, myTemp2.param2);
    }

    // for (int i = 0; i < QUEUE_SIZE_ITEMS && !myServoQueue1.isEmpty(); i++)
    // {
    //     if (!myServoQueue1.isEmpty())
    //     {
    //         //... stuff goes here
    //     } else {
    //         Serial.println("Queue is empty!");
    //     }
    // }

    printQueueStats();

    while(true) {
        ESP.wdtFeed();
    }
}
