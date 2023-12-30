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
                if (this->data[i][j])
                {
                    cout << this->data[i][j];
                }
                else
                {
                    cout << ' ';
                }
            }
            cout << "\n";
        }
    }
    void setLine(int x1, int y1, int x2, int y2, char sign)
    {
        const int deltaX = abs(x2 - x1);
        const int deltaY = abs(y2 - y1);
        const int signX = (x1 < x2) ? 1 : -1;
        const int signY = (y1 < y2) ? 1 : -1;
        int error = deltaX - deltaY;
        set(x2, y2, sign);
        while (x1 != x2 || y1 != y2)
        {
            set(x1, y1, sign);
            int error2 = error * 2;
            if (error2 > -deltaY)
            {
                error -= deltaY;
                x1 += signX;
            }
            if (error2 < deltaX)
            {
                error += deltaX;
                y1 += signY;
            }
        }
    }
    void setCircle(int x0, int y0, int radius, char sign)
    {
        int x = 0;
        int y = radius;
        int delta = 1 - 2 * radius;
        int error = 0;
        while (y >= 0)
        {
            set(x0 + x, y0 + y, sign);
            set(x0 + x, y0 - y, sign);
            set(x0 - x, y0 + y, sign);
            set(x0 - x, y0 - y, sign);
            error = 2 * (delta + y) - 1;
            if (delta < 0 && error <= 0)
            {
                ++x;
                delta += 2 * x + 1;
                continue;
            }
            error = 2 * (delta - x) - 1;
            if (delta > 0 && error > 0)
            {
                --y;
                delta += 1 - 2 * y;
                continue;
            }
            ++x;
            delta += 2 * (x - y);
            --y;
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
        cin >> x >> y >> sign;
        current_canvas.set(x, y, sign);
        current_canvas.print();
    }

    return 0;
}
