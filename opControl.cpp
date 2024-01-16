#include "main.h"
#include "vex.h"
#include <cmath>

void joystickCont()
{
   int X,Y;
 
  if(abs(Controller1.Axis2.value())>9)
    Y = Controller1.Axis2.value() * 0.11;
    
  else
    Y = 0;
   
  if(abs(Controller1.Axis1.value()) >9)
    X = Controller1.Axis1.value() * 0.095 ;  

  else
  X = 0;

  frontL.spin(forward,(X + Y), volt);
  middleL.spin(forward,(X + Y),volt);
  backL.spin(forward,(X + Y), volt);
  frontR.spin(forward,(Y - X), volt);
  middleR.spin(forward,(Y - X), volt);
  backR.spin(forward,(Y - X), volt);  

  frontL.setStopping(brakeType::hold);
  middleL.setStopping(brakeType::hold);
  backL.setStopping(brakeType::hold);
  frontR.setStopping(brakeType::hold);
  middleR.setStopping(brakeType::hold);
  backR.setStopping(brakeType::hold);
}

void intakeCont()
{
  if(Controller1.ButtonR1.pressing())
    intake.spin(forward,100,percent);
  else if(Controller1.ButtonR2.pressing())
    intake.spin(reverse,100,percent);
  else
    intake.stop(brakeType::coast);
}

void cataCont()
{
  //manual shooting 
  if(Controller1.ButtonL1.pressing())
    cata.spin(forward,100,percent);
  else
    cata.stop(brakeType::brake   );

  //automatic shooting
  /*
    if(Controller1.ButtonL2.pressing())
  {
    cata.spin(forward, 100, percent);
    if(cataLimit.pressing())
    {
      //task::sleep(40);
      cata.stop(brakeType::brake);
    }
    if(ballDetector.value(analogUnits::mV) <= 1700)
    {
      cata.spin(forward,100,percent);

    }
  }
  */
}

bool autoToggle = false;
bool autoLatch = false;

void autoCata()
{
if(Controller1.ButtonL2.pressing())
   {

    if(!autoLatch)
    {
    autoToggle = !autoToggle;
    autoLatch = true;
    }

    }
  else {
  autoLatch = false;
  //wings.close();
  }

  if(autoToggle)
  {
    //wings.open();
    cata.spin(forward, 100, percent);
    if(cataLimit.pressing())
    {
      //task::sleep(40);
      cata.stop(brakeType::brake);
    }
    if(ballDetector.value(analogUnits::mV) <= 2700)
    {
      cata.spin(forward,100,percent);

    }
  }
}

bool wingToggle = false;
bool wingLatch = false;

void wingsCont()
{
if(Controller1.ButtonLeft.pressing())
   {

    if(!wingLatch)
    {
    wingToggle = !wingToggle;
    wingLatch = true;
    }

    }
  else {
  wingLatch = false;
  wings.close();
  }

  if(wingToggle)
  {
    wings.open();
  }
}



bool liftToggle = false;
bool liftLatch = false;

void autoLift()
{
if(Controller1.ButtonX.pressing())
   {

    if(!liftLatch)
    {
    liftToggle = !liftToggle;
    liftLatch = true;
    }

    }
  else {
  liftLatch = false;
  //pullUp.close();
  //assist.close();

  pullUp.close();
    assist.close();
  }

  if(liftToggle)
  {
    pullUp.open();
  assist.open();
  }
}









/*
bool clampToggle = false;
bool latch = false;

void mogoClampControl()
{
   if(Controller1.ButtonLeft.pressing())
   {

    if(!latch)
    {
    clampToggle = !clampToggle;
    latch = true;
    }

    }
  else {
  latch = false;
  clamp.open();
  }

  if(clampToggle)
  {
    clamp.close();
  }
}

*/
