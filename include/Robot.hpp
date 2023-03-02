#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "Configs.hpp"

//-- Robot Class
class Robot {
    private:
        double x;
        double y;
        double theta;
        int checkValue;
        string errorInfo;
        double vX;
        double vY;
        double vTheta;
        double tempX;
        double tempY;
        double tempTheta;
        double tempVX;
        double tempVY;
        double tempVTheta;
    public:
        //-- Config Robot's Spawn Position
        void setPosition(double, double, double);
        //-- Stores Last Position Before Updating Window
        void storePosition(double, double, double, double, double, double);
        //-- Position Accessors
        double accessX();
        double accessY();
        double accessTheta();
        double accessVX();
        double accessVY();
        double accessVTheta();
        void setX(double);
        void setY(double);
        void setTheta(double);
        //-- Border Impact Check
        int borderCheck();
        void resetCheck();
        //-- Error Output
        string error();
        //-- Seek Movement and Rotation Changes
        int state();
        //-- Set Robot's Velocity (Movement Velocity, Rotation Velocity)
        void setVelocity(double, double, double);
        void update();
};

#endif // ROBOT_HPP
