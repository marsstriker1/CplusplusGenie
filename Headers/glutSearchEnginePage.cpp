
#include <GL/glut.h>
#include<string>
#include<iostream>
//#include"mingw.thread.h"

#include"SearchEngine.h"
//#include"ErrorWindow.h"
#include "ScrollBox.h"

#define COORD_X 1
#define COORD_Y 1

const float SB_X1 = 0.2;  //search box
const float SB_Y1 = 0.8;
const float SB_X2 = -0.8;
const float SB_Y2 = 0.7;

const float SYNB1_X1 = 0.9;  //synonym box 1
const float SYNB1_Y1 = 0.75;
const float SYNB1_X2 = 0.5;
const float SYNB1_Y2 = 0.65;

const float SYNB2_X1 = SYNB1_X1; //synonym box 1
const float SYNB2_Y1 = SYNB1_Y1-0.2;
const float SYNB2_X2 = SYNB1_X2;
const float SYNB2_Y2 = SYNB1_Y2-0.2;

const float SSYNB_X1 = 0.8;   //set synonym box
const float SSYNB_Y1 = 0.35;
const float SSYNB_X2 = 0.6;
const float SSYNB_Y2 = 0.25;

//const float CHAR_WIDTH = 0.02667;

namespace SearchWindow
{
    ScrollBox scbx(-0.9,SB_Y2-0.1,SYNB1_X2-0.1,-0.8);
    float scrollthreshold = 0.1;
    //SearchEngine se;
    int index;
    bool canMake = true;
    bool isSearching = false;
    bool syn1 = false;
    bool syn2 = false;
    bool displaysyn1 = true;
    bool displaysyn2 = true;
    bool displaySearchWord = true;
    bool wheelSelected = false;
   // bool setSyn = false;
    std::string keyword ("");
    std::string synonym1("");
    std::string synonym2("");
    const int X = 0, Y =0;
    string dummy[]={"dummy1","dummy2","dummy3","dummy4","dummy5","dummy6","dummy7","dummy8","dummy9","dummy10","dummy11","dummy12","dummy13","dummy14","dummy15","dummy16","dummy17","dummy18","dummy19","dummy20","dummy21","dummy22","dummy23","dummy24"};
    void destroy()
    {
        glutDestroyWindow(index);
    }

    void printText(std::string tex,float x,float y,float max_x)
   {
      glColor3f(0,0,0);
      glRasterPos2d(x,y);
      int i = 0;
      float tsize = tex.size()* CHAR_WIDTH;
      if( tsize < (max_x-x))
        i =0;
      else
        i = (tex.size() - (int)((max_x - x)/CHAR_WIDTH));
      for (i;tex[i]!='\0';i++)
      {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,tex[i]);
      }
      glutPostRedisplay();
   }

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

    void makeObjects()
    {
        //glPointSize(0.1);
        makeBox(SB_X1,SB_X2,SB_Y1,SB_Y2,Color(1,1,1));  //search box
        makeBox(SYNB1_X1,SYNB1_X2,SYNB1_Y1,SYNB1_Y2,Color(0.8,0.8,0.85));  //SYNONYM BOX 1
        makeBox(SYNB2_X1,SYNB2_X2,SYNB2_Y1,SYNB2_Y2,Color(0.85,0.8,0.8)); //SYNONYM BOX 2
        makeBox(SSYNB_X1,SSYNB_X2,SSYNB_Y1,SSYNB_Y2,Color(0.8,0.85,0.8));  //synonym set box
        scbx.display();
        printText(string("SEARCH"),SSYNB_X2,SSYNB_Y2+0.03,SSYNB_X1); //text for synonym set
        printText(keyword,SB_X2+0.02,SB_Y2+0.03,SB_X1-0.02);
        printText(synonym1,SYNB1_X2+0.02,SYNB1_Y2+0.03,SYNB1_X1-0.02);
        printText(synonym2,SYNB2_X2+0.02,SYNB2_Y2+0.03,SYNB2_X1-0.02);

        /*if(isSearching)
        {
           glRasterPos2f()
           glutBitmapCharacter(GLUT_BITMAP_8_BY_13,'#');
        }
        else if(syn1)
        else if(syn2)*/
    }

    void setToString(string& setstr, unsigned int key)
    {
        if((key == 8)&&(setstr.size()>0))
        {
            setstr.pop_back();
        }
        else if((key == 13 ) && (setstr.size()>1))
            {
                if(isSearching)
                {
                    glutHideWindow();
                    Search(setstr.data(),"./data/");
                    setstr = "";
                    std::cout<<"\ndisize: "<<searchEngineDi.getsize();
                    for(int dic =0;dic<searchEngineDi.getsize();dic++)  //dic= string count of display info
                        std::cout<<"\n"<<searchEngineDi.get(dic);
                        searchEngineDi.clear();
                        scbx.setlines(searchEngineDi.getstring(),searchEngineDi.getsize());
                    glutShowWindow();
                }

                isSearching = false;
                syn1 = false;
                syn2 = false;
                //setSyn = false;
            }
        else
        {
            setstr+=key;
        }
    }

    void OnKeyPressed(unsigned char key,int x,int y)
    {
      if(isSearching)
      {
         setToString(keyword,key);
         //std::cout<<"\nKeyword: "<<keyword;
      }
      else if(syn1)
      {
         setToString(synonym1,key);
         //std::cout<<"\nSynonym1: "<<synonym1;
      }
      else if(syn2)
      {
         setToString(synonym2,key);
         //std::cout<<"\nSynonyn2: "<<synonym2;
      }
    }

   void render()
    {
        //std::cout<<"\tRendering";
        glClear(GL_COLOR_BUFFER_BIT);
        //glLoadIdentity();
        makeObjects();
        glFlush();
        //glutPostRedisplay();
        //glutSwapBuffers();
    }

    void OnMouseDrag(int x,int y)
    {
        if(scbx.canScroll && wheelSelected)
        {
           if(y > ((1-(scbx.wheel_Y2 + scrollthreshold))*300) )
           {
               scbx.increaseWheelPos();
               //std::cout<<"\nwheeldown";
           }
           else if(y < ((1-(scbx.wheel_Y1 + scrollthreshold))*300))
           {
               scbx.decreaseWheelPos();
               //std::cout<<"\nwheelup";
           }
        }
    }

   void mouseFunc(int button,int state,int x,int y)
    {
        wheelSelected = false;
        if((button == GLUT_LEFT_BUTTON) &&(state == GLUT_DOWN) )
        {
            isSearching = false;
            syn1 = false;
            syn2 = false;
            //std::cout<<"\tx:"<<x<<"\ty:"<<y;
           if((x< ((1+SB_X1)*300) && x>((1+SB_X2)*300)) && (y>((1-SB_Y1)*300) && y<((1-SB_Y2)*300)))
           {
              //std::cout<<"\nx:"<<x<<"\ty:"<<y;
              isSearching = true;
           }
           else if((x< ((1+SYNB1_X1)*300) && x>((1+SYNB1_X2)*300)) && (y>((1-SYNB1_Y1)*300) && y<((1-SYNB1_Y2)*300)))
           {
              syn1 = true;
           }
           else if((x< ((1+SYNB2_X1)*300) && x>((1+SYNB2_X2)*300)) && (y>((1-SYNB2_Y1)*300) && y<((1-SYNB2_Y2)*300)))
           {
              syn2 = true;
           }
           else if((x< ((1+SSYNB_X1)*300) && x>((1+SSYNB_X2)*300)) && (y>((1-SSYNB_Y1)*300) && y<((1-SSYNB_Y2)*300)))
           {
              if(synonym1.size() > 3 && synonym2.size()>3)
              {
                SetSynonym(synonym1.data(),synonym2.data());
                synonym1 = "";
                synonym2 = "";
              }
           }
           else if(scbx.canScroll && ((x> ((1+scbx.wheel_X1)*300) && x<((1+scbx.wheel_X2)*300)) && (y>((1-scbx.wheel_Y1)*300) && y<((1-scbx.wheel_Y2)*300))) ) //ccordinate for scroll wheel is opposite to other textboxes
           {
              wheelSelected = true;
              //std::cout<<"\ndrag";
           }
          //ErrorWindow::create("Error");
        }
        else if((button == GLUT_RIGHT_BUTTON) &&(state == GLUT_DOWN))
        {
           // ErrorWindow::create("Error",100,200);
            destroy();
        }
    }

    inline unsigned int drawToScreenCoordx(int x)
    {
        return ((1+x)*300);
    }
    inline unsigned int drawToScreenCoordy(int y)
    {
        return ((1-y)*300);
    }

    void create(const char* err)
    {
        scbx.setlines(dummy,24);
        index = glutCreateWindow(err);
        glutReshapeWindow(600,600);
        glutPositionWindow(100,100);
        glutDisplayFunc(render);
        glClearColor(0.09, 0.14, 0.4, 1);
        glutMouseFunc(mouseFunc);
        glutMotionFunc(OnMouseDrag);
        glutKeyboardFunc(OnKeyPressed);
        //glutReshapeFunc(onReshape);
        canMake = false;
    }
}

int main(int argcp, char **argv)
{
    glutInit (&argcp, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE /*| GLUT_DOUBLE*/);
    SearchWindow::create("Search Engine");

    glutMainLoop();
    return 0;

}


