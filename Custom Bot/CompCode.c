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
#define waitUntil(condition) \
    do                       \
    {                        \
        wait(5, msec);       \
    } while (!(condition))

#define repeat(iterations) \
    for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS

// Robot configuration code.
motor ArmMotor = motor(PORT3, ratio18_1, false);

controller Controller1 = controller(primary);
pot PotentiometerF = pot(Brain.ThreeWirePort.F);
motor LeftDriveSmart = motor(PORT19, ratio18_1, false);
motor RightDriveSmart = motor(PORT20, ratio18_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 10, mm, 1);

// generating and setting random seed
void initializeRandomSeed()
{
    int systemTime = Brain.Timer.systemHighResolution();
    double batteryCurrent = Brain.Battery.current();
    double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

    // Combine these values into a single integer
    int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

    // Set the seed
    srand(seed);
}

void vexcodeInit()
{

    // Initializing random seed.
    initializeRandomSeed();
}

// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName)
{
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

void controller_L1_Pressed()
{
    ArmMotor.spin(forward);
    while (Controller1.ButtonL1.pressing())
    {
        wait(5, msec);
    }
    ArmMotor.stop();
}

void controller_R2_Pressed()
{
    ArmMotor.spin(forward);
    while (Controller1.ButtonR2.pressing())
    {
        wait(5, msec);
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

void controller_L2_Pressed()
{

    ArmMotor.setVelocity(80, percent);
    ArmMotor.spin(forward);
    wait(1.2, seconds);
    ArmMotor.stop();

    // LeftMotor.setVelocity(50, percent);
    // RightMotor.setVelocity(50, percent);
    Drivetrain.driveFor(reverse, 10, inches);

    ArmMotor.spin(reverse);
    wait(1.2, seconds);
    ArmMotor.stop();
    ArmMotor.setVelocity(50, percent);
    Drivetrain.turnFor(right, 20, degrees);
}

int main()
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    Brain.Screen.print(PotentiometerF.angle(degrees));

    // Create Controller callback events - 15 msec delay to ensure events get registered
    Controller1.ButtonL1.pressed(controller_L1_Pressed);
    Controller1.ButtonL2.pressed(controller_L2_Pressed);
    Controller1.ButtonR1.pressed(controller_R1_Pressed);
    Controller1.ButtonR2.pressed(controller_R2_Pressed);
    wait(15, msec);

    // Configure Arm and Claw motor hold settings and velocity
    ArmMotor.setStopping(hold);
    ArmMotor.setStopping(hold);
    ArmMotor.setVelocity(45, percent);

    // Main Controller loop to set motors to controller axis postiions
    while (true)
    {
        LeftMotor.setVelocity((-Controller1.Axis3.position() + Controller1.Axis1.position()), percent);
        RightMotor.setVelocity((-Controller1.Axis3.position() - Controller1.Axis1.position()), percent);
        LeftMotor.spin(forward);
        RightMotor.spin(forward);
        wait(20, msec);
    }
}