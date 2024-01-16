#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller Controller1 = controller(primary);
motor frontL = motor(PORT6, ratio6_1, true);
motor middleL = motor(PORT9, ratio6_1, true);
motor backL = motor(PORT10, ratio6_1, true);
motor frontR = motor(PORT3, ratio6_1, false);
motor middleR = motor(PORT2, ratio6_1, false);
motor backR = motor(PORT1, ratio6_1, false);

motor intake = motor(PORT11, ratio6_1, true);
motor cata = motor(PORT7,ratio18_1, false);

pneumatics wings(Brain.ThreeWirePort.C);
pneumatics pullUp(Brain.ThreeWirePort.B);
pneumatics assist(Brain.ThreeWirePort.A);

inertial iner = inertial(PORT6);

line ballDetector = line(Brain.ThreeWirePort.H);
limit cataLimit = limit(Brain.ThreeWirePort.G);





/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}
