#include "main.h"
//#include "custom/auton/routines.hpp"
//#include "custom/auton/selection.cpp"
#include <iostream>
#include "selection.hpp"
#include "drive.hpp"
//#include "Auton"

TankDrive tankDrive(std::make_shared<okapi::Motor(11, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees)>,
                    std::make_shared<okapi::Motor(20, false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees)>,
                    std::make_shared<okapi::Controller(okapi::ControllerId::master)>);

okapi::Controller con(okapi::ControllerId::master);

okapi::Motor dmfr(2, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor dmmr(20, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor dmbr(4, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor dmfl(11, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor dmml(11, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor dmbl(11, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
// motor lr is lift.
okapi::Motor lr(15, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);
okapi::Motor ll(20, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::degrees);

pros::Optical goalcheck(11);

pros::ADIDigitalOut glp(1);
pros::ADIDigitalOut fgl(5);
pros::ADIDigitalOut fts(6);

pros::ADIDigitalIn toplift(4);
pros::ADIDigitalIn bottomlift(3);
// ph.set_value(true);
pros::Imu platpls(10);

okapi::MotorGroup ldrib({dmfr, dmmr, dmbr});
okapi::MotorGroup rdrib({dmfl, dmml, dmbl});
okapi::MotorGroup Liftmotors({lr});
okapi::MotorGroup Biftmotors({ll});
okapi::ControllerButton RBumper1(okapi::ControllerId::master, okapi::ControllerDigital::R1);
okapi::ControllerButton RBumper2(okapi::ControllerId::master, okapi::ControllerDigital::R2);
okapi::ControllerButton LBumper2(okapi::ControllerId::master, okapi::ControllerDigital::L2);
okapi::ControllerButton LBumper1(okapi::ControllerId::master, okapi::ControllerDigital::L1);
okapi::ControllerButton Y(okapi::ControllerId::master, okapi::ControllerDigital::Y);
okapi::ControllerButton right(okapi::ControllerId::master, okapi::ControllerDigital::right);
okapi::ControllerButton A(okapi::ControllerId::master, okapi::ControllerDigital::A);
okapi::ControllerButton B(okapi::ControllerId::master, okapi::ControllerDigital::B);
okapi::ControllerButton left(okapi::ControllerId::master, okapi::ControllerDigital::left);
okapi::ControllerButton down(okapi::ControllerId::master, okapi::ControllerDigital::down);

void initialize()
{
  auton::selection::screenInit();
  fts.set_value(false);
  platpls.reset();
  dmfr.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  dmfl.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  dmbr.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  dmbl.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  dmmr.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  dmml.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  lr.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  ll.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  ll.tarePosition();
  dmbl.tarePosition();
  dmbr.tarePosition();
  dmfl.tarePosition();
  dmfr.tarePosition();
  dmmr.tarePosition();
}
void disabled() {}

bool clamped = false;
void competition_initialize() {}

void hold(bool brk)
{
  if (brk = false)
  {
    dmfr.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    dmfl.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    dmbr.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    dmbl.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    dmmr.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    dmml.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  }
  else if (brk = true)
  {
    dmfr.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    dmfl.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    dmbr.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    dmbl.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    dmmr.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    dmml.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  }
}
void Adrive(int dist, int i, int ii) // Adrive(20,200,200);
{
  dmbl.tarePosition();
  dmbr.tarePosition();
  dmfl.tarePosition();
  dmfr.tarePosition();
  //  incccch = dmbl.getPosition()*12.5;
  while (12.57 * dist > abs(dmbr.getPosition()))
  {
    rdrib.moveVelocity(i);
    ldrib.moveVelocity(-ii);
  }
  rdrib.moveVelocity(0);
  ldrib.moveVelocity(0);
}

void Abalance()
{ // probly dont work
  platpls.reset();
  double rotation = platpls.get_pitch();
  if (rotation < 2 && rotation > -2)
  {
    ldrib.moveVelocity(75);
    rdrib.moveVelocity(75);
  }
  else
  {
    ldrib.moveVelocity(0);
    rdrib.moveVelocity(0);
  }
  hold(true);
  if (rotation > 2)
  {
    ldrib.moveVelocity(75);
    rdrib.moveVelocity(75);
  }
  else if (rotation < -2)
  {
    ldrib.moveVelocity(75);
    rdrib.moveVelocity(75);
  }
  else
  {
    ldrib.moveVelocity(0);
    rdrib.moveVelocity(0);
  }
}

void Aflift(int distfl, int ifl) // afilft(200,200);
{
  lr.tarePosition();
  while (distfl > abs(lr.getPosition()))
  {
    Liftmotors.moveVelocity(ifl);
  }
  Liftmotors.moveVelocity(0);
}

//                                                                      FIX ME PLZ
void Aclaw(int distBl, int iBl) // dont use
{
  ll.tarePosition();
  while (distBl * 7 > abs(ll.getPosition()))
  {
    ll.moveVelocity(iBl);
  }
  ll.moveVelocity(0);
  ll.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
}

void ARingle(int rs, int irl) // dont use
{
  ll.tarePosition();
  while (rs * 120 > abs(ll.getPosition()))
  {
    ll.moveVelocity(irl);
  }
  ll.moveVelocity(0);
}
void shlurprings()
{
  Aflift(500, 200);
  Adrive(15, -50, -50);
  Adrive(15, 50, 50);
  Adrive(15, -50, -50);
  Adrive(15, 50, 50);
  Adrive(15, -50, -50);
  Adrive(15, 50, 50);
  Adrive(15, -50, -50);
  Adrive(30, 50, 50);
  glp.set_value(false);
}
void AutonRight()
{ // when doing backwards movement do not tell the distance rather do negitive motor velocity.
  glp.set_value(false);
  fgl.set_value(true);
  fts.set_value(true);
  Adrive(20, 26, 99); // curves to middle goal.
  Adrive(72, 200, 200);
  pros::delay(200);
  fgl.set_value(false); // grabs middle gaol
  Adrive(2, -10, -10);
  Aflift(100, 200); // lifts goal off of ground
  Adrive(5, -80, -80);
  Adrive(10, -150, -15);  // Rotates
  Adrive(30, -100, -100); // backs up to hit goal.
  pros::delay(200);
  glp.set_value(true);
  Adrive(95, 100, 200);
}
void AutonLeft()
{
  fgl.set_value(true);
  fts.set_value(true);
  glp.set_value(false);
  hold(true);
  Adrive(84, 200, 200);
  Adrive(3, 100, 100);
  fgl.set_value(false);
  Aflift(300, 200);
  pros::delay(200);
  Adrive(5, -190, 12);
  Adrive(30, -110, -50);
  pros::delay(200);
  // Adrive(10, -100, -100);
  //  Adrive(30,-200,-170);
  glp.set_value(true);
  Adrive(90, 200, 160);
  hold(false);
}
void AutonWinPointRight()
{
  glp.set_value(false);
  fgl.set_value(true);
  fts.set_value(true);
  Adrive(1, 50, 50);
  Adrive(2, 100, 100);
  Adrive(3, 150, 150);
  Adrive(56, 200, 200);
  Adrive(2, 100, 100);
  pros::delay(150);
  fgl.set_value(false);
  Adrive(2, -100, -100);
  Adrive(40, -150, -150);
  rdrib.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  ldrib.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Adrive(5, -180, 200);
  Adrive(25, -100, -100);
  rdrib.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  ldrib.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  pros::delay(200);
  glp.set_value(true);
  ll.moveVelocity(200);
  // Aflift(1000, 200);
  Adrive(9, -40, 40);
  Adrive(20, 50, 50);
  shlurprings();
}

void AutonWinPointLeft()
{
  glp.set_value(false); // Backgoal clamp. False is open true is clamped
  fgl.set_value(true);  // Front goal clamp true is open false is clamped
  fts.set_value(true);  // Front toilet seat true is open false is clamped.
  Adrive(2, 50, 50);    // Drive durring auton, First number is distance the other two are wheel speeds.
  Adrive(3, 100, 100);
  Adrive(4, 150, 150); // drive in this area is first
  Adrive(56, 190, 200);
  Adrive(2, 100, 100);
  // Adrive(1,50,50);
  pros::delay(300); // Delays
  fgl.set_value(false);
  Adrive(2, -75, -75);
  pros::delay(200);
  Aflift(100, 200); // lift, first number is distance, second is speed.
  lr.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  // pros::delay(2000);
  // Aflift(1,-200);
  Adrive(4, -125, -125);
  Adrive(45, -120, -150);
  Adrive(4, -125, -125);
  Adrive(2, -75, -75);
  // fgl.set_value(true);
  Adrive(15, -110, -20);
  pros::delay(300);
  Adrive(4, -100, -100);
  pros::delay(150);
  glp.set_value(true);
  ll.moveVelocity(200); // ring intake just controls speed.
  Aflift(800, 200);
  Adrive(36, 90, 100);
  // Adrive(15,100,100);
  // Adrive(9,100,35);
  shlurprings();
}
void AutonRightMidWinpoint()
{
  glp.set_value(false);
  fgl.set_value(true);
  fts.set_value(true);
  hold(true);
  Adrive(20, 26, 99); // curves to middle goal.
  Adrive(77, 200, 200);
  pros::delay(200);
  fgl.set_value(false); // grabs middle gaol
  Aflift(200, 200);
  hold(false);
  Adrive(69, -100, -100);
  Adrive(9, -40, 40);
  Adrive(30, -70, -70);
  glp.set_value(true);
  Adrive(9, -40, 40);
  Adrive(30, 70, 70);
  ll.moveVelocity(200);
  shlurprings();
  glp.set_value(false);
}
void Autonsuperultimatewinpointthatmadeethanwanttohanghimself()
{ // right auton two goal.
  glp.set_value(false);
  fgl.set_value(true);
  fts.set_value(true);
  Adrive(2, 50, 50);
  Adrive(3, 100, 100);
  Adrive(4, 150, 150);
  Adrive(56, 190, 200);
  Adrive(2, 100, 100);
  // Adrive(1,50,50);
  pros::delay(300);
  fgl.set_value(false);
  Aflift(100, 200);
  lr.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  pros::delay(150);
  // pros::delay(2000);
  // Aflift(1,-200);
  Adrive(7, 50, 50);
  pros::delay(200);
  Adrive(16, -80, -20);
  Adrive(22, -100, -100);
  pros::delay(150);
  glp.set_value(true);
  Adrive(110, 85, 120);
}


void AutonSkills()
{ // left go to mid auton.
  glp.set_value(false);
  fgl.set_value(true);
  dmfl.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
  dmfr.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
  dmbr.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
  dmbl.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
  lr.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  Adrive(1, -70, -70);
  // pros::delay(100);
  glp.set_value(true);
  Adrive(5, 50, 50);
  ll.moveVelocity(200);
  pros::delay(100);
  Adrive(8, 103, 13);
  pros::delay(300);
  Adrive(65, 100, 100);
  pros::delay(300);
  fgl.set_value(false);
  pros::delay(50);
  Aflift(1100, 200);
  Adrive(85, 75, 65);
  pros::delay(500);
  lr.moveVelocity(0);
  Adrive(10, 0, 40);
  Aflift(200, -200);
  fgl.set_value(true);
  Adrive(20, -100, -100);
  Aflift(600, -200);
  Adrive(20, -100, 100);
  Adrive(15, 150, 150);
  glp.set_value(false);
  Aflift(300, -200);
  Adrive(37, 150, 100);
  pros::delay(300);
  fgl.set_value(false);
  Adrive(110, -115, -120);
  pros::delay(200);
  glp.set_value(true);
  pros::delay(200);
  Adrive(100, -125, -150);
  glp.set_value(false);
  Adrive(30, 90, 140);
  fgl.set_value(true);
}

void AutonFullWinpoint()
{
  fgl.set_value(true);
  glp.set_value(false);
  Adrive(25, 50, 50);
  fgl.set_value(false);
  pros::delay(500);
  fts.set_value(true);
  Adrive(25, -60, -70);
  Adrive(10, -20, 20);
  Adrive(63, 100, 70);
  Adrive(70, 70, 70);
  Adrive(40, 20, -20);
  fgl.set_value(true);
  fts.set_value(false);
  Adrive(35, -50, -50);
  glp.set_value(true);
  ll.moveVelocity(200);
  Adrive(60, 0, 40);
  shlurprings();
}
void autonomous()
{ // BOTH CLAW AND LIFT MUST BE ON THE GROUND IF IT IS NOT IT WILL BREAK.

  auton::selection::execute();
}
void drive()
{
  // MECHANUM BBYYYYYYYYY
  /*   double joyXL{deadband(con.getAnalog(ControllerAnalog::rightX), -15.0 / 200, 15.0 / 200)};
  double joyYL{deadband(con.getAnalog(ControllerAnalog::rightY), -15.0 / 200, 15.0 / 200)};
  double joyXR{deadband(con.getAnalog(ControllerAnalog::leftX), -15.0 / 200, 15.0 / 200)};
  double joyYR{deadband(con.getAnalog(ControllerAnalog::leftY), -15.0 / 200, 15.0 / 200)};

  double X{joyXL + joyXR / 2};
  double Y{joyYL + joyYR / 2};
  double Z{joyYR - Y};

  deadband(X, -100.0 / 200, 100.0 / 200);
  dmbl.moveVelocity((Y + X - Z) * 200);
  dmbml.moveVelocity((Y + X - Z) * 200);

  dmbr.moveVelocity((Y - X + Z) * 200);
  dmbmr.moveVelocity((Y - X + Z) * 200);

  dmfl.moveVelocity((Y - X - Z) * 200);
  dmfml.moveVelocity((Y - X - Z) * 200);

  dmfl.moveVelocity((Y - X - Z) * 200);
  dmfml.moveVelocity((Y + X + Z) * 200);
  */
  // OMNIIIII
  /*
  if (std::abs(con.getAnalog(okapi::ControllerAnalog::rightY)) < 0.08)
  {
    if(dmml.getPosition()>0){
    dmml.moveVelocity(-50);
    }
    else{
    dmml.moveVelocity(0);
      dmml.tarePosition();
    }
  }
  else
  {
    dmml.moveVelocity(|con.getAnalog(okapi::ControllerAnalog::rightY) * 20|);
  }
  if (std::abs(con.getAnalog(okapi::ControllerAnalog::leftY)) < 0.08)
  {
    if(dmml.getPosition()>0){
    dmml.moveVelocity(-50);
    }
    else{
    dmml.moveVelocity(0);
      dmml.tarePosition();
    }

  }
  else
  {
    dmmr.moveVelocity(|con.getAnalog(okapi::ControllerAnalog::leftY) * 20|);
  }
  */

  /*if (std::abs(con.getAnalog(okapi::ControllerAnalog::rightY)) < 0.08){
    if(dmmr.getPosition()>0){
    dmmr.moveVelocity(-50);
  }
  else{
    dmmr.moveVelocity(0);
    dmmr.tarePosition();
  }
}
else{*/
}

void flift()
{
  if (LBumper1.isPressed() /* && 1280>abs(lr.getPosition())*/)
  {
    Liftmotors.moveVelocity(200);
  }
  else if (LBumper2.isPressed() && 22 < abs(lr.getPosition()))
  {
    Liftmotors.moveVelocity(-200);
  }
  else if (down.isPressed())
  {
    Liftmotors.moveVelocity(-200);
    Liftmotors.tarePosition();
  }
  else
  {
    Liftmotors.moveVelocity(0);
  }
}

bool togA = false;
bool togc = false;
void btna()
{

  // std::cout << A.changed() << A.isPressed() << std::endl;
  if (RBumper1.changed())
  {
    if (RBumper1.isPressed())
    {
      togA = !togA;
      fgl.set_value(togA);
    }
  }
  if (RBumper2.changed())
  {
    if (RBumper2.isPressed())
    {
      togc = !togc;
      fts.set_value(togc);
    }
  }
}

bool togB = false;
void btnb()
{
  // std::cout << A.changed() << A.isPressed() << std::endl;
  if (Y.changed())
  {
    if (Y.isPressed())
    { // init
      togB = !togB;
      glp.set_value(togB);
      // ph2.set_value(togB);
      // std::cout << togB << std::endl;
    }
  }
  // std::cout << A.changed() << A.isPressed() << std::endl;
  if (right.changed())
  {
    if (right.isPressed())
    { // init
      togA = !togA;
      int wokr = 0;
      if (togA == true)
      {
        wokr = 200;
      }
      else
      {
        wokr = 0;
      }
      ll.moveVelocity(wokr);
      // std::cout << togA << std::endl;
    }
  }
}

bool togBrake = false;
void btnbrake()
{
  // std::cout << A.changed() << A.isPressed() << std::endl;
  if (A.changed())
  {
    if (A.isPressed())
    { // init
      togBrake = !togBrake;
      if (togBrake == true)
      {

        dmfr.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        dmfl.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        dmbr.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        dmbl.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
      }
      else
      {

        dmfr.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
        dmfl.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
        dmbr.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
        dmbl.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
      }
      // ph2.set_value(togB);
      // std::cout << togB << std::endl;
    }
  }
}

void opcontrol()
{
  while (true)
  {
    tankDrive.execute();
    pros::delay(20);
  }
}
// autotps();
// std::cout << "loop" << A.changed() << A.isPressed() << std::endl;
// drive();
// shlurp();
// btnbrake();
// flift();
// blift();
// btna();
// btnb();
//  //pros::delay(1);
// testing();
// std::cout << "loop" << i1.getPosition() << std::endl;
/* pros::Task::delay_until(&preMS, 20);
if(pros::millis()<starttime+104000){
 btnb();
 std::cout << starttime << std::endl;
}
else{
 glp.set_value(false);

 std::cout << starttime << std::endl;
}
}

/*
while(1==1){
 if (std::abs(con.getAnalog(okapi::ControllerAnalog::rightY)) < 0.08){
   if(dmmr.getPosition()>0){
   dmmr.moveVelocity(-50);
 }
 else{
   dmmr.moveVelocity(0);
   dmmr.tarePosition();
 }
}
else{
 if(dmmr.getPosition()<std::abs(con.getAnalog(okapi::ControllerAnalog::rightY*8){
 dmml.moveVelocity(20);}
}
 if (std::abs(con.getAnalog(okapi::ControllerAnalog::leftY)) < 0.08){
   if(dmml.getPosition()>0){
   dmml.moveVelocity(-50);
 }
 else{
   dmml.moveVelocity(0);
   dmml.tarePosition();
 }
}
else{
 if(dmml.getPosition()<std::abs(con.getAnalog(okapi::ControllerAnalog::leftY*8){
 dmml.moveVelocity(20);}
}
}






if (std::abs(con.getAnalog(okapi::ControllerAnalog::rightY)) < 0.08)
{
 if(dmml.getPosition()>0){
 dmml.moveVelocity(-50);
 }
 else{
 dmml.moveVelocity(0);
   dmml.tarePosition();
 }
}
else
{
 dmml.moveVelocity(|con.getAnalog(okapi::ControllerAnalog::rightY) * 20|);
}
if (std::abs(con.getAnalog(okapi::ControllerAnalog::leftY)) < 0.08)
{
 if(dmml.getPosition()>0){
 dmml.moveVelocity(-50);
 }
 else{
 dmml.moveVelocity(0);
   dmml.tarePosition();
 }

}
else
{
 dmmr.moveVelocity(|con.getAnalog(okapi::ControllerAnalog::leftY) * 20|);
}


*/
