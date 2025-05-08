#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>

using namespace std;
int ver;
int polx[100] ,poly[100];

void draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINE_LOOP);
  glColor3f(0.0,0.0,0.0);
  for(int i = 0 ; i < ver ; i++){
    
    glVertex2f(polx[i],poly[i]);
  }
  glEnd();
  glFlush();
}

void fill(int x , int y , float od[3] ,float nc[3]){
  float color[3];
  glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
  if(od[0]==color[0] && od[1]==color[1] && od[2]==color[2]){
    glBegin(GL_POINTS);
    glColor3f(nc[0],nc[1],nc[2]);
    glVertex2f(x,y);
    glEnd();
    glFlush();
    
    fill(x+1,y,od,nc);
    fill(x,y+1,od,nc);
    fill(x-1,y,od,nc);
    fill(x,y-1,od,nc);
  }
}

void mouse(int button , int state , int x, int y){
  if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    y=500-y;
    float nc[3]={1.0,0.0,0.0};
    float oc[3]={1.0,1.0,1.0};
    fill(x,y,oc,nc);
  }
}
int main(int c , char *v[]){
  cout<<"Enter the no. of vertices: ";
  cin>>ver;
  for(int i = 0 ; i < ver ; i++){
    cout<<"Enter the vertex: ";
    cin>>polx[i]>>poly[i];
  }
  glutInit(&c , v);
  glutInitWindowSize(500,500);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("flood fill");
  glClearColor(1.0,1.0,1.0,1.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,500,0,500);
  glutDisplayFunc(draw);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}
