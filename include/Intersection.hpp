#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include "Configs.hpp"
#define MAX_POINT_POLYGON 64

class polygon {

	private : 
	
		Point polygonPoints[MAX_POINT_POLYGON];
		int polygonNumber;

	public :

		//polygon(int);
		void clear();
		void add(const Point2d &);
		void push_back(const Point2d &);
		int size() const;
		Point getCenter() const;
		Point& operator[](int);
		void pointsOrdered();
		//float area() const;
		float computeArea();
		//bool pointIsInPolygon(Point) const;
		bool pointInPolygon(Point2d ,const Point2d * ,int);
		double distPoint(Point ,Point);
		bool segementIntersection(Point2d ,Point2d ,Point2d ,Point2d ,Point2d *);
		void intersectPolygon( const Point2d *, int, const Point2d *, int, polygon &);
		void intersectPolygonSHPC(const polygon *, const polygon *, polygon *) ;

static int comp_point_with_angle(const void * ,const void *);
static inline int cross(const Point* ,const Point* );
static inline Point* vsub(const Point* ,const Point* , Point*);
static int line_sect(const Point* ,const Point* ,const Point* , const Point*, Point*);
static int left_of(const Point* ,const Point* ,const Point*);
static void poly_edge_clip(const polygon* ,const  Point* ,const  Point* , int, polygon*);
static int poly_winding(const polygon*);

};


#endif //