#include"login.h"
#include "ScrollBox.h"

const float SB_X1 = 0.2*10;  //search box
const float SB_Y1 = 0.8*10;
const float SB_X2 = -0.8*10;
const float SB_Y2 = 0.7*10;

const float SYNB1_X1 = 0.9*10;  //synonym box 1
const float SYNB1_Y1 = 0.35*10;
const float SYNB1_X2 = 0.5*10;
const float SYNB1_Y2 = 0.25*10;

const float SYNB2_X1 = SYNB1_X1; //synonym box 1
const float SYNB2_Y1 = SYNB1_Y1-0.2*10;
const float SYNB2_X2 = SYNB1_X2;
const float SYNB2_Y2 = SYNB1_Y2-0.2*10;

const float SSYNB_X1 = 0.8*10;   //set synonym box
const float SSYNB_Y1 = SYNB2_Y1-0.2*10;
const float SSYNB_X2 = 0.6*10;
const float SSYNB_Y2 = SYNB2_Y2-0.2*10;

//const float CHAR_WIDTH = 0.02667;

namespace SearchWindow
{
    ScrollBox scbx(-0.9*10,SB_Y2-0.1*10,SYNB1_X2-0.1*10,-0.8*10);
    float scrollthreshold = 0.1*10;
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
    std::string userName;
    //const int X = 0, Y =0;
    string dummy[]={"dummy1","dummy2","dummy3","dummy4","dummy5","dummy6","dummy7","dummy8","dummy9","dummy10","dummy11","dummy12","dummy13","dummy14","dummy15","dummy16","dummy17","dummy18","dummy19","dummy20","dummy21","dummy22","dummy23","dummy24"};

    void printText(std::string text,float x,float y,float max_x)
   {
      glColor3f(0,0,0);
      glRasterPos2d(x,y);
      int i = 0;
      float tsize = text.size()* CHAR_WIDTH;
      if( tsize < (max_x-x))
        i =0;
      else
        i = (text.size() - (unsigned int)((max_x - x)/CHAR_WIDTH));
      for (i;i<text.size();i++)
      {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,text[i]);
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
        printText(string("ADD"),SSYNB_X2+0.05*10,SSYNB_Y2+0.03*10,SSYNB_X1); //text for synonym set
        printText(keyword,SB_X2+0.2,SB_Y2-0.3,SB_X1-0.2);
        printText(synonym1,SYNB1_X2+0.02*10,SYNB1_Y2+0.03*10,SYNB1_X1-0.01*10);
        printText(synonym2,SYNB2_X2+0.02*10,SYNB2_Y2+0.03*10,SYNB2_X1-0.01*10);
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
                    string searchpath = string("./") + userName + string("/data/");
                    Search(setstr.data(),searchpath.data());
                    setstr = "";
                    //std::cout<<"\ndisize: "<<searchEngineDi.getsize();
                    /*for(int dic =0;dic<searchEngineDi.getsize();dic++)  //dic= string count of display info
                        std::cout<<"\n"<<searchEngineDi.get(dic);*/
                    scbx.setlines(searchEngineDi.getstring(),searchEngineDi.getsize());
                    searchEngineDi.clear();
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
        //std::cout<<"\nsearch window: key pressed";
      if(isSearching)
      {
         setToString(keyword,key);
         std::cout<<"\nKeyword: "<<keyword;
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

    void OnMouseDrag(int x,int y)
    {
        if(scbx.canScroll && wheelSelected)
        {
           if(y > ((10-(scbx.getwheely2() + scrollthreshold))*32.5) )
           {
               scbx.increaseWheelPos();
               //std::cout<<"\nwheeldown";
           }
           else if(y < ((10-(scbx.getwheely1() + scrollthreshold))*32.5))
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
            //std::cout<<"\nsearch window: mouse pressed";
            isSearching = false;
            syn1 = false;
            syn2 = false;
            //std::cout<<"\tx:"<<x<<"\ty:"<<y;
           if((x< ((10+SB_X1)*35) && x>((10+SB_X2)*35)) && (y>((10-SB_Y1)*32.5) && y<((10-SB_Y2)*32.5)))
           {
              //std::cout<<"\nx:"<<x<<"\ty:"<<y;
              isSearching = true;
              std::cout<<"\nissearching";
           }
           else if((x< ((10+SYNB1_X1)*35) && x>((10+SYNB1_X2)*35)) && (y>((10-SYNB1_Y1)*32.5) && y<((10-SYNB1_Y2)*32.5)))
           {
              syn1 = true;
              std::cout<<"\nissynonym1";
           }
           else if((x< ((10+SYNB2_X1)*35) && x>((10+SYNB2_X2)*35)) && (y>((10-SYNB2_Y1)*32.5) && y<((10-SYNB2_Y2)*32.5)))
           {
              syn2 = true;
              std::cout<<"\nissynonym2";
           }
           else if((x< ((10+SSYNB_X1)*35) && x>((10+SSYNB_X2)*35)) && (y>((10-SSYNB_Y1)*32.5) && y<((10-SSYNB_Y2)*32.5)))
           {
               std::cout<<"\nissetsynonym";
              if(synonym1.size() > 3 && synonym2.size()>3)
              {
                SetSynonym(synonym1.data(),synonym2.data());
                synonym1 = "";
                synonym2 = "";
                //std::cout<<"\nissetsynonym";
              }
           }
           else if(scbx.canScroll && ((x> ((10+scbx.getwheelx1())*35) && x<((10+scbx.getwheelx2())*35)) && (y>((10-scbx.getwheely1())*32.5) && y<((10-scbx.getwheely2())*32.5))) ) //ccordinate for scroll wheel is opposite to other textboxes
           {
              wheelSelected = true;
              //std::cout<<"\ndrag";
           }
          //ErrorWindow::create("Error");
        }
    }

    void setUser(string username)
    {
        userName = username;
    }
    void create()
    {
        scbx.setlines(dummy,24);
    }
}
