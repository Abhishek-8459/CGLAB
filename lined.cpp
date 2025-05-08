#include<iostream>

#include<GL/glut.h>
#include<GL/glu.h>
using namespace std;
int x1,y11,x2,y2,n;

void draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  
  glBegin(GL_LINES);
  glColor3f(0,0,0);
      glVertex2f(-500,0);
      glVertex2f(500,0);
      
      glVertex2f(0,-500);
      glVertex2f(0,500);
  glEnd();
  float x,y,dx,dy,m,xinc , yinc;
  x=x1;
  y=y11;
  dx=x2-x1;
  dy=y2-y11;
  m=max(dx,dy);
  xinc=dx/m;
  yinc=dy/m;
  
  glBegin(GL_POINTS);
  switch (n){
    case 1:
      for(int i =0 ; i < m ; i++){
        glVertex2f(x,y);
        x=x+xinc;
        y=y+yinc;
      }
      break;
    case 2:
      for(int i =0 ; i < m ; i++){
        if(i%16<=8) glVertex2f(x,y);
        x=x+xinc;
        y=y+yinc;
      }
      break;
    case 3:
      for(int i =0 ; i < m ; i++){
        if(i%8==0) glVertex2f(x,y);
        x=x+xinc;
        y=y+yinc;
      }
      break;
  }
  glEnd();
  glFlush();
  
}
int main(int c , char *v[]){
  cout<<"Choose a line\n1.simple\n2.dashed\n3.dotted";
  cin>>n;
  cout<<"Enter x1 and y1";
  cin>>x1>>y11;
  cout<<"Enter x2 and y2";
  cin>>x2>>y2;
  
  glutInit(&c,v);
  glutInitWindowPosition(250,50);
  glutInitWindowSize(1201,1201);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("DDA");
  glClearColor(1,1,1,1);
  glColor3f(0,0,1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-500, 500, -500, 500, -1, 1);  // Set the orthogonal projection (left, right, bottom, top, near, far)
  
  // Setting up the model view matrix
  glMatrixMode(GL_MODELVIEW);
  glutDisplayFunc(draw);
  glutMainLoop();
  
  return 0;
}
