#include <Arduino.h>
#include "ArduinoQueue.h"

#define QUEUE_SIZE_ITEMS 10

// Give ourselves a GenericFP type
// with malleable passed values
typedef void (*GenericFP)(void *, ...);

// Now give ourselves a queue object type
typedef struct {
    String targetDevice;
    GenericFP call;
} deviceQueueItem;

ArduinoQueue<deviceQueueItem> servo1Queue(QUEUE_SIZE_ITEMS);
// ArduinoQueue<deviceQueueItem> servo2Queue(QUEUE_SIZE_ITEMS);
// ArduinoQueue<deviceQueueItem> pixelQueue(QUEUE_SIZE_ITEMS);
deviceQueueItem tempDeviceQueueItem;

// Declare the queueable functions
void myFunction1(void *skip, ...);
void myFunction2(void *skip, ...);
void myFunction3(void *skip, ...);

String targetDevice;

void printQueueStats(ArduinoQueue<deviceQueueItem> thisQueue) {
    Serial.println("");
    Serial.printf("Size of each element:    %u bytes\r\n", thisQueue.item_size());
    Serial.printf("Items in queue now:      %u items\r\n", thisQueue.item_count());
    Serial.printf("Queue actual max items:  %u items\r\n",
                    thisQueue.maxQueueSize());
    Serial.printf("Queue actual max memory: %u bytes\r\n",
                    thisQueue.maxMemorySize());
    Serial.println("");
}

void setup() {
    Serial.begin(115200);
    Serial.println(">>> STARTING functionQueueTest");
    printQueueStats(servo1Queue);

    // This line validates (trying to debug queue population, below)
    tempDeviceQueueItem = {"This", &myFunction1};


    // populate the queue
    targetDevice = "Servo1";
    tempDeviceQueueItem = {targetDevice, myFunction1(NULL, 1) };
    servo1Queue.enqueue(tempDeviceQueueItem);
    tempDeviceQueueItem = {targetDevice, myFunction2(NULL, 5, 3.444)};
    servo1Queue.enqueue(tempDeviceQueueItem);
    tempDeviceQueueItem = {targetDevice, myFunction3(NULL, 7, 2.77, "Hello")};
    servo1Queue.enqueue(tempDeviceQueueItem);

    printQueueStats(servo1Queue);

    for (int i = 0; i < QUEUE_SIZE_ITEMS; i++)
    {
        if (!servo1Queue.isEmpty())
        {
            deviceQueueItem myTemp2 = servo1Queue.dequeue();
            Serial.printf("Popped: ");
            Serial.print(myTemp2.targetDevice);
            // Serial.print(myTemp2.call);
        } else {
            Serial.println("Queue is empty!");
        }

    }

}

void loop() {
    // We're just going to pop the elements off the queue


}


void myFunction1(void *skip, ...)
{
    va_list args;
    va_start(args, skip);
    int foo1 = va_arg(args, int);
    Serial.print("myFunction1 = ");
    Serial.println(foo1);
}

void myFunction2(void *skip, ...)
{
    va_list args;
    va_start(args, skip);
    int foo1 = va_arg(args, int);
    float foo2 = (float)va_arg(args, double);

    Serial.print("myFunction2 = ");
    Serial.print(foo1);
    Serial.print(", ");
    Serial.println(foo2);
}

void myFunction3(void *skip, ...)
{
    va_list args;
    va_start(args, skip);
    int foo1 = va_arg(args, int);
    float foo2 = (float)va_arg(args, double);
    const char *foo3 = va_arg(args, const char *);

    Serial.print("myFunction3 = ");
    Serial.print(foo1);
    Serial.print(", ");
    Serial.print(foo2);
    Serial.print(", ");
    Serial.println(foo3);
}
