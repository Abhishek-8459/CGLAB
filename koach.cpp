#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Function to compute the midpoint of two points
void midpoint(float x1, float y1, float x2, float y2, float* xm, float* ym) {
    *xm = (x1 + x2) / 2.0f;
    *ym = (y1 + y2) / 2.0f;
}

// Function to draw a single segment of the Koch curve
void kochCurve(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        // Base case: just draw the line segment
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    } else {
        // Recursive case: divide the segment into four new ones
        float xm1, ym1, xm2, ym2, xm3, ym3;

        // First divide the segment into three equal parts
        midpoint(x1, y1, x2, y2, &xm1, &ym1);

        // Calculate the third point by creating an equilateral triangle
        float angle = M_PI / 3.0f; // 60 degrees
        float dx = xm1 - x1;
        float dy = ym1 - y1;
        xm2 = xm1 + cos(angle) * (dx - dy);
        ym2 = ym1 + sin(angle) * (dx - dy);

        // Create the third midpoint
        midpoint(xm1, ym1, x2, y2, &xm3, &ym3);

        // Recursively draw 4 smaller Koch curves
        kochCurve(x1, y1, xm1, ym1, depth-1);
        kochCurve(xm1, ym1, xm2, ym2, depth-1);
        kochCurve(xm2, ym2, xm3, ym3, depth-1);
        kochCurve(xm3, ym3, x2, y2, depth-1);
    }
}

// Display function to render the Koch curve
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Define the initial line segment
    float x1 = -0.6f, y1 = -0.4f, x2 = 0.6f, y2 = -0.4f;
    
    int depth = 4; // Set recursion depth for fractal complexity

    // Draw the Koch curve using the initial segment
    kochCurve(x1, y1, x2, y2, depth);

    glFlush();
}

// Initialize OpenGL settings
void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f); // White color for the curve
    glPointSize(1.0f);
    glLineWidth(1.5f);

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Set the viewing area
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Koch Curve");

    initOpenGL();
    
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

