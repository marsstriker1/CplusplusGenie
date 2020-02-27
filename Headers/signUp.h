#include <fstream>
#include <string>
#include <iostream>
#include<dirent.h>


#include"SearchEngine.h"

class signUp{

private:
    std::string username;
    std::string password;

public:

signUp(){  //default constructor
    username="invalid";
    password="";
}

signUp(std::string username,std::string password):username(std::move(username)),password(std::move(password)){} //parametric constructor


    void signup()
    {
        if(username!="" && password!="")
        {
            string dirPath = createDirectory();
            string path = dirPath + string("\\\\password.txt");

            ofstream file;
            //create a file
            file.open(path.c_str());
            //file name is username.txt
            file << username << endl <<password;
            //file holds username is first line and password in the other
            file.close();
        }
    }

    string createDirectory()
    {
        DirectoryHandler d1;
        std::string dirpath = std::string(".\\\\")+username;  //D:\\\\C++GenieFile\\\\") + username;
        d1.setDirName(dirpath.data());

        if(d1.exists())
        {
            std::cout<<"\ndirectory already exists";
        }
        else
        {
            d1.createDir();
        }

        return dirpath;
    }
    void createTodoDirectory()
    {
        DirectoryHandler d1;
        std::string dirpath = std::string(".\\\\")+username+std::string("\\\\Todo");  //D:\\\\C++GenieFile\\\\") + username;
        d1.setDirName(dirpath.data());

        if(d1.exists())
        {
            std::cout<<"\ndirectory already exists";
        }
        else
        {
            d1.createDir();
        }

    }
};
