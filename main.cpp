#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
int counter=2;
int count_points=0;
int shift=10;
int drawBeizer=0;
int motion=0;
typedef struct
    {
         double x;
         double y;
    }Point;
    Point B[4];
    void printtext(int x,int y,char* st)
      {
          int l,i;

              l=strlen( st );
             glRasterPos2i( x, y);
             for( i=0; i < l; i++)
               {
                   glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, st[i]);
                }
                glFlush();
      }
        void myMouse(int button, int state,int x,int y)
       {
           int actualHeight;
           actualHeight=glutGet(GLUT_WINDOW_HEIGHT)-y;
           counter--;
           if(drawBeizer==1&&button==GLUT_LEFT_BUTTON&&counter==1)
           {
               motion=1;
               counter=3;
               int i=0;
               while(i<4)
               {
                   //printf("\n x=%d B[i].x=%f y=%d B[i].y=%f",x,B[i].x,actualHeight,B[i].y);
                   if(x-B[i].x>=-4&&x-B[i].x<=4&&actualHeight-B[i].y>=-4&&actualHeight-B[i].y<=4)
                   {
                       shift=i;
                     //  printf("value of %d",i);
                       break;
                   }
                    i++;
                    if(i==4)
                        shift=10;
               }
           }
           if(button==GLUT_LEFT_BUTTON&&counter==0&&drawBeizer==0)
           {
               B[count_points].x=x;
               B[count_points].y=actualHeight;
                glPointSize(5.0);
                glBegin(GL_POINTS);
                glVertex2f(x,actualHeight);
                glEnd();
                glFlush();
               counter=2;
                if(count_points==3)
                {
                    glLineWidth(1.4f);
                    drawBeizer=1;
                    glutPostRedisplay();
                }
                count_points++;
           }
       }
    void beizerCode()
       {
           glPointSize(5.0f);
           glColor3ub(0,0,0);
           double x,y,z,t=0;
           glBegin(GL_POINTS);
                     glVertex2f(B[0].x,B[0].y);
                     glVertex2f(B[1].x,B[1].y);
                     glVertex2f(B[2].x,B[2].y);
                     glVertex2f(B[3].x,B[3].y);
                    glEnd();
                    glFlush();
                    glPointSize(1.0f);
                    glColor3ub(255,0,0);
          for(t=0;t<=1;t=t+0.01)
          {
          x=pow((1-t),3)*B[0].x+3*t*pow((1-t),2)*B[1].x+3*pow(t,2)*(1-t)*B[2].x+pow(t,3)*B[3].x;
          y=pow((1-t),3)*B[0].y+3*t*pow((1-t),2)*B[1].y+3*pow(t,2)*(1-t)*B[2].y+pow(t,3)*B[3].y;
          glBegin(GL_POINTS);
          glVertex2f(x,y);
          glEnd();
          glFlush();
          }
       }
       void myMotion(int x,int y)
          {
              int actualHeight;
           actualHeight=glutGet(GLUT_WINDOW_HEIGHT)-y;
             if(motion)
             {
                 if(shift<=4)
                 {
                     B[shift].x=x;
                     B[shift].y=actualHeight;
                     glutPostRedisplay();
                 }
             }
          }
     void reshape(int w,int h)
       {
           glViewport(0,0,w,h);
       }
     void display()
      {
       glClear(GL_COLOR_BUFFER_BIT);
       glColor3ub(0,0,0);
        printtext(200,480,"Use your Mouse to Drag These Four Points");
       if(drawBeizer==1)
       {
       beizerCode();

       }
      }
      void init()
          {
        glClearColor(1.0,1.0,1.0,1.0);
        glColor3ub(0,0,0);
        gluOrtho2D(0.0f, 700.0f, 0.0f, 500);
         }
int main(int argc,char**argv)
  {
      glutInit(&argc,argv);
      glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
      glutInitWindowSize(700,500);
      glutInitWindowPosition(300,100);
      glutCreateWindow("Beizer Curve");
      init();
      glutDisplayFunc(display);
      glutMotionFunc(myMotion);
      glutMouseFunc(myMouse);
      glutReshapeFunc(reshape);
      glutMainLoop();
      return 0;
  }

