#include "Planner.hpp"
#include "Util.hpp"

Planner::Planner() {
    state = 0;
}

void Planner::setState(int st) {
    state = st;
}

void Planner::setDestination(cv::Point2d dest) {
    destination = dest;
}

int Planner::getState() {
    return state;
}

std::vector<double> Planner::update(cv::Point3d robotPose) {
    vector <double> posGlobal(3, 0);
    posGlobal[0] = destination.x;
    posGlobal[1] = destination.y;
    posGlobal[2] = 0;

    vector <double> robotPos(3, 0);
    robotPos[0] = robotPose.x;
    robotPos[1] = robotPose.y;
    robotPos[2] = robotPose.z;

    vector <double> relative = poseRelative(posGlobal, robotPos);
    std::vector<double> v(3, 0);

    // std::cout << "robot : " << robotPos[0] << " " << robotPos[1] << " " << robotPos[2] << std::endl;
    // std::cout << "posGlobal : " << posGlobal[0] << " " << posGlobal[1] << " " << posGlobal[2] << std::endl;
    // std::cout << "relative : " << relative[0] << " " << relative[1] << " " << relative[2] << std::endl;

    double result = sqrt(pow(relative[0], 2) + pow(relative[1], 2));
    v[0] = (relative[0] /result ) * maxMovementSpeed;
    v[1] = (relative[1] / result) * maxMovementSpeed;
    // v[2] = (relative[2] / M_PI) * maxRotationSpeed;
    v[2] = (atan2(relative[1], relative[0]) / M_PI) * maxRotationSpeed;

    if (result < 0.01) {
        state = 0;
    }

    return v;
}
