//BoundryFill

#include <GL/glut.h>
#include <iostream>
using namespace std;

float fillColor[3] = {1.0, 0.0, 0.0};      // Red fill color
float boundaryColor[3] = {0.0, 0.0, 0.0};  // Black boundary

// Store polygon vertices
int vertices;
int polyX[100], polyY[100];

void setPixel(int x, int y, float color[3]) {
    glBegin(GL_POINTS);
    glColor3fv(color);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void getPixel(int x, int y, float color[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

void boundaryFill(int x, int y, float boundaryColor[3], float fillColor[3]) {
    float color[3];
    getPixel(x, y, color);
    if ((color[0] != boundaryColor[0] || color[1] != boundaryColor[1] || color[2] != boundaryColor[2]) &&
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {
        setPixel(x, y, fillColor);
        boundaryFill(x + 1, y, boundaryColor, fillColor);
        boundaryFill(x - 1, y, boundaryColor, fillColor);
        boundaryFill(x, y + 1, boundaryColor, fillColor);
        boundaryFill(x, y - 1, boundaryColor, fillColor);
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = 500 - y;
        boundaryFill(x, y, boundaryColor, fillColor);
    }
}

void drawPolygon() {
    glColor3fv(boundaryColor);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < vertices; i++) {
        glVertex2i(polyX[i], polyY[i]);
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
    cout << "Enter number of polygon vertices: ";
    cin >> vertices;
    for (int i = 0; i < vertices; i++) {
        cout << "Enter vertex " << i + 1 << " (x y): ";
        cin >> polyX[i] >> polyY[i];
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Boundary Fill Algorithm with User Input");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}