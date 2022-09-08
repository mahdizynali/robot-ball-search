#ifndef WORLD_HPP
#define WORLD_HPP

//-- Includes Needed Files
#include "HelpWindow.hpp"
#include "Field.hpp"
#include "Robot.hpp"
#include "Planner.hpp"
#include "Coverage.hpp"
#include "ballSearch.hpp"

class World {
private:
    Field field;
    Robot robot;
    HelpWindow status;
    Mat realWorld;
    Planner planner;
    Coverage coverage;
    ballSearch bSearch;
    bool plannerMode;
    Point mousePoint;
    int coverageMode = -1;
    int ballSearchMode = -1;
    int randomX,randomY;
    Point agentCenter,agentDirection,agentRight,agentLeft;
    
public:
    World();
    int updateWindow();
    void create();
    static void mouseAttacher(int ,int ,int ,int ,void *);
    void Mouse(int ,int ,int ,int);
    cv::Point2d pixel2Meter(cv::Point pixel);
    cv::Point meter2Pixel(cv::Point2d meter);
    void cvg();
    void ball();
};

#endif // WORLD_HPP
