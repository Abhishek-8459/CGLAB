#include <GL/glut.h>
#include <iostream>
using namespace std;

// Maximum number of polygon vertices
const int MAX_VERTICES = 20;

// Polygon vertex array
int polygon[MAX_VERTICES][2];

// Number of vertices in the polygon
int vertexCount;

// Clipping window boundaries
int wxmin = 200, wxmax = 500;
int wymin = 100, wymax = 350;

// Initialize OpenGL window
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);   // Set background color to white
    gluOrtho2D(0, 640, 0, 480);        // Define orthographic 2D projection
}

// Draw the clipping window and polygon
void draw() {
    glClear(GL_COLOR_BUFFER_BIT);       // Clear the screen

    // Draw clipping rectangle (green)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(wxmin, wymin);
        glVertex2i(wxmax, wymin);
        glVertex2i(wxmax, wymax);
        glVertex2i(wxmin, wymax);
    glEnd();

    // Draw polygon (blue)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
        for (int i = 0; i < vertexCount; i++) {
            glVertex2i(polygon[i][0], polygon[i][1]);
        }
    glEnd();

    glFlush();   // Render the scene
}

// Compute intersection of polygon edge with a clipping boundary
void intersect(int x1, int y1, int x2, int y2, int &ix, int &iy, int edge) {
    float m = (x2 - x1 != 0) ? (float)(y2 - y1) / (x2 - x1) : 1e6;  // Avoid divide by zero

    switch (edge) {
        case 1: // Left (x = wxmin)
            ix = wxmin;
            iy = y1 + m * (wxmin - x1);
            break;
        case 2: // Right (x = wxmax)
            ix = wxmax;
            iy = y1 + m * (wxmax - x1);
            break;
        case 3: // Bottom (y = wymin)
            iy = wymin;
            ix = x1 + (1 / m) * (wymin - y1);
            break;
        case 4: // Top (y = wymax)
            iy = wymax;
            ix = x1 + (1 / m) * (wymax - y1);
            break;
    }
}

// Clip polygon against a specific edge
void clip(int edge) {
    int temp[MAX_VERTICES][2];
    int newCount = 0;

    for (int i = 0; i < vertexCount; i++) {
        int x1 = polygon[i][0];
        int y1 = polygon[i][1];

        int x2 = polygon[(i + 1) % vertexCount][0];
        int y2 = polygon[(i + 1) % vertexCount][1];

        // Determine if each point is inside or outside the clipping boundary
        bool in1 = true, in2 = true;

        switch (edge) {
            case 1: in1 = (x1 >= wxmin); in2 = (x2 >= wxmin); break; // Left
            case 2: in1 = (x1 <= wxmax); in2 = (x2 <= wxmax); break; // Right
            case 3: in1 = (y1 >= wymin); in2 = (y2 >= wymin); break; // Bottom
            case 4: in1 = (y1 <= wymax); in2 = (y2 <= wymax); break; // Top
        }

        // Apply Sutherland-Hodgman rules
        if (in1 && in2) {
            // Both points inside – keep P2
            temp[newCount][0] = x2;
            temp[newCount][1] = y2;
            newCount++;
        }
        else if (in1 && !in2) {
            // P1 inside, P2 outside – add intersection point
            int ix, iy;
            intersect(x1, y1, x2, y2, ix, iy, edge);
            temp[newCount][0] = ix;
            temp[newCount][1] = iy;
            newCount++;
        }
        else if (!in1 && in2) {
            // P1 outside, P2 inside – add intersection and P2
            int ix, iy;
            intersect(x1, y1, x2, y2, ix, iy, edge);
            temp[newCount][0] = ix;
            temp[newCount][1] = iy;
            newCount++;
            temp[newCount][0] = x2;
            temp[newCount][1] = y2;
            newCount++;
        }
        // else: both points outside – do nothing
    }

    // Copy clipped polygon back
    vertexCount = newCount;
    for (int i = 0; i < vertexCount; i++) {
        polygon[i][0] = temp[i][0];
        polygon[i][1] = temp[i][1];
    }

    glutPostRedisplay(); // Redraw with the new polygon
}

// GLUT menu callback
void menu(int choice) {
    clip(choice);  // Clip using selected boundary
}

// Main program
int main(int argc, char** argv) {
    // Get polygon input
    cout << "Enter number of vertices: ";
    cin >> vertexCount;

    for (int i = 0; i < vertexCount; i++) {
        cout << "Enter vertex " << i + 1 << " (x y): ";
        cin >> polygon[i][0] >> polygon[i][1];
    }

    // GLUT and OpenGL initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping");

    init();                // Set up projection
    glutDisplayFunc(draw); // Register draw function

    // Create right-click menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Left", 1);
    glutAddMenuEntry("Right", 2);
    glutAddMenuEntry("Bottom", 3);
    glutAddMenuEntry("Top", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop(); // Start event loop
    return 0;
}

