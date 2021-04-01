#include <Arduino.h>

// This from https://forum.arduino.cc/index.php?topic=171069.0

// Function pointer prototype to a function which takes an 'int' and returns 'void'
typedef void (*GenericFP)(void *, ...);

void Page1(void *skip, ...);
void Page2(void *skip, ...);
void Page3(void *skip, ...);
// Create an array of 'GenericFP' function pointers. Note & operator
GenericFP MenuFP[3] = {&Page1, &Page2, &Page3};

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    MenuFP[0](NULL, 1);
    MenuFP[1](NULL, 5, 3.444);
    MenuFP[2](NULL, 7, 2.77, "Hello");

    delay(2000);
}

void Page1(void *skip, ...)
{
    va_list args;
    va_start(args, skip);
    int foo1 = va_arg(args, int);
    Serial.print("Page1 = ");
    Serial.println(foo1);
}

void Page2(void *skip, ...)
{
    va_list args;
    va_start(args, skip);
    int foo1 = va_arg(args, int);
    float foo2 = (float)va_arg(args, double);

    Serial.print("Page2 = ");
    Serial.print(foo1);
    Serial.print(", ");
    Serial.println(foo2);
}

void Page3(void *skip, ...)
{
    va_list args;
    va_start(args, skip);
    int foo1 = va_arg(args, int);
    float foo2 = (float)va_arg(args, double);
    const char *foo3 = va_arg(args, const char *);

    Serial.print("Page3 = ");
    Serial.print(foo1);
    Serial.print(", ");
    Serial.print(foo2);
    Serial.print(", ");
    Serial.println(foo3);
}
