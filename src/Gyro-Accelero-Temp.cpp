#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

char report[80];

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();

  compass.m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
  compass.m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};
}

void loop() 
{
  compass.read();

  float heading = compass.heading((LSM303 :: vector <int>) {0, -1, 0});
  
  Serial.println(heading);

  snprintf(report, sizeof(report), "Acceleration X :%6d,    Acceleration Y :%6d,    Acceleration Z :%6d",(compass.a.x/232), (compass.a.y/232), abs((compass.a.z/1600)));
  Serial.println(report);
  
  delay(800);
}