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

sonar RangeFinderC = sonar(Brain.ThreeWirePort.C);

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

// helper
void playVexcodeSound(const char *soundName)
{
    printf("VEXPlaySound:%s\n", soundName);
    wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration

// ----------------------------------------------------------------------------
//
//    Project:        3-Wire Rangefinder Sensing
//    Description:    This example will show all of the available commands
//                    for using the 3-Wire Rangefinder Sensor
//    Configuration:  V5 Speedbot (Drivetrain 2-motor, No Gyro)
//                    Rangefinder in 3-Wire Ports A B
//
// ----------------------------------------------------------------------------

#include "vex.h"

using namespace vex;

// Begin project code

int main()
{
    vexcodeInit();

    while (true)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);

        // RangeFinderC
        Brain.Screen.print("Found Object?: %s", RangeFinderC.foundObject() ? "TRUE" : "FALSE");
        Brain.Screen.newLine();

        Brain.Screen.print("Distance - Inches: %.2f", RangeFinderC.distance(inches));
        Brain.Screen.newLine();

        Brain.Screen.print("Distance - MM: %.2f", RangeFinderC.distance(mm));

        // used inches instead of mm as im more familiar
        double distanceInches = RangeFinderC.distance(inches);

        // adding nested if conditional for action
        if (RangeFinderC.foundObject())
        {
            if (distanceInches > 40)
            { // ~40 inches = ~1016mm
                LeftDriveSmart.setVelocity(70, percent);
                RightDriveSmart.setVelocity(70, percent);
                RightDriveSmart.spin(forward);
                LeftDriveSmart.spin(forward);
                Brain.Screen.print("Status: Far - Fast Forward");
            }
            else if (distanceInches > 20)
            { // ~20 inches = ~508mm
                LeftDriveSmart.setVelocity(50, percent);
                RightDriveSmart.setVelocity(50, percent);
                RightDriveSmart.spin(forward);
                LeftDriveSmart.spin(forward);
                Brain.Screen.print("Status: Medium - Medium Speed");
            }
            else if (distanceInches > 10)
            { // ~10 inches = ~254mm
                LeftDriveSmart.setVelocity(25, percent);
                RightDriveSmart.setVelocity(25, percent);
                RightDriveSmart.spin(forward);
                LeftDriveSmart.spin(forward);
                Brain.Screen.print("Status: Close - Slow Speed");
            }
            else if (distanceInches < 8)
            { 
                Drivetrain.stop();
                Brain.Screen.print("Status: Very Close - STOPPED");
            }
            else
            {
                // stop otherwise
                Drivetrain.stop();
                Brain.Screen.print("Status: In Stopping Range");
            }
        }
        else
        {
            // if nothings there then we dont need to move
            Drivetrain.stop();
            Brain.Screen.print("No object detected!");
        }

        Brain.Screen.newLine();
        wait(50, msec);
    }
}