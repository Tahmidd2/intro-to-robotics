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
motor LeftDriveSmart = motor(PORT19, ratio18_1, false);
motor RightDriveSmart = motor(PORT20, ratio18_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 10, mm, 1);

bumper BumperA = bumper(Brain.ThreeWirePort.F);
motor ArmMotor = motor(PORT3, ratio18_1, false);

motor ClawMotor = motor(PORT2, ratio18_1, false);

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

#pragma endregion VEXcode Generated Robot Configuration

#include "vex.h"

using namespace vex;

// Scoring routine function
void bumpaction()
{
    // Stop driving first
    Drivetrain.stop();
    LeftDriveSmart.setVelocity(25, percent);
    RightDriveSmart.setVelocity(25, percent);
    RightDriveSmart.spin(forward);
    LeftDriveSmart.spin(forward);
    wait(.25, seconds);

    ArmMotor.spin(forward);
    wait(1.5, seconds);
    ArmMotor.stop();
    wait(.5, seconds);

    ClawMotor.spin(forward);
    wait(3, seconds);

    LeftDriveSmart.spin(forward);
    RightDriveSmart.spin(forward);
    wait(1, seconds);
    LeftDriveSmart.stop();
    RightDriveSmart.stop();

    ArmMotor.spin(reverse);
    wait(1, seconds);
}

int main()
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    ArmMotor.spin(forward);
    wait(2, seconds);
    ArmMotor.setVelocity(100, percent);
    ArmMotor.spin(reverse);
    wait(.3, seconds);
    // Register bumper press callback
    BumperA.pressed(bumpaction);
    while (true)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);

        // Display sensor readings
        Brain.Screen.print("Bumper: %s", BumperA.pressing() ? "PRESSED" : "Ready");
        Brain.Screen.newLine();
        Brain.Screen.newLine();
        Brain.Screen.newLine();

        // Normal driving code can go here
        // For example, you could add joystick control or autonomous driving

        // A brief delay to allow text to be printed without distortion or tearing
        wait(20, msec);
    }
}