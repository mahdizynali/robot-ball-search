#ifndef BALLSEARCH_HPP
#define BALLSEARCH_HPP

#include "Configs.hpp"
#include "Intersection.hpp"

class ballSearch {

    private : 
        bool state;
        int directLine;
        int gridState = -1;
        int width, height;
        double stepWidth, stepHeight;
        Point upPoint,downPoint,distance,agentCenter,ball;
        polygon intersect;
        vector <vector<Point>> gridCenter;
    
    public :

        void drawGrid(const Mat &);
        void setGridState(int);
        int getGridState();
        void setState(bool);
        bool getState();
        void visibility(const Mat &, const Point &, double, const Point &);
        int pointFinder(const double &, const double &);
        double pointDistance(const Point2f &, const Point2f &);
        double pointAngle(const Point2f &, const Point2f &);
        vector <double> tangentCircle(const Point2f &, const Point2f &, double);
        Point2d pixel2Meter(Point pixel);
        void checkIntersect(const Mat &);

};

#endif // BALLSEARCH_HPP