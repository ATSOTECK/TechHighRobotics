#include "LogitechController.h"

LogitechController::LogitechController(int port)
{
    Controller = new Joystick(port,4,12);
}

LogitechController::~LogitechController()
{
    delete Controller;
}

double LogitechController::GetX1()
{
    return Controller->GetRawAxis(1);
}

double LogitechController::GetY1()
{
    return Controller->GetRawAxis(2);
}

double LogitechController::GetX2()
{
    return Controller->GetRawAxis(3);
}

double LogitechController::GetY2()
{
    return Controller->GetRawAxis(4);
}

bool LogitechController::GetButton(int index)
{
    return Controller->GetRawButton(index);
}
