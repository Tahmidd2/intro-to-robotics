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
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);

motor ArmMotor = motor(PORT3, ratio18_1, false);
motor ClawMotor = motor(PORT2, ratio18_1, false);

bumper BumperA = bumper(Brain.ThreeWirePort.A);
pot PotentiometerA = pot(Brain.ThreeWirePort.A);
sonar RangeFinder = sonar(Brain.ThreeWirePort.C, Brain.ThreeWirePort.D);
line LineTracker = line(Brain.ThreeWirePort.H);

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

    // Lower the arm
    ArmMotor.spinFor(reverse, 600, degrees, 50, velocityUnits::pct);
    // Open the claw to release object
    ClawMotor.spinFor(forward, 180, degrees, 50, velocityUnits::pct);
    // Back away from scoring area
    Drivetrain.driveFor(reverse, 5, inches, 50, velocityUnits::pct);
    // Reset arm position (optional - adjust as needed)
    ArmMotor.spinFor(forward, 300, degrees, 50, velocityUnits::pct);
}

int main()
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    // Register bumper press callback
    BumperA.pressed(bumpaction);
    while (true)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);

        // Display sensor readings
        Brain.Screen.print("Bumper: %s", BumperA.pressing() ? "PRESSED" : "Ready");
        Brain.Screen.newLine();
        Brain.Screen.print("Arm Angle: %.1f deg", PotentiometerA.angle(degrees));
        Brain.Screen.newLine();
        Brain.Screen.print("Distance: %.1f inches", RangeFinder.distance(inches));
        Brain.Screen.newLine();
        Brain.Screen.print("Line Brightness: %d", LineTracker.value(percent));

        // Normal driving code can go here
        // For example, you could add joystick control or autonomous driving

        // A brief delay to allow text to be printed without distortion or tearing
        wait(20, msec);
    }
}
