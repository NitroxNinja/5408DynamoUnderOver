
#include "vex.h"
#include "main.h"

using namespace vex;

competition Competition;

int autonomousSelection = -1;

typedef struct _button {
    int    xpos;
    int    ypos;
    int    width;
    int    height;
    bool   state;
    vex::color offColor;
    vex::color onColor;
    const char *label;
} button;

button buttons[] = {
    {   25,  30, 70, 70,  false, 0x404040, 0x40826d , "5 Ball"},
    {  145,  30, 70, 70,  false, 0x404040, 0x40826d ,"AWP" },
    {  265,  30, 70, 70,  false, 0x404040, 0xE00000, "BallCornerLeft" },
    {  385,  30, 70, 70,  false, 0x404040, 0xE34234, "Skills" },
    {   25, 140, 70, 70,  false, 0x404040, 0x0000E0, "Blue 1" },
    {  145, 140, 70, 70,  false, 0x404040, 0x0000E0, "Blue 2" },
    {  265, 140, 70, 70,  false, 0x404040, 0x0000E0, "Blue 3" },
    {  385, 140, 70, 70,  false, 0x404040, 0XDC9E43 , "Simple" }
};

void displayButtonControls( int index, bool pressed );

int findButton(  int16_t xpos, int16_t ypos ) {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &buttons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);
}

/*-----------------------------------------------------------------------------*/
/** @brief      Init button states                                             */
/*-----------------------------------------------------------------------------*/
void initButtons() {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      buttons[index].state = false;
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been touched                                        */
/*-----------------------------------------------------------------------------*/
void userTouchCallbackPressed() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton( xpos, ypos )) >= 0 ) {
      displayButtonControls( index, true );
    }

}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been (un)touched                                    */
/*-----------------------------------------------------------------------------*/
void userTouchCallbackReleased() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton( xpos, ypos )) >= 0 ) {
      // clear all buttons to false, ie. unselected
      //      initButtons(); 

      // now set this one as true
      if( buttons[index].state == true) {
      buttons[index].state = false; }
      else    {
      buttons[index].state = true;}

      // save as auton selection
      autonomousSelection = index;

      displayButtonControls( index, false );
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Draw all buttons                                               */
/*-----------------------------------------------------------------------------*/
void displayButtonControls( int index, bool pressed ) {
    vex::color c;
    Brain.Screen.setPenColor( vex::color(0xe0e0e0) );

    for(int i=0;i<sizeof(buttons)/sizeof(button);i++) {

      if( buttons[i].state )
        c = buttons[i].onColor;
      else
        c = buttons[i].offColor;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c );
      }
      else
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height );

      // outline
      Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, vex::color::transparent );

// draw label  
      if(  buttons[i].label != NULL )
        Brain.Screen.printAt( buttons[i].xpos + 8, buttons[i].ypos + buttons[i].height - 8, buttons[i].label );
    }
}

double speedCap = 1; 
double speedCapTurn = 1;

double kP = 0.118; //.13
double kI = 0.0; //integral control causes the robot to jitter
double kD = 0.27; //0.5
double turnkP = 0.285;//0.14
double turnkI = 0.0; //integral control causes the robot to jitter
double turnkD = 0.34;//0.0015; 0.44
 
float dV = 0;
int dTV = 0;
 
int error; //sensor-desired value positional value
int prevError = 0; //error 20 milliseconds ago
int derivative;
int totalError = 0; //what in the world is this
 
int turnError; //sensor-desired value positional value
int turnPrevError = 0; //error 20 milliseconds ago
int turnDerivative;
int turnTotalError = 0; //what in the world is this
 
bool resetDriveSensors = false;
bool enablePID = false;
 
int drivePID()
{
 
 while(enablePID)
 {
 
   if(resetDriveSensors)
   { 
     frontL.setPosition(0,degrees);
     frontR.setPosition(0,degrees);
  
     iner.setRotation(0,degrees);
     resetDriveSensors = false; //this is a bool, once the sensors have been reset, it will return as "true"
   }
  
   int inertialPosition = iner.rotation(degrees);

   int averagePosition = (frontL.position(degrees) + frontR.position(degrees)) / 2;

   error = averagePosition - ((360 * dV) * 1.05); 
 
   derivative = error - prevError; 

   totalError += error;  
 
   double lateralMotorPower = ((error * kP + derivative * kD + totalError * kI) / 12 );
  
   int turnDifference = inertialPosition; 
   
   turnError = turnDifference - dTV;
 
   turnDerivative = turnError - turnPrevError; 
 
   turnTotalError += turnError; 
 
   double turnMotorPower = (turnError * turnkP + turnDerivative * turnkD + turnTotalError * turnkI) / 2 ;
 
   frontL.spin(reverse , (lateralMotorPower * speedCap) + (turnMotorPower * speedCapTurn) , voltageUnits::volt);
   middleL.spin(reverse , (lateralMotorPower * speedCap) + (turnMotorPower * speedCapTurn) , voltageUnits::volt);
   backL.spin(reverse , (lateralMotorPower * speedCap) + (turnMotorPower * speedCapTurn) , voltageUnits::volt);   
   frontR.spin(reverse , (lateralMotorPower * speedCap) - (turnMotorPower * speedCapTurn) , voltageUnits::volt);
   middleR.spin(reverse , (lateralMotorPower * speedCap) - (turnMotorPower * speedCapTurn) , voltageUnits::volt);
   backR.spin(reverse , (lateralMotorPower * speedCap) - (turnMotorPower * speedCapTurn) , voltageUnits::volt);

   prevError = error;
   turnPrevError = turnError;
 
   vex::task::sleep(25);
 }
 return 1; 
}





void pre_auton(void) {
  calib();
  vexcodeInit();

 
}


void autonomous(void) {
  vex::task bill(drivePID);
  enablePID = true; 
  resetDriveSensors = true; 

  int Red1   = buttons[0].state; //auton selector 
  int Red2   = buttons[1].state;
  int Red3   = buttons[2].state;
  int Skills = buttons[3].state;
  int Blue1  = buttons[4].state;
  int Blue2  = buttons[5].state;
  int Simple = buttons[7].state;
  int Blue3  = buttons[6].state;

  if(Red1){
    //utilizing heading control, avoid using "resetDriveSensors"
    
    kP = 0.124;
    //while going forward open the wings to release preload, additionally intake is spinning
    spinUp(true);
    wings.open();
    task::sleep(400);
    dV = 5.2;
    dTV = -48;
    wings.close(); 
    task::sleep(1600);
    spinUp(false);

    kP = 0.118;
    //turn right to align with goal, swipe to avoid touching middle pipe 
    dV = 5.0; 
    dTV = 90; 
    task::sleep(800);

    //reverse the intakes while pushing both balls into the goal 
    spinUpReverse(true);
    wings.open();
    dV = 7.5;
    dTV = 90;
    task::sleep(1000);
    spinUpReverse(false);
    wings.close();
    
    //reverse a bit
    kP = 0.124;
    dV = 5;
    dTV = 90;
    task::sleep(700);

    //turn right to get the 2nd ball 
    kP = 0.119;
    dV = 5;
    dTV = 225;
    task::sleep(800);

    //intakes the 2nd ball 
    spinUp(true);
    dV = 6.8; 
    dTV = 225; 
    task::sleep(1100);

    //back out get ready for alignment for match load bar to push ball out w/Wings
    //the robot should be perpindicular to the middle pipe 
    dV = 3.7;
    dTV = 225;
    task::sleep(1300);
    spinUp(false);
    resetDriveSensors = true;

    
    
    dV = 1; //this is the problem child 
    dTV = -135;
    task::sleep(700);

    spinUpReverse(true);
    dV = 3;
    dTV = -135;
    task::sleep(700);

    dV = 1;
    dTV = -135;
    task::sleep(700);

    dV = 1;
    dTV = -235;
    task::sleep(900);
    resetDriveSensors = true;

    dV = -5.3; //hit the wall for alignment 
    dTV = 0;
    task::sleep(1500);
    resetDriveSensors = true;


    //speedCapTurn = 0.8;
    dV = 0; 
    dTV = 77;
    task::sleep(800);

    speedCap = 1;
    wings.open();
    dV = 2.8;
    dTV = 77;
    task::sleep(700);

    speedCap = 1;
    dV = 4.55;
    dTV = 0;
    task::sleep(800);

    
    wings.close();
    kP = 0.8;
    dV = 4.1;
    dTV = 0;
    task::sleep(300);
    
    dV = 6.5;
    dTV = 20;
    task::sleep(1000);
    //LOL 
    

/*
    dV = 2;
    dTV = -135;
    task::sleep(1000);


    dV = 3.3;
    dTV = 90;
    task::sleep(1500);
    */
   
    
    //hit the wall 
    /*dV = -1;
    dTV = 90;
    task::sleep(700);
    resetDriveSensors = true;

    wings.open();
    spinUpReverse(true);
    dV = 6; 
    dTV = 30;
    task::sleep(2000);
    
    dV = 8;
    dTV = 90;
    task::sleep(2000);
    wings.close();
    resetDriveSensors = true;

    spinUpReverse(false);

    dV = 2;
    dTV = 0;
    task::sleep(1000);

*/

    

    


  }
  if(Red2)
  {
    //AWP 
    spinUp(true);
    wings.open();
    speedCap = 0.2;
    speedCapTurn = 0.5;
    dV = 1.5;
    dTV = 30;
    task::sleep(3000);
  }

  if(Red3){
    spinUp(true);
    wings.open();

    dV = 2;
    dTV = 50;
    task::sleep(3000);

    dV = 2.2;
    dTV = 50;
    task::sleep(1000);
    wings.close();

    dV = -6;
    dTV = 0;
    task::sleep(2000);
    resetDriveSensors = true;
    
    dV = 0.1;
    dTV = 90;
    task::sleep(2000);
  
    dV = 1.37;

  }

  if(Blue1){}
  if(Blue2){}
  if(Blue3){}

  if(Skills)
  {
    spinUp(true);
    task::sleep(50);
    spinUp(false);


    spinUpReverse(true);
    kP = 0.9;
    dV = 2;
    dTV = 0;
    task::sleep(900);

    kP = 0.118;
    dV = -0.1;
    dTV = 0;
    task::sleep(1000);

    dV = -2;
    dTV = 85;
    task::sleep(1000);

    dV = -2.08;
    dTV = 85;
    task::sleep(400);



    /*int stupidSkills = 0;
    do
    {
      cata.spin(forward, 100, percent);
    
    if(ballDetector.value(analogUnits::mV) <= 2700)
    {
      cata.spin(forward,100,percent);
      //stupidSkills++;

    }
    else if (cataLimit.pressing())
    {
      task::sleep(40);
      cata.stop(brakeType::brake);
      
    }
    
    }
    while(stupidSkills < 10000);

    cata.stop(brakeType::brake);*/
    task::sleep(1000);

    cata.spin(forward, 70, percent);
    task::sleep(55000);
    cata.stop(brakeType::coast);

    dV = 6;
    dTV = 110;
    task::sleep(2000);
    
    dV = 12;
    dTV = 90;
    task::sleep(3000);

    wings.open();
    dV = 15;
    dTV = 20;
    task::sleep(2000);

    wings.close();
    dV = 13;
    dTV = -20;
    task::sleep(2000);

    wings.open();
    dV = 14;
    dTV = 75;
    task::sleep(2000);

    dV = 11;
    dTV = 30;
    task::sleep(2000);

    dV = 17;
    dTV = 60;
    task::sleep(2000);



    /*

    do

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
    */
    
    
  }
  if(Simple)
  {
    speedCap = 0.6;
    //(true);
    dV = 4;
    dTV = 0;
    task::sleep(3000);

    speedCap = 1;
    dV = 3;
    dTV = 0;
    task::sleep(2000);
     

    dV = 4.1;
    dTV = 0;
    task::sleep(3000);
  }

}


void usercontrol(void) {
  enablePID = false;
  while (1) {
    joystickCont();
    intakeCont();
    cataCont();
    autoCata();
  
    wingsCont();
    //assistUp();
    autoLift();
    
    wait(10, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  Brain.Screen.pressed(userTouchCallbackPressed);
  Brain.Screen.released(userTouchCallbackReleased);
  displayButtonControls(0, false);
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();
  Brain.Screen.setFont(mono20);
  Brain.Screen.setCursor(2,14);
  Brain.Screen.print("Base Temperature(C):");
  Brain.Screen.setCursor(2,37);

  // Prevent main from exiting with an infinite loop.
  while (true) {
  
    
    Brain.Screen.print(motorStats());

    wait(100, msec);
  }
}
