#include <Arduino.h>
#include "cppQueue.h"
#include <ESP8266WiFi.h>
// #include "functionheader.h"

#define IMPLEMENTATION FIFO
#define QUEUE_SIZE_ITEMS 10

typedef void (*GenericFP)(void *, ...);
// typedef void (*GenericFP)();

typedef struct {
    String targetDevice;
    GenericFP call;
    int queueVar1;
    float queueVar2;
    char * queueVar3;
    int startPos;
    int endPos;
    const char * animationType;
    float animationDuration;
} deviceQueueItem;


cppQueue servo1queue(sizeof(deviceQueueItem), QUEUE_SIZE_ITEMS, IMPLEMENTATION);

deviceQueueItem tempDeviceQueueItem;
deviceQueueItem myTemp2;

// Declare the queueable functions
// Variadic functions, we'll decode with va_args parsing within the function declarations
void myFunction1(void *skip, ...);
void myFunction2(void *skip, ...);
void myFunction3(void *skip, ...);
void myFunction4(void *skip, ...);

String TargetDevice;
String dummyString;

void setup() {
    // Disable wifi for testing so we're not spamming network message.
    WiFi.mode(WIFI_OFF);

    Serial.begin(115200);
    Serial.println(">>> STARTING functionQueueTest2");

    TargetDevice = "Servo1";
    dummyString = "";
    // Note that we can pass full data with null values...
    tempDeviceQueueItem = {TargetDevice, &myFunction1, 3, 0.0, "", 0, 0, "", 0.0};
    servo1queue.push(&tempDeviceQueueItem);
    Serial.println("Pushed first item");

    // ...or truncated data
    tempDeviceQueueItem = {"Cabbages", &myFunction2, 5, 3.444, ""};
    servo1queue.push(&tempDeviceQueueItem);
    Serial.println("Pushed second item");

    tempDeviceQueueItem = {"Turnips", &myFunction3, 7, 2.77, "Hello"};
    servo1queue.push(&tempDeviceQueueItem);
    Serial.println("Pushed third item");

    tempDeviceQueueItem = {"Carrots", &myFunction4, 1, 2.0, "World", 5, 175, "BOUNCE", 3.0};
    servo1queue.push(&tempDeviceQueueItem);
    Serial.println("Pushed fourth item");


    delay(1000);


    while (!servo1queue.isEmpty())
    {
        servo1queue.pop(&myTemp2);
        Serial.println(myTemp2.targetDevice); //This is a String type, not a char * []

        // In principle, could parse servo vs. LED queues and tidy up the
        // following function call slightly. Or pass to handler functions to
        // call onwards to library methods.

        // Call the function pointed to by .call, passing variables by key
        // (and let variadic function declarations handle the excess)
        myTemp2.call(NULL,
                     myTemp2.queueVar1,
                     myTemp2.queueVar2,
                     myTemp2.queueVar3,
                     myTemp2.startPos,
                     myTemp2.endPos,
                     myTemp2.animationType,
                     myTemp2.animationDuration);
        delay(500);
    }

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


void myFunction4(void * skip, ...)
{
    Serial.print("myFunction4 = ");
    va_list args;
    va_start(args, skip);
    int foo1 = va_arg(args, int);
    float foo2 = (float)va_arg(args, double);
    const char *foo3 = va_arg(args, const char *);
    int startPos = va_arg(args, int);
    int endPos = va_arg(args, int);
    const char *animationType = va_arg(args, const char *);
    // Implicit double, whatever the typedef says, cast to float
    float animationDuration = (float)va_arg(args, double);
    // We're done parsing arguments, so clean up the list
    va_end(args);


    Serial.print(foo1);
    Serial.print(", ");
    Serial.print(foo2);
    Serial.print(", ");
    Serial.print(foo3);
    Serial.print(", ");
    Serial.print(startPos);
    Serial.print(", ");
    Serial.print(endPos);
    Serial.print(", ");
    Serial.print(animationType);
    Serial.print(", ");
    Serial.println(animationDuration);

}
