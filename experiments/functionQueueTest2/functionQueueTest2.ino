#include <Arduino.h>
#include "cppQueue.h"
#include "functionheader.h"

#define IMPLEMENTATION FIFO
#define QUEUE_SIZE_ITEMS 10


cppQueue servo1queue(sizeof(deviceQueueItem), QUEUE_SIZE_ITEMS, IMPLEMENTATION);

deviceQueueItem tempDeviceQueueItem;
deviceQueueItem myTemp2;

// Declare the queueable functions
void myFunction1(void *skip, ...);
void myFunction2(void *skip, ...);
void myFunction3(void *skip, ...);

String TargetDevice;
String dummyString;

void setup() {
    Serial.begin(115200);
    Serial.println(">>> STARTING functionQueueTest2");

    TargetDevice = "Servo1";
    dummyString = "";
    tempDeviceQueueItem = {TargetDevice, &myFunction1, 1, 0.0, ""};
    servo1queue.push(&tempDeviceQueueItem);
    Serial.println("Pushed first item");

    delay(2000);

    servo1queue.pop(&myTemp2);
    Serial.println(myTemp2.targetDevice);

}


void loop() {

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
