#pragma once
#include "support.h"

//finds the intersection between two 2D line segments l1 and l2
//however, this function fails if the lines don't intersect
//or are colinear
Point2D findIntersect(Line2D l1, Line2D l2);
void translatePoint3D(Point3D * point, Point3D translation);
void translateLines3D(Line3D lines[], int nOfLines, Point3D translation);

void rotatePoints3DX(Point3D * points, unsigned int nOfPoints, float angle);
void rotatePoints3DY(Point3D * points, unsigned int nOfPoints, float angle);
void rotatePoints3DZ(Point3D * points, unsigned int nOfPoints, float angle);