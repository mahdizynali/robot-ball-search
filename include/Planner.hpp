#ifndef PLANNER_HPP
#define PLANNER_HPP

#include "Configs.hpp"

//-- Planner Class
class Planner {
    private:
        int state;
        cv::Point2d destination;
    public:
        Planner();
        void setState(int st);
        void setDestination(cv::Point2d dest);
        int getState();
        std::vector<double> update(cv::Point3d robotPose);
};

#endif // PLANNER_HPP
