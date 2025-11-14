// THIS CODE DOESN"T WORK, has to be tested and fixed
// red side
void autonomous(void)
{
    Brain.Screen.clearScreen();
    Brain.Screen.print("autonomous code");

    // Lift arm 
    ArmMotor.spin(forward);
    wait(1, seconds);
    ArmMotor.stop();

    // forward
    LeftMotor.setVelocity(100, percent);
    RightMotor.setVelocity(100, percent);
    LeftMotor.spin(reverse); // reversed drivetrain, forward means backward
    RightMotor.spin(reverse);
    wait(4.5, seconds);
    LeftMotor.stop();
    RightMotor.stop();

    // turn right 90 degrees
    LeftMotor.setVelocity(100, percent);
    RightMotor.setVelocity(100, percent);
    LeftMotor.spin(forward);
    RightMotor.spin(reverse);
    wait(0.15, seconds); // time needs to be adjusted
    LeftMotor.stop();
    RightMotor.stop();

    // go to scoring area
    LeftMotor.spin(reverse);
    RightMotor.spin(reverse);
    wait(1.5, seconds);
    LeftMotor.stop();
    RightMotor.stop();

    // lower arm
    ArmMotor.spin(reverse);
    wait(1, seconds);
    ArmMotor.stop();

    // open claw
    ClawMotor.spin(forward);
    wait(0.5, seconds);
    ClawMotor.stop();

    // back up
    LeftMotor.spin(forward);
    RightMotor.spin(forward);
    wait(.5, seconds);
    LeftMotor.stop();
    RightMotor.stop();

    // shake arm
    for (int i = 0; i < 3; i++)
    {
        ArmMotor.spin(forward);
        wait(0.15, seconds);
        ArmMotor.spin(reverse);
        wait(0.15, seconds);
    }
    ArmMotor.stop();
}