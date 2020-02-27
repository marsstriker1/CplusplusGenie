#include "vars.h"
// Menu items
enum MENU_TYPE
{
        A,
        MENU_SPOT,
        MENU_BACK,
        MENU_BACK_FRONT,
        MENU_DEPTH,
};

// Assign a default value

MENU_TYPE show = MENU_BACK_FRONT;
//pageNo=0;
// Menu handling function declaration

void menu(int);


// Menu handling function definition
void menu(int item)
{
        switch (item)
        {
        case A:
            {
                //pageNo=1;
            std::cout<<"Add File";
            break;
            }

        case MENU_SPOT:
            {
                std::cout<<"Delete File";
                break;
            }
        case MENU_DEPTH:
        case MENU_BACK:
            {
                std::cout<<"Edit File";
                break;
            }
        case MENU_BACK_FRONT:
                {
                        //show = (MENU_TYPE) item;
                }
                break;
        default:
                {       /* Nothing */       }
                break;
        }

        glutPostRedisplay();

        return;
}

