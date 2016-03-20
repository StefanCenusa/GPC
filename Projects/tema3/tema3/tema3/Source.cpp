#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "glut.h"
#include <algorithm>

using namespace std;

class GrilaCarteziana {
	double default_margin = 10;
	double radius_percent = 25.0 / 100.0;
	int rows, columns;
	double height, width, min, h, w, step, h_margin, w_margin, init_w, final_w, init_h, final_h, h_unit, w_unit;


public:
	GrilaCarteziana(int rows, int columns);
	void writePixel(int i, int j);
	void displaySegment(GrilaCarteziana GC, int x0, int y0, int xn, int yn, int grosime);
	void drawLine(int x0, int y0, int xn, int yn);
};

void GrilaCarteziana::drawLine(int x0, int y0, int xn, int yn) {
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINES);
	double x1, y1, x2, y2;
	x1 = -1 + (step * y0 * w_unit) + w_margin;
	y1 = 1 - (step * x0 * h_unit) - h_margin;

	x2 = -1 + (step * yn * w_unit) + w_margin;
	y2 = 1 - (step * xn * h_unit) - h_margin;

	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

GrilaCarteziana::GrilaCarteziana(int rows_input, int columns_input) {
	rows = rows_input;
	columns = columns_input;

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);

	double x, y;

	height = glutGet(GLUT_WINDOW_HEIGHT);
	width = glutGet(GLUT_WINDOW_WIDTH);

	min = width < height ? width : height;

	h = min / rows;
	w = min / columns;

	step = h < w ? h : w;

	h_margin = (height - min + min - rows * step) / 2;
	w_margin = (width - min + min - columns * step) / 2;

	h_unit = 2.0 / height;
	w_unit = 2.0 / width;

	h_margin *= h_unit;
	w_margin *= w_unit;

	init_w = -1;
	final_w = 1;
	init_h = -1;
	final_h = 1;

	/* Horizontal lines. */

	for (double i = 0; i <= rows; i++) {
		x = init_w + w_margin;
		y = init_h + (step * i * h_unit) + h_margin;

		glVertex2f(x, y);

		x = final_w - w_margin;
		y = init_h + (step * i * h_unit) + h_margin;

		glVertex2f(x, y);
	}


	/* Vertical lines. */

	for (double i = 0; i <= columns; i++) {
		x = init_w + (step * i * w_unit) + w_margin;
		y = init_h + h_margin;

		glVertex2f(x, y);

		x = init_w + (step * i * w_unit) + w_margin;
		y = final_h - h_margin;

		glVertex2f(x, y);
	}
	glEnd();


}

void drawFilledSun(double x, double y, double x_radius, double y_radius, int precision) {

	double pi = 4 * atan(1.0);
	double twicePi = 2.0 * pi;

	glColor3f(0.28, 0.28, 0.28);
	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(x, y);

	for (int i = 0; i <= precision; i++) {
		glVertex2f((x + (x_radius * cos(i * twicePi / precision))), (y + (y_radius * sin(i * twicePi / precision))));
	}
	glEnd();
}

void GrilaCarteziana::writePixel(int i, int j) {

	if (i > rows || j > columns) {
		return;
	}

	double x, y;

	x = -1 + (step * j * w_unit) + w_margin;
	y = 1 - (step * i * h_unit) - h_margin;

	double x_radius = radius_percent * step * w_unit,
		y_radius = radius_percent * step * h_unit;

	
	drawFilledSun(x, y, x_radius, y_radius, 20);
}


void GrilaCarteziana::displaySegment(GrilaCarteziana GC, int x0, int y0, int xn, int yn, int line_width) {
	int dx = abs(x0 - xn),
		dy = abs(y0 - yn);

	if (dy <= dx) {
		GC.drawLine(x0, y0, xn, yn);

		int dx = abs(xn - x0),
			dy = abs(yn - y0);

		int d = 2 * dy - dx;
		int dE = 2 * dy,
			dNE = 2 * (dy - dx);

		int x = x0,
			y = y0;
		int step = 1;

		if (y0 > yn) {
			step = -1;
		}

		if (x0 > xn) {
			swap(x0, xn);
		}

		for (int yp = y - (line_width / 2); yp <= y + (line_width / 2); yp++) {
			GC.writePixel(x, yp);
		}

		for (int x = x0; x < xn;)
		{
			if (d <= 0)
				d += dE, x++;
			else
				d += dNE, x++, y += step;
			for (int yp = y - (line_width / 2); yp <= y + (line_width / 2); yp++) {
				GC.writePixel(x, yp);
			}
		}
	}
	else if (dx == 0) {
		GC.drawLine(x0, y0, xn, yn);

		if (y0 > yn) {
			swap(y0, yn);
		}
		for (int y = y0; y <= yn; y++) {
			for (int xp = x0 - (line_width / 2); xp <= x0 + (line_width / 2); xp++) {
				GC.writePixel(xp, y);
			}
		}
	}
	else {
		GC.drawLine(x0, y0, xn, yn);

		int dx = abs(xn - x0),
			dy = abs(yn - y0);

		int d = dy - 2 * dx;
		int dN = -2 * dx,
			dNE = 2 * (dy - dx);

		int x = x0,
			y = y0;
		int step = 1;

		if (x0 > xn) {
			step = -1;
		}

		if (y0 > yn) {
			swap(y0, yn);
		}

		for (int xp = x0 - (line_width / 2); xp <= x0 + (line_width / 2); xp++) {
			GC.writePixel(xp, y0);
		}

		for (int y = y0; y <= yn;) {
			if (d <= 0) {
				d += dNE;
				y++;
				x += step;
			}
			else {
				d += dN;
				y++;
			}

			for (int xp = x - (line_width / 2); xp <= x + (line_width / 2); xp++) {
				GC.writePixel(xp, y);
			}
		}
	}
}

void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	glPolygonMode(GL_FRONT, GL_FILL);
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	GrilaCarteziana GC = GrilaCarteziana(15, 15);

	GC.displaySegment(GC, 0, 0, 7, 15, 3);

	GC.displaySegment(GC, 15, 0, 10, 15, 1);

	glFlush();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(500, 300);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}

