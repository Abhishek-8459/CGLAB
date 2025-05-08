//SeedFill(Flood)

#include <GL/glut.h>
#include <iostream>
using namespace std;

float fillColor[3] = {1.0, 0.0, 0.0}; // Red color for fill

// Store polygon coordinates
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

void seedFill(int x, int y, float oldColor[3], float newColor[3]) {
    float color[3];
    getPixel(x, y, color);
    if (color[0] == oldColor[0] && color[1] == oldColor[1] && color[2] == oldColor[2]) {
        setPixel(x, y, newColor);
        seedFill(x + 1, y, oldColor, newColor);
        seedFill(x - 1, y, oldColor, newColor);
        seedFill(x, y + 1, oldColor, newColor);
        seedFill(x, y - 1, oldColor, newColor);
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = 500 - y;
        float oldColor[3] = {1.0, 1.0, 1.0}; // White background
        seedFill(x, y, oldColor, fillColor);
    }
}

void drawPolygon() {
    float boundaryColor[3] = {0.0, 0.0, 0.0}; // Black boundary
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
    cout << "Enter number of vertices: ";
    cin >> vertices;

    for (int i = 0; i < vertices; i++) {
        cout << "Enter coordinates for vertex " << i + 1 << " (x y): ";
        cin >> polyX[i] >> polyY[i];
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Seed Fill Algorithm with User Input");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
o/p:g++ seedfill.cpp -o seedfill -lGL -lGLU -lglut
o/p:./seedfill

