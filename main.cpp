#include <iostream>
#include "vector"
#include <cmath>

using namespace std;

// Точка
class dot {
public:
    double x;
    double y;

    dot(int x1 = 0, int y1 = 0) {
        x = x1;
        y = y1;
    }

    dot(dot &copy) {
        x = copy.x;
        y = copy.y;
    }

    dot &operator=(const dot &copy) {
        x = copy.x;
        y = copy.y;
        return *this;
    }

    void print() const {
        cout << x << " " << y << endl;
    }

    double distance(dot &another_dot) {
        return sqrt(pow((x - another_dot.x), 2) + pow((y - another_dot.y), 2));
    }
};

// Ломаная линия
class polyline : public dot{
protected:
    int amount_of_dots;
    dot dots[1024];
public:
    polyline() {
        amount_of_dots = 0;
    }

    polyline(int amount, dot input_dots[]) {
        amount_of_dots = amount;
        for (int i = 0; i < amount; ++i) {
            dots[i] = input_dots[i];
        }
    }

    polyline(polyline &copy) {
        amount_of_dots = copy.amount_of_dots;
        for (int i = 0; i < amount_of_dots; ++i) {
            dots[i] = copy.dots[i];
        }
    }

    polyline &operator=(const polyline &copy) {
        amount_of_dots = copy.amount_of_dots;
        for (int i = 0; i < amount_of_dots; ++i) {
            dots[i] = copy.dots[i];
        }
        return *this;
    }

    double perimeter() {
        double result = 0;
        for (int i = 0; i < amount_of_dots - 1; ++i) {
            result += dots[i].distance(dots[i + 1]);
        }
        return result;
    }
};

//Замкнутая ломаная линия
class closed_polyline : public polyline {
public:
    closed_polyline() {
        amount_of_dots = 0;
    }

    closed_polyline(int amount, dot input_dots[]) {
        amount_of_dots = amount;
        for (int i = 0; i < amount; ++i) {
            dots[i] = input_dots[i];
        }
    }

    closed_polyline(closed_polyline &copy) {
        amount_of_dots = copy.amount_of_dots;
        for (int i = 0; i < amount_of_dots; ++i) {
            dots[i] = copy.dots[i];
        }
    }

    closed_polyline &operator=(const closed_polyline &copy) {
        amount_of_dots = copy.amount_of_dots;
        for (int i = 0; i < amount_of_dots; ++i) {
            dots[i] = copy.dots[i];
        }
        return *this;
    }

    double perimeter() {
        double result = 0;
        for (int i = 0; i < amount_of_dots - 1; ++i) {
            result += dots[i].distance(dots[i + 1]);
        }
        return result + dots[0].distance(dots[amount_of_dots - 1]);
    }
};

//многоугольник
class polygon : public closed_polyline {
public:
    polygon() {
        amount_of_dots = 0;
    }

    polygon(int amount, dot input_dots[]) {
        amount_of_dots = amount;
        for (int i = 0; i < amount; ++i) {
            dots[i] = input_dots[i];
        }
    }

    polygon(polygon &copy) {
        amount_of_dots = copy.amount_of_dots;
        for (int i = 0; i < amount_of_dots; ++i) {
            dots[i] = copy.dots[i];
        }
    }

    polygon &operator=(const polygon &copy) {
        amount_of_dots = copy.amount_of_dots;
        for (int i = 0; i < amount_of_dots; ++i) {
            dots[i] = copy.dots[i];
        }
        return *this;
    }

    double area() {
        double result = 0;
        double sum1 = 0, sum2 = 0;
        for (int i = 0; i < amount_of_dots - 1; i++) {
            sum1 += dots[i].x * dots[i + 1].y;
            sum2 += dots[i + 1].x * dots[i].y;
        }
        sum1 += dots[amount_of_dots - 1].x * dots[0].y;
        sum2 += dots[0].x * dots[amount_of_dots - 1].y;
        result = abs((sum1 - sum2)) / 2;
        return result;
    }
};

int main(){
    dot d1, d2 = {1, 2};
    d1.print();
    d2.print();
    d1 = d2;
    d2 = {0, 0};
    d1.print();
    d2.print();
    dot d[4];
    d[0] = {0, 0};
    d[1] = {0, 1};
    d[2] = {1, 1};
    d[3] = {1, 0};
    polyline pl1 = {3, d}, pl2;
    pl2 = pl1;
    cout << pl2.perimeter() << endl;
    closed_polyline cpl1 = {3, d}, cpl2;
    cpl2 = cpl1;
    cout << cpl2.perimeter() << endl;
    polygon pol1 = {4, d};
    cout << pol1.perimeter() << " " << pol1.area() << endl;

    return 0;
}
