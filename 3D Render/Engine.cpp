#define _USE_MATH_DEFINES

#include "Engine.h"
#include "linearmath.h"
#include <math.h>

Point3D findzFarPlaneIntersect(Point3D *p, Point3D *p1) {
	Point3D delta_vector = { p1->x - p->x,p1->y - p->y,p1->z - p->z };
	float scaler = (-5 - p->z) / delta_vector.z;
	return { p->x + scaler * delta_vector.x, p->y + scaler * delta_vector.y, -5 };
}

Point3D findzIntersect(Point3D *p, Point3D *p1) {
	Point3D delta_vector = { p1->x - p->x,p1->y - p->y,p1->z - p->z };
	float scaler = (-1 - p->z) / delta_vector.z;
	return { p->x + scaler * delta_vector.x, p->y + scaler * delta_vector.y, -1 };
}

unsigned int RenderEngine::projectLines(Line3D lines[], unsigned int nOfLines, Line2D transformedLines[], float fov)
{
	float fov_factor = tan(M_PI*((fov / 2) / 180));
	float fov_factor_n = -fov_factor;
	unsigned int linesToDraw = 0;

	for (int i = 0; i < nOfLines; i++) {

		Point3D p, p1;
		p = lines[i].start; p1 = lines[i].end;  //two points of the start, p and the end of lines, p1
		float x, y, x1, y1;  //rasterized x,y coordinates of the lines

		//see if the line is clipped by the near plane
		if (p.z > -1) {
			if (p1.z > -1) {
				continue;  //line outside the viewing area, do not render
			}
			//if the point is behind near plane, then find intersection point where with near plane where
			//line would be cut off
			Point3D intersect = findzIntersect(&lines[i].start, &lines[i].end);
			x = intersect.x;  y = intersect.y;
		}
		else if (p.z < -5) {
			if (p1.z < -5) {
				continue;  //clipped
			}
			//if the point is behind near plane, then find intersection point where with near plane where
			//line would be cut off
			Point3D intersect = findzFarPlaneIntersect(&lines[i].start, &lines[i].end);
			x = intersect.x / 5;  y = intersect.y / 5;
		}
		else {
			x = -1 * p.x / p.z;
			y = -1 * p.y / p.z;
		}
		if (p1.z > -1) {
			//if the point is behind near plane, then find intersection point where with near plane where
			//line would be cut off
			Point3D intersect = findzIntersect(&lines[i].end, &lines[i].start);
			x1 = intersect.x;  y1 = intersect.y;
		}
		else if (p1.z < -5) {
			//if the point is behind near plane, then find intersection point where with near plane where
			//line would be cut off
			Point3D intersect = findzFarPlaneIntersect(&lines[i].end, &lines[i].start);
			x1 = intersect.x / 5;  y1 = intersect.y / 5;
		}
		else {
			x1 = -1 * p1.x / p1.z;
			y1 = -1 * p1.y / p1.z;
		}

		if (x > fov_factor) {
			if (x1 > fov_factor) {
				continue; //clipped
			}
			/**if the x coordinate is outside the right side of view area, then find the point at which it intersects with the
			plane**/
			float delta_x, delta_y, delta_z, f;
			delta_x = p1.x - p.x; delta_y = p1.y - p.y; delta_z = p1.z - p.z;
			f = -(p.x + fov_factor * p.z) / (delta_x + fov_factor * delta_z);
			y = -(p.y + f * delta_y) / (p.z + f * delta_z);  //y intersection point
			x = 1;  //x intersects with the plane
		}
		else if (x < fov_factor_n) {
			if (x1 < fov_factor_n) {
				continue; //clipped
			}
			float delta_x, delta_y, delta_z, f;
			delta_x = p1.x - p.x; delta_y = p1.y - p.y; delta_z = p1.z - p.z;
			f = -(p.x + fov_factor_n * p.z) / (delta_x + fov_factor_n * delta_z);
			y = -(p.y + f * delta_y) / (p.z + f * delta_z);  //y intersection point
			x = -1;  //x intersects with the plane
		}
		else {
			x /= fov_factor;
		}

		if (x1 > fov_factor) {
			float delta_x, delta_y, delta_z, f;
			delta_x = p.x - p1.x; delta_y = p.y - p1.y; delta_z = p.z - p1.z;
			f = -(p1.x + fov_factor * p1.z) / (delta_x + fov_factor * delta_z);
			y1 = -(p1.y + f * delta_y) / (p1.z + f * delta_z);  //y intersection point
			x1 = 1;  //x intersects with the plane
		}
		else if (x1 < fov_factor_n) {
			float delta_x, delta_y, delta_z, f;
			delta_x = p.x - p1.x; delta_y = p.y - p1.y; delta_z = p.z - p1.z;
			f = -(p1.x + fov_factor_n * p1.z) / (delta_x + fov_factor_n * delta_z);
			y1 = -(p1.y + f * delta_y) / (p1.z + f * delta_z);  //y intersection point
			x1 = -1;  //x intersects with the plane
		}
		else {
			x1 /= fov_factor;
		}

		if (y > fov_factor) {
			if (y1 > fov_factor) {
				continue; //clipped
			}
			float delta_x, delta_y, delta_z, f;
			delta_x = p1.x - p.x; delta_y = p1.y - p.y; delta_z = p1.z - p.z;
			f = -(p.y + fov_factor * p.z) / (delta_y + fov_factor * delta_z);
			x = -(p.x + f * delta_x) / (p.z + f * delta_z); x /= fov_factor;
			y = 1;
		}
		else if (y < fov_factor_n) {
			if (y1 < fov_factor_n) {
				continue; //clipped
			}
			float delta_x, delta_y, delta_z, f;
			delta_x = p1.x - p.x; delta_y = p1.y - p.y; delta_z = p1.z - p.z;
			f = -(p.y + fov_factor_n * p.z) / (delta_y + fov_factor_n * delta_z);
			x = -(p.x + f * delta_x) / (p.z + f * delta_z); x /= fov_factor;
			y = -1;
		}
		else {
			y /= fov_factor;
		}

		if (y1 > fov_factor) {
			float delta_x, delta_y, delta_z, f;
			delta_x = p.x - p1.x; delta_y = p.y - p1.y; delta_z = p.z - p1.z;
			f = -(p1.y + fov_factor * p1.z) / (delta_y + fov_factor * delta_z);
			x1 = -(p1.x + f * delta_x) / (p1.z + f * delta_z); x1 /= fov_factor;
			y1 = 1;
		}
		else if (y1 < fov_factor_n) {
			float delta_x, delta_y, delta_z, f;
			delta_x = p.x - p1.x; delta_y = p.y - p1.y; delta_z = p.z - p1.z;
			f = -(p1.y + fov_factor_n * p1.z) / (delta_y + fov_factor_n * delta_z);
			x1 = -(p1.x + f * delta_x) / (p1.z + f * delta_z); x1 /= fov_factor;
			y1 = -1;
		}
		else {
			y1 /= fov_factor;
		}

		transformedLines[linesToDraw] = { {x, y}, {x1, y1} };
		linesToDraw++;
	}
	return linesToDraw;
}
