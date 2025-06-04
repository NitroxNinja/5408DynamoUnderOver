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

Every robot is different. Every programmer must optomize their code to different robots, which have different wheelbases, and such. In our particular case, our code is based off measurements of cubits (around 18 inches), for every movement. This was convienient b/c VEX rules only allow an 18" x 18" x 18" robot, thus you can imagine the robot in your head and make measurements and approximations pretty easily, and program/tune autons on the get-go.

## Driver-focused 

There is also very little drive macros and automated tasks. **This is a driver's robot. Not a neat robot.** Everything is raw control and skill. It's supposed to be a **viseral experience to drive one of my robots!** Even my drivetrain uses voltage control instead of PID (but this does come at some consequences such as low torque in both ends of the RPM limits), and features a autolocking drive (most people complain that this may damage the motors, but if you drive properly, it shouldn't). It uses arguably the most difficult to control setting, right hand single-stick arcade, and absolutely no power curves to the thing, just linear pure movement. 

The lifting of the robot auton this pole requires 6 steps that all need to be driven by hand. Deploying the lift mechanism, aligning the standoffs to the pole, engaging the transmission shift fork to the drive, driving forward(which moves the lift up), moving the side stick out of the way, and then compressing the lift. There is no ratchet on the thing, and it simply uses the natural resistance of the motors to hold the robot in on the pole and the forwarded friction.  

I will admit that just b/c it's hard to control doesn't mean this robot is better than others or that I am a one-of-a-kind drivers. It is just that it's supposed to be engaging, and a little fun. If you can drive my robot, you can drive any other robot. Even if it has curvature drive! 

## Driver Control Methodology

Driver control functions are located in `opControl.cpp` and functions can be listed in main.h (which isn't on this repo, go check my other repos), and use a right hand single-stick arcade drive, which allows me (the driver) to do other tasks with the left hand. People in countries that drive RHD will find this workable, however most people may find this weird, so they can move it to their left hand. To be honest figuring out macros and other driver widgets is pretty easy,`if, else` and whatnot can be used. 

If you are still learning how to code, I highly recommend watching some videos on control structures, boolean statements, variables, functions, and more basic C++ topics. I have no idea how I taught myself C++ so good luck!

## Autonomous Routine Methodology

To adjust the lateral and turning PID, simply go to the `kP`, `kI`, and `kD` and tune accordingly. You can always adjust these values on the go, I think you could make a function to do that or something. 

There is an autonomous button selector, that when you run this code, 8 buttons will pop up. You can possibly add more but I think 8 is enough. Put your autonomous code into the autonomous function where there are `if` statements with the corresponding function/button. You could make a function to do that but nah. 

If you go to the autonomous function of the code, you may notice that I turn "on" my drivePID, but in my driver code I turn "off" my drivePID. This will be important as you do want your robot to move accurately in autonomous, but you do not want your robot to move against your will (of your controller) in drive control. 

## Autonomous Programming Tips and Remarks

### i. How to use this code
'`dV`' and '`dTV`' are short for "desiredValue" and "desiredTurnValue" respectively. The reason why I named it like this was so that it would be easier for me to input instructions on the go. '`resetDriveSensors`' is a boolean variable, that once is set to true, will reset all the IMEs and IMUs so that you can achieve a new movement from that pose. I will warn you to avoid using `resetDriveSensors` when possible and simply learn how to link movements by connecting the lines of code together, and adjusting the `task::sleep();` values. You can also make a function for to do that or something. Let's take a look at an example of how to do movements: 

      kP = 0.124; // adjust kP value for aggression
    //while going forward open the wings to release preload, additionally intake is spinning
    spinUp(true); //this function SPINS the intake
    wings.open(); // this one OPENS the pneumatic wings that are on both sides of the robot
    task::sleep(400); // the robot is given 400 milliseconds to complete this task before moving onto the next one.
    dV = 5.2; // the robot will move 5.2 cubits forward 
    dTV = -48; // AND the robot turns left while going forward
    wings.close(); // this one CLOSES the pneumatic wings that are on both sides of the robot
    task::sleep(1600); // the robot is given 1600 milliseconds (1.6 seconds) to complete this task before moving onto the next one
    spinUp(false); // the robot stops spinning the intake 

    kP = 0.118; //decrease kP value for accuracy and reducing oscillation. 
    //turn right to align with goal, swipe to avoid touching middle pipe 
    dV = 5.0; // the robot backs up 0.2 cubits, because previously dV was 5.2 and now it's 5.0. Thus 5.2-5.0 = 0.2  
    dTV = 90; // the robot turs 138 degrees to the right b/c it has a pose angle of -48 previously, and now it's 90. 90 - (-48) = 138.
    task::sleep(800); // the robot is given 800 milliseconds to COMPLETE this turn

This represents the most raw form of control and it often is kind of hard to think about, but once you get the gist of it, you can code super advanced movements without requiring advanced odom or pure pursuit systems. Given that those systems are probably better, but this code presents a challenge to be independent and develop my own solutions to coding. 

### ii. Tips in developing autonomous routines (KISS, Keep it simple, stupid)
Make movements simple as possible. Make it fast. Make it reasonable. Why go in a curve when you just drive in a straight line? More crazier movements mean more crazier readings from your IMU and IMEs (aka this is called noise). There is a lack of kalman filtering on this system, and you're gonna have to be careful. 
But you may be asking why the hell would I do that? Well VEX is a very small field, and it doesn't have to dive deep into the real world sh-t of nonlinear systems, and special instrumentation devices. You should be able to go very far based on this code, and create more functions and make my code a WHOLE lot neater to help you simplify your programming. 

### iii. Include some comments 
I know CS teachers make a huge deal out of this, but to be honest take a chill pill. You don't always have to include comments on obivious things, just include comments where they may be complicated movements. In the code snippet above, I just included a lot to help you get a more intuitive sense on how our team programs. In reality, I just include one comment like "the robot is (should be) doing a right curve turn into the goal". Don't spend all your time on documentation.

### iv. Improve this code 
You get this. Don't just take this code at face value. There's so much work that can be done to this program which can make moving your robot better. I don't suggest using the same code for more than 4 years like how I did. I have an excuse to use the same code since our team didn't really invest into programming R&D, and most of the time it was me just building the robot and figuring out ideas rather than figuring out how to code. Try to make improvements to it every week or atleast monthly. 

You can also alternatively switch to another coding library like EZ-Template or LemLib, but I am different. 

## Conclusion 

This code is very simple. But it takes the right programmer to configure this code to your own. I shared this to others so that they could know how stupidly dumb this code is and how it brought my team's successes in a increasingly competitive region. You don't need a whole lot widgets to be good. You just need to get the perfect the basics. 



