#pragma once
#include "okapi/api.hpp"
#include <memory>


class TankDrive{
    public:
    TankDrive(std::shared_ptr<okapi::AbstractMotor> lMtr, std::shared_ptr<okapi::AbstractMotor> rMtr, std::shared_ptr<okapi::Controller> con);
    void execute();
    protected:
    std::shared_ptr<okapi::AbstractMotor> lMtr;
    std::shared_ptr<okapi::AbstractMotor> rMtr;
    std::shared_ptr<okapi::Controller> con;
};