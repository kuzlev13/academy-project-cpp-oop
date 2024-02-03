#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


class NEW {
    string name;
    int height;
    int width;
    char** data;
public:
    NEW(string name, int height, int width) {
        this->name = name;
        this->height = height;
        this->width = width;
    }
    void save(char** data) {
        this->height = height;
        this->width = width;
        this->data = data;
        //cout << file;
        ofstream MyFile(name + ".txt");
        MyFile << width << "\n";
        MyFile << height << "\n";
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->width; j++)
            {
                if (this->data[i][j])
                {
                    MyFile << this->data[i][j];
                }
                else
                {
                    MyFile << ' ';
                }
            }
            MyFile << "\n";
        }
        MyFile.close();
    }
    void create() {
        string file = name + ".txt";
        //cout << file;
        ofstream MyFile(file);
    }
};


class canvas
{
private:
    char** data;
    int width;
    int height;

public:
    void save(string name) {
        NEW ne{ name,height,width };
        ne.save(data);
    }
    void setDot(int x, int y, char sign)
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
    void Clear()
    {
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->width; j++)
            {
                this->data[i][j] = ' ';
            }
        }
    }
    void setLine(int x1, int y1, int x2, int y2, char sign)
    {
        const int deltaX = abs(x2 - x1);
        const int deltaY = abs(y2 - y1);
        const int signX = (x1 < x2) ? 1 : -1;
        const int signY = (y1 < y2) ? 1 : -1;
        int error = deltaX - deltaY;
        setDot(x2, y2, sign);
        while (x1 != x2 || y1 != y2)
        {
            setDot(x1, y1, sign);
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
            setDot(x0 + x, y0 + y, sign);
            setDot(x0 + x, y0 - y, sign);
            setDot(x0 - x, y0 + y, sign);
            setDot(x0 - x, y0 - y, sign);
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
    void fill(int x0, int y0, char sign)
    {
        char based_sign = this->data[y0][x0];

        if (x0 == 0 && y0 == 0)
        {
            if (this->data[y0][x0 + 1] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0 + 1, y0, sign);
            }
            if (this->data[y0 + 1][x0] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0, y0 + 1, sign);
            }
        }
        else if (x0 == (this->width - 1) && y0 == (this->height - 1))
        {
            if (this->data[y0][x0 - 1] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0 - 1, y0, sign);
            }
            if (this->data[y0 - 1][x0] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0, y0 - 1, sign);
            }
        }
        else if (x0 == 0 && y0 == (this->height - 1))
        {
            if (this->data[y0][x0 + 1] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0 + 1, y0, sign);
            }
            if (this->data[y0 - 1][x0] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0, y0 - 1, sign);
            }
        }
        else if (x0 == (this->width - 1) && y0 == 0)
        {
            if (this->data[y0 + 1][x0] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0, y0 + 1, sign);
            }
            if (this->data[y0][x0 - 1] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0 - 1, y0, sign);
            }
        }
        else if (x0 == 0)
        {
            if (this->data[y0][x0 + 1] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0 + 1, y0, sign);
            }
            if (this->data[y0 + 1][x0] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0, y0 + 1, sign);
            }
            if (this->data[y0 - 1][x0] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0, y0 - 1, sign);
            }
        }
        else if (y0 == 0)
        {
            if (this->data[y0][x0 + 1] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0 + 1, y0, sign);
            }
            if (this->data[y0 + 1][x0] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0, y0 + 1, sign);
            }
            if (this->data[y0][x0 - 1] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0 - 1, y0, sign);
            }
        }
        else if (x0 == (this->width - 1))
        {
            if (this->data[y0 + 1][x0] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0, y0 + 1, sign);
            }
            if (this->data[y0][x0 - 1] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0 - 1, y0, sign);
            }
            if (this->data[y0 - 1][x0] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0, y0 - 1, sign);
            }
        }
        else if (y0 == (this->height - 1))
        {
            if (this->data[y0][x0 + 1] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0 + 1, y0, sign);
            }
            if (this->data[y0][x0 - 1] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0 - 1, y0, sign);
            }
            if (this->data[y0 - 1][x0] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0, y0 - 1, sign);
            }
        }
        else
        {
            if (this->data[y0][x0 + 1] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0 + 1, y0, sign);
            }
            if (this->data[y0 + 1][x0] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0, y0 + 1, sign);
            }
            if (this->data[y0][x0 - 1] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0 - 1, y0, sign);
            }
            if (this->data[y0 - 1][x0] == based_sign)
            {
                setDot(x0, y0, sign);
                fill(x0, y0 - 1, sign);
            }
        }
    }

    canvas(int width, int height)
    {
        this->height = height;
        this->width = width;
        this->data = new char* [height];
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

class OPEN {
    string s;
    string s1;
    string name;
    int width;
    int height;
    char g;
    int iriski = 0;
public:
    OPEN(string _name, string s) {
        this->name = _name;
        this->s = s;
    }

    int open() {
        string file = name + ".txt";
        char ch;
        fstream fin;
        fin.open(file);
        if (!fin.is_open()) {
            cout << "ERROR";
        }
        else {

            cout << "TRUE\n";

            while (getline(fin, s)) { // пока не достигнут конец файла класть очередную строку в переменную (s)
                if (iriski == 0) {
                    //cout << s;
                    istringstream(s) >> width;
                }
                else if (iriski == 1) {
                    //cout << s;
                    //int(s);
                    istringstream(s) >> height;
                    break;
                }
                iriski++;
            }
            iriski--;
            //cout << iriski << "\n";
            canvas new_canvas(width, height);
            while (getline(fin, s1)) { 
                int r = size(s1);
                //cout << r << "\n";
                for (int i = 0; i < r; i++) {
                    g = s1.at(i);
                    //cout << "\n" << s1;
                    new_canvas.setDot(i, iriski, g);
                }
                iriski++;
            }
            int x0, y0, x1, y1, input, radius, a, b, c, d, a0, b0, c0, d0;
            new_canvas.print();
            cout << "\n\n";
            while (true)
            {
                cout << "Choose function:\n0.Print\n1.Dot\n2.Line\n4.Circle\n5.Clear\n6.Fill\n7.Quadrilateral\n8.Triangle\n9.Save\n10.Exit\n: ";
                cin >> input;
                switch (input)
                {
                case 0:
                    //system("cls");
                    new_canvas.print();
                    break;
                case 1:
                    cout << "Enter the coordinate of the dot and sign by space\n";
                    cin >> x0 >> y0 >> g;
                    new_canvas.setDot(x0, y0, g);
                    break;
                case 2:
                    cout << "Enter the coordinate of the 1st dot by space\n";
                    cin >> x0 >> y0;
                    cout << "Enter the coordinate of the 2nd dot and sign by space\n";
                    cin >> x1 >> y1 >> g;
                    new_canvas.setLine(x0, y0, x1, y1, g);
                    break;
                case 3:
                    cout << "Portal 3 won't be released\n"
                        << endl;
                    break;
                case 4:
                    cout << "Enter the coordinate of the center, radius and sign by space\n";
                    cin >> x0 >> y0 >> radius >> g;
                    new_canvas.setCircle(x0, y0, radius, g);
                    break;
                case 5:
                    new_canvas.Clear();
                    break;
                case 6:
                    cout << "Enter the coordinate of the dot-fill and sign by space\n";
                    cin >> x0 >> y0 >> g;
                    new_canvas.fill(x0, y0, g);
                    break;

                case 7:
                    cout << "\nEnter the coordinate of the 1nd dot and sign by space\n";
                    cin >> a >> a0 >> g;
                    cout << "\nEnter the coordinate of the 2nd dot and sign by space\n";
                    cin >> b >> b0 >> g;
                    cout << "\nEnter the coordinate of the 3nd dot and sign by space\n";
                    cin >> c >> c0 >> g;
                    cout << "\nEnter the coordinate of the 4nd dot and sign by space\n";
                    cin >> d >> d0 >> g;
                    new_canvas.setLine(a, a0, b, b0, g);
                    new_canvas.setLine(a, a0, c, c0, g);
                    new_canvas.setLine(c, c0, d, d0, g);
                    new_canvas.setLine(d, d0, b, b0, g);
                    break;

                case 8:
                    cout << "\nEnter the coordinate of the 1nd dot and sign by space\n";
                    cin >> a >> a0 >> g;
                    cout << "\nEnter the coordinate of the 2nd dot and sign by space\n";
                    cin >> b >> b0 >> g;
                    cout << "\nEnter the coordinate of the 3nd dot and sign by space\n";
                    cin >> c >> c0 >> g;
                    new_canvas.setLine(a, a0, b, b0, g);
                    new_canvas.setLine(a, a0, c, c0, g);
                    new_canvas.setLine(c, c0, b, b0, g);
                    break;

                case 9:
                    new_canvas.save(name);
                    break;
                case 10:
                    int what;
                    cout << "save file?(1 - yes, 2 - no) - ";
                    cin >> what;
                    int a = 0;
                    while (a == 0) {
                        if (what == 1) {
                            new_canvas.save(name);
                            return 0;
                        }
                        else if (what == 2) {
                            return 0;
                        }
                        else {
                            cout << "error";
                            cout << "\nsave file?(1 - yes, 2 - no) - ";
                            cin >> what;
                        }
                    }
                    break;
                }
            }
        }

        fin.close();
        
        
    }
    int GETwidth() {
        return width;

    }
    int GETheight() {
        return height;
    }

};

int main()
{
    string s;
    int height, width, action;
    string name;
    cout << "0 - open project\n1 - new project\n";
    cout << "Please choose an action:";
    cin >> action;
    if (action == 0) {
        cout << "Please enter project name :";
        cin >> name;
        OPEN op{ name,s };
        op.open();
    }
    else if (action == 1) {
        cout << "Please enter name for new project :";
        cin >> name;
        cout << "Please, enter the width and height by space: ";
        cin >> width >> height;
        NEW ne{ name,height,width };
        ne.create();
        canvas current_canvas(width, height);
        int x0, y0, x1, y1, input, radius,a,b,c,d, a0, b0, c0, d0;
        char sign;
        current_canvas.Clear();
        while (true)
        {
            cout << "Choose function:\n0.Print\n1.Dot\n2.Line\n4.Circle\n5.Clear\n6.Fill\n7.Quadrilateral\n8.Triangle\n9.Save\n10.Exit\n: ";
            cin >> input;
            switch (input)
            {
            case 0:
                //system("cls");
                current_canvas.print();
                break;
            case 1:
                cout << "Enter the coordinate of the dot and sign by space\n";
                cin >> x0 >> y0 >> sign;
                current_canvas.setDot(x0, y0, sign);
                break;
            case 2:
                cout << "Enter the coordinate of the 1st dot by space\n";
                cin >> x0 >> y0;
                cout << "Enter the coordinate of the 2nd dot and sign by space\n";
                cin >> x1 >> y1 >> sign;
                current_canvas.setLine(x0, y0, x1, y1, sign);
                break;
            case 3:
                cout << "Portal 3 won't be released\n"
                    << endl;
                break;
            case 4:
                cout << "Enter the coordinate of the center, radius and sign by space\n";
                cin >> x0 >> y0 >> radius >> sign;
                current_canvas.setCircle(x0, y0, radius, sign);
                break;
            case 5:
                current_canvas.Clear();
                break;
            case 6:
                cout << "Enter the coordinate of the dot-fill and sign by space\n";
                cin >> x0 >> y0 >> sign;
                current_canvas.fill(x0, y0, sign);
                break;

            case 7:
                cout << "\nEnter the coordinate of the 1nd dot and sign by space\n";
                cin >> a >> a0 >> sign;
                cout << "\nEnter the coordinate of the 2nd dot and sign by space\n";
                cin >> b >> b0 >> sign;
                cout << "\nEnter the coordinate of the 3nd dot and sign by space\n";
                cin >> c >> c0 >> sign;
                cout << "\nEnter the coordinate of the 4nd dot and sign by space\n";
                cin >> d >> d0 >> sign;
                current_canvas.setLine(a,a0,b,b0, sign);
                current_canvas.setLine(a,a0,c,c0, sign);
                current_canvas.setLine(c,c0,d,d0, sign);
                current_canvas.setLine(d,d0,b,b0, sign);
                break;

            case 8:
                cout << "\nEnter the coordinate of the 1nd dot and sign by space\n";
                cin >> a >> a0 >> sign;
                cout << "\nEnter the coordinate of the 2nd dot and sign by space\n";
                cin >> b >> b0 >> sign;
                cout << "\nEnter the coordinate of the 3nd dot and sign by space\n";
                cin >> c >> c0 >> sign;
                current_canvas.setLine(a, a0, b, b0, sign);
                current_canvas.setLine(a, a0, c, c0, sign);
                current_canvas.setLine(c, c0, b, b0, sign);
                break;

            case 9:
                current_canvas.save(name);
                break;
            case 10:
                int what;
                cout << "save file?(1 - yes, 2 - no) - ";
                cin >> what;
                int a = 0;
                while (a == 0) {
                    if (what == 1) {
                        current_canvas.save(name);
                        return 0;
                    }
                    else if (what == 2) {
                        return 0;
                    }
                    else {
                        cout << "error";
                        cout << "\nsave file?(1 - yes, 2 - no) - ";
                        cin >> what;
                    }
                }
                break;
            }
        }
    }
    return 0;
}
