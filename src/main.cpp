#include <Arduino.h>

String ReceivedMessage = "";
String LTValue = "";
String RTValue = "";
String ValeurH = "";

int pinPR=A0; //pin de connexion pour la photor�sistance

float valeurtension;
float valeurcm;

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
    else if (ReceivedMessage.startsWith("Sensor"))
    {
      Serial.println("J'envoie les mesures");
    }
    else // This information is not acceptable
    {
      Serial.println("Je ne comprends rien ^^");
    }
  }
}

void IR(){
  int valeur=analogRead(pinPR); // on lit la valeur transmise par la photor�sistance
  valeurtension = valeur*4.97/1023;
  //valeurcm = 4.4405*pow(valeurtension,-1.385); // calcul moins pr�cis mais plus simple. observ� fiable.
  valeurcm = -1.48*pow(valeurtension,5) + 14.233*pow(valeurtension,4) - 53.985*pow(valeurtension,3) + 100.94*pow(valeurtension,2) - 95.813*valeurtension + 41.05;

  //valeurcm = -1*exp(-11*pow(valeurtension,5)) + 2*exp(-8*pow(valeurtension,4)) - 1*exp(-5*pow(valeurtension,3)) + 0.0031*pow(valeurtension,2) - 0.5072*valeurtension + 40.99; //formule sens�e am�liorer encore la pr�cision, non test�e.
  Serial.println(valeurtension); // on l'affiche
  Serial.println(valeurcm); // on l'affiche
  Serial.println("  ");

  delay(300); // wait for 0.3 second
}
