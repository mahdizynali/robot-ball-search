#ifndef CONFIGS_HPP
#define CONFIGS_HPP
//-- Config File
//-- Don't Forget to Include This File

//-----------------
//--| Libraries |--
//-----------------
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>

#include <stdlib.h>
#include <time.h>

//--Name Spaces
using namespace std;
using namespace cv;
using namespace chrono;
using namespace this_thread;

//---------------------
//--| Model Configs |--
//---------------------
//-- Robot Size (in Meter) :
extern double robotSize;
extern double robotLineSize;
//-- Window Scale (in Pixels) :
//- for 3K Monitors := 222
//- for 2k Monitors := 180
//- for 1k Monitors := 140
extern double modelScale;
//-- Font Size Scale :
extern double fontSize;
//-- Lines of Model Scale :
extern double lineSize;
//-- Blue, Green, Red
extern double fieldLineBlue;
extern double fieldLineGreen;
extern double fieldLineRed;
extern double fieldBGBlue;
extern double fieldBGGreen;
extern double fieldBGRed;
extern double enemyGoalBlue;
extern double enemyGoalGreen;
extern double enemyGoalRed;
extern double teamGoalBlue;
extern double teamGoalGreen;
extern double teamGoalRed;
//-- Refresh Rate (ms)
extern double refreshRate;
//-- Mouse Click Flag
extern int mouseFlag;
//-- Rotation Value with Mouse
extern double mouseRotationValue;
//-- Click Area Radius
extern double clickAreaRadius;

//---------------------
//--| Robot Configs |--
//---------------------
//-- Sharpness of Robot (in Degree) :
extern double robotSharpness;
//-- Robot Spawining Position (According to Scale in Meter) :
extern double xSpawn;
extern double ySpawn;
extern double rotationSpawn;
//-- Robot Colors
extern double robotBlue;
extern double robotGreen;
extern double robotRed;
//-- Color Value When Clicked
extern int clickedColorValue;
//-- Speed Increase/Decrease Value
extern double moveSpeedValue;
extern double rotateSpeedValue;

//-------------------------
//--| Movements Configs |--
//-------------------------
//-- Robot Move (in Pixels)
extern double robotMoveValue;
//-- Robot Rotation (in Degree) -- Should be 1
extern double robotRotationValue;
//-- Max Movement Speed (in m/s)
extern double maxMovementSpeed;
//-- Max Rotation Speed (in Degree/s)
extern double maxRotationSpeed;

//---------------------------
//--| Robocup Field Rules |--
//---------------------------
//-- Field Width & Length
extern double fieldWidth;
extern double fieldLength;
//-- Field Padding (in Meter)
extern double fieldPadding;
//-- Penalty Area (in Meter)
extern double penaltyAreaWidth;
extern double penaltyAreaLength;
extern double penaltyMarkDistance;
extern double penaltyMarkRadius;
//-- Goal Area (in Meter)
extern double goalAreaWidth;
extern double goalAreaLength;
//-- Goal (in Meter)
extern double goalWidth;
extern double goalDepth;
//-- Middle Circle Diameter (in Meter)
extern double middleCircle1;
extern double middleCircle2;
//-- Middle Line Size
extern double middleLine;

//--------------------
//--| Mathematical |--
//--------------------
//-- Half
extern double half;
extern double rad;

//---------------------------------------
//--| Playground and Help Window Size |--
//---------------------------------------
extern double windowWidth;
extern double windowLength;

//---------------------------------
//--| Help Window Configuration |--
//---------------------------------
//-- Help Window Size
extern double helpWindowWidth;
extern double helpWindowLength;
//-- Activity Circle Colors and Attributes
extern int activityStateValue;
extern int stopStateValue;
extern int counter;
extern int state;
//-- Help Window Background Color Cnonfig
extern int windowColorBlue;
extern int windowColorGreen;
extern int windowColorRed;
//-- Help Window Font Size
extern double helpWindowFontSize;
//-- Help Window Text Colors
extern int helpWindowTextBlue;
extern int helpWindowTextGreen;
extern int helpWindowTextRed;

#endif // CONFIGS_HPP