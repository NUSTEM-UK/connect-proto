/*  This doesn't work.
    BUT
    it does give me a start. I _think_:
    - I don't need the generic function pointers component.
    - I'm going to have to pass all the variables in the queue objects,
      and do some instruction decoding, because I can't store a full
      call in the queue.
    Picking up the pieces in functionQueueTest2
    2021-04-16
    Update an hour later:
    That went nowhere, since I ended up writing the same code.
    This crashes when I try to dequeue, with an apparent memory error.
    Try the cppQueue library instead?
    - So that's what I'm going to do in the functionQueueTest2.ino sketch.
*/

#include <Arduino.h>
#include "ArduinoQueue.h"
#include "functionheader.h"

#define QUEUE_SIZE_ITEMS 10

// Give ourselves a GenericFP type
// with malleable passed values
// Moved to a separate header file, to see if that helps at all. It doesn't.
// typedef void (*GenericFP)(void *, ...);

// Now give ourselves a queue object type
// typedef struct {
//     String targetDevice;
//     GenericFP call;
//     int queueVar1;
//     float queueVar2;
//     String queueVar3;
// } deviceQueueItem;

ArduinoQueue<deviceQueueItem> servo1Queue(QUEUE_SIZE_ITEMS);

deviceQueueItem tempDeviceQueueItem;
deviceQueueItem myTemp2;

// Declare the queueable functions
void myFunction1(void *skip, ...);
void myFunction2(void *skip, ...);
void myFunction3(void *skip, ...);

String targetDevice;
String dummyString;

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
    // tempDeviceQueueItem = {"This", myFunction1};

    // populate the queue
    targetDevice = "Servo1";
    dummyString ="";
    tempDeviceQueueItem = {targetDevice, &myFunction1, 1, 0.0, "" };
    servo1Queue.enqueue(tempDeviceQueueItem);
    Serial.println("Enqueued first item");
    // tempDeviceQueueItem = {targetDevice, &myFunction2, 5, 3.444};
    // servo1Queue.enqueue(tempDeviceQueueItem);
    // Serial.println("Enqueued second item");
    // tempDeviceQueueItem = {targetDevice, &myFunction3, 7, 2.77, "Hello"};
    // servo1Queue.enqueue(tempDeviceQueueItem);
    // Serial.println("Enqueued third item");

    printQueueStats(servo1Queue);

    delay(3000);

}

void loop() {
    // We're just going to pop the elements off the queue

    for (int i = 0; i < QUEUE_SIZE_ITEMS; i++)
    {
        if (!servo1Queue.isEmpty())
        {
            Serial.println("Queue has a thing");
            deviceQueueItem myTemp = servo1Queue.dequeue();
            Serial.println("Popped the thing");
            Serial.print("Popped: ");
            Serial.println(myTemp.targetDevice);
            // Serial.print(myTemp2.call);
        } else {
            Serial.println("Queue is empty!");
        }

    }

    delay(1000);
    Serial.println("Made it through the loop");


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
