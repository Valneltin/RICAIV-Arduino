#include <Arduino.h>

int ReceivedMessage = 0;


void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{

  if (Serial.available() == -1) // Test if the buffer is empty
  {

  }
  else
  {
    ReceivedMessage = Serial.read(); // Read buffer
    Serial.print("Message : ");
    Serial.println(ReceivedMessage);
  }
}
