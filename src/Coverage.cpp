#include "include/Coverage.hpp"

void Coverage::setState (bool st) {
    state = st;
}

bool Coverage::getState () {
    return state;
}

// calculate amount of y by gradient of line
double Coverage::lineGradientY (const Point2f &point1, const Point2f &point2, double x) {
    // y = ax + b
    double gradient = (point2.y - point1.y) / (point2.x - point1.x); // equal a
    double intercept = point1.y - gradient * (point1.x); // equal b
    return (int)(gradient * x + intercept); // equal y
}

// calculate amount of x by gradient of line
double Coverage::lineGradientX (const Point2f &point1, const Point2f &point2, double y) {
    // y = ax + b
    double gradient = (point2.y - point1.y) / (point2.x - point1.x); // equal a
    double intercept = point1.y - gradient * (point1.x); // equal b
    return (int)((y - intercept) / gradient); // equal X
}

// calculate two point distance
double Coverage::pointDistance (const Point2f &point1, const Point2f &point2) {

    return sqrt(pow((point1.x - point2.x), 2) + pow((point1.y - point2.y), 2));
}

// calculate two point angle
double Coverage::pointAngle (const Point2f &point1, const Point2f &point2) {

    return atan2((point2.y - point1.y) , (point2.x - point1.x));
}

// calculate angle between two line
double Coverage::lineAngle (const double &gradient1, const double &gradient2) {

    //tan A = |(m-m’) / (1 + mm’ )|
    return atan(abs((gradient1-gradient2) / (1 + (gradient1*gradient2))));
}

// draw lines by Points positions
void Coverage::drawLines (const Mat &field, const Point &mousePoint, const Point &agentCenter ,double radius) {

    ownBorderLeft = Point(fieldPadding * modelScale, (windowWidth - goalWidth) * half * modelScale);
    ownBorderRight = Point(fieldPadding * modelScale, (windowWidth + goalWidth) * half * modelScale);
    oppBorderLeft = Point((windowLength - fieldPadding) * modelScale, (windowWidth - goalWidth) * half * modelScale);
    oppBorderRight = Point((windowLength - fieldPadding) * modelScale, (windowWidth + goalWidth) * half * modelScale);

    circle(field, ownBorderLeft, middleCircle1 * modelScale * half, Scalar(200, 200, 100), -1, 8, 0);
    circle(field, ownBorderRight, middleCircle1 * modelScale * half, Scalar(200, 200, 100), -1, 8, 0);    
    circle(field, oppBorderLeft, middleCircle1 * modelScale * half, Scalar(150, 150, 150), -1, 8, 0);
    circle(field, oppBorderRight, middleCircle1 * modelScale * half, Scalar(150, 150, 150), -1, 8, 0);    

    vector <double> tangentPoints (4, 0);
    tangentPoints = tangentCircle (mousePoint,agentCenter, radius);

    Point left,right;
    left.x = tangentPoints[0];
    left.y = tangentPoints[1];
    right.x = tangentPoints[2];
    right.y = tangentPoints[3];

    double theta = pointAngle(mousePoint, agentCenter);

    // Avoid beging infinit
    if (mousePoint.x == left.x)
        left.x += 1;
    else if (mousePoint.x == right.x)
        right.x += 1;

    // localization of the drawing points
    ownYLeftLine =  lineGradientY (mousePoint, left, fieldPadding * modelScale);
    ownYRightLine = lineGradientY (mousePoint, right, fieldPadding * modelScale);
    //avoid being the same result as down one
    if(theta >= 1.2 && theta <= 1.75){
        ownYLeftLine = abs(ownYLeftLine);
        ownYRightLine = abs(ownYRightLine);
    }
    ownDistPointLeft = Point(fieldPadding * modelScale, ownYLeftLine);
    ownDistPointRight = Point(fieldPadding * modelScale, ownYRightLine);

    oppYLeftLine =  lineGradientY (mousePoint, left, (windowLength - fieldPadding) * modelScale);
    oppYRightLine = lineGradientY (mousePoint, right, (windowLength - fieldPadding) * modelScale);
    //avoid being the same result as down one
    if(theta >= 1.2 && theta <= 1.75){
        oppYLeftLine = abs(oppYLeftLine);
        oppYRightLine = abs(oppYRightLine);
    }
    oppDistPointLeft = Point((windowLength - fieldPadding) * modelScale, oppYLeftLine);
    oppDistPointRight = Point((windowLength - fieldPadding) * modelScale, oppYRightLine);

    upXLeftLine =  lineGradientX (mousePoint, left, fieldPadding * modelScale);
    upXRightLine = lineGradientX (mousePoint, right, fieldPadding * modelScale);
    upDistPointLeft = Point(upXLeftLine ,fieldPadding * modelScale);
    upDistPointRight = Point(upXRightLine ,fieldPadding * modelScale); 

    downXLeftLine =  lineGradientX (mousePoint, left, (fieldPadding + fieldWidth) * modelScale);
    downXRightLine = lineGradientX (mousePoint, right, (fieldPadding + fieldWidth) * modelScale);
    downDistPointLeft = Point(downXLeftLine ,(fieldPadding + fieldWidth) * modelScale);
    downDistPointRight = Point(downXRightLine ,(fieldPadding + fieldWidth) * modelScale); 
    cout<<"\n============\n";      
    //===================================
    circle(field, mousePoint, middleCircle1 * modelScale * half, Scalar(100,100,250), -1, 8, 0);

    if (state == 1) {

        line(field, mousePoint, left, Scalar(100, 100, 100), 2, 8, 0);
        line(field, mousePoint, right, Scalar(100, 100, 100), 2, 8, 0);

        if (ownYRightLine <= fieldPadding * modelScale) {
            line(field, left, upDistPointLeft, Scalar(100, 100, 100), 2, 8, 0);
            line(field, right, upDistPointRight, Scalar(100, 100, 100), 2, 8, 0); 

        }

        else if (ownYLeftLine >= (fieldPadding + fieldWidth) * modelScale) {
            line(field, left, downDistPointLeft, Scalar(100, 100, 100), 2, 8, 0);
            line(field, right, downDistPointRight, Scalar(100, 100, 100), 2, 8, 0); 
        }

        else if (ownYLeftLine <= fieldPadding * modelScale) {
            line(field, left, upDistPointLeft, Scalar(100, 100, 100), 2, 8, 0);
            line(field, right, ownDistPointRight, Scalar(100, 100, 100), 2, 8, 0); 
        }

        else if (ownYRightLine >= (fieldPadding + fieldWidth) * modelScale) {
            line(field, left, ownDistPointLeft, Scalar(100, 100, 100), 2, 8, 0);
            line(field, right, downDistPointRight, Scalar(100, 100, 100), 2, 8, 0); 
        }
        
        else {
            line(field, left, ownDistPointLeft, Scalar(100, 100, 100), 2, 8, 0);
            line(field, right, ownDistPointRight, Scalar(100, 100, 100), 2, 8, 0); 
        }
        checkCoverage();
    } 

    else {

        line(field, mousePoint, left, Scalar(100, 100, 100), 2, 8, 0);
        line(field, mousePoint, right, Scalar(100, 100, 100), 2, 8, 0);                 

        if (oppYLeftLine <= fieldPadding * modelScale) {
            line(field, left, upDistPointLeft, Scalar(100, 100, 100), 2, 8, 0);
            line(field, right, upDistPointRight, Scalar(100, 100, 100), 2, 8, 0); 
        }

        else if (oppYRightLine >= (fieldPadding + fieldWidth) * modelScale) {
            line(field, left, downDistPointLeft, Scalar(100, 100, 100), 2, 8, 0);
            line(field, right, downDistPointRight, Scalar(100, 100, 100), 2, 8, 0); 
        }

        else if (oppYRightLine <= fieldPadding * modelScale) {
            line(field, left, oppDistPointLeft, Scalar(100, 100, 100), 2, 8, 0);
            line(field, right, upDistPointRight, Scalar(100, 100, 100), 2, 8, 0); 
        }

        else if (oppYLeftLine >= (fieldPadding + fieldWidth) * modelScale) {
            line(field, left, downDistPointLeft, Scalar(100, 100, 100), 2, 8, 0);
            line(field, right, oppDistPointRight, Scalar(100, 100, 100), 2, 8, 0); 
        }

        else {
            line(field, left, oppDistPointLeft, Scalar(100, 100, 100), 2, 8, 0);
            line(field, right, oppDistPointRight, Scalar(100, 100, 100), 2, 8, 0);
        }
        checkCoverage();
    }
}

//checking amount of robot coverage
void Coverage::checkCoverage () {

    double leftPointMeter;
    double rightPointMeter;
    double meter = 0;
    int pixel = 0;

    if(state == 1) {

        if (ownDistPointLeft.y < ownBorderLeft.y || ownDistPointRight.y > ownBorderRight.y) {
            cout<<"Outside of goals !!"<<endl;
        }
        else if (ownYLeftLine > ownBorderLeft.y && ownYRightLine > ownBorderRight.y) {

            leftPointMeter = pixel2Meter (ownDistPointLeft.y);
            rightPointMeter = pixel2Meter (ownBorderRight.y);
            meter = abs(leftPointMeter - rightPointMeter);
            pixel = abs(ownDistPointLeft.y - ownBorderRight.y);
        }
        else if (ownYLeftLine < ownBorderLeft.y && ownYRightLine < ownBorderRight.y) {

            leftPointMeter = pixel2Meter (ownBorderLeft.y);
            rightPointMeter = pixel2Meter (ownDistPointRight.y);
            meter = abs(leftPointMeter - rightPointMeter);
            pixel = abs(ownBorderLeft.y - ownDistPointRight.y);
        }
        else {
            leftPointMeter = pixel2Meter (ownDistPointLeft.y);
            rightPointMeter = pixel2Meter (ownDistPointRight.y);
            meter = abs(leftPointMeter - rightPointMeter);
            pixel = abs(ownDistPointLeft.y - ownDistPointRight.y);
        }
        cout<< "Own goal coverage : "<< meter << " meter" << endl;    
        cout<< "Own goal coverage : "<< pixel << " pixel" << endl;
        cout<< "------------------\n";
    }
    else {

        if (oppDistPointLeft.y < oppBorderLeft.y || oppDistPointRight.y > oppBorderRight.y) {
            cout<<"Outside of goals !!"<<endl;
        }
        else if (oppYLeftLine > oppBorderLeft.y && oppYRightLine > oppBorderRight.y) {

            leftPointMeter = pixel2Meter (oppDistPointLeft.y);
            rightPointMeter = pixel2Meter (oppBorderRight.y);
            meter = abs(leftPointMeter - rightPointMeter);
            pixel = abs(oppDistPointLeft.y - oppBorderRight.y);
        }
        else if (oppYLeftLine < oppBorderLeft.y && oppYRightLine < oppBorderRight.y) {

            leftPointMeter = pixel2Meter (oppBorderLeft.y);
            rightPointMeter = pixel2Meter (oppDistPointRight.y);
            meter = abs(leftPointMeter - rightPointMeter);
            pixel = abs(oppBorderLeft.y - oppDistPointRight.y);
        }
        else {
            leftPointMeter = pixel2Meter (oppDistPointLeft.y);
            rightPointMeter = pixel2Meter (oppDistPointRight.y);
            meter = abs(leftPointMeter - rightPointMeter);
            pixel = abs(oppDistPointLeft.y - oppDistPointRight.y);
        }
        cout<< "opp goal coverage : " << meter << " meter" << endl;    
        cout<< "opp goal coverage : " << pixel << " pixel" << endl;
        cout<< "------------------\n";       
    }
}

// tranform pixel to the meter
double Coverage::pixel2Meter (int pixel) {

    return ((pixel - (windowWidth * modelScale / 2)) / modelScale);
}

// find tangent ponts on circle
vector <double> Coverage::tangentCircle (const Point2f &mouse, const Point2f &center, double radius) {

    vector <double> points (4,0);

    // Line between point mouse and center
    double directLine = sqrt(pow((mouse.x - center.x), 2) + pow((mouse.y - center.y), 2));
    
    // angle of point mouse and center
    double directAngle = pointAngle(mouse, center);

    // angle between radius and directLine
    double theta = acos(radius / directLine);
    
    // direction angle of point tangent 1 and center
    double d1 = directAngle + theta;
    
    // direction angle of point tangent 2 and center
    double d2 = directAngle - theta;

    points[0] = (int)(center.x + radius * cos(d1));
    points[1] = (int)(center.y + radius * sin(d1));

    points[2] = (int)(center.x + radius * cos(d2));
    points[3] = (int)(center.y + radius * sin(d2));

    return points;
}
