#include <Arduino.h>

/***  VARIABLES ***/

String ReceivedMessage = "";
char buffer[]= "";

int leftarmforward;
int leftarmbackward;
int rightarmbackward;
int rightarmforward;
int leftshoulderforward;
int leftshoulderbackward;
int rightshoulderforward;
int rightshoulderbackward;
int leftmotorspeed;
int rightmotorseed;

/*** MOTORS VARIABLES ***/

// Left Motor
int pwmLM = 2;
int dirLM = 22;
int duty_cycle_LM = 0;
// Right Motor
int pwmRM = 3;
int dirRM = 23;
int duty_cycle_RM = 0;

// Left Schoulder
int pwmLS = 4;
int dirLS = 24;
int speedforwardLS = 255;
int speedbackwardLS = 1;
// Right Schoulder
int pwmRS = 5;
int dirRS = 24;
int speedforwardRS = 255;
int speedbackwardRS = 1;

// Left Arm
int pwmLA = 6;
int dirLA = 25;
int speedforwardLA = 255;
int speedbackwardLA = 1;
// Right Arm
int pwmRA = 7;
int dirRA = 26;
int speedforwardRA = 255;
int speedbackwardRA = 1;


/*___________ SET UP ___________*/
void setup() {
    Serial.begin(115200); // Begin serial link

    pinMode(pwmLM, OUTPUT);
    pinMode(dirLM, OUTPUT);

    pinMode(pwmRM, OUTPUT);
    pinMode(dirRM, OUTPUT);

    pinMode(pwmLS, OUTPUT);
    pinMode(dirLS, OUTPUT);

    pinMode(pwmRS, OUTPUT);
    pinMode(dirRS, OUTPUT);

    pinMode(pwmLA, OUTPUT);
    pinMode(dirLA, OUTPUT);

    pinMode(pwmRA, OUTPUT);
    pinMode(dirRA, OUTPUT);
}


/*___________ SUB FUNCTION ___________*/
/*** Calcul the duty cycle from value of potentiometer's value ***/
int dutyCycleCalcul(int speed){
  int value = map(speed, 0, 200, 0, 255);
  return value;
}

/*** Set value of speed for motors in function of duty cycle ***/
void motor(int pinpwm, int pindir, int duty_cycle ){
  if (duty_cycle <128) // Motor go backward
  {
    boolean dirvalue = LOW;           // Set direction value of motor
    duty_cycle = 2*128-duty_cycle;    // Calculate PWM duty cycle to go backward
    digitalWrite(pindir, dirvalue);   // Direction
    analogWrite(pinpwm, duty_cycle);  // Speed
  }
  else if (duty_cycle>=128) // Motor go forward
  {
    boolean dirvalue = HIGH;          // Set direction value of motor
    digitalWrite(pindir, dirvalue);   // Direction
    analogWrite(pinpwm, duty_cycle);  // Speed
  }

}


/*___________ MAIN CODE ___________*/
void loop()
{

  ReceivedMessage = ""; // Reset ReceivedMessage

  if (Serial.available()) // Test if the buffer is empty
  {

    ReceivedMessage = Serial.readString();            // Read buffer
    Serial.print("Message : ["+ReceivedMessage+"]");  // Send received message to serial link

    ReceivedMessage.toCharArray(buffer,30); // Convert String to Char
    sscanf(buffer, "%d %d %d %d %d %d %d %d %d %d", &leftarmforward, &leftarmbackward, &rightarmforward, &rightarmbackward, &leftshoulderforward, &leftshoulderbackward, &rightshoulderforward, &rightshoulderbackward, &leftmotorspeed, &rightmotorseed);

    /*** CONTROL LEFT ARM ***/
    if (leftarmforward == 1 && leftarmbackward == 0){       // Left arm go forward
      motor(pwmLA, dirLA, speedforwardLA);
      Serial.print("LA : FORWARD");
    }
    else if (leftarmforward == 0 && leftarmbackward == 1){  // Left arm go backward
      motor(pwmLA, dirLA, speedbackwardLA);
      Serial.print("LA : BACKWARD");
    }
    else if (leftarmforward == 0 && leftarmbackward == 0){  // Left arm don't move
      motor(pwmLA, dirLA, 128);
      Serial.print("LA : STOP 1");
    }
    else if (leftarmforward == 1 && leftarmbackward == 1){  // Left arm don't move because two buttons are pressed
      motor(pwmLA, dirLA, 128);
      Serial.print("LA : STOP 2");
    }

    /*** CONTROL RIGHT ARM ***/
    if (rightarmforward == 1 && rightarmbackward == 0){       // Right arm go forward
      motor(pwmRA, dirRA, speedforwardRA);
      Serial.print("RA : FORWARD");
    }
    else if (rightarmforward == 0 && rightarmbackward == 1){  // Right arm go backward
      motor(pwmRA, dirRA, speedbackwardRA);
      Serial.print("RA : BACKWARD");
    }
    else if (rightarmforward == 0 && rightarmbackward == 0){  // RIght arm don't move
      motor(pwmRA, dirRA, 128);
      Serial.print("RA : STOP 1");
    }
    else if (rightarmforward == 1 && rightarmbackward == 1){  // Right arm don't move because two buttons are pressed
      motor(pwmRA, dirRA, 128);
      Serial.print("RA : STOP 2");
    }

    /*** CONTROL LEFT SHOULDER ***/
    if (leftshoulderforward == 1 && leftshoulderbackward == 0){       // Left shoulder go forward
      motor(pwmLS, dirLS, speedforwardLS);
      Serial.print("LS : FORWARD");
    }
    else if (leftshoulderforward == 0 && leftshoulderbackward == 1){  // Left shoulder go backward
      motor(pwmLS, dirLS, speedbackwardLS);
      Serial.print("LS : BACKWARD");
    }
    else if (leftshoulderforward == 0 && leftshoulderbackward == 0){  // Left shoulder don't move
      motor(pwmLS, dirLS, 128);
      Serial.print("LS : STOP 1");
    }
    else if (leftshoulderforward == 1 && leftshoulderbackward == 1){  // Left shoulder don't move because two buttons are pressed
      motor(pwmLS, dirLS, 128);
      Serial.print("LS : STOP 2");
    }

    /*** CONTROL RIGHT SHOULDER ***/
    if (rightshoulderforward == 1 && rightshoulderbackward == 0){       // Right shoulder go forward
      motor(pwmRS, dirRS, speedforwardRS);
      Serial.print("RS : FORWARD");
    }
    else if (rightshoulderforward == 0 && rightshoulderbackward == 1){  // Right shoulder go backward
      motor(pwmRS, dirRS, speedbackwardRS);
      Serial.print("RS : BACKWARD");
    }
    else if (rightshoulderforward == 0 && rightshoulderbackward == 0){  // Right shoulder don't move
      motor(pwmRS, dirRS, 128);
      Serial.print("RS : STOP 1");
    }
    else if (rightshoulderforward == 1 && rightshoulderbackward == 1){  // Right shoulder don't move because two buttons are pressed
      motor(pwmRS, dirRS, 128);
      Serial.print("RS : STOP 2");
    }

    /*** WHEEL MOTOR ***/
    duty_cycle_LM = dutyCycleCalcul(leftmotorspeed);  // Calcul duty cycle for left motor
    duty_cycle_RM = dutyCycleCalcul(rightmotorseed);  // Calcul duty cycle for right motor
    motor(pwmLM, dirLM, duty_cycle_LM);               // Set speed to left motor
    motor(pwmRM, dirRM, duty_cycle_RM);               // Set speed to right motor

  }
}

/*void IR(){
  int valeur=analogRead(pinPR); // on lit la valeur transmise par la photor�sistance
  valeurtension = valeur*4.97/1023;
  //valeurcm = 4.4405*pow(valeurtension,-1.385); // calcul moins pr�cis mais plus simple. observ� fiable.
  valeurcm = -1.48*pow(valeurtension,5) + 14.233*pow(valeurtension,4) - 53.985*pow(valeurtension,3) + 100.94*pow(valeurtension,2) - 95.813*valeurtension + 41.05;

  //valeurcm = -1*exp(-11*pow(valeurtension,5)) + 2*exp(-8*pow(valeurtension,4)) - 1*exp(-5*pow(valeurtension,3)) + 0.0031*pow(valeurtension,2) - 0.5072*valeurtension + 40.99; //formule sens�e am�liorer encore la pr�cision, non test�e.
  Serial.println(valeurtension); // on l'affiche
  Serial.println(valeurcm); // on l'affiche
  Serial.println("  ");

  delay(300); // wait for 0.3 second
}*/
