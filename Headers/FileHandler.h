#include<iostream>
#include<fstream>

class FileHandler
{
protected:
    const char* filePath;
    fstream file;
public:
    void setFilePath(const char* fpath)
    {
        filePath = fpath;
    }
    void createFile()
    {
        file.open(filePath ,ios::out);
        if(!file)
        {
            filePath = "\0";
            std::cout<<"\nError creating file";
        }
        file.close();
    }

    inline bool exists ()
    {
    file.open(filePath,ios::in);
    bool check = file.good();
    file.close();
    return check;
    }

};
