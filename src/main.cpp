#include <Arduino.h>

string ReceivedMessage;
int IRL_data;
int IRR_data;
int Gyro_1_data;
int Gyro_2_data;
int Gyro_3_data;

void setup() {
    Serial.begin(115200)
}

void loop() {
  if (Serial.available()) // Test if the buffer is empty
  {
    ReceivedMessage = Serial.read(); // Read buffer

    switch (ReceivedMessage) // Begin test on ReceivedMessage
    {
      case "IRL":
        IRL_data = measure_IRL();
        break;

      case "IRR":
        IRR_data = measure_IRR();
        break;

      case "Gyro_1":
        Gyro_1_data = measure_Gyro(1);
        break;

      case "Gyro_2":
        Gyro_2_data = measure_Gyro(2);
        break;

      case "Gyro_3":
        Gyro_3_data = measure_Gyro(3);
        break;

      default:
        break;
    }

  }
}


/***** MEASUREMENT FUNCTION *****/

/* Measure distance of left arm*/
int measure_IRL() {

}

/* Measure distance of right arm */
int measure_IRR() {

}

/* Measure the gyro */
int measure_Gyro(i) {

}
