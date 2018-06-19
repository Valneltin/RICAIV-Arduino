#include <Arduino.h>

String ReceivedMessage = "";

void setup() {
    Serial.begin(115200); //Begin serial link
}

void loop()
{

  if (Serial.available()) // Test if the buffer is empty
  {
    ReceivedMessage = Serial.readString(); // Read buffer
    Serial.print("Message : ["+ReceivedMessage+"]"); //Send received message to serial link
  }
}
