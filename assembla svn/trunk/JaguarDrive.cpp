#include "JaguarDrive.h"

JaguarDrive::JaguarDrive(bool enablevariables)
{
    VariablesEnabled = enablevariables;
    for(int a = 0;a < 8;a += 1) 
    {
        Jaguar[a] = 0;
        Variable[a] = 0;
        Reversed[a] = false;
        if(a < 4) RightSide[a] = false;
        else RightSide[a] = true;
    }
}

JaguarDrive::~JaguarDrive()
{
    for(int a = 0;a < 8;a += 1)
    {
        if(Jaguar[a] != 0) Jaguar[a]->Set(0); //Stop Jaguars on Destruction
    }
}

void JaguarDrive::SetReverse()
{
    for(int a = 0;a < 8;a += 1)
    {
        if(Reversed[a]) Reversed[a] = false;
        else Reversed[a] = true;
    }
}

void JaguarDrive::SetReverse(int id)
{
    if(Reversed[id]) Reversed[id] = false;
    else Reversed[id] = true;
}

void JaguarDrive::Update()
{
    if(VariablesEnabled)
    {
        for(var a = 0;a < 8;a += 1)
        {
            if(Jaguar[a] != 0 && Variables[a] != 0)
            {
                if(!Reversed[a]) Jaguar[a]->Set(*Variable[a]);
                else Jaguar[a]->Set(-*Variable[a]);
            }
        }
    }
}

void JaguarDrive::Move(double speed,double turn)
{
    double rght,left;
    
    //Set Max/Min
    if(speed > 1) speed = 1;
    if(speed < -1) speed = -1;
    if(turn > 1) turn = 1;
    if(turn < -1) turn = -1;
    
    rght = speed - turn/2;
    left = speed + turn/2;
    
    if(left > 1)
    {
        rght -= (left - 1);
        left = 1;
    }

    if(rght < -1)
    {
        left += (rght + 1);
        rght = -1;
    }

    for(int a = 0;a < 8;a += 1)
    {
        if(Jaguar[a] != 0)
        {
            if(RightSide[a])
            {
                if(!Reversed[a]) Jaguar[a]->Set(rght);
                else Jaguar[a]->Set(-rght);
            }
            else
            {
                if(!Reversed[a]) Jaguar[a]->Set(left);
                else Jaguar[a]->Set(left);
            }
        }
    }
}

void JaguarDrive::SetRightSide(double speed)
{
    //Set Max/Min
    if(speed > 1) speed = 1;
    if(speed < -1) speed = -1;
    
    for(int a = 0;a < 8;a += 1)
    {
        if(Jaguar[a] != 0)
        {
            if(RightSide[a])
            {
                if(!Reversed[a]) Jaguar[a]->Set(speed);
                else Jaguar[a]->Set(-speed);
            }
        }
    }
}

void JaguarDrive::SetLeftSide(double speed)
{
    //Set Max/Min
    if(speed > 1) speed = 1;
    if(speed < -1) speed = -1;
    
    for(int a = 0;a < 8;a += 1)
    {
        if(Jaguar[a] != 0)
        {
            if(!RightSide[a])
            {
                if(!Reversed[a]) Jaguar[a]->Set(speed);
                else Jaguar[a]->Set(-speed);
            }
        }
    }
}
