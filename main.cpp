#include <GL/gl.h>      //lib for openGL
#include <GL/glu.h>     //lib of glut utilities
#include <GL/glut.h>    //lib glut

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include "Headers/Timecl.h"
#include "Headers/TodoList.h"
#include "Headers/menu.h"
#include "Headers/vars.h"
#include "Headers/logIn.h"


#define WID 700
#define HEI 650
#define INI_X 350    //335
#define INI_Y 70     //25
#define WC_R 0.094
#define WC_G 0.157
#define WC_B 0.4
#define WC_A 1.0
#define COORD_X 10
#define COORD_Y 10
#define DEL_KEY 8
#define ENTER_KEY 13
#define ESC_KEY 27
#define TAB_KEY 9

using namespace std;

void callBackFun(); //initial on the window
void initColor();//color of the window
void ReshapeCallBack(int wid, int heig); // in case of change in window size,avoid distortion
void mouseclicked(int button,int state,int x,int y);//action of mouse click
void keyPressed(unsigned char key,int x, int y); //keyboard

class windows{
private:
    const int lx=-0.7,ly=-8,lyt=-4;

    std::string *task;
    int i=0;

public:
    void welcomePage();
    void signUpPage();
    void loginPage();
    void workScreen();
    void todoScreen(); //to do list and reminder window
}navigate;

//features
    void addMenu();
    void clockpart();

GLfloat X=7.0;
GLfloat Y=5.0;
GLfloat Xc=2.0;
GLfloat Yc=3.0;
GLfloat pageNo=-1;

std::string *files;
std::string userName="";
std::string password="";
std::string userNameN="";
std::string passwordN="";
std::string desText="";
std::string dueText="";
std::string desFFile="";
std::string dateFFile="";

int bossel =1;
int enterCount=0;
float x_pos =-10.0;
float todo_x=-8;
float todo_y=2;
float dx,dy;
int dir = 1;
int numFile;

long long unsigned int blinkera =0;
long long unsigned int blinkerb =0;
long long unsigned int blinkerc =0;

bool showTextUserName =true;
bool showTextPass = false;
bool showTextUserNameN =true;
bool showTextPassN = false;
bool showDes=true;
bool showDueDate=false;
bool validLogIn=false;
bool showTodo =false;
bool showTodoList=true;


//GLUT functions

int main(int argc, char ** argv)    //default arguments of main
{

    glutInit(&argc, argv);  //always required to render glut
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); //sets the display mode of the window
    glutInitWindowPosition(INI_X ,INI_Y ); //initialize the position of window when 1st displayed in screen
    glutInitWindowSize(WID,HEI); //width and height of windows in pixels
    int mpar = glutCreateWindow("C++Genie");    //defines the name of the window


    glutDisplayFunc(callBackFun); //takes function pointer and is used to draw on window
    glutReshapeFunc(ReshapeCallBack);//used to register a callback , argument function pointer
    glutMouseFunc(mouseclicked);//mouse click function redirects to different pages
    glutKeyboardFunc(keyPressed);//keyboard press function

    //if(pageNo==1)
    addMenu();

    initColor(); //background color function
    glutCreateSubWindow(mpar,1,1,200,100);
    glutDisplayFunc(clockpart);
    glutReshapeFunc(ReshapeCallBack);
    initColor();

    glutMainLoop();  //glut loop required to keep window live until exit is done


}

void callBackFun()    //Call  back function to draw on the window
{
    glClear(GL_COLOR_BUFFER_BIT); //Clears the frame buffer of window,good habit
    glLoadIdentity(); //resets the matrix transformation done is previous options(i.e.,make default coordinate points)

    if(pageNo==-1)
    {
        navigate.welcomePage();
        glutSwapBuffers();
    }
    if(pageNo==10)
    {
        navigate.signUpPage();
        glutSwapBuffers();
    }
    if(pageNo==0)
    {
        navigate.loginPage();
        glutSwapBuffers();
    }

    else if(pageNo==1)
    {
        navigate.workScreen();
        glutSwapBuffers();
    }
    else if(pageNo==2)
    {
        navigate.todoScreen();
        glutSwapBuffers();
    }

}

void initColor() //Sets initial Background Color of the window
{
    glClearColor(WC_R,WC_G,WC_B,WC_A); // RGB and Alpha  //color intensity of color of screen
}

void ReshapeCallBack(int wid, int heig)// width and height passed by the API
{
    glViewport(0,0,wid,heig); //full screen has been taken as view port //all drawings are displayed in the view port
    glMatrixMode(GL_PROJECTION); //Switches to projection mode to draw stuff on the window //from GL model view matrix(default)
    glLoadIdentity(); //resets the parameters of projection matrix
    gluOrtho2D(-COORD_X,COORD_X,-COORD_Y,COORD_Y); //takes 4 arguments left,right,bottom,top (2D graph)
    glMatrixMode(GL_MODELVIEW); //switches back to model-view mode,the default mode
    //always should be in model view matrix , only go to projection matrix to set coordinates
}

void keyPressed(unsigned char pressedKey,int x,int y)
{
    if(pressedKey==ENTER_KEY && enterCount==2 && pageNo==0)
    {
            logIn logine(userName,password);   //login class
                //validate login
                if(userName==""){
                    std::cout<<"\nInvalid Login khali\n";
                    pageNo=0;
                }
                else if(logine.IsLogedIn()){
                    pageNo=1;               //to working page
                }
                else{
                    std::cout<<"\ninvalid Login\n";
                }
    }
    if(pressedKey==ENTER_KEY && enterCount==4 && pageNo==2)
    {
        showTodo=true;
        showDes=true;
    }

   if(pressedKey==8 && pageNo==0)
   {
       if(showTextUserName && bossel==1)
       {
           if(userName!="")
           {
             userName.pop_back();
           }

       }

       if(showTextPass && bossel==2)
       {
           if(password!="")
          password.pop_back();
       }
   }
   if(pressedKey==8 && pageNo==2)
   {
       if(showDes && bossel==3)
       {
           if(desText!="")
           desText.pop_back();
       }

       if(showDueDate && bossel==4)
       {
           if(dueText!="")
          dueText.pop_back();
       }

   }

   if(pressedKey==8 && pageNo==10)
   {
       if(showTextUserNameN && bossel==5)
       {
           if(userNameN!="")
           userNameN.pop_back();
       }

       if(showTextPassN && bossel==6)
       {
           if(passwordN!="")
          passwordN.pop_back();
       }
   }
    //std::cout<<static_cast<int>(pressedKey);
    if(pageNo==0)
    {
    if(pressedKey>=36 && pressedKey <=126)
    {
       if(bossel==1)
        {
            userName+=pressedKey;
            //std::cout<<"\n"<<userName;
            showTextUserName=true;
        }
        else if(bossel==2)
        {
            password+=pressedKey;
            showTextPass=true;
        }
    }

    if (pressedKey == ENTER_KEY || pressedKey == TAB_KEY)
    {
        showTextPass=true;
        bossel=2;
        enterCount=2;
    }
    }
    else if (pageNo==1)
    {
    }
    else if(pageNo==2)
    {
        if(bossel==1 || bossel==2)
            bossel=3;

        if((pressedKey>=36 && pressedKey <=126) || pressedKey==32)
        {
            if(bossel==3)
            {
                desText+=pressedKey;
                showDes=true;
                enterCount=3;
            }
            else if(bossel==4)
            {
                dueText+=pressedKey;
                showDueDate=true;
                enterCount=4;
            }
        }
        //glutPostRedisplay();

        if (pressedKey == ENTER_KEY || pressedKey == TAB_KEY)
        {
            showDueDate=true;
            bossel=4;
            enterCount=4;
            //glutPostRedisplay();
        }
    }
    if(pageNo==10)
    {
        if(bossel==1 || bossel==2 )
            bossel=5;

        if(pressedKey>=36 && pressedKey <=126)
        {
            if(bossel==5)
            {
                userNameN+=pressedKey;
                showTextUserNameN=true;
            }

            else if(bossel==6)
            {
                passwordN+=pressedKey;
                showTextPassN=true;
            }

      //glutPostRedisplay();
    }

    if (pressedKey == ENTER_KEY || pressedKey == TAB_KEY)
        {
            showTextPassN=true;
            bossel=6;

            //glutPostRedisplay();
        }
    }
    glutPostRedisplay();
}

void mouseclicked(int button,int state,int a,int b)
{
    int MAX_X=glutGet(GLUT_WINDOW_WIDTH);
    int MAX_Y=glutGet(GLUT_WINDOW_HEIGHT);

    int x=(a/static_cast<float>(MAX_X))*700;
    int y=(b/static_cast<float>(MAX_Y))*650;
//    std::cout<<"\nX="<<a/MAX_X<<"\tY="<<MAX_Y<<"\n";
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
       //std::cout<<"\nX= "<<a<<"\tY = "<<b;
       //std::cout<<"\nMAX-X="<<x<<"\tMAX-YY="<<y<<"\n";
    }

if(pageNo==-1)          //Welcome Page
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if((x>=365 && x<=490) && (y>=570 && y<=615))
        {
            pageNo=0;
        }
        if((x>=505 && x<=630) && (y>=570 && y<=615))
        {
            pageNo=10;
        }
    }
}
if(pageNo==0)       //login page
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
     {
        if((x>=300 && x<=450) && (y>=440 && y<=495)) //login page to working page
           {
                logIn login(userName,password);   //login class
                validLogIn=login.IsLogedIn();   //validate login
                if(userName==""){
                    std::cout<<"\nInvalid Login khali\n";
                    pageNo=0;
                }
                else if(validLogIn){
                    pageNo=1;               //to working page
                }
                else{
                    std::cout<<"\ninvalid Login\n";
                }
           }

        if((x<=560 && x>=140) && (y<=275 && y>=210))
        {
            showTextUserName=true;
            showTextPass=false;
            bossel=1;
            enterCount=1;
        }

        if((x<=560 && x>=140) && (y<=405 && y>=340))
        {
            showTextPass=true;
            showTextUserName=false;
            bossel=2;
            enterCount=2;
        }

     //std::cout<<"\nx= "<<x<<"\ty= "<<y;

     if((x<=665 && x>=505) && (y<=635 && y>=595))
     {
            pageNo=10;
     }
    }

}

if(pageNo==10)      //SignUp Page
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
     {
        if((x>=300 && x<=450) && (y>=450 && y<=495)) //sign up page to working page
           {
               if(userNameN!="" && passwordN!="")
               {
                   signUp signup(userNameN,passwordN);   //sign up class
                    signup.signup();   //create sign up file
                    signup.createTodoDirectory();
                    pageNo=1;
                    userName=userNameN;

               }
           }

        if((x<=560 && x>=140) && (y<=275 && y>=210))
        {
            bossel=5;
            showTextUserNameN=true;
            showTextPassN=false;

        }

        if((x<=560 && x>=140) && (y<=405 && y>=340))
        {
            bossel=6;
            showTextPassN=true;
            //showTextUserName=false;
        }
     if((x<=448 && x>=385) && (y<=600 && y>=565))   //redirects to login page
     {
            userName="";
            password="";
            showTextUserName=true;
            showTextPass=false;
            pageNo=0;
     }
    }
}

/*if(pageNo!=-1) //BACK BUTTON
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
    if((x<=680 || x>=635) && (y>=15 && y<=40)) //return back page
            {
                if(pageNo!=0 && pageNo!=10)
                    pageNo--;
                else
                    pageNo=-1;
            }
    }
}*/
if(pageNo==1)
{

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
            if((x<=680 || x>=635) && (y>=15 && y<=40)) //Log Out
            {
                pageNo=0;
                userName="";
                password="";
                showTextUserName=true;
                showTextPass=false;
                bossel=1;
            }
            if((x>=510 || x<=670) && (y>=95 && y<=145)) //from working page to to do page
            {
                pageNo=2;
            }

    }

}

if(pageNo==2)       //TO DO Page
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        dx=toFloatX(x);
        dy=toFloatY(y);
        for(int i=0;i<numFile;i++)
        {
            if((dx>todo_x+10 && dx<todo_x+12.4) && (dy<todo_y-2.5-(static_cast<float>(i)/2) && dy>todo_y-(static_cast<float>(i)/2)-2.9))
            {
                std::cout<<files[i];
                std::remove((userName+"\\\\Todo\\\\"+files[i]+".txt").c_str());
            }
        }
        if((x<=525 && x>=245) && (y<=180 && y>=140))
        {
            bossel=3;
            showDes=true;
            showDueDate=false;
            enterCount=3;
        }
        if((x<=525 && x>=245) && (y<=245 && y>=207))
        {
            bossel=4;
            showDueDate=true;
            enterCount=4;
        }
        if((x<=420 && x>=315) && (y<=290 && y>=260))    //Add Button
        {
            showTodo=true;
          //  showDueDate=false;
            //showDes=true;
            //clearBoxes=true;
        }
        if((x<=680 || x>=635) && (y>=15 && y<=40)) //Back Button
            {
                pageNo=1;
                desText="";
                dueText="";
                showDes=true;
                showDueDate=false;
                bossel=3;
            }
    }
}
    glutPostRedisplay();
}


//class windows functions

void windows::welcomePage()
{


    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
        glVertex2f(lx+.5,ly+0.5);
        glVertex2f(lx+4,ly+0.5);
        glVertex2f(lx+4,ly-1);
        glVertex2f(lx+.5,ly-1);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(lx+4.5,ly+0.5);
        glVertex2f(lx+8,ly+0.5);
        glVertex2f(lx+8,ly-1);
        glVertex2f(lx+4.5,ly-1);
    glEnd();
    printText(lx-7.3,lyt+1,"DEVELOPED BY:",GLUT_BITMAP_HELVETICA_18,1,1,1);
    printText(lx-7.3,lyt+.1,"Ravi Pandey",GLUT_BITMAP_HELVETICA_18,1,1,1);
    printText(lx-7.3,lyt-.85,"Rohan Chhetry",GLUT_BITMAP_HELVETICA_18,1,1,1);
    printText(lx-7.3,lyt-1.9,"Nikesh D.C.",GLUT_BITMAP_HELVETICA_18,1,1,1);


    printText(lx+1.5,ly-0.35,"LOG IN",GLUT_BITMAP_8_BY_13,0,0,0);
    printText(lx+5.32,ly-0.35,"SIGN UP",GLUT_BITMAP_8_BY_13,0,0,0);
}

void windows::signUpPage()
{
    glColor3f(0.78,0.749,0.9055);
    glBegin(GL_POLYGON);    //Back to login page button
        glVertex2f(1,-7.4);
        glVertex2f(2.8,-7.4);
        glVertex2f(2.8,-8.4);
        glVertex2f(1,-8.4);
    glEnd();

    printText(-3.1,-8,"Already a user? :",GLUT_BITMAP_HELVETICA_18,0.5,1,0.5);
    printText(1.2,-8,"Login",GLUT_BITMAP_HELVETICA_18,0,0,0);

        glBegin(GL_LINES);
        glPointSize(5);
        glLineWidth(1); //width of drawn line

        glVertex2f(-X,Y);   //UpperLine
        glVertex2f(X,Y);

        glVertex2f(-X,-Y+2);  //LowerLine
        glVertex2f(X,-Y+2);

        glVertex2f(-X,Y);  //LeftLine
        glVertex2f(-X,-Y+2);

        glVertex2f(X,Y);   //RightLine
        glVertex2f(X,-Y+2);

    glEnd();

    glBegin(GL_LINES);
        glPointSize(5);
        glLineWidth(1); //width of drawn line

        glVertex2f(-X-.1,Y+.1);   //UpperLine
        glVertex2f(X+.1,Y+.1);

        glVertex2f(-X-.1,-Y+1.9);  //LowerLine
        glVertex2f(X+.1,-Y+1.9);

        glVertex2f(-X-.1,Y+.1);  //LeftLine
        glVertex2f(-X-.1,-Y+1.9);

        glVertex2f(X+.1,Y+.1);   //RightLine
        glVertex2f(X+.1,-Y+1.9);

    glEnd();

    printText(-X+5,Y+0.51,"Sign-up Screen",GLUT_BITMAP_TIMES_ROMAN_24,1.0,0,0);
    printText(-X+1,Y-1,"User-name",GLUT_BITMAP_8_BY_13,1,1,0);
    printText(-X+1,-Y+5,"Password",GLUT_BITMAP_8_BY_13,1,1,0);

     glColor3f(0.78,0.749,0.9055);

    glBegin(GL_POLYGON);
        glVertex2f(-X+1,Y-1.5);
        glVertex2f(X-1,Y-1.5);
        glVertex2f(X-1,Y-3.5);
        glVertex2f(-X+1,Y-3.5);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-X+1,Y-5.5);
        glVertex2f(X-1,Y-5.5);
        glVertex2f(X-1,Y-7.5);
        glVertex2f(-X+1,Y-7.5);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-1.5,-3.5);
        glVertex2f(2.5,-3.5);
        glVertex2f(2.5,-5);
        glVertex2f(-1.5,-5);
    glEnd();

     if(showTextUserNameN)// || showTextPass)
    {

        printText(-X+1.2,-Y+7.2,userNameN.c_str(),GLUT_BITMAP_9_BY_15,0,0,0);
            if(!showTextPassN && showTextUserNameN)
        {
            blinkerc++;
            if (blinkerc%100>=0 && blinkerc%100<=50)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'|');
        glutPostRedisplay();
    }
    }
    if(showTextPassN)
    {
        printText(-X+1.2,-Y+3.2,"",GLUT_BITMAP_9_BY_15,0,0,0);
        for( unsigned int l=0;l<passwordN.length();l++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'*');
        if(showTextPassN)
        {
            blinkerc++;
            if (blinkerc%100>=0 && blinkerc%100<=50)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'|');
        glutPostRedisplay();
        }
    }
    printText(-0.5,-4.3,"Sign Up",GLUT_BITMAP_8_BY_13,0,0,0);
    glBegin(GL_LINES);
        glPointSize(5);
        glLineWidth(1); //width of drawn line
        glColor3f(0,0,0);
        glVertex2f(X-12.9,Y-3.4);   //LefttLine
        glVertex2f(X-12.9,Y-1.6);

        glVertex2f(X-1.1,Y-3.4);   //RightLine
        glVertex2f(X-1.1,Y-1.6);

        glVertex2f(X-12.9,Y-3.4);   //RLowerLine
        glVertex2f(X-1.1,Y-3.4);

        glVertex2f(X-12.9,Y-1.6);   //UpperLine
        glVertex2f(X-1.1,Y-1.6);
    glColor3f(1,1,0);
    glEnd();
    glBegin(GL_LINES);
        glPointSize(5);
        glLineWidth(1); //width of drawn line
        glColor3f(0,0,0);
        glVertex2f(X-12.9,Y-7.4);   //LefttLine
        glVertex2f(X-12.9,Y-5.6);

        glVertex2f(X-1.1,Y-7.4);   //RightLine
        glVertex2f(X-1.1,Y-5.6);

        glVertex2f(X-12.9,Y-7.4);   //LowerLine
        glVertex2f(X-1.1,Y-7.4);

        glVertex2f(X-12.9,Y-5.6);   //UpperLine
        glVertex2f(X-1.1,Y-5.6);
    glColor3f(1,1,0);
    glEnd();
}

void windows::loginPage()
{
    printText(-X+5.5,Y+0.51,"LOG IN",GLUT_BITMAP_TIMES_ROMAN_24,1.0,0.7,0);
    printText(-X+1,Y-1,"User-name",GLUT_BITMAP_8_BY_13,1,1,0);
    printText(-X+1,-Y+5,"Password",GLUT_BITMAP_8_BY_13,1,1,0);

     glColor3f(0.78,0.749,0.9055);

    glBegin(GL_POLYGON);
        glVertex2f(-X+1,Y-1.5);
        glVertex2f(X-1,Y-1.5);
        glVertex2f(X-1,Y-3.5);
        glVertex2f(-X+1,Y-3.5);
    glEnd();


    glBegin(GL_POLYGON);
        glVertex2f(-X+1,Y-5.5);
        glVertex2f(X-1,Y-5.5);
        glVertex2f(X-1,Y-7.5);
        glVertex2f(-X+1,Y-7.5);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-1.5,-3.5);
        glVertex2f(2.5,-3.5);
        glVertex2f(2.5,-5);
        glVertex2f(-1.5,-5);
    glEnd();

    if(showTextUserName || bossel==1 || showTextPass)
    {
        printText(userName,-X+1.2,-Y+7.2,6,GLUT_BITMAP_9_BY_15);
        if(!showTextPass)
        {
            blinkera++;
            if (blinkera%100>=0 && blinkera%100<=50)
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'|');
            glutPostRedisplay();
        }
    }

    if(showTextPass)
    {
        printText(-X+1.2,-Y+3.2,"",GLUT_BITMAP_9_BY_15,0,0,0);


        for( unsigned int l=0;l<password.length();l++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'*');
        }

        if(showTextPass)
        {
           blinkera++;
            if (blinkera%100>=0 && blinkera%100<=50)
            {
                if(password.length()>=33)
                {
                    glColor3f(0,0,0);
                    glRasterPos2f(5.58,-1.8);
                    glColor3f(1,1,0);
                }
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'|');
                //glutStrokeCharacter(GLUT_STROKE_ROMAN,'|');
            }

            glutPostRedisplay();
        }
        glColor3f(0.78,0.749,0.9055);
        glBegin(GL_POLYGON);
        glVertex2f(5.67,-2);
        glVertex2f(6,-2);
        glVertex2f(6,-1);
        glVertex2f(5.67,-1);
        glEnd();
        glColor3f(WC_R,WC_G,WC_B);
        glBegin(GL_POLYGON);
        glVertex2f(6,-2);
        glVertex2f(10,-2);
        glVertex2f(10,-1);
        glVertex2f(6,-1);
        glEnd();

    }
    printText(-0.5,-4.3,"LOG IN",GLUT_BITMAP_8_BY_13,0,0,0);

    glBegin(GL_POLYGON);
        glVertex2f(4.5,-9.5);
        glVertex2f(9,-9.5);
        glVertex2f(9,-8.3);
        glVertex2f(4.5,-8.3);
    glEnd();
    printText(4.9,-8.9,"Don't have an Account?",GLUT_BITMAP_HELVETICA_10,0,0,0);
    glBegin(GL_LINES);
        glPointSize(5);
        glLineWidth(1); //width of drawn line

        glVertex2f(-X,Y);   //UpperLine
        glVertex2f(X,Y);

        glVertex2f(-X,-Y+2);  //LowerLine
        glVertex2f(X,-Y+2);

        glVertex2f(-X,Y);  //LeftLine
        glVertex2f(-X,-Y+2);

        glVertex2f(X,Y);   //RightLine
        glVertex2f(X,-Y+2);

    glEnd();

    glBegin(GL_LINES);
        glPointSize(5);
        glLineWidth(1); //width of drawn line

        glVertex2f(-X-.1,Y+.1);   //UpperLine
        glVertex2f(X+.1,Y+.1);

        glVertex2f(-X-.1,-Y+1.9);  //LowerLine
        glVertex2f(X+.1,-Y+1.9);

        glVertex2f(-X-.1,Y+.1);  //LeftLine
        glVertex2f(-X-.1,-Y+1.9);

        glVertex2f(X+.1,Y+.1);   //RightLine
        glVertex2f(X+.1,-Y+1.9);

    glEnd();

    glBegin(GL_LINES);
        glPointSize(5);
        glLineWidth(1); //width of drawn line
        glColor3f(0,0,0);
        glVertex2f(X-12.9,Y-3.4);   //LefttLine
        glVertex2f(X-12.9,Y-1.6);

        glVertex2f(X-1.1,Y-3.4);   //RightLine
        glVertex2f(X-1.1,Y-1.6);

        glVertex2f(X-12.9,Y-3.4);   //RLowerLine
        glVertex2f(X-1.1,Y-3.4);

        glVertex2f(X-12.9,Y-1.6);   //UpperLine
        glVertex2f(X-1.1,Y-1.6);
    glColor3f(1,1,0);
    glEnd();
    glBegin(GL_LINES);
        glPointSize(5);
        glLineWidth(1); //width of drawn line
        glColor3f(0,0,0);
        glVertex2f(X-12.9,Y-7.4);   //LefttLine
        glVertex2f(X-12.9,Y-5.6);

        glVertex2f(X-1.1,Y-7.4);   //RightLine
        glVertex2f(X-1.1,Y-5.6);

        glVertex2f(X-12.9,Y-7.4);   //LowerLine
        glVertex2f(X-1.1,Y-7.4);

        glVertex2f(X-12.9,Y-5.6);   //UpperLine
        glVertex2f(X-1.1,Y-5.6);
    glColor3f(1,1,0);
    glEnd();
}

void windows::workScreen()
{
    glRasterPos2f(-2,9);
    printText(-2.25,8.8,("Hi,"+userName).c_str(),GLUT_BITMAP_HELVETICA_18,1,1,0);

    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex2f(9.5,8.7);
        glVertex2f(7.4,8.7);
        glVertex2f(7.4,9.5);
        glVertex2f(9.5,9.5);
    glEnd();

    printText(7.5,8.8,"Log Out",GLUT_BITMAP_HELVETICA_18,0,0,0);

    glColor3f(0.78,0.749,0.9055); //color of glut polygon

    glBegin(GL_POLYGON);
        glVertex2f(9.5,5.5);
        glVertex2f(4.5,5.5);
        glVertex2f(4.5,7);
        glVertex2f(9.5,7);
    glEnd();

    printText(5.8,6.2,"ToDo list",GLUT_BITMAP_8_BY_13,0,0,0);
}

void windows::todoScreen()
{

    glColor3f(1,1,1);
    glBegin(GL_POLYGON);    //BACK BUTTON
        glVertex2f(9.5,8.7);
        glVertex2f(8.2,8.7);
        glVertex2f(8.2,9.5);
        glVertex2f(9.5,9.5);
    glEnd();

    printText(8.3,8.8,"Back",GLUT_BITMAP_HELVETICA_18,0,0,0);
    glColor3f(0.78,0.749,0.9055); //color of glut polygon

    glBegin(GL_POLYGON);  //description box
        glVertex2f(-Xc+7,Yc+2.6);
        glVertex2f(-Xc-1,Yc+2.6);
        glVertex2f(-Xc-1,Yc+1.5);
        glVertex2f(-Xc+7,Yc+1.5);
    glEnd();

    glBegin(GL_POLYGON); //due date box
        glVertex2f(-Xc+7,Yc+0.6);
        glVertex2f(-Xc-1,Yc+0.6);
        glVertex2f(-Xc-1,Yc-0.5);
        glVertex2f(-Xc+7,Yc-0.5);
    glEnd();

    printText(-Xc-1.3,Yc+3.5,"Add to list:",GLUT_BITMAP_TIMES_ROMAN_24,0.5,0.5,1);
    printText(-Xc-1.1,Yc+2.8,"Title:",GLUT_BITMAP_8_BY_13,1,1,0);
    printText(-Xc-1.1,Yc+1,"Due Date(DD/MM/YY):",GLUT_BITMAP_8_BY_13,1,1,0);
    if(showDes || showDueDate)
    {
        //keyboard input description
        printText(desText,-Xc-0.85,Yc+1.8,-Xc+8,GLUT_BITMAP_8_BY_13);
        if(showDes && !showDueDate)
        {
            blinkerb++;
            if (blinkerb%100>=0 && blinkerb%100<=50)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'|');
            glutPostRedisplay();
        }
    }
    if(showDueDate || showDes)
    {
        //keyboard input due date
        printText(dueText,-Xc-0.85,Yc-0.2,-Xc+8,GLUT_BITMAP_8_BY_13);
        if(showDueDate)
        {
            blinkerb++;
            if (blinkerb%100>=0 && blinkerb%100<=50)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,'|');
                //glutStrokeCharacter(GLUT_STROKE_ROMAN,'|');
            glutPostRedisplay();
        }
    }

    glColor3f(0.8,0.5,0.7); //add button color

    glBegin(GL_POLYGON);  //add bottom
        glVertex2f(-1,1);
        glVertex2f(2,1);
        glVertex2f(2,2);
        glVertex2f(-1,2);
    glEnd();

    printText(-0.8,1.4,"Add to list",GLUT_BITMAP_8_BY_13,0,0,0); //add button

    ToDo todo(desText,dueText,userName);
    DirectoryHandler todoNum;

    //use of *file,numFile,i
    if(showTodo)
    {
            todo.addTodo(); std::cout<<"\nfile made\n";
            todo.readTodo();
            showTodo=false;
            showTodoList=true;
    }
    todoNum.setDirName(std::string("./"+userName+"/Todo/").c_str());
    todoNum.setFileNames();
    numFile=todoNum.getFileNumber();

    files = new string[numFile];
    task = new string[numFile];

    for(i=0;i<numFile;i++)
        {
            files[i]=todoNum.getFileName(i);
            task[i]=viewTodoList(userName,files[i]);
        }

    if(showTodoList)
    {

        //float todo_x=-8,todo_y=2;

        for(i=0;i<numFile;i++)
        {
            if(files[i]!="")
            {

            printText(todo_x-1,todo_y-1,"TODO LIST",GLUT_BITMAP_TIMES_ROMAN_24,1,1,1);
            printText(todo_x-0.5,todo_y-2,"Tasks\t\t\t\t",GLUT_BITMAP_HELVETICA_18,1,1,1);

                for(int popper=0;popper<4;popper++)
                    files[i].pop_back();

                glColor3f(0.10,0.4,0);
                for(int d=0;d<numFile;d++)
                {
                    glDrawP(todo_x+10,todo_y-2.3-static_cast<float>(i)/2,2.4,0.4);
                }
                printText(todo_x-0.5,todo_y-2.5-(0.5*i),(files[i]).c_str(),GLUT_BITMAP_8_BY_13,1,1,1);
                printText(todo_x+4,todo_y-2.5-(0.5*i),(task[i]).c_str(),GLUT_BITMAP_8_BY_13,1,1,1);
                printText(todo_x+10.15,todo_y-2.6-(0.5*i),"Delete",GLUT_BITMAP_8_BY_13,0,0,0);

            }

        }

    }



}


//feature functions

void addMenu()
{
    if(pageNo==1 || true)
    {
         glutCreateMenu(menu);

        // Add menu items
        glutAddMenuEntry("Add File", A);
        glutAddMenuEntry("Edit File", MENU_BACK);
        glutAddMenuEntry("Delete File", MENU_SPOT);
        glutAddMenuEntry("Nothing", MENU_BACK_FRONT);

        // Associate a mouse button with menu
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
}

void clockpart()
{
    glClear(GL_COLOR_BUFFER_BIT); //Clears the frame buffer of window,good habit

        glLoadIdentity(); //resets the matrix transformation done is previous options(i.e.,make default coordinate points)
        glClearColor(WC_R,WC_G,WC_B,WC_A);

        Showtime s1(-9,1.5,1,1,1);
    s1.displayClock(GLUT_BITMAP_TIMES_ROMAN_24);
    s1.displayCalendar(-5,-2.5,GLUT_BITMAP_HELVETICA_18);
    glutPostRedisplay();
    glutSwapBuffers();
}
