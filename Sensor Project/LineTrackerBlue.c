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

line LineTrackerH = line(Brain.ThreeWirePort.H);

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

int main()
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // Calibration for blue detection (adjust these values based on testing)
    const int BLUE_BRIGHTNESS_THRESHOLD = 60; // Higher brightness = darker surface
    const int BLUE_HUE_MIN = 180;             // Blue colors typically 180-240 hue
    const int BLUE_HUE_MAX = 240;

    while (true)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);

        // Get line tracker values
        int brightness = LineTrackerH.value(percent);
        color detectedColor = LineTrackerH.color();
        int hue = LineTrackerH.hue();

        // Display sensor readings
        Brain.Screen.print("Brightness: %d%%", brightness);
        Brain.Screen.newLine();
        Brain.Screen.print("Hue: %d", hue);
        Brain.Screen.newLine();

        // Check if blue is detected
        bool blueDetected = (brightness > BLUE_BRIGHTNESS_THRESHOLD &&
                             hue >= BLUE_HUE_MIN &&
                             hue <= BLUE_HUE_MAX);

        if (blueDetected)
        {
            Brain.Screen.print("Status: BLUE DETECTED - GOING STRAIGHT");
            // Drive straight forward
            LeftDriveSmart.setVelocity(50, percent);
            RightDriveSmart.setVelocity(50, percent);
            LeftDriveSmart.spin(forward);
            RightDriveSmart.spin(forward);
        }
        else
        {
            Brain.Screen.print("Status: No blue - Stopped");
            // Stop the robot
            LeftDriveSmart.stop();
            RightDriveSmart.stop();
        }

        Brain.Screen.newLine();
        Brain.Screen.print("Blue Detected: %s", blueDetected ? "YES" : "NO");

        // A brief delay to allow text to be printed without distortion or tearing
        wait(50, msec);
    }
}