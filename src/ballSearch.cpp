#include "include/ballSearch.hpp"

//================================================

// set the state of ball searching mod
void ballSearch :: setState (bool st) {
    state = st;
}

bool ballSearch :: getState () {
    return state;
}

//================================================

// set the state of grid lines
void ballSearch :: setGridState(int gr) {
    gridState *= gr;
}

int ballSearch :: getGridState() {
    return gridState;
}

//================================================

// find up & douwn amount of point positions of visibility
int ballSearch :: pointFinder(const double &theta, const double &directLine) {

    return (int)(directLine / (tan(theta)));
}

//================================================

// calculate two point distance
double ballSearch :: pointDistance (const Point2f &point1, const Point2f &point2) {

    return sqrt(pow((point1.x - point2.x), 2) + pow((point1.y - point2.y), 2));
}

//================================================

// calculate two point angle
double ballSearch :: pointAngle (const Point2f &point1, const Point2f &point2) {

    return atan2((point2.y - point1.y) , (point2.x - point1.x));
}

//================================================

// draw the lines of visibility
void ballSearch :: visibility (const Mat &field, const Point &ag, double robotTheta, const Point &bl) {

    agentCenter = ag;
    ball = bl;
    directLine = (1.5) * modelScale;
    distance = Point(agentCenter.x - (directLine * cos(robotTheta)), agentCenter.y + (directLine * sin(robotTheta)));
    
    rectangle(field, ball, Point(ball.x+10,ball.y-10), Scalar(10,10,200), FILLED);

    vector <double> tangentPoints (4, 0);
    tangentPoints = tangentCircle (distance,agentCenter, directLine / 2);

    upPoint.x   = tangentPoints[0];
    upPoint.y   = tangentPoints[1];
    downPoint.x = tangentPoints[2];
    downPoint.y = tangentPoints[3];

    line(field, agentCenter, distance, Scalar(100, 100, 200), 2, 8, 0);
    line(field, distance, upPoint, Scalar(100, 100, 200), 2, 8, 0);
    line(field, distance, downPoint, Scalar(100, 100, 200), 2, 8, 0);
    line(field, downPoint, agentCenter, Scalar(100, 100, 200), 2, 8, 0);
    line(field, upPoint, agentCenter, Scalar(100, 100, 200), 2, 8, 0);   

    checkIntersect(field); 
}

//================================================

void ballSearch :: drawGrid (const Mat &field) {

    width = (windowWidth - fieldPadding) * modelScale;
    height = (windowLength - fieldPadding) * modelScale;
    stepWidth = 0.30 * modelScale;
    stepHeight = 0.45 * modelScale;

    for (int i = (fieldPadding * modelScale) ; i < width; i += stepWidth) {
        line(field, Point((fieldPadding * modelScale), i), Point(height, i), Scalar(10, 30, 10));
        vector<Point>store;
        for (int j = (fieldPadding * modelScale) ; j < height ; j += stepHeight) {
                line(field, Point(j, (fieldPadding * modelScale)), Point(j, width), Scalar(10, 30, 10));                
                store.push_back(Point(j+stepHeight / 2, i+stepWidth / 2)); 
        }
        gridCenter.push_back(store);
    }

    // Point locate[1][4];
    // locate[0][0] = agentCenter;
    // locate[0][1] = upPoint;
    // locate[0][2] = distance;
    // locate[0][3] = downPoint;

    // const Point* ppt[1] = { locate[0] };
    // int npt[] = { 4 };
    // fillPoly(field, ppt, npt, 1, Scalar(50, 235, 75), LINE_AA);
}

//================================================

void ballSearch :: checkIntersect (const Mat &field) {

    polygon poly[3];

    poly[0].clear();	 
	poly[0].add(agentCenter);
	poly[0].add(upPoint);
	poly[0].add(distance);
	poly[0].add(downPoint);

    poly[1].clear();	 
	poly[1].add(ball);
    poly[1].add(Point(ball.x+10,ball.y));
    poly[1].add(Point(ball.x+10,ball.y-10));
    poly[1].add(Point(ball.x,ball.y-10));

    // vector<Point2d>clip(4,Point(0,0));
    // clip[0] = agentCenter;
    // clip[1] = upPoint;
    // clip[2] = distance;
    // clip[3] = downPoint;

    // vector<Point2d>sub(4,Point(0,0));
    // sub[0] = ball;
    // sub[1] = (Point(ball.x+10,ball.y));
    // sub[2] = (Point(ball.x+10,ball.y-10));
    // sub[3] = (Point(ball.x,ball.y-10));
    
    double surround = 0;
    //vector <Point> visited;
    for(int i = 0; i <= 19; i++) {
        for(int j = 0; j <= 19 ; j++) {
            surround= sqrt(pow((agentCenter.x - gridCenter[i][j].x), 2) + pow((agentCenter.y - gridCenter[i][j].y), 2));
            if(surround <= directLine) {
                //visited.push_back(gridCenter[i][j]);
                circle(field, gridCenter[i][j], 1, Scalar(200,200,200), 2, 8, 0); 

                poly[2].clear();
                //up left
                poly[2].add(Point2d(gridCenter[i][j].x-(stepHeight/2),gridCenter[i][j].y-(stepWidth/2)));
                //up right
                poly[2].add(Point2d(gridCenter[i][j].x+(stepHeight/2),gridCenter[i][j].y-(stepWidth/2)));
                //down right
                poly[2].add(Point2d(gridCenter[i][j].x+(stepHeight/2),gridCenter[i][j].y+(stepWidth/2)));
                //down left
                poly[2].add(Point2d(gridCenter[i][j].x-(stepHeight/2),gridCenter[i][j].y+(stepWidth/2)));       
            
                intersect.intersectPolygonSHPC(& poly[0],& poly[2],& intersect);
                double area = 0.001;
                area = intersect.computeArea() / (modelScale*modelScale);
                if( area >= 0.135 ) {
                    visited[i][j] = '1'; 
                    rectangle(field, poly[2][0], poly[2][2], Scalar(1,200,1), FILLED);
                }
            }
        }
    }

    intersect.intersectPolygonSHPC(& poly[1],& poly[0],& intersect);
    //intersect.intersectPolygon(sub,4,clip,4,intersect);

    bool detect = intersect.computeArea();
    double area = 0.001;
    if( detect ) {
        area = intersect.computeArea() / (modelScale*modelScale);
        cout<<"detected !!\n";
        cout<< "area : " <<area << " m^2" <<endl;
        cout<<"=======\n";
    }
    else {
        cout<<"finding ball...\n\n";
    }
    visit();
}

//================================================
// display the visited nodes
void ballSearch :: visit () {

    for(int i = 0; i <= 19; i++) {
        for(int j = 0; j <= 19 ; j++) 
            cout<< visited[i][j] << " ";
        cout<<endl;
    }
}
//================================================

// find tangent ponts on circle of visibility
vector <double> ballSearch :: tangentCircle (const Point2f &distance, const Point2f &center, double radius) {

    vector <double> points (4,0);
    
    // angle of point mouse and center
    double directAngle = pointAngle(distance, center);

    // angle between radius and directLine
    double theta = acos(radius / directLine);
    //double theta = M_PI_2;
    // direction angle of point tangent 1 and center
    double d1 = directAngle + theta;
    
    // direction angle of point tangent 2 and center
    double d2 = directAngle - theta;

    points[0] = (int)(distance.x + radius * cos(d1));
    points[1] = (int)(distance.y + radius * sin(d1));

    points[2] = (int)(distance.x + radius * cos(d2));
    points[3] = (int)(distance.y + radius * sin(d2));

    return points;
}

//================================================

Point2d ballSearch::pixel2Meter(cv::Point pixel) {
    cv::Point2d out;
    out.x = -(pixel.x - (windowLength * modelScale / 2)) / modelScale;
    out.y = (pixel.y - (windowWidth * modelScale / 2)) / modelScale;
    return out;
}