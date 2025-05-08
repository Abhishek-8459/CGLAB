#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>
using namespace std;

int x1, y11, x2, y2, n;
float x, y, dx, dy, m, xinc, yinc, p;

void ddaLine() {
    glClear(GL_COLOR_BUFFER_BIT);

    dx = x2 - x1;
    dy = y2 - y11;
    m = max(dx, dy);
    xinc = dx / m;
    yinc = dy / m;
    
    glBegin(GL_POINTS);
    for (int i = 0; i <= m; i++) {
        glVertex2f(x, y);
        x += xinc;
        y += yinc;
    }
    glEnd();
    glFlush();
}

void bresenhamLine() {
    glClear(GL_COLOR_BUFFER_BIT);

    dx = x2 - x1;
    dy = y2 - y11;
    p = (2 * dy) - dx;
    x = x1;
    y = y11;
    
    glBegin(GL_POINTS);
    while (x <= x2) {
        glVertex2f(x, y);
        if (p >= 1) {
            y++;
            p = p + 2 * dy - 2 * dx;
        } else {
            p = p + 2 * dy;
        }
        x++;
    }
    glEnd();
    glFlush();
}

void draw() {
    switch (n) {
        case 1: // DDA
            ddaLine();
            break;
        case 2: // Bresenham
            bresenhamLine();
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
    }
}

int main(int argc, char* argv[]) {
    cout << "Choose a line drawing algorithm:\n1. DDA\n2. Bresenham\n";
    cin >> n;

    cout << "Enter x1, y1 (starting point of the line): ";
    cin >> x1 >> y11;

    cout << "Enter x2, y2 (ending point of the line): ";
    cin >> x2 >> y2;

    glutInit(&argc, argv);
    glutInitWindowPosition(250, 50);
    glutInitWindowSize(800, 800);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Line Drawing");

    glClearColor(1, 1, 1, 1);  // White background
    glColor3f(0, 0, 1);        // Blue color for the line

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -1, 1);  // Set the orthogonal projection

    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}

