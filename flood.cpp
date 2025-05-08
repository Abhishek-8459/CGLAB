#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>

using namespace std;
float fillc[3]={1.0,0.0,0.0};
int ver;
int polx[100],poly[100];


void draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0,0.0,0.0);
  glBegin(GL_LINE_LOOP);
  for(int i = 0 ; i < ver ; i++){
    glVertex2f(polx[i],poly[i]);
  }
  glEnd();
  glFlush();
}

void setPixel(int x, int y, float color[3]) {
    glBegin(GL_POINTS);
    glColor3fv(color);  // Set the color to fill
    glVertex2i(x, y);  // Place the pixel
    glEnd();
    glFlush();  // Ensure the pixel is rendered
}

void getPixel(int x, int y, float color[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color); 
}

void seedFill(int x, int y, float oldColor[3], float newColor[3]) {
    float color[3];
    getPixel(x, y, color);  // Get the color of the current pixel
    if (color[0] == oldColor[0] && color[1] == oldColor[1] && color[2] == oldColor[2]) {
        setPixel(x, y, newColor);  // Set the pixel to the new color
        seedFill(x + 1, y, oldColor, newColor);  // Recurse to the right
        seedFill(x - 1, y, oldColor, newColor);  // Recurse to the left
        seedFill(x, y + 1, oldColor, newColor);  // Recurse upwards
        seedFill(x, y - 1, oldColor, newColor);  // Recurse downwards
    }
}
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = 500 - y;  // Flip the y-coordinate to account for OpenGL's origin being at the bottom-left
        float oldColor[3] = {1.0, 1.0, 1.0};  // Background color (white)
        seedFill(x, y, oldColor, fillc);  // Start filling from the clicked point
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the display
    draw();  // Call the draw function to render the polygon
}
int main(int c , char *v[]){
  cout<<"Enter the number of vertices: ";
  cin>>ver;
  for(int i = 0 ; i < ver ; i++){
    cout<<"Enter values of "<<i+1<<" Vertices";
    cin>>polx[i]>>poly[i];
  }
  glutInit(&c,v);
  glutInitWindowSize(500,500);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("Flood fill");
glClearColor(1.0, 1.0, 1.0, 1.0);  // Set background color to white
    glMatrixMode(GL_PROJECTION);  // Set the projection matrix
    gluOrtho2D(0, 500, 0, 500); 
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
 glutMainLoop();
  return 0;
}
