
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "glut.h"

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

void Display1() {
	double a = 0.02;
	double end = 100;
	double pi = 4 * atan(1.0);
	double ratia = 0.005;
	double t;
	double r;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);

	for (t = 0 + ratia; t < end; t += ratia) {
		double x, y;

		r = a * exp(1 + t);
		x = r * cos(t);
		y = r * sin(t);

		glVertex2f(x, y);
	}
	glEnd();
}

void Display3() {
	double xmax = 100;
	double ymax = 1;
	double ratia = 0.05;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.0, 1.0);

	for (double x = ratia; x < xmax; x += ratia) {
		double x1, y1;
		x1 = x / xmax;
		y1 = (fabs(round(x) - x) / x) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();
}

//melcul lui Pascal (concoida cercului):
void Display4() {
	double xmax, ymax;
	double a = 0.3, b = 0.2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;


	xmax = ymax = 0;

	for (t = -pi + ratia; t < pi; t += ratia) {
		double x, y;
		x = 2 * (a * cos(t) + b) * cos(t);
		xmax = (xmax < fabs(x)) ? fabs(x) : xmax;

		y = 2 * (a * cos(t) + b) * sin(t);
		ymax = (ymax < fabs(y)) ? fabs(y) : ymax;
	}

	double max = xmax > ymax ? xmax : ymax;
	max = max > 1 ? max : 1;

	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_LOOP);

	for (t = -pi + ratia; t < pi; t += ratia) {
		double x, y;
		x = (2 * (a * cos(t) + b) * cos(t));
		y = (2 * (a * cos(t) + b) * sin(t));

		glVertex2f(x/max, y/max);
	}
	glEnd();
}

void Display5() {
	double xmax = 0, ymax = 0;
	double ratia = 5;
	double a = 0.2;
	double pi = 4 * atan(1);
	int counter = 0;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_TRIANGLES);
	for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x, y;

		if (t != -pi / 6 && t != pi / 6) {
			x = a / (4 * cos(t) * cos(t) - 3);
			y = (a * tan(t)) / (4 * cos(t) * cos(t) - 3);

			if (x < 0 && y > 0) {
				if (x < -a || y > a) {
					if (counter == 0) {
						glVertex2f(-1, 1);
						counter = 1;
					}
				}

				counter++;
				glVertex2f(x, y);

				if (counter == 3) {
					counter = 0;
				}
			}
		}
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.2, 0.15, 0.88); // albastru
	for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x, y;

		if (t != -pi / 6 && t != pi / 6) {
			x = a / (4 * cos(t) * cos(t) - 3);
			y = (a * tan(t)) / (4 * cos(t) * cos(t) - 3);

			if (x < 0 && y > 0) {
				counter++;
				glVertex2f(x, y);

			}
		}
	}

	glEnd();
}

//cicloida
void Display6() {
	double start = -100, end = 100;
	double a = 0.1, b = 0.2;
	double ratia = 0.05;
	double t;

	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (t = start; t <= end; t += ratia) {
		double x, y;
		x = a * t - b * sin(t);
		y = a - b * cos(t);

		glVertex2f(x, y);
	}
	glEnd();
}

//epicicloida
void Display7() {
	double R = 0.1, r = 0.3;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t, factor;

	double xmax, ymax;

	xmax = ymax = 0;

	for (t = 0; t <= 2 * pi; t += ratia) {
		double x, y;
		factor = r / R * t;

		x = (R + r) * cos(factor) - r * cos(t + factor);
		y = (R + r) * sin(factor) - r * sin(t + factor);

		xmax = (xmax < fabs(x)) ? fabs(x) : xmax;
		ymax = (ymax < fabs(y)) ? fabs(y) : ymax;
	}

	double max = xmax > ymax ? xmax : ymax;
	max = max > 1 ? max : 1;

	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_LOOP);
	for (t = 0; t <= 2 * pi; t += ratia) {
		double x, y;
		factor = r / R * t;
		x = ((R + r) * cos(factor) - r * cos(t + factor));
		y = ((R + r) * sin(factor) - r * sin(t + factor));

		glVertex2f(x/max, y/max);
	}
	glEnd();
}

//hipocicloida
void Display8() {
	double R = 0.1, r = 0.3;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t, factor;
	double xmax, ymax;

	xmax = ymax = 0;

	for (t = 0; t <= 2 * pi; t += ratia) {
		double x, y;
		factor = r / R * t;

		x = (R - r) * cos(factor) - r * cos(t - factor);
		y = (R - r) * sin(factor) - r * sin(t - factor);

		xmax = (xmax < fabs(x)) ? fabs(x) : xmax;
		ymax = (ymax < fabs(y)) ? fabs(y) : ymax;
	}

	double max = xmax > ymax ? xmax : ymax;
	max = max > 1 ? max : 1;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_LOOP);
	for (t = 0; t <= 2 * pi; t += ratia) {
		double x, y;
		factor = r / R * t;
		x = ((R - r) * cos(factor) - r * cos(t - factor)) ;
		y = ((R - r) * sin(factor) - r * sin(t - factor));

		glVertex2f(x/max, y/max);
	}
	glEnd();
}

//lemniscata lui Bernoulli
void Display9() {
	double a = 0.4;
	double pi = 4 * atan(1.0);
	double ratia = 0.0005;
	double t;
	double r;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);

	double xmax, ymax;

	xmax = ymax = 0;

	for (t = -pi / 4 + ratia; t < pi / 4; t += ratia) {
		double x, y;

		r = a * sqrtf(2 * cos(2 * t));
		x = r * cos(t);
		y = r * sin(t);

		xmax = (xmax < fabs(x)) ? fabs(x) : xmax;
		ymax = (ymax < fabs(y)) ? fabs(y) : ymax;

	}

	double max = xmax > ymax ? xmax : ymax;
	max = max > 1 ? max : 1;


	for (t = pi / 4 - ratia; t > -pi / 4; t -= ratia) {
		double x, y;

		r = a * sqrtf(2 * cos(2 * t));
		x = r * cos(t);
		y = r * sin(t);

		glVertex2f(x/max, y/max);
	}

	for (t = -pi / 4 + ratia; t < pi / 4; t += ratia) {
		double x, y;

		r = -a * sqrtf(2 * cos(2 * t));
		x = r * cos(t);
		y = r * sin(t);

		glVertex2f(x/max, y/max);
	}
	glEnd();
}


void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	//   glPointSize(4);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		Display1();
		break;
	case '3':
		Display3();
		break;
	case '4':
		Display4();
		break;
	case '5':
		Display5();
		break;
	case '6':
		Display6();
		break;
	case '7':
		Display7();
		break;
	case '8':
		Display8();
		break;
	case '9':
		Display9();
		break;
	default:
		break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
