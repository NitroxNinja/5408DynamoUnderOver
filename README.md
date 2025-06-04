# 5408DynamoUnderOver
This is the Over Under Code that won't be used for so long, but it uses the inertial sensor a lot.
If you wanna learn more about this code, then just read this file.

## Gallery

- SR450, or Sport Rise 450, is a 3.25" 450 RPM speedster that featured a pneumatic PTO from the drive to power the lift capable of support the 13.5 pounds of robot upon a plastic pole.

![image](https://github.com/user-attachments/assets/d92a282e-b7c0-4da9-9e24-7d60bf641151)

- SL360, or Sport LongWheelBase 360, is a 3.25" 360 RPM nimble bot that featured... not a whole lot, but it got to finals so it worked good enough. 

![image](https://github.com/user-attachments/assets/a8ece1cf-10cf-4b6d-bdf8-164ad4f42832)

## Intro 

The code has pretty much been cycled since 2020-2024, however there have been some small improvements, as this code does a pretty ok job for the robot in terms of multitasking, and robustness (and ease of code if your experienced enough). It is a raw form of control for the base, simply using IMUs and IMEs, making this code work for a variety of robots who don't have access to fancy expensive sensors (tracking wheels and distance sensors). To start, just copy and paste this code into your editor with all the correct files and header files. 

## Methodology

To adjust the lateral and turning PID, simply go to the kP, kI, and kD and tune accordingly. You can always adjust these values on the go, I think you could make a function to do that or something. 

There is an autonomous button selector, that when you run this code, 8 buttons will pop up. You can possibly add more but I think 8 is enough. 

'`dV`' and '`dTV`' are short for "desiredValue" and "desiredTurnValue" respectively. The reason why I named it like this was so that it would be easier for me to input instructions on the go. '`resetDriveSensors`' is a boolean variable, that once is set to true, will reset all the IMEs and IMUs so that you can achieve a new movement from that pose. I will warn you to avoid using `resetDriveSensors` when possible and simply learn how to link movements by connecting the lines of code together, and adjusting the `task::sleep();` values. You can also make a function for to do that or something. Let's take a look at an example of how to do movements: 

If you go to the autonomous function of the code, you may notice that I turn "on" my drivePID, but in my driver code I turn "off" my drivePID. This will be important as you do want your robot to move accurately in autonomous, but you do not want your robot to move against your will (of your controller) in drive control. 

''' 
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
'''

