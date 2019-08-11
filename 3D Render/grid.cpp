#include "grid.h"

void makeGrid(Point3D outline[], Line3D inner_lines[]) {
	outline[0] = { 1,2,3 };

	float x_anchor = -1;
	float y_anchor = 1;

	outline[0] = { x_anchor, 1.0, -2.0 };
	outline[1] = { x_anchor, -1.0, -2.0 };
	outline[2] = { -1 * x_anchor, -1.0, -4.0 };
	outline[3] = { -1 * -x_anchor, 1.0, -4.0 };

	float f;
	for (int i = 1; i < 10; i++) {
		Line3D line, line1, line2, line3;
		f = i * 0.2f;
		int index = (i - 1) * 4;

		line.start = { x_anchor + f, y_anchor, -2 - f };
		line.end = { x_anchor + f, -y_anchor, -2 - f };
		inner_lines[index] = line;

		index++;
		line1.start = { x_anchor, y_anchor - f, -2 };
		line1.end = { -x_anchor, y_anchor - f, -4 };
		inner_lines[index] = line1;

		index++;
		line2.start = { 2 + x_anchor + f, 2 + y_anchor, -2 - f };
		line2.end = { 2 + x_anchor + f, 2 + -y_anchor, -2 - f };
		inner_lines[index] = line2;

		index++;
		line3.start = { 2 + x_anchor, 2 + y_anchor - f, -2 };
		line3.end = { 2 + -x_anchor, 2 + y_anchor - f, -4 };
		inner_lines[index] = line3;
	}
}

void makeGridHorizontal(Line3D inner_lines[]) {
	float x_anchor = -1;
	float y_anchor = 1;

	float f;
	for (int i = 1; i < 10; i++) {
		Line3D line;
		f = i * 0.2f;

		line.start = { x_anchor, y_anchor - f, -2 };
		line.end = { -x_anchor, y_anchor - f, -4 };
		inner_lines[i - 1] = line;
	}
}

void makeGridVertical(Line3D inner_lines[]) {
	float x_anchor = -1;
	float y_anchor = 1;

	float f;
	for (int i = 1; i < 10; i++) {
		Line3D line;
		f = i * 0.2f;
		line.start = { x_anchor + f, y_anchor, -2 - f };
		line.end = { x_anchor + f, -y_anchor, -2 - f };
		inner_lines[i - 1] = line;
	}
}