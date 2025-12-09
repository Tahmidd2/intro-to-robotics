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
motor ClawMotor = motor(PORT3, ratio18_1, false);

motor ArmMotor = motor(PORT8, ratio18_1, false);

motor LeftMotor = motor(PORT1, ratio18_1, false);

motor RightMotor = motor(PORT10, ratio18_1, true);

controller Controller1 = controller(primary);
pot PotentiometerA = pot(Brain.ThreeWirePort.A);


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



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

#pragma endregion VEXcode Generated Robot Configuration

// ----------------------------------------------------------------------------
//
//    Project:        Clawbot Controller with Events
//    Description:    This example will use Controller button events to
//                    control the V5 Clawbot arm and claw
//    Configuration:  V5 Clawbot (Individual Motors)
//                    Controller
//                    Claw Motor in Port 3
//                    Arm Motor in Port 8
//                    Left Motor in Port 1
//                    Right Motor in Port 10
//
// ----------------------------------------------------------------------------

#include "vex.h"

using namespace vex;

// Begin project code


//ARM DOWN
void controller_L1_Pressed()
{
    ArmMotor.spin(reverse);
    while (Controller1.ButtonL1.pressing())
    {
        wait(5, msec);
    }
    ArmMotor.stop();
}

void controller_L2_Pressed()
{
    while (Controller1.ButtonL2.pressing())
    {
        // should be autonomous routine for single climb

        int angle = PotentiometerA.angle(degrees);
        ArmMotor.setVelocity(50, percent);
        ArmMotor.spin(forward);
        wait(.7, seconds);
        ArmMotor.setVelocity(100, percent);
        while (angle > 10){
        ArmMotor.spin(reverse);
        leftMotor.spin(forward);
        rightMotor.spin(forward);
        }
        leftMotor.stop();
        rightMotor.stop();

    }
    ArmMotor.stop();
}

void controller_R1_Pressed()
{
    ArmMotor.spin(forward);
    while (Controller1.ButtonR1.pressing())
    {
        wait(5, msec);
    }
    ArmMotor.stop();
}

void controller_R2_Pressed()
{
    while (Controller1.ButtonR2.pressing())
    {
        // NOTHING HERE YET, could maybe be double climb automation
    }
}

int main()
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // Create Controller callback events - 15 msec delay to ensure events get registered
    Controller1.ButtonL1.pressed(controller_L1_Pressed); // arm down
    Controller1.ButtonL2.pressed(controller_L2_Pressed); // auto climb (single)
    Controller1.ButtonR1.pressed(controller_R1_Pressed); // arm up
    Controller1.ButtonR2.pressed(controller_R2_Pressed); // auto climb (double) maybe
    wait(15, msec);

    // Configure Arm motor hold settings and velocity
    ArmMotor.setStopping(hold);
    ArmMotor.setVelocity(60, percent);

    // Main Controller loop to set motors to controller axis postiions
    // arcade drive, axis 1-4 used
    while (true)
    {
        LeftMotor.setVelocity((-Controller1.Axis3.position() + Controller1.Axis1.position()), percent);
        RightMotor.setVelocity((-Controller1.Axis3.position() - Controller1.Axis1.position()), percent);
        LeftMotor.spin(forward);
        RightMotor.spin(forward);
        wait(20, msec);
    }
}