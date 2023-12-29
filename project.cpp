#include <iostream>
#include "canvasfunc.h"
using namespace std;
class canvas
{
private:
    char **data;
    int width;
    int height;

public:
    canvas(int height, int width)
    {
        this->height = height;
        this->width = width;
        this->data = new char *[height];
        for (size_t i = 0; i < height; i++)
        {
            this->data[i] = new char[width];
        }
    }
    set();
    ~canvas()
    {
        for (int i = 0; i < height; ++i)
        {
            delete[] this->data[i];
        }
        delete[] this->data;
    }
};
int main()
{
    return 0;
}
