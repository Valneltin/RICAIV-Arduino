#include <Arduino.h>
#include <Wire.h>

/*___________ VARIABLES ___________*/

String ReceivedMessage;
char buffer [25];

int leftarmforward;
int leftarmbackward;
int rightarmbackward;
int rightarmforward;
int leftshoulderforward;
int leftshoulderbackward;
int rightshoulderforward;
int rightshoulderbackward;
int leftmotorspeed;
int rightmotorspeed;

/*** MOTORS VARIABLES ***/

// Left Motor
int pwmLM = 2;
int dirLM = 22;
// Right Motor
int pwmRM = 3;
int dirRM = 23;

// Left Schoulder
int pwmLS = 4;
int dirLS = 24;
int speedforwardLS = 1000;
int speedbackwardLS = -1000;
// Right Schoulder
int pwmRS = 5;
int dirRS = 25;
int speedforwardRS = 1000;
int speedbackwardRS = -1000;

// Left Arm
int pwmLA = 6;
int dirLA = 26;
int speedforwardLA = 1000;
int speedbackwardLA = -1000;
// Right Arm
int pwmRA = 7;
int dirRA = 27;
int speedforwardRA = 1000;
int speedbackwardRA = -1000;

/*** SENSORS VARIABLES ***/

int stateFC[4]={1,1,1,1};

int pinFC1 = A0;
int powerFC1 = 30;
int stateFC1 = 0;

int pinFC2 = A1;
int powerFC2 = 31;
int stateFC2 = 0;

int pinFC3 = A2;
int powerFC3 = 32;
int stateFC3 = 0;

int pinFC4 = A3;
int powerFC4 = 33;
int stateFC4 = 0;

/*___________ SET UP ___________*/
void setup() {

    Serial.begin(9600); // Begin serial link
    Wire.begin();       // Begin wire link
    //compass.init();
    //compass.enableDefault();

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

    pinMode(powerFC1,OUTPUT);
    pinMode(powerFC2,OUTPUT);
    pinMode(powerFC3,OUTPUT);
    pinMode(powerFC4,OUTPUT);
}


/*___________ SUB FUNCTION ___________*/

// SET MOTOR SPEED AND DIRECTION
void motor(int pinpwm, int pindir, int speed)
{
  if (speed < 0){
    digitalWrite(pindir, LOW);
    speed = -speed;
    speed = map(speed, 0, 1000, 0, 255);
    analogWrite(pinpwm, speed);
  }
  else if (speed >= 0){
    digitalWrite(pindir, HIGH);
    speed = map(speed, 0, 1000, 0, 255);
    analogWrite(pinpwm, speed);
  }
}

/*___________ MAIN CODE ___________*/
void loop()
{
  // ARM SENSORS
  stateFC1 = analogRead(pinFC1);
  stateFC2 = analogRead(pinFC2);
  stateFC3 = analogRead(pinFC3);
  stateFC4 = analogRead(pinFC4);

  // Only to have 1 or 0 to limit sensor
  if (stateFC1 < 200)
  {
    stateFC1=0;
  }
  else
  {
    stateFC1=1;
  }

  if (stateFC2 < 200)
  {
    stateFC2=0;
  }
  else
  {
    stateFC2=1;
  }

  if (stateFC3 < 200)
  {
    stateFC3=0;
  }
  else
  {
    stateFC3=1;
  }

  if (stateFC4 < 200)
  {
    stateFC4=0;
  }
  else
  {
    stateFC4=1;
  }

  // READ SERIAL
  if (Serial.available()) // Test if the buffer is empty
  {
    ReceivedMessage = Serial.readStringUntil('e'); // Read serial port until character "e"

    Serial.println(String(stateFC1)+" "+String(stateFC2)+" "+String(stateFC3)+" "+String(stateFC4)+" 111 222 333 444 555 e"); // Send values sensors

    ReceivedMessage.toCharArray(buffer, ReceivedMessage.length()); // Convert ReceivedMessage in char array
    sscanf(buffer, "%d%d%d%d%d%d%d%d%d%d e", &leftarmforward, &leftarmbackward, &rightarmforward, &rightarmbackward, &leftshoulderforward, &leftshoulderbackward, &rightshoulderforward, &rightshoulderbackward, &leftmotorspeed, &rightmotorspeed);

    // CONTROL LEFT ARM
    if (leftarmforward == 1 && leftarmbackward == 0){       // Left arm go forward
      if(stateFC1 == 0) // Impossible to go forward because limit sensor is pressed
      {
        motor(pwmLA, dirLA, 0); //Stop arm to go forward
      }
      else
      {
        motor(pwmLA, dirLA, speedforwardLA); // Go forward
      }
    }
    else if (leftarmforward == 0 && leftarmbackward == 1){  // Left arm go backward
      if (stateFC2 == 0) // Impossible to go backward because limit sensor is pressed
      {
        motor(pwmLA, dirLA, 0); // Stop arm to go backward
      }
      else
      {
        motor(pwmLA, dirLA, speedbackwardLA); // Go backward
      }
    }
    else if (leftarmforward == 0 && leftarmbackward == 0){  // Left arm don't move
      motor(pwmLA, dirLA, 0);
    }
    else if (leftarmforward == 1 && leftarmbackward == 1){  // Left arm don't move because two buttons are pressed
      motor(pwmLA, dirLA, 0);
    }

    // CONTROL RIGHT ARM
    if (rightarmforward == 1 && rightarmbackward == 0){       // Right arm go forward
      if (stateFC3 == 0) // Impossible to go forward because limit sensor is pressed
      {
        motor(pwmRA, dirRA, 0); // Stop arm to go forward
      }
      else
      {
        motor(pwmRA, dirRA, speedforwardRA); // Go forward
      }
    }
    else if (rightarmforward == 0 && rightarmbackward == 1){  // Right arm go backward
      if (stateFC4 == 0) // Impossible to go backward because limit sensor is pressed
      {
        motor(pwmRA, dirRA, 0); // Stop arm to go backward
      }
      else
      {
        motor(pwmRA, dirRA, speedbackwardRA); // Go backward
      }
    }
    else if (rightarmforward == 0 && rightarmbackward == 0){  // RIght arm don't move
      motor(pwmRA, dirRA, 0);
    }
    else if (rightarmforward == 1 && rightarmbackward == 1){  // Right arm don't move because two buttons are pressed
      motor(pwmRA, dirRA, 0);
    }

    // CONTROL LEFT SHOULDER
    if (leftshoulderforward == 1 && leftshoulderbackward == 0){       // Left shoulder go forward
      motor(pwmLS, dirLS, speedforwardLS);
    }
    else if (leftshoulderforward == 0 && leftshoulderbackward == 1){  // Left shoulder go backward
      motor(pwmLS, dirLS, speedbackwardLS);
    }
    else if (leftshoulderforward == 0 && leftshoulderbackward == 0){  // Left shoulder don't move
      motor(pwmLS, dirLS, 0);
    }
    else if (leftshoulderforward == 1 && leftshoulderbackward == 1){  // Left shoulder don't move because two buttons are pressed
      motor(pwmLS, dirLS, 0);
    }

    //CONTROL RIGHT SHOULDER
    if (rightshoulderforward == 1 && rightshoulderbackward == 0){       // Right shoulder go forward
      motor(pwmRS, dirRS, speedforwardRS);
    }
    else if (rightshoulderforward == 0 && rightshoulderbackward == 1){  // Right shoulder go backward
      motor(pwmRS, dirRS, speedbackwardRS);
    }
    else if (rightshoulderforward == 0 && rightshoulderbackward == 0){  // Right shoulder don't move
      motor(pwmRS, dirRS, 0);
    }
    else if (rightshoulderforward == 1 && rightshoulderbackward == 1){  // Right shoulder don't move because two buttons are pressed
      motor(pwmRS, dirRS, 0);
    }

    // WHEEL MOTOR
    motor(pwmLM, dirLM, leftmotorspeed);  // Set speed to left motor
    motor(pwmRM, dirRM, rightmotorspeed); // Set speed to right motor
  }

  else // Reset value of speed if not receive value from serial port
  {
    leftarmforward = 0;
    leftarmbackward = 0;
    rightarmbackward = 0;
    rightarmforward = 0;
    leftshoulderforward = 0;
    leftshoulderbackward = 0;
    rightshoulderforward = 0;
    rightshoulderbackward = 0;
    leftmotorspeed = 0;
    rightmotorspeed = 0;

    ReceivedMessage = ""; // Reset ReceivedMessage

    for(int j=0;j<20;j++) // Reset buffer
    {
      buffer [j] = 0;
    }
  }
}
