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
    wait(.25, seconds);
    LeftMotor.stop();
    RightMotor.stop();

    ArmMotor.spin(forward);
    wait(1, seconds);
}