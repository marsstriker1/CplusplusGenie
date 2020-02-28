#include <GL/glut.h>

const float CHAR_WIDTH = 0.2667;

void printText(float x, float y,const char * text,void *font,float r,float g, float b)
{
    glColor3f(r,g,b);
    char *c;
    glRasterPos2f(x,y);
    char buf[100] = {0};
    sprintf(buf,text);
    for (c=buf;*c!='\0';c++)
    {
        glutBitmapCharacter(font,*c);
    }
    glColor3f(1.0,1.0,0.0);
    glutPostRedisplay();
}
 void printText(std::string tex,double x,double y,float max_x,void * font)
 {
      glColor3f(0,0,0);
      glRasterPos2d(x,y);
      int i = 0,a;
      //char width is width of character in float value here charWidthInPixel/(windowSize/2)  = 8/300 = 0.02667
      //(windowSize/2) because window in float value -1 t0 +1
      float tsize = tex.size()* CHAR_WIDTH;
      //std::cout<<"\ttexsize: "<<tex.size()<<"\ttw:"<<tsize<<"\tcw:"<<CHAR_WIDTH;
      if( tsize < (max_x-x))
        a =0;
      else
        a = (tex.size() - (int)((max_x - x)/CHAR_WIDTH));

      for (i=a;tex[i]!='\0';i++)
      {
        glutBitmapCharacter(font,tex[i]);
      }
      glColor3f(0,0,0);
      glutPostRedisplay();
 }
std::string viewTodoList(std::string uName,std::string task)
 {
        std::fstream file;
        std::string str;
        file.open(uName+"////Todo////"+task,std::ios::in);
        if(!file)
        {
            std::cerr<<"rfchm";
        }

            getline(file,str);
            getline(file,str);

        file.close();
        return str;

 }
 void glDrawP(float x, float y,float w,float h)
 {
     glBegin(GL_POLYGON);
     glVertex2f(x,y);
     glVertex2f(x+w,y);
     glVertex2f(x+w,y-h);
     glVertex2f(x,y-h);
     glEnd();
 }
float toFloatX(int x)
{
    float tx;

    tx=static_cast<float>(x)/(70/2);

    if(tx<10)
    {
        tx=(10-tx)*(-1);
    }
    if(tx>10)
    {
        tx=(tx-10);
    }
    return tx;
}
float toFloatY(int y)
{
    float ty=static_cast<float>(y)/(65/2);
    if(ty<10)
    {
        ty=10-ty;
    }
    if(ty>10)
    {
        ty=(ty-10)*(-1);
    }
    //std::cout<<"X= "<<tx<<"\tY= "<<ty<<"\n";
    return ty;
}
void mglErrorMsg(const char* msg1,const char * msg2)
{
    glColor3f(0,0,0);
    glDrawP(-4.3,0.3,8.6,5.6);
    glColor3f(0.85,0,0);
    glDrawP(-4,0,8,5);
    printText(-2.0,-1.5,msg1,GLUT_BITMAP_HELVETICA_18,0,0,0);
    printText(-2.5,-3,msg2,GLUT_BITMAP_HELVETICA_12,0,0,0);
}
void mglErrorMsg(const char* msg1,const char * msg2,const char * msg3)
{
    glColor3f(0,0,0);
    glDrawP(-4.3,0.3,8.6,5.6);
    glColor3f(0.85,0,0);
    glDrawP(-4,0,8,5);
    printText(-2.0,-1.5,msg1,GLUT_BITMAP_HELVETICA_18,0,0,0);
    printText(-2.5,-3,msg2,GLUT_BITMAP_HELVETICA_12,0,0,0);
    printText(-3.2,-3.8,msg3,GLUT_BITMAP_HELVETICA_12,0,0,0);
}
