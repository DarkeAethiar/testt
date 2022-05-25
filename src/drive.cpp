#include "drive.hpp"

TankDrive::TankDrive(
    std::shared_ptr<okapi::AbstractMotor> lMtr,
    std::shared_ptr<okapi::AbstractMotor> rMtr,
    std::shared_ptr<okapi::Controller> con)
    :lMtr(lMtr),rMtr(rMtr),con(con)
    {}
    void TankDrive::execute(){
      float lNut = con->getAnalog(okapi::ControllerAnalog::leftY);
      float rNut = con->getAnalog(okapi::ControllerAnalog::rightY);
      double lPos = lMtr->moveAbsolute(std::abs(lNut)*8.0,50);
      double rPos = rMtr->moveAbsolute(std::abs(rNut)*8.0,50);
    }