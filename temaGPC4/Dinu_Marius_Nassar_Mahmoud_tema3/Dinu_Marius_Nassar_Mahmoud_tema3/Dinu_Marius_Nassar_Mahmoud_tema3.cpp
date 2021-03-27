/*
Dinu Marius
Nassar Mahmoud
Tema 3 GPC
*/
#include <cstdlib>
#include <list>
#include "glut.h"


#define DIM 400
#define def 10
#define DIST 0.5
#define numar 15

using namespace std;
unsigned char prevKey;

class GrilaCarteziana
{
private:
	int number;
	float cellsNumber;
	float margin;
public:
	GrilaCarteziana()
	{
		this->number = def;
	}

	GrilaCarteziana(const int number)
	{
		this->number = number;
	}

	void drawLine()
	{
		const auto negXPoint = -1 + margin;
		const auto pozXPoint = 1 - margin;

		glLineWidth(4.0);
		glColor3f(1.0, 0.0, 0.0);

		glBegin(GL_LINES);
		glVertex2f(negXPoint, pozXPoint);
		glVertex2f(pozXPoint, 2.5 / (cellsNumber + DIST));
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(negXPoint, negXPoint);
		glVertex2f(pozXPoint, (-0.5 / (cellsNumber + DIST)));
		glEnd();

		SegmentDreapta3(0, numar, numar, 10, 2);
		SegmentDreapta3(0, 0, numar, 7, 0);
	}

	void drawGrid()
	{
		//un cast gasit pe stackover 
		cellsNumber = static_cast<float>(numar) / 2;
		margin = 1 - (cellsNumber / (cellsNumber + DIST));
		const auto startXPoint = -1 + margin;
		const auto endXPoint = 1 - margin;

		glLineWidth(1.0);
		glColor3f(0.1, 0.1, 0.1);

		for (float i = -cellsNumber; i <= cellsNumber; i++)
		{
			const auto commonYPoint = static_cast<float>(i / (cellsNumber + DIST));

			glBegin(GL_LINES);
			glVertex2f(startXPoint, commonYPoint);
			glVertex2f(endXPoint, commonYPoint);
			glEnd();
		}

		for (auto i = -cellsNumber; i <= numar; i++)
		{
			const auto commonXPoint = static_cast<float>(i / (cellsNumber + DIST));

			glBegin(GL_LINES);
			glVertex2f(commonXPoint, endXPoint);
			glVertex2f(commonXPoint, startXPoint);
			glEnd();
		}
	}

	void writePixel(int i, int j)
	{
		glColor3f(0.3, 0.3, 0.3);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		const auto point_x_position = i + -cellsNumber;
		const auto point_y_position = j + -cellsNumber;

		glBegin(GL_POLYGON);
		for (float k = 0; k <= 360; k += 0.5)
		{
			const float radius = 0.35;
			const auto output_x = static_cast<float>(point_x_position + radius * sin(k)) / (cellsNumber + DIST);
			const auto output_y = static_cast<float>(point_y_position + radius * cos(k)) / (cellsNumber + DIST);
			glVertex2f(output_x, output_y);
		}
		glEnd();
	}

	void pixels(int x, int y, int length)
	{
		length = length / 2;
		for (auto i = -length; i <= length; i++)
		{
			writePixel(x, y + i);
		}
	}

	void SegmentDreapta3(const int from_x, const int from_y, const int to_x, const int to_y, const unsigned int bold = 0)
	{
		int dx = to_x - from_x;
		int x = from_x, y = from_y;
		float m = ((to_y - from_y) / static_cast<float>(to_x - from_x));
		int i = m > 0 ? 1 : -1;
		int dy = i * (to_y - from_y);

		auto d = 2 * dy - dx,
			dE = 2 * dy,
			dNE = 2 * (dy - dx);

		pixels(x, y, bold);
		while (x < to_x) {
			if (d <= 0)
			{
				d += dE;
				x++;
			}
			else
			{
				d += dNE;
				x++;
				y += i;
			}
			pixels(x, y, bold);
		}
	}

};

//creare grilei
auto grila = new GrilaCarteziana(numar);

void Init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glLineWidth(1);
	glPolygonMode(GL_FRONT, GL_LINE);
	glMatrixMode(GL_PROJECTION);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (prevKey == '1')
	{
		grila->drawGrid();
		grila->drawLine();
	}

	glFlush();
}

void Reshape(const int width, const int height)
{
	glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	prevKey = key;
	if (key == 27)
		exit(0);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(DIM, DIM);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow(argv[0]);
	Init();
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyboardFunc);
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}