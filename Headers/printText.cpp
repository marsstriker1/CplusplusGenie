#include <GL/glut.h>
#include<string>
#include<iostream>

const float CHAR_WIDTH = 0.2667;

std::string text("");
bool showtext = true;

 void render();
 void mouseFunc(int button,int state,int x,int y);
 void OnKeyPressed(unsigned char key,int x,int y);
 void printText(std::string tex,float x,float y,float max_x);
 void ReshapeCallBack(int wid, int heig);


int main(int argcp, char **argv)
{
    glutInit (&argcp, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    //std::cout<<"\nwidth: "<<glutBitmapWidth(GLUT_BITMAP_8_BY_13,'&');
    glutCreateWindow("what");
        glutReshapeWindow(600,600);
        glutPositionWindow(100,100);
        glClearColor(0.09, 0.14, 0.4, 1);
        glutDisplayFunc(render);
        glClearColor(0.09, 0.14, 0.4, 1);
        glutMouseFunc(mouseFunc);
        glutKeyboardFunc(OnKeyPressed);

    glutMainLoop();
    return 0;
}
 void printText(std::string tex,double x,double y,float max_x)
 {
      glColor3f(1,1,1);
      glRasterPos2d(x,y);
      int i = 0;
      //char width is width of character in float value here charWidthInPixel/(windowSize/2)  = 8/300 = 0.02667
      //(windowSize/2) because window in float value -1 t0 +1
      float tsize = tex.size()* CHAR_WIDTH;
      //std::cout<<"\ttexsize: "<<tex.size()<<"\ttw:"<<tsize<<"\tcw:"<<CHAR_WIDTH;
      if( tsize < (max_x-x))
        i =0;
      else
        i = (tex.size() - (int)((max_x - x)/CHAR_WIDTH));

        //std::cout<<std::fixed<<"\ti:"<<i;
      for (i;tex[i]!='\0';i++)
      {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,tex[i]);
        //std::cout<<"\ntex: "<<tex[i];
      }
      glColor3f(0,0,0);
      //glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'|');
       glutPostRedisplay();
 }

void OnKeyPressed(unsigned char key,int x,int y)
{
        if((key == 8)&&(text.size()>0))
        {
            text.pop_back();
        }
        else
        {
            text+=key;
        }
        //std::cout<<"\n"<<text;

}
void render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  if(showtext)
    printText(text,-0.5,0.0,0.5);
  glutSwapBuffers();
}
void mouseFunc(int key,int state,int x, int y)
{

}
