#include <Arduino.h>
#include <MD_TCS230.h>
#include "button.h"

#define  S0_OUT  2
#define  S1_OUT  3
#define  S2_OUT  4
#define  S3_OUT  5

#define R_OUT 6
#define G_OUT 7
#define B_OUT 8

#define BUTTON_R 10
#define BUTTON_G 11
#define BUTTON_B 12

MD_TCS230 colorSensor(S2_OUT, S3_OUT, S0_OUT, S1_OUT);

Button buttonR(BUTTON_R);
Button buttonG(BUTTON_G);
Button buttonB(BUTTON_B);

double stateR = false;
double stateG = false;
double stateB = false;

void setup()
{
    Serial.begin(115200);
    Serial.println("Started!");

    sensorData whiteCalibration;
    whiteCalibration.value[TCS230_RGB_R] = 111060;
    whiteCalibration.value[TCS230_RGB_G] = 105240;
    whiteCalibration.value[TCS230_RGB_B] = 130580;

    sensorData blackCalibration;
    blackCalibration.value[TCS230_RGB_R] = 9540;
    blackCalibration.value[TCS230_RGB_G] = 9190;
    blackCalibration.value[TCS230_RGB_B] = 11870;

    colorSensor.begin();
    colorSensor.setDarkCal(&blackCalibration);
    colorSensor.setWhiteCal(&whiteCalibration);

    pinMode(R_OUT, OUTPUT);
    pinMode(G_OUT, OUTPUT);
    pinMode(B_OUT, OUTPUT);
}

void loop() 
{
    colorData rgb;
    colorSensor.read();

    while (!colorSensor.available());

    colorSensor.getRGB(&rgb);
    set_rgb_led(rgb);
    print_rgb(rgb);
}

void print_rgb(colorData rgb)
{
    Serial.print(rgb.value[TCS230_RGB_R]);
    Serial.print(" ");
    Serial.print(rgb.value[TCS230_RGB_G]);
    Serial.print(" ");
    Serial.print(rgb.value[TCS230_RGB_B]);
    Serial.println();
}



void check_buttons()
{
  if(buttonR.wasPressed())
  {
    if(stateR == false)
    {
      stateR = true;
    }
    else
    {
      stateR = false;
    }
  }
  if(buttonG.wasPressed())
  {
    if(stateG == false)
    {
      stateG = true;
    }
    else
    {
      stateG = false;
    }
  }
  if(buttonB.wasPressed())
  {
    if(stateB == false)
    {
      stateB = true;
    }
    else
    {
      stateB = false;
    }
  }
  return;
}

void set_rgb_led(colorData rgb)
{
    check_buttons();

    if(stateR == true)
    {
        analogWrite(R_OUT, 255 - rgb.value[TCS230_RGB_R]);
    }
    else
    {
       analogWrite(R_OUT, 255);
    }

    if(stateG == true)
    {
        analogWrite(G_OUT, 255 - rgb.value[TCS230_RGB_G]);
    }
    else
    {
       analogWrite(G_OUT, 255);
    }

    if(stateB == true)
    {
        analogWrite(B_OUT, 255 - rgb.value[TCS230_RGB_B]);
    }
    else
    {
       analogWrite(B_OUT, 255);
    }
    
}
