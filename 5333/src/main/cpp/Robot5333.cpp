#include "Robot5333.h"

#include <math.h>
#include <iostream>

#include <SmartDashboard/SmartDashboard.h>
#include <cameraserver/CameraServer.h>

using namespace frc;
using namespace curtinfrc;

void Robot::RobotInit() {
  table = nt::NetworkTableInstance::GetDefault().GetTable("vision");
  yOffset = table->GetEntry("yOffset");
  xOffset = table->GetEntry("xOffset");
  endAngle = table->GetEntry("endAngle");

  CameraServer::GetInstance()->StartAutomaticCapture(0);
  CameraServer::GetInstance()->StartAutomaticCapture(1);

  joy = new curtinfrc::Joystick(0);

  leftSRX = new TalonSrx(1);
  leftSRX->SetInverted(false);
  leftSPX = new VictorSpx(2);
  leftSPX->SetInverted(false);
  left = new SensoredTransmission{ new SpeedControllerGroup(*leftSRX, *leftSPX), nullptr };

  rightSRX = new TalonSrx(3);
  rightSRX->SetInverted(true);
  rightSPX = new VictorSpx(4);
  rightSPX->SetInverted(true);
  right = new SensoredTransmission{ new SpeedControllerGroup(*rightSRX, *rightSPX), nullptr };

  DrivetrainConfig drivetrainConfig{*left, *right};
  drivetrain = new Drivetrain(drivetrainConfig);


  liftMotors[0] = new Spark(5);
  liftGearbox = new Gearbox{ new SpeedControllerGroup(*liftMotors[0]), nullptr };

  ElevatorConfig elevatorConfig{ *liftGearbox, nullptr, nullptr };
  beElevator = new Lift(elevatorConfig);
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  SmartDashboard::PutNumber("Y Offset", yOffset.GetDouble(0));
  SmartDashboard::PutNumber("X Offset", xOffset.GetDouble(0));
  SmartDashboard::PutNumber("End Angle", endAngle.GetDouble(0));

  double joyY = -joy->GetCircularisedAxisAgainst(joy->kYAxis, joy->kZAxis) * 0.9;
  double joyZ = joy->GetCircularisedAxisAgainst(joy->kZAxis, joy->kYAxis) * 0.65;

  joyY *= abs(joyY);
  joyZ *= abs(joyZ);

  double leftSpeed = joyY + joyZ;
  double rightSpeed = joyY - joyZ;

  drivetrain->Set(leftSpeed, rightSpeed);


  double beElevatorSpeed = (joy->GetRawButton(8) - joy->GetRawButton(7)) * 0.8;

  beElevator->Set(beElevatorSpeed);
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
