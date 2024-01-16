#include "vex.h"
#include "main.h"
#include <cmath>

using namespace vex; 

void spinUp(bool spinIndex){ 
  if(spinIndex == true){
    intake.spin(forward,12,voltageUnits::volt);
  }

  if(spinIndex == false){
    intake.stop(brakeType::brake);
  }

  task::sleep(5);
}

void spinUpReverse(bool spinIndex){ 
  if(spinIndex == true){
    intake.spin(reverse,12,voltageUnits::volt);
  }

  if(spinIndex == false){
    intake.stop(brakeType::brake);
  }

  task::sleep(5);
}

void createTag(){
  Brain.Screen.clearLine(1, black);
  Brain.Screen.setFont(mono20);
  Brain.Screen.setCursor(1, 14);
}

//calibration of sensor 

void calib(){
  iner.calibrate();
  
  while(iner.isCalibrating()){
    createTag();
    Brain.Screen.print("Inertial is Calibrating...");
    task::sleep(20);

    if(iner.isCalibrating() == false){
    createTag();
    Brain.Screen.print("Inertial is Calibrated!");
    }
  }
}

int motorStats(){
  //temperature of the base 
  int avgTemp = (frontL.temperature() + middleL.temperature() + backL.temperature() + frontR.temperature() + middleR.temperature() + backR.temperature())/6;
  int tempC = avgTemp/2 + 20;
  return tempC; 
  /*Brain.Screen.setFont(mono20);
  Brain.Screen.setCursor(2,14);
  Brain.Screen.print("Average Temperature");
  Brain.Screen.setCursor(3,14);
  Brain.Screen.print(avgTemp);  */
  
  //power of the base 
}
