#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

const int N = 10;
int n, poly[N][2];
float sx=1, sy=1, angle=0, rx=0, ry=0, tx=0, ty=0;
int reflectOpt = 0; // 0: none, 1: X, 2: Y

void drawAxes() {
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_LINES);
    glVertex2i(-400,0); glVertex2i(400,0);
    glVertex2i(0,-400); glVertex2i(0,400);
    glEnd();
}

void drawPoly(int pts[][2], float r, float g, float b) {
    glColor3f(r,g,b);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<n;i++) glVertex2i(pts[i][0], pts[i][1]);
    glEnd();
}

void scaling() {
    int temp[N][2];
    for(int i=0;i<n;i++) {
        temp[i][0] = poly[i][0]*sx;
        temp[i][1] = poly[i][1]*sy;
    }
    drawPoly(temp, 1,0,0);
}

void rotation() {
    int temp[N][2];
    float rad = angle*M_PI/180.0;
    for(int i=0;i<n;i++) {
        float x = poly[i][0] - rx, y = poly[i][1] - ry;
        temp[i][0] = rx + (x*cos(rad) - y*sin(rad));
        temp[i][1] = ry + (x*sin(rad) + y*cos(rad));
    }
    drawPoly(temp, 0,1,0);
}

void reflection() {
    int temp[N][2];
    for(int i=0;i<n;i++) {
        if(reflectOpt==1) { temp[i][0] = poly[i][0]; temp[i][1] = -poly[i][1]; }
        else if(reflectOpt==2) { temp[i][0] = -poly[i][0]; temp[i][1] = poly[i][1]; }
    }
    drawPoly(temp, 0,0,1);
}

void translation() {
    int temp[N][2];
    for(int i=0;i<n;i++) {
        temp[i][0] = poly[i][0] + tx;
        temp[i][1] = poly[i][1] + ty;
    }
    drawPoly(temp, 1,0,1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawPoly(poly, 0,0,0); // Original in black
    scaling();
    rotation();
    if(reflectOpt) reflection();
    if(tx!=0 || ty!=0) translation();
    glFlush();
}

void menu(int opt) {
    if(opt==1) { cout<<"Scaling factors sx sy: "; cin>>sx>>sy; }
    else if(opt==2) { cout<<"Rotation angle and point (angle rx ry): "; cin>>angle>>rx>>ry; }
    else if(opt==3) { cout<<"Reflect about (1:X-axis, 2:Y-axis): "; cin>>reflectOpt; }
    else if(opt==4) { cout<<"Translation tx ty: "; cin>>tx>>ty; }
    else if(opt==5) { sx=1; sy=1; angle=0; rx=0; ry=0; reflectOpt=0; tx=0; ty=0; }
    glutPostRedisplay();
}

void init() {
    glClearColor(1,1,1,1);
    gluOrtho2D(-400,400,-400,400);
}

int main(int argc,char**argv) {
    cout<<"No. of vertices: "; cin>>n;
    for(int i=0;i<n;i++) {
        cout<<"Vertex "<<i+1<<": "; cin>>poly[i][0]>>poly[i][1];
    }
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("2D Transformations");
    init();
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Scaling",1);
    glutAddMenuEntry("Rotation about point",2);
    glutAddMenuEntry("Reflection",3);
    glutAddMenuEntry("Translation",4);
    glutAddMenuEntry("Reset",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}

