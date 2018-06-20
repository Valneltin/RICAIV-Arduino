#include <Arduino.h>

String ReceivedMessage = "";
String LTValue = "";
String RTValue = "";
String ValeurH = "";

void setup() {
    Serial.begin(115200); //Begin serial link
}

void loop()
{
  ReceivedMessage = "";

  if (Serial.available()) // Test if the buffer is empty
  {
    ReceivedMessage = Serial.readString(); // Read buffer
    // Serial.print("Message : ["+ReceivedMessage+"]"); // Send received message to serial link

    if (ReceivedMessage.startsWith("JOY_")) // Test if is a joystick information
    {
      Serial.println("JOY_OK");
    }
    else if (ReceivedMessage.startsWith("LT_")) // Test if is a LT command
    {
      ReceivedMessage.replace("LT_", "");
      LTValue = ReceivedMessage;
      Serial.println("LT Value = ["+LTValue+"]");
    }
    else if (ReceivedMessage.startsWith("RT_")) // Test if is a RT command
    {
      ReceivedMessage.replace("RT_", "");
      RTValue = ReceivedMessage;
      Serial.println("RT Value = ["+RTValue+"]");
    }
    else // This information is not acceptable
    {
      Serial.println("Je ne comprends rien ^^");
    }
  }
}

void IR()
{

}
