#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>




#include "vex.h"


using namespace vex;


// Brain should be defined by default
brain Brain;




// START V5 MACROS
#define waitUntil(condition)                                                   \
 do {                                                                         \
   wait(5, msec);                                                             \
 } while (!(condition))


#define repeat(iterations)                                                     \
 for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS




// Robot configuration code.
motor LeftDriveSmart = motor(PORT1, ratio18_1, false);
motor RightDriveSmart = motor(PORT10, ratio18_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);


pot PotentiometerA = pot(Brain.ThreeWirePort.A);
motor ArmMotor = motor(PORT3, ratio18_1, false);






// generating and setting random seed
void initializeRandomSeed(){
 int systemTime = Brain.Timer.systemHighResolution();
 double batteryCurrent = Brain.Battery.current();
 double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);


 // Combine these values into a single integer
 int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;


 // Set the seed
 srand(seed);
}






void vexcodeInit() {


 //Initializing random seed.
 initializeRandomSeed();
}




// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
 printf("VEXPlaySound:%s\n", soundName);
 wait(5, msec);
}


#pragma endregion VEXcode Generated Robot Configuration


// ----------------------------------------------------------------------------
//                                                                           
//    Project:        3-Wire Potentiometer Sensing                                     
//    Description:    This example will show all of the available commands
//                    for using the 3-Wire Potentiometer Sensor                       
//    Configuration:  V5 Speedbot (Drivetrain 2-motor, No Gyro)
//                    Potentiometer in 3-Wire Port A             
//                                                                           
// ----------------------------------------------------------------------------


#include "vex.h"


using namespace vex;


// Begin project code


// Optional: Controller button handler for manual control
void controller_R1_Pressed() {
   // Move arm down to lower position
   ArmMotor.spin(reverse, 50, percent);
   while (Controller1.ButtonR1.pressing()) {
       wait(5, msec);
   }
   ArmMotor.stop();
}


void controller_L1_Pressed() {
   // Move arm up
   ArmMotor.spin(forward, 50, percent);
   while (Controller1.ButtonL1.pressing()) {
       wait(5, msec);
   }
   ArmMotor.stop();
}


int main() {
   // Initializing Robot Configuration. DO NOT REMOVE!
   vexcodeInit();
  
   // Register controller callbacks for manual control
   Controller1.ButtonR1.pressed(controller_R1_Pressed);
   Controller1.ButtonL1.pressed(controller_L1_Pressed);
  
   const int TARGET_ANGLE = 90;
   const int TOLERANCE = 3; // ±3 degrees tolerance
  
   // Print all Potentiometer sensing values to the screen in an infinite loop
   while(true) {
       // Clear the screen and set the cursor to top left corner on each loop
       Brain.Screen.clearScreen();
       Brain.Screen.setCursor(1,1);
      
       // Read current angle
       double currentAngle = PotentiometerA.angle(degrees);
      
       // Display potentiometer values
       Brain.Screen.print("Angle - Degrees: %.2f", currentAngle);
       Brain.Screen.newLine();
       Brain.Screen.print("Angle - Percent: %d", PotentiometerA.angle(percent));
       Brain.Screen.newLine();
       Brain.Screen.print("Angle - Turns: %.2f", PotentiometerA.angle(turns));
       Brain.Screen.newLine();
      
       // Smart position control with tolerance
       if (currentAngle < TARGET_ANGLE - TOLERANCE) {
           // Too low - move up
           ArmMotor.spin(forward, 50, percent);
           Brain.Screen.print("Status: Moving UP to 90 deg");
       } else if (currentAngle > TARGET_ANGLE + TOLERANCE) {
           // Too high - move down 
           ArmMotor.spin(reverse, 50, percent);
           Brain.Screen.print("Status: Moving DOWN to 90 deg");
       } else {
           // Within tolerance - stop
           ArmMotor.stop();
           Brain.Screen.print("Status: AT TARGET POSITION!");
       }
      
       // A brief delay to allow text to be printed without distortion or tearing
       wait(50, msec);
   }
}