#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>
using namespace std; 

int wxmin = 200, wxmax = 500;
int wymin = 100, wymax = 350;
int ver;
int pol[20][2];
void draw(){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,0.0,0.0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(wxmin,wymin);
  glVertex2f(wxmax,wymin);
  glVertex2f(wxmax,wymax);
  glVertex2f(wxmin,wymax);
  glEnd();
  
  glColor3f(0.0,1.0,0.0);
  glBegin(GL_POLYGON);
  for(int i = 0 ; i < ver ; i++){
    glVertex2f(pol[i][0],pol[i][1]);
  }
  glEnd();
  glFlush();
  
}
void intersect(int x1,int y1,int x2,int y2 , int &xi , int &yi , int edge){
  float m = (x2-x1)!=0 ? (float)(y2-y1)/(x2-x1) : 1e6;
  switch(edge){
    case 1:
      xi=wxmin;
      yi=y1+m*(wxmin-x1);
      break;
    case 2:
      xi=wxmax;
      yi=y1+m*(wxmax-x1);
      break;
    case 4:
      yi=wymin;
      xi=x1+(1/m)*(wymin-y1);
      break;
    case 3:
      yi=wymax;
      xi=x1+(1/m)*(wymax-y1);
      break;
      
}
}

void clip(int edge){
  int npol[20][2];
  int count = 0;
  
  for(int i = 0 ; i < ver ; i++){
    int x1 = pol[i][0];
    int y1 = pol[i][1];
    
    int x2 = pol[(i+1)%ver][0];
    int y2 = pol[(i+1)%ver][1];
    
    bool in1 , in2;
    
    switch(edge){
      case 1:
        in1 = (x1>=wxmin) ; in2= (x2>=wxmin); break;
      case 2:
        in1 = (x1<=wxmax) ; in2= (x2<=wxmax); break;
      case 3:
        in1 = (y1<=wymax) ; in2= (y2<=wymax); break;
      case 4:
        in1 = (y1>=wymin) ; in2= (y2>=wymin); break;
    }
    if(in1 && in2){
      npol[count][0]=x2;
      npol[count][1]=y2; count++;
    }
    else if(in1 && !in2){
      int xi , yi;
      intersect(x1,y1,x2,y2,xi,yi,edge);
      npol[count][0]=xi;
      npol[count][1]=yi; count++;
    }
    else if (!in1 && in2){
      int xi , yi;
      intersect(x1,y1,x2,y2,xi,yi,edge);
      npol[count][0]=xi;
      npol[count][1]=yi; count++;
       npol[count][0]=x2;
      npol[count][1]=y2; count++;
    }
  }
  ver = count;
  for(int i = 0 ; i < count ; i++){
    pol[i][0]=npol[i][0];
    pol[i][1]=npol[i][1];
  }
  glutPostRedisplay();
}
void menu(int edge){
  clip(edge);
}
int main(int c , char *v[]){
  cout<<"Enter the number of vertices: ";
  cin>>ver;
  for(int i = 0 ; i < ver ; i++){
    cout<<"Enter the vertex(x,y): ";
    cin>>pol[i][0]>>pol[i][1];
  }
  glutInit(&c,v);
  glutInitWindowSize(700,700);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("clipping");
  glClearColor(1.0,1.0,1.0,1.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-700,700,-700,700);
  glutDisplayFunc(draw);
  glutCreateMenu(menu);
  glutAddMenuEntry("left",1);
  glutAddMenuEntry("right",2);
  glutAddMenuEntry("top",3);
  glutAddMenuEntry("bottom",4);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutMainLoop();
  return 0;
}
