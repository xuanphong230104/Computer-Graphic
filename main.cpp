#include <GLUT/glut.h>
#include <cmath>
#include <cstdio>
#include <vector>

// Define the Point struct here
typedef struct {
    int x, y;
} Point;

// Define the Circle struct for storing circle data
typedef struct {
    int x, y, r;
} Circle;

std::vector<Circle> circles;
Point P[10];
int n = -1;

void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glOrtho(-320, 320, -240, 240, -1, 1);
}

void put8pixel(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x + xc, y + yc);
    glVertex2i(y + xc, x + yc);
    glVertex2i(y + xc, -x + yc);
    glVertex2i(x + xc, -y + yc);
    glVertex2i(-x + xc, -y + yc);
    glVertex2i(-y + xc, -x + yc);
    glVertex2i(-y + xc, x + yc);
    glVertex2i(-x + xc, y + yc);
    glEnd();
}

void CircleBres(int xc, int yc, int r) {
    int x, y, p;
    x = 0;
    y = r;
    p = 3 - 2 * r;
    while (x <= y) {
        put8pixel(xc, yc, x, y);
        if (p < 0) {
            p += 4 * x + 6;
        } else {
            p += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void Mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    
    for (auto& circle : circles) {
        CircleBres(circle.x, circle.y, circle.r);
    }

    glFlush();
}

void MouseEventHandler(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        n++;
        P[n].x = x - 320;
        P[n].y = 240 - y;
        printf("\n n=%i x=%d y=%d", n, P[n].x, P[n].y);

        if (n == 1) {
            // Calculate radius
            int radius = (int)sqrt(pow(P[1].x - P[0].x, 2) + pow(P[1].y - P[0].y, 2));
            circles.push_back({P[0].x, P[0].y, radius}); // Store the circle
            n = -1;  // Reset to allow for another circle to be drawn
            glutPostRedisplay();
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Bresenham Circle Drawing");
    initGL();
    glutDisplayFunc(Mydisplay);
    glutMouseFunc(MouseEventHandler);
    glutMainLoop();
    return 0;
}
