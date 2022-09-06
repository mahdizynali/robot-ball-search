#ifndef COVERAGE_HPP
#define COVERAGE_HPP

#include "Configs.hpp"

class Coverage {
    private:
        int ownYLeftLine;
        int ownYRightLine;
        int oppYLeftLine;
        int oppYRightLine;
        int upXLeftLine;
        int upXRightLine;
        int downXLeftLine;
        int downXRightLine;

        Point ownBorderLeft;
        Point ownBorderRight;
        Point oppBorderLeft;
        Point oppBorderRight;
        Point ownDistPointLeft;
        Point ownDistPointRight;
        Point oppDistPointLeft;
        Point oppDistPointRight;
        Point upDistPointLeft;
        Point upDistPointRight;
        Point downDistPointLeft;
        Point downDistPointRight;

        bool state;
        int moveMouse;
        
    public:
        double lineGradientY(const Point2f &, const Point2f &, double);
        double lineGradientX(const Point2f &, const Point2f &, double);
        double pointDistance(const Point2f &, const Point2f &);
        double pointAngle(const Point2f &, const Point2f &);
        double lineAngle(const double &, const double &);
        void drawLines(const Mat &,const Point &, const Point &, double);
        void checkCoverage();
        void setState(bool);
        bool getState();
        double pixel2Meter(int pixel);
        vector <double> tangentCircle(const Point2f &, const Point2f &, double);
};

#endif // COVERAGE_HPP