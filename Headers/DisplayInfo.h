
class DisplayInfo
{
private:
    string* info;
    int size;
public:
    DisplayInfo()
    { size = 0;}
    int getsize()
    { return size; }
    string* getstring()
    { return info;}
    void add(const char* str)
    {
       string* temp = new string[size+1];
       for(int i=0;i<size;i++)
          temp[i] = info[i];
        temp[size] = string(str);
        if(info != 0)
            delete[] info;
        info = temp;
        size++;
    }
    void add(std::string str)
    {
        add(str.data());
    }
    void clear()
    {
        delete[] info;
        info = 0;
        size = 0;
    }
    std::string get(int i)
    {
        if(i<size)
            return info[i];
        else
            return std::string("");
    }

    DisplayInfo& operator<<(const char* str)
    {
        add(str);
        return (*this);
    }
    DisplayInfo& operator<<(std::string str)
    {
        return (operator<<(str.data()));
    }
    ~DisplayInfo()
    {
        if(info != 0)
            delete[] info;
    }
};
