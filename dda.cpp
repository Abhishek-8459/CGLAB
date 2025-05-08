#include<iostream>

#include<GL/glut.h>
#include<GL/glu.h>
using namespace std;
int x1,y1,x2,y2,n;

void draw(){
  glclear(GL_COLOR_BUFFER_BIT);
  float x,y,dx,dy,m,xinc , yinc;
  x=x1;
  y=y1;
  dx=x2-x1;
  dy=y2-y1;
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
  cout<<"Choose a line\n1.simple\n2.dashed\n3.dotted;
  cin>>n;
  count<<"Enter x1 and y1;
  cin>>x1>>y1;
  cout<<"Enter x2 and y2;
  cin>>x2>>y2;
  
  glutInit(&c,v);
  glutInitWindowPoistion(250,50);
  glutInitWindowSize(1201,1201);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("DDA");
  glClearColor(1,1,1,1);
  glColor3f(0,0,1);
  glutDisplayFunc(draw);
  glutMainLoop();
  
  return 0;
}
