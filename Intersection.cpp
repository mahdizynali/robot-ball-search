#include "Intersection.hpp"

struct PointAngle{
	Point p;
	float angle;
};

//======================================
// polygon :: polygon (int num = 0 ) { 

// 	if(num >= 0 && num < MAX_POINT_POLYGON); 
// 	polygonNumber = num;
// }

//======================================
void polygon :: clear () { 
	polygonNumber = 0; 
}

//======================================
void polygon :: add (const Point2d &p) {
	if(polygonNumber < MAX_POINT_POLYGON) 
		polygonPoints[polygonNumber++] = p;
}

//======================================
void polygon :: push_back (const Point2d &p) {
	add(p);
}

//======================================
int polygon :: size () const {
	return polygonNumber;
}

//======================================
Point polygon :: getCenter () const {
	Point center;
	center.x = 0;
	center.y = 0;
	for (int i = 0 ; i < polygonNumber ; i++ ) {
		center.x += polygonPoints[i].x;
		center.y += polygonPoints[i].y;
	}
	center.x /= polygonNumber;
	center.y /= polygonNumber;
	return center;
}

//======================================
Point & polygon ::  operator [] (int index) {
	assert(index >= 0 && index < polygonNumber); 
		return polygonPoints[index];
}

//======================================
void polygon :: pointsOrdered () {
	if( polygonNumber <= 0) return;
	Point center = getCenter();
	PointAngle pc[MAX_POINT_POLYGON];
	for (int i = 0 ; i < polygonNumber ; i++ ) {
		pc[i].p.x = polygonPoints[i].x;
		pc[i].p.y = polygonPoints[i].y;
		pc[i].angle = atan2f((float)(polygonPoints[i].y - center.y),(float)(polygonPoints[i].x - center.x));
	}
	qsort(pc,polygonNumber,sizeof(PointAngle),comp_point_with_angle);
	for (int i = 0 ; i < polygonNumber ; i++ ) {
		polygonPoints[i].x = pc[i].p.x;
		polygonPoints[i].y = pc[i].p.y;
	}
}

//======================================
// float polygon :: area () const {
// 	return computeArea(& polygonPoints,polygonNumber);
// }

float polygon :: computeArea () {
	float area0 = 0.f;
	for (int i = 0 ; i < polygonNumber ; i++ ) {
		int j = (i+1)%polygonNumber;
		area0 += polygonPoints[i].x * polygonPoints[j].y;
		area0 -= polygonPoints[i].y * polygonPoints[j].x;
	}
	return 0.5f * fabs(area0);
}

//======================================
// bool polygon :: pointIsInPolygon (Point point) const {
// 	return pointInPolygon(point, polygonPoints, polygonNumber);
// }

bool polygon :: pointInPolygon (Point2d p,const Point2d * points,int n) {
	int i, j ;
	bool c = false;
	for(i = 0, j = n - 1; i < n; j = i++) {
		if( ( (points[i].y >= p.y ) != (points[j].y >= p.y) ) &&
			(p.x <= (points[j].x - points[i].x) * (p.y - points[i].y) / (points[j].y - points[i].y) + points[i].x)
			)
			c = !c;
	}
	return c;
}
//======================================
double distPoint (Point p1,Point p2) { 
	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

//======================================
bool polygon :: segementIntersection (Point2d p0,Point2d p1,Point2d p2,Point2d p3,Point2d * intersection){
	Point2d s1, s2;
	s1 = Point2d(p1.x - p0.x, p1.y - p0.y);
	s2 = Point2d(p3.x - p2.x, p3.y - p2.y);

	float s10_x = p1.x - p0.x;
	float s10_y = p1.y - p0.y;
	float s32_x = p3.x - p2.x;
	float s32_y = p3.y - p2.y;
	float denom = s10_x * s32_y - s32_x * s10_y;

	if(denom == 0) {
		return false;
	}

	bool denom_positive = denom > 0;

	float s02_x = p0.x - p2.x;
	float s02_y = p0.y - p2.y;
	float s_numer = s10_x * s02_y - s10_y * s02_x;

	if((s_numer < 0.f) == denom_positive) {
		return false;
	}

	float t_numer = s32_x * s02_y - s32_y * s02_x;
	if((t_numer < 0) == denom_positive) {
		return false;
	}

	if((s_numer > denom) == denom_positive || (t_numer > denom) == denom_positive) {
		return false;
	}

	float t = t_numer / denom;

	*intersection = Point2d(p0.x + (t * s10_x), p0.y + (t * s10_y) );
	return true;
}


//======================================
void polygon :: intersectPolygon ( const Point2d * poly0, int size0,const Point2d * poly1,int size1, polygon & inter )  {
	inter.clear();
	for (int i = 0 ; i < size0 ;i++) {
		if( pointInPolygon(poly0[i],poly1,size1) ) {
			inter.add(poly0[i]);
		}
	}

	for (int i = 0 ; i < size1 ;i++) { 
		if( pointInPolygon(poly1[i],poly0,size0) ) 
			inter.add(poly1[i]);
	}

	for (int i = 0 ; i < size0 ;i++) {
		Point p0,p1,p2,p3;
		p0 = poly0[i];
		p1 = poly0[(i+1)%size0];
		for (int j = 0 ; j < size1 ;j++) {
			p2 = poly1[j];
			p3 = poly1[(j+1)%size1];
			Point2d pinter;
			if(segementIntersection(p0,p1,p2,p3,&pinter)) {
				inter.add(pinter);
			}
		}
	}
	inter.pointsOrdered();
}

//======================================
//---------------------------------------------------------------------------
//             SHPC :  Sutherland-Hodgeman-Polygon-Clipping Algorihtm
//---------------------------------------------------------------------------

void polygon :: intersectPolygonSHPC (const polygon * sub,const polygon* clip,polygon* res) {
	int i;
	polygon P1,P2;
	polygon * p1 = &P1;
	polygon * p2 = &P2;
	polygon * tmp ;

	int dir = poly_winding(clip);
	poly_edge_clip(sub, clip->polygonPoints + clip->polygonNumber - 1, clip->polygonPoints, dir, p2);
	for (i = 0; i < clip->polygonNumber - 1; i++) {
		tmp = p2; p2 = p1; p1 = tmp;
		if(p1->polygonNumber == 0) {
			p2->polygonNumber = 0;
			break;
		}
		poly_edge_clip(p1, clip->polygonPoints + i, clip->polygonPoints + i + 1, dir, p2);
	}
	res->clear();
	for (i = 0 ; i < p2->polygonNumber ; i++) res->add(p2->polygonPoints[i]);
}

//======================================
int polygon :: comp_point_with_angle (const void * a, const void * b) {
	if ( ((PointAngle*)a)->angle <  ((PointAngle*)b)->angle ) 
		return -1;
	else if ( ((PointAngle*)a)->angle > ((PointAngle*)b)->angle ) 
		return 1;
	else //if ( ((PointAngle*)a)->angle == ((PointAngle*)b)->angle ) return 0;
		return 0;
}
//======================================

inline int polygon :: cross(const Point* a,const Point* b) {
	return a->x * b->y - a->y * b->x;
}

inline Point* polygon :: vsub(const Point* a,const Point* b, Point* res) {
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	return res;
}

int polygon :: line_sect(const Point* x0,const Point* x1,const Point* y0,const Point* y1, Point* res) {
	Point dx, dy, d;
	vsub(x1, x0, &dx);
	vsub(y1, y0, &dy);
	vsub(x0, y0, &d);
	float dyx = (float)cross(&dy, &dx);
	if (!dyx) return 0;
	dyx = cross(&d, &dx) / dyx;
	if (dyx <= 0 || dyx >= 1) return 0;
	res->x = int(y0->x + dyx * dy.x);
	res->y = int(y0->y + dyx * dy.y);
	return 1;
}

int polygon :: left_of(const Point* a,const Point* b,const Point* c) {
	Point tmp1, tmp2;
	int x;
	vsub(b, a, &tmp1);
	vsub(c, b, &tmp2);
	x = cross(&tmp1, &tmp2);
	return x < 0 ? -1 : x > 0;
}

void polygon :: poly_edge_clip(const polygon* sub,const  Point* x0,const  Point* x1, int left, polygon* res) {
	int i, side0, side1;
	Point tmp;
	const Point* v0 = sub->polygonPoints + sub->polygonNumber - 1;
	const Point* v1;
	res->clear();

	side0 = left_of(x0, x1, v0);
	if (side0 != -left) res->add(*v0);

	for (i = 0; i < sub->polygonNumber; i++) {
		v1 = sub->polygonPoints + i;
		side1 = left_of(x0, x1, v1);
		if (side0 + side1 == 0 && side0)
			/* last point and current straddle the edge */
			if (line_sect(x0, x1, v0, v1, &tmp))
				res->add(tmp);
		if (i == sub->polygonNumber - 1) break;
		if (side1 != -left) res->add(*v1);
		v0 = v1;
		side0 = side1;
	}
}

int polygon :: poly_winding(const polygon* p) {
	return left_of(p->polygonPoints, p->polygonPoints + 1, p->polygonPoints + 2);
}



