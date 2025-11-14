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
motor ClawMotor = motor(PORT2, ratio18_1, false);

motor ArmMotor = motor(PORT3, ratio18_1, false);

motor LeftMotor = motor(PORT19, ratio18_1, false);

motor RightMotor = motor(PORT20, ratio18_1, true);

controller Controller1 = controller(primary);

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

void controller_L2_Pressed()
{
    ArmMotor.spin(reverse);
    while (Controller1.ButtonL2.pressing())
    {
        wait(5, msec);
    }
    ArmMotor.stop();
}

void controller_R1_Pressed()
{
    ClawMotor.spin(reverse);
    while (Controller1.ButtonR1.pressing())
    {
        wait(5, msec);
    }
    ClawMotor.stop();
}

void controller_R2_Pressed()
{
    ClawMotor.spin(forward);
    while (Controller1.ButtonR2.pressing())
    {
        wait(5, msec);
    }
    ClawMotor.stop();
}

void preAutonomous(void)
{
    // actions to do when the program starts
    Brain.Screen.clearScreen();
    Brain.Screen.print("pre auton code");
    wait(1, seconds);
}

void autonomous(void)
{
    Brain.Screen.clearScreen();
    Brain.Screen.print("autonomous code");

    wait(.5, seconds);

    ClawMotor.spin(reverse);
    wait(.5, seconds);
    ArmMotor.spin(forward);
    wait(1, seconds);

    wait(10, msec);
    LeftMotor.setVelocity(85, percent);
    RightMotor.setVelocity(85, percent);
    LeftMotor.spin(reverse);
    RightMotor.spin(reverse);
    wait(2.5, seconds);

    LeftMotor.stop();
    RightMotor.stop();
    wait(1.5, seconds);

    ArmMotor.spin(reverse);
    wait(.5, seconds);
    ArmMotor.stop();
    wait(2.0, seconds);

    ClawMotor.spin(forward);
    wait(1.5, seconds);

    LeftMotor.spin(forward);
    RightMotor.spin(forward);
    wait(2, seconds);
    LeftMotor.stop();
    RightMotor.stop();

    ArmMotor.spin(forward);
    wait(1, seconds);
}

void userControl(void)
{
    Brain.Screen.clearScreen();
    // place driver control in this while loop
    while (true)
    {
        LeftMotor.setVelocity((-Controller1.Axis3.position() + Controller1.Axis1.position()), percent);
        RightMotor.setVelocity((-Controller1.Axis3.position() - Controller1.Axis1.position()), percent);
        LeftMotor.spin(forward);
        RightMotor.spin(forward);
        wait(20, msec);
    }
}

int main()
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // Create Controller callback events - 15 msec delay to ensure events get registered
    Controller1.ButtonL1.pressed(controller_L1_Pressed);
    Controller1.ButtonL2.pressed(controller_L2_Pressed);
    Controller1.ButtonR1.pressed(controller_R1_Pressed);
    Controller1.ButtonR2.pressed(controller_R2_Pressed);
    wait(15, msec);

    // Configure Arm and Claw motor hold settings and velocity
    ArmMotor.setStopping(hold);
    ClawMotor.setStopping(hold);
    ArmMotor.setVelocity(60, percent);
    ClawMotor.setVelocity(30, percent);

    // Main Controller loop for arcade drive

    competition Competition;

    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(userControl);

    // Run the pre-autonomous function.
    preAutonomous();

    autonomous();

    while (true)
    {

        wait(5, msec);
    }
}