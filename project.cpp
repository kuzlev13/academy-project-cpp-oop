#include <iostream>
using namespace std;
class canvas
{
private:
    char **data;
    int width;
    int height;

public:
    void set(int x, int y, char sign)
    {
        if (x < this->width && y < this->height)
        {
            this->data[y][x] = sign;
        }
    }
    void print()
    {
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->width; j++)
            {
                if (this->data[i][j]){
                    cout << this->data[i][j];
                }else{
                    cout << ' ';
                }
            }
            cout << "\n";
        }
    }

    canvas(int width, int height)
    {
        this->height = height;
        this->width = width;
        this->data = new char *[height];
        for (int i = 0; i < height; i++)
        {
            this->data[i] = new char[width];
        }
    }
    ~canvas()
    {
        for (int i = 0; i < height; i++)
        {
            delete[] this->data[i];
        }
        delete[] this->data;
    }
};
int main()
{
    int height, width;
    cout << "Please, enter the width and height by space: ";
    cin >> width >> height;
    canvas current_canvas(width, height);
    int x, y;
    char sign;
    while (true)
    {
        cin >>x >> y >> sign;
        current_canvas.set(x, y, sign);
        current_canvas.print();
    }

    return 0;
}
