#include "Util.hpp"

double modAngle(double theta) {
    if (theta < 0) {
        theta = theta + 2 * M_PI;
    }
    theta = fmod(theta, (2 * M_PI));
    if (theta >= M_PI) {
        theta -= 2 * M_PI;
    }
    return theta;
}

vector <double> poseGlobal(vector <double> pRelative, vector <double> pose) {
    vector <double> globalPose(3, 0);
    double ca = cos(pose[2]);
    double sa = sin(pose[2]);
    globalPose[0] = pose[0] + ca * pRelative[0] - sa * pRelative[1];
    globalPose[1] = pose[1] + sa * pRelative[0] + ca * pRelative[1];
    globalPose[2] = pose[2] + pRelative[2];
    return globalPose;
}

vector <double> poseRelative(vector <double> pGlobal, vector <double> pose) {
    vector <double> relativePose(3, 0);
    double ca = cos(pose[2]);
    double sa = sin(pose[2]);
    double pX = pGlobal[0] - pose[0];
    double pY = pGlobal[1] - pose[1];
    double pT = pGlobal[2] - pose[2];
    relativePose[0] = ca * pX + sa * pY;
    relativePose[1] = ca * pY - sa * pX;
    relativePose[2] = modAngle(pT);
    return relativePose;
}
