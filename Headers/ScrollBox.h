#include "GlutUtility.h"
const float CHAR_HEIGHT = 0.0666666;   //height of each char is 13 pixels so (13+7)/300 = 0.066667
const float CHAR_WIDTH = 0.02667;
const int MAX_LINES = 40;

class ScrollBox
{

private:
    float X1;
    float Y1;
    float X2;
    float Y2;
    //Color color;
    float wheelheight;
    int maxlines;
    string lines[MAX_LINES];
    int wheelpos;
    int nooflines;
    int maxletter;
    int maxWheelpos;
 public:
     float wheel_X1;
     float wheel_X2;
     float wheel_Y1;
     float wheel_Y2;
     bool canScroll = false;
    ScrollBox(float x1,float y1,float x2,float y2) /*,string* line,int stringsize*/
    {
        //X1 = x1; Y1 = y1; X2 = x1+width; Y2 = y1 - height;  //x1 y1 is top left corner
        X1 = x1; Y1 = y1; X2 = x2; Y2 = y2;
        //color = c;
       maxletter = (X1 - X2)/ CHAR_WIDTH;
       maxlines = (int)((Y1 - Y2)/ CHAR_HEIGHT);
       //std::cout<<"\nmaxlines: "<<maxlines;
    }
    void setlines(string* inlin,int stringsize)
    {
         for(int i=0;i<stringsize;i++)
            lines[i] = inlin[i];
        nooflines = stringsize;
        if(nooflines > maxlines)
       {
            wheelheight = (Y1 - Y2)/((nooflines-maxlines) + 1);
            wheelpos = 0;
            canScroll = true;
            maxWheelpos = nooflines-maxlines;
       }
        else
        {
            wheelheight = 0;
            wheelpos = -1;
            canScroll = false;
        }
        wheel_X1 = X2 - 0.05;
        wheel_X2 = X2;
        wheel_Y1 = Y1-wheelheight*wheelpos;
        wheel_Y2 = wheel_Y1-wheelheight;

        //std::cout<<"\nbox height: "<<(Y1-Y2);
        //std:cout<<"\nwheelheight: "<<wheelheight;
    }
    void increaseWheelPos()
    {
        if(wheelpos < maxWheelpos)
        {
        wheelpos++;
        wheel_Y1 = Y1-wheelheight*wheelpos;
        wheel_Y2 = wheel_Y1-wheelheight;
        }
    }
    void decreaseWheelPos()
    {
        if(wheelpos > 0)
        {
        wheelpos--;
        wheel_Y1 = Y1-wheelheight*wheelpos;
        wheel_Y2 = wheel_Y1-wheelheight;
        }
    }

 private:
    void makeBox(float X1,float X2,float Y1,float Y2,Color c)
    {
        glBegin(GL_QUADS);
        glColor3f(c.r,c.g,c.b);
        glVertex2f(X2,Y1);    //1st quadrant
        glVertex2f(X1,Y1);    //2nd quadrant , x1 y1 is left-top corner
        glVertex2f(X1,Y2);    //3rd quadrant
        glVertex2f(X2,Y2);    //4th quadrant , x2 y2 is right-bottom corner
        glEnd();
    }

    void printText(std::string text,float x,float y,float max_x)
    {
      glColor3f(0,0,0);
      glRasterPos2d(x,y);
      int i = 0;
      float tsize = text.size()* CHAR_WIDTH;
      if( tsize < (max_x-x))
        i =0;
      else
        i = (text.size() - (int)((max_x - x)/CHAR_WIDTH));
      for (i;text[i]!='\0';i++)
      {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,text[i]);
        std::cout<<text[i];
      }
      glutPostRedisplay();
    }

    void printLines()
    {
        if(nooflines<=maxlines)
            for(int i=0;i<nooflines;i++)
                printText(lines[i],X1+0.05,Y1-i*CHAR_HEIGHT-0.05,X2-0.05);
        else
        {  for(int i=0;i<maxlines;i++)
                printText(lines[i+wheelpos],X1+0.05,Y1-i*CHAR_HEIGHT-0.05,X2-0.05);
        }
    }
  public:
    void display()
    {
        makeBox(X1,X2,Y1,Y2,Color(1,1,1));  //scroll box
        makeBox(X2-0.05,X2,Y1,Y2,Color(0.5,0.5,0.5));  //scrollwheel placement box
        if(canScroll)
            makeBox(wheel_X1,wheel_X2,wheel_Y1,wheel_Y2,Color(0.2,0.2,0.2));  //scroll wheel
        printLines();
        //std::cout<<"\nin scroll box";

    }

   /* string& breakIntoLines(string str)
    {

        for(int lc=0,lic =0;lc<string.size();lc++)    //lc-letter count lic-linecount
        {
           if()
        }
    }*/
};


