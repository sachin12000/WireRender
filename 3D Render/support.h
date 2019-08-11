#pragma once
struct Point2D {
	float x;
	float y;
};

struct Point3D {
	float x;
	float y;
	float z;
};

struct Line2D {
	Point2D start;
	Point2D end;
};

struct Line3D {
	Point3D start;
	Point3D end;
};