#include <GLUT/glut.h>
#include <cmath>
#include <cstdio>

// Define the Point struct
typedef struct {
    int x, y;
} Point;

// Define the Ellipse struct
typedef struct {
    int xc, yc, a, b;
    bool exists;
} Ellipse;

Point P[10];
int n = -1;
Ellipse currentEllipse = {0, 0, 0, 0, false};

void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glOrtho(-320, 320, -240, 240, -1, 1);
}

void put4pixel(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x + xc, y + yc);
    glVertex2i(x + xc, -y + yc);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc - x, yc + y);
    glEnd();
}

void ElipBres(int xc, int yc, int a, int b) {
    double x, y, p, x0, y0, a2, b2;
    a2 = a * a;
    b2 = b * b;
    x = 0;
    y = b;
    p = -2 * b + 1 + 2 * b2 / (a2);
    x0 = a2 / (sqrt(a2 + b2));
    y0 = b2 / (sqrt(a2 + b2));
    while (x <= x0) {
        put4pixel(xc, yc, x, y);
        if (p < 0) {
            p += 2 * b2 * (2 * x + 3) / a2;
        } else {
            p += 4 * (1 - y) + 2 * b2 * (2 * x + 3) / a2;
            y--;
        }
        x++;
    }
    x = a;
    y = 0;
    p = 2 * a2 / b2 - 2 * a + 1;
    while (y <= y0) {
        put4pixel(xc, yc, x, y);
        if (p < 0) {
            p += 2 * a2 * (2 * y + 3) / b2;
        } else {
            p += 4 * (1 - x) + 2 * a2 * (2 * y + 3) / b2;
            x--;
        }
        y++;
    }
}

void Mydisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    
    // Redraw the ellipse if it exists
    if (currentEllipse.exists) {
        ElipBres(currentEllipse.xc, currentEllipse.yc, currentEllipse.a, currentEllipse.b);
    }
    
    glFlush();
}

void MouseEventHandler(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        n++;
        P[n].x = x - 320;
        P[n].y = 240 - y;
        printf("\n n=%i x=%d y=%d", n, P[n].x, P[n].y);

        if (n == 2) {
            // Calculate the lengths of the semi-major and semi-minor axes
            int a = abs(P[1].x - P[0].x);  // Semi-major axis
            int b = abs(P[2].y - P[0].y);  // Semi-minor axis
            
            // Store the ellipse parameters
            currentEllipse = {P[0].x, P[0].y, a, b, true};
            
            n = -1;  // Reset to allow for another ellipse to be drawn
            glutPostRedisplay();
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Bresenham Ellipse Drawing");
    initGL();
    glutDisplayFunc(Mydisplay);
    glutMouseFunc(MouseEventHandler);
    glutMainLoop();
    return 0;
}
