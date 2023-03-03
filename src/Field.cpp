#include "include/Field.hpp"

//---------------------------
//--| Robocup Field Rules |--
//---------------------------
//-- Field Width & Length
double fieldWidth = 6;
double fieldLength = 9;
//-- Field Padding (in Meter)
double fieldPadding = 1;
//-- Penalty Area (in Meter)
double penaltyAreaWidth = 5;
double penaltyAreaLength = 2;
double penaltyMarkDistance = 1.5;
double penaltyMarkRadius = 0.11;
//-- Goal Area (in Meter)
double goalAreaWidth = 3;
double goalAreaLength = 1;
//-- Goal (in Meter)
double goalWidth = 2.6;
double goalDepth = 0.6;
//-- Middle Circle Diameter (in Meter)
double middleCircle1 = 0.11;
double middleCircle2 = 1.5 ;
//-- Middle Line Size
double middleLine = 6;

//--------------------
//--| Mathematical |--
//--------------------
//-- Half
double half = 0.5;

//------------------------------
//--| Playground Window Size |--
//------------------------------
double windowWidth = (fieldWidth + 2 * fieldPadding);
double windowLength = (fieldLength + 2 * fieldPadding);

//-- Constructor to Set Default Values
Field::Field(){
    double Scale = modelScale * 12;
    if (Scale >= 2500){
        fontSize = 1.7;
        lineSize = 4;
    }
    else if (Scale > 1550 && Scale < 2500){
        fontSize = 1.2;
        lineSize = 4;
    }
    else{
        fontSize = 0.6;
        lineSize = 1;
    }
}

//-- Makes the Field
void Field::fieldCreate(){
    //-- Creates the Window
    Ground = Mat(windowWidth * modelScale, windowLength * modelScale, CV_8UC3, Scalar(fieldBGBlue, fieldBGGreen, fieldBGRed));
    //--------------
    //--| Points |--
    //--------------
    //-- Ground Corners
    Point topLeft(0, 0);
    Point downRight(windowLength * modelScale - lineSize, windowWidth * modelScale - lineSize);
    //-- Field Corners, Middle Line and Middle Circle
    Point fieldCorner1(fieldPadding * modelScale, fieldPadding * modelScale);
    Point fieldCorner2((fieldPadding + fieldLength) * modelScale, (fieldPadding + fieldWidth) * modelScale);
    Point middleLineTop((windowLength * half) * modelScale, fieldPadding * modelScale);
    Point middleLineDown((windowLength * half) * modelScale, (fieldPadding + middleLine) * modelScale);
    Point middle((fieldPadding + fieldLength * half) * modelScale, (fieldPadding + fieldWidth * half) * modelScale);
    //-- Penalty Areas Corners
    //- Team :
    Point penaltyCornerTop1(fieldPadding * modelScale, (windowWidth - penaltyAreaWidth) * half * modelScale);
    Point penaltyCornerDown1((fieldPadding + penaltyAreaLength) * modelScale, (windowWidth + penaltyAreaWidth) * half * modelScale);
    //- Enemy :
    Point penaltyCornerTop2((windowLength - fieldPadding) * modelScale, (windowWidth - penaltyAreaWidth) * half * modelScale);
    Point penaltyCornerDown2((windowLength - fieldPadding - penaltyAreaLength) * modelScale, (windowWidth + penaltyAreaWidth) * half * modelScale);
    //-- Goal Areas Corners
    //- Team :
    Point goalAreaCornerTop1(fieldPadding * modelScale, (windowWidth - goalAreaWidth) * half * modelScale);
    Point goalAreaCornerDown1((fieldPadding + goalAreaLength) * modelScale, (windowWidth + goalAreaWidth) * half * modelScale);
    //- Enemy :
    Point goalAreaCornerTop2((windowLength - fieldPadding) * modelScale, (windowWidth - goalAreaWidth) * half * modelScale);
    Point goalAreaCornerDown2((windowLength - fieldPadding - goalAreaLength) * modelScale, (windowWidth + goalAreaWidth) * half * modelScale);
    //-- Goals Corners
    //- Team :
    Point goalCornerTop1(fieldPadding * modelScale, (windowWidth - goalWidth) * half * modelScale);
    Point goalCornerDown1((fieldPadding - goalDepth) * modelScale, (windowWidth + goalWidth) * half * modelScale);
    //- Enemy :
    Point goalCornerTop2((windowLength - fieldPadding) * modelScale, (windowWidth - goalWidth) * half * modelScale);
    Point goalCornerDown2((windowLength - fieldPadding + goalDepth) * modelScale, (windowWidth + goalWidth) * half * modelScale);
    //-- Penalty Marks
    Point penaltyMarkRight((fieldPadding + penaltyMarkDistance) * modelScale, windowWidth * half * modelScale);
    Point penaltyMarkLeft((windowLength - fieldPadding - penaltyMarkDistance) * modelScale, windowWidth * half * modelScale);
   
    //------------------------
    //--| Draw with Points |--
    //------------------------
    //-- Ground
    rectangle(Ground, topLeft, downRight, Scalar(fieldLineBlue, fieldLineGreen, fieldLineRed), lineSize, 8, 0);
    //-- Field
    rectangle(Ground, fieldCorner1, fieldCorner2, Scalar(fieldLineBlue, fieldLineGreen, fieldLineRed), lineSize, 8, 0);
    //-- Middle
    line(Ground, middleLineTop, middleLineDown, Scalar(fieldLineBlue, fieldLineGreen, fieldLineRed), lineSize, 8, 0);
    circle(Ground, middle, middleCircle1 * modelScale * half, Scalar(fieldLineBlue, fieldLineGreen, fieldLineRed), -1, 8, 0);
    circle(Ground, middle, middleCircle2 * modelScale * half, Scalar(fieldLineBlue, fieldLineGreen, fieldLineRed), lineSize, 8, 0);
    //-- Penalty Areas
    rectangle(Ground, penaltyCornerTop1, penaltyCornerDown1, Scalar(fieldLineBlue, fieldLineGreen, fieldLineRed), lineSize, 8, 0);
    rectangle(Ground, penaltyCornerTop2, penaltyCornerDown2, Scalar(fieldLineBlue, fieldLineGreen, fieldLineRed), lineSize, 8, 0);
    //-- Goals
    rectangle(Ground, goalCornerTop1, goalCornerDown1, Scalar(teamGoalBlue, teamGoalGreen, teamGoalRed), lineSize, 8, 0);
    rectangle(Ground, goalCornerTop2, goalCornerDown2, Scalar(enemyGoalBlue, enemyGoalGreen, enemyGoalRed), lineSize, 8, 0);
    //-- Goal Areas
    rectangle(Ground, goalAreaCornerTop1, goalAreaCornerDown1, Scalar(fieldLineBlue, fieldLineGreen, fieldLineRed), lineSize, 8, 0);
    rectangle(Ground, goalAreaCornerTop2, goalAreaCornerDown2, Scalar(fieldLineBlue, fieldLineGreen, fieldLineRed), lineSize, 8, 0);
    //-- Penalty Marks
    circle(Ground, penaltyMarkRight, penaltyMarkRadius * modelScale * half, Scalar(fieldLineBlue, fieldLineGreen, fieldLineRed), -1, 8, 0);
    circle(Ground, penaltyMarkLeft, penaltyMarkRadius * modelScale * half, Scalar(fieldLineBlue, fieldLineGreen, fieldLineRed), -1, 8, 0);

}

Mat Field::Access(){
    return Ground;
}

void Field :: Set (Point &agentCenter) {

    // Vec3b & clr = Ground.at<Vec3b>(agentCenter.x+100,agentCenter.y+100);
    // clr[0] = 140;
    // clr[1] = 100;
    // clr[2] = 13;

    Ground.at<Vec3b>(agentCenter.x,agentCenter.y)[0] = 100;
    Ground.at<Vec3b>(agentCenter.x,agentCenter.y)[1] = 150;
    Ground.at<Vec3b>(agentCenter.x,agentCenter.y)[3] = 10;
    circle(Ground, agentCenter, 10, Scalar(100, 150, 10), LINE_AA);

}





