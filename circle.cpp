#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>

using namespace std;

int x , y , r , px , py , p;
void draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  
  glBegin(GL_LINES);
  glVertex2f(500,0);
  glVertex2f(-500,0);
  
  glVertex2f(0,500);
  glVertex2f(0,-500);
  glEnd();
  
  x=0;
  y=r;
  p=3-2*r;
  glBegin(GL_POINTS);
  while(y>=x){
    glVertex2f(x+px,y+py);
    glVertex2f(-x+px,y+py);
    glVertex2f(x+px,-y+py);
    glVertex2f(-x+px,-y+py);
    glVertex2f(y+px,x+py);
    glVertex2f(-y+px,x+py);
    glVertex2f(y+px,-x+py);
    glVertex2f(-y+px,-x+py);
    
    if(p<0) {
      p=p+(4*x)+6;
      
    }
    else{
      p=p+(4*(x-y))+10;
       y--;
    }x++;
    
  }
  glEnd();
  glFlush();
}
int main(int c , char *v[]){
  cout<<"Enter the radius of the circle: ";
  cin>>r;
  cout<<"Enter center of the circle x and y: ";
  cin>>px>>py;
  
  glutInit(&c,v);
  glutInitWindowSize(1201,1201);
  glutInitWindowPosition(200,50);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("Circle");
  glClearColor(1,1,1,1);
  glColor3f(0,0,0);
 glMatrixMode(GL_PROJECTION);  // Set the projection matrix
    gluOrtho2D(-500, 500, -500, 500); 
  glutDisplayFunc(draw);
  glutMainLoop();
  return 0;
  }
