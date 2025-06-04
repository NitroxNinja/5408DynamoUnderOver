# 5408DynamoUnderOver
This is the Over Under Code that won't be used for so long, but it uses the inertial sensor a lot.

## Gallery

- SR450, or Sport Rise 450, is a 3.25" 450 RPM speedster that featured a pneumatic PTO from the drive to power the lift capable of support the 13.5 pounds of robot upon a plastic pole.

![image](https://github.com/user-attachments/assets/d92a282e-b7c0-4da9-9e24-7d60bf641151)

- SL360, or Sport LongWheelBase 360, is a 3.25" 360 RPM nimble bot that featured... not a whole lot, but it got to finals so it worked good enough. 

![image](https://github.com/user-attachments/assets/a8ece1cf-10cf-4b6d-bdf8-164ad4f42832)

## Intro 

The code has pretty much been cycled since 2020-2024, however there have been some small improvements, as this code does a pretty ok job for the robot in terms of multitasking, and robustness (and ease of code if your experienced enough). It is a raw form of control for the base, simply using IMUs and IMEs, making this code work for a variety of robots who don't have access to fancy expensive sensors (tracking wheels and distance sensors). To start, just copy and paste this code into your editor with all the correct files and header files. 

## Methodology

To adjust the lateral and turning PID, simply go to the kP, kI, and kD and tune accordingly. You can always adjust these values on the go, I think you could make a function to do that or something. 

'`dV`' and '`dTV`' are short for "desiredValue" and "desiredTurnValue" respectively. The reason why I named it like this was so that it would be easier for me to input instructions on the go. '`resetDriveSensors`' is a boolean variable, that once is set to true, will reset all the IMEs and IMUs so that you can achieve a new movement from that pose. I will warn you to avoid using `resetDriveSensors` when possible and simply learn how to link movements by connecting the lines of code together, and adjusting the `task::sleep();` values. You can also make a function for to do that or something. 


