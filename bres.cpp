#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
using namespace std;
 int x1, y11, x2, y2, p, dx, dy, x, y;
void draw(){
  glClear(GL_COLOR_BUFFER_BIT);
 

  // Ask the user for coordinates of the line
 
  dx=x2-x1;
  dy=y2-y11;
  
  p=((2*dy)-dx);
  x=x1;
  y=y11;
  glBegin(GL_POINTS);
  while(x<=x2){
    glVertex2f(x,y);
    if(p>=1){
      y++;
      p=p+2*dy-2*dx;
    }
    else{
      y=y;
      p=p+2*dy;
    }
    x++;
  }
  glEnd();
  glFlush();
  
}
int main(int c , char *V[]){
 cout << "Enter x1, y1 (starting point of the line): ";
  cin >> x1 >> y11;

  cout << "Enter x2, y2 (ending point of the line): ";
  cin >> x2 >> y2;
  glutInit(&c,V);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(1000,1000);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("Line Drawing");
  glClearColor(0,0,0,1);
  glColor3f(0,1,0);
  
   glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 300, 0, 300, -1, 1);  // Set the orthogonal projection (left, right, bottom, top, near, far)
  
  // Setting up the model view matrix
  glMatrixMode(GL_MODELVIEW);
  glutDisplayFunc(draw);
  glutMainLoop();
  return 0;
  
}
