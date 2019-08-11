#define _USE_MATH_DEFINES

#include "linearmath.h"
#include "support.h"
#include <math.h>

Point2D findIntersect(Line2D l1, Line2D l2)
{
	Point2D intersect;

	Point2D pToq, r, s;
	float t;

	pToq = { l2.start.x - l1.start.x, l2.start.y - l1.start.y }; //vector from staring points of l1 to l2
	r = { l1.end.x - l1.start.x, l1.end.y - l1.start.y }; //vector from start to the end of l1
	s = { l2.end.x - l2.start.x, l2.end.y - l2.start.y }; //vector from start to the end of l2
	t = (pToq.x*s.y - pToq.y*s.x) / (r.x*s.y - r.y*s.x);

	//intersection point
	return { l1.start.x + t * r.x, l1.start.y + t * r.y };
}

void translatePoint3D(Point3D * point, Point3D translation)
{
	point->x += translation.x;
	point->y += translation.y;
	point->z += translation.z;
}

void translateLines3D(Line3D lines[], int nOfLines, Point3D translation)
{
	for (int i = 0; i < nOfLines; i++) {
		translatePoint3D(&lines[i].start, translation);
		translatePoint3D(&lines[i].end, translation);
	}
}

void rotatePoints3DZ(Point3D * points, unsigned int nOfPoints, float angle)
{
	float c = cos(M_PI*(angle / 180));
	float s = sin(M_PI*(angle / 180));
	for (int i = 0; i < nOfPoints; i++) {
		float x = points[i].x;
		points[i].x = c * x - s * points[i].y;
		points[i].y = s * x + c * points[i].y;
	}
}

void rotatePoints3DX(Point3D * points, unsigned int nOfPoints, float angle)
{
	float c = cos(M_PI*(angle / 180));
	float s = sin(M_PI*(angle / 180));
	for (int i = 0; i < nOfPoints; i++) {
		float z = points[i].z;
		points[i].z = c * z - s * points[i].y;
		points[i].y = s * z + c * points[i].y;
	}
}

void rotatePoints3DY(Point3D * points, unsigned int nOfPoints, float angle)
{
	float c = cos(M_PI*(angle / 180));
	float s = sin(M_PI*(angle / 180));
	for (int i = 0; i < nOfPoints; i++) {
		float x = points[i].x;
		points[i].x = c * x - s * points[i].z;
		points[i].z = s * x + c * points[i].z;
	}
}