#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>


// Выходы программы:
// 4 - Трапеция не имеет параллельных сторон
// 3 - Многоугольник имеет пересекающиеся отрезки
// 2 - Дано недостаточно точек
// 1 - Правильный многоугольник задан неправильно

using namespace std;

// Точка
class point {
private:
    double x_;
    double y_;
public:
    double x() {
        return x_;
    }

    double y() {
        return y_;
    }

    point(int x1 = 0, int y1 = 0) {
        x_ = x1;
        y_ = y1;
    }

    point(point &copy) {
        x_ = copy.x_;
        y_ = copy.y_;
    }

    point &operator=(const point &copy) = default;

    ~point() = default;

    void print() const {
        cout << x_ << " " << y_ << endl;
    }

    double distance(point &another_dot) {
        return sqrt(pow((x_ - another_dot.x_), 2) + pow((y_ - another_dot.y_), 2));
    }
};

// Ломаная линия
class polyline {
protected:
    int amount_of_dots;
    point dots[1024];
public:
    polyline() {
        amount_of_dots = 0;
    }

    polyline(int amount, point input_dots[]) {
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

    closed_polyline(int amount, point input_dots[]) {
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

// Многоугольник
class polygon : public closed_polyline {
private:
    static bool is_crossed(point a, point b, point c, point d) {
        double common = (b.x() - a.x()) * (d.y() - c.y()) - (b.y() - a.y()) * (d.x() - c.x());
        if (common == 0) return false;

        double rH = (a.y() - c.y()) * (d.x() - c.x()) - (a.x() - c.x()) * (d.y() - c.y());
        double sH = (a.y() - c.y()) * (b.x() - a.x()) - (a.x() - c.x()) * (b.y() - a.y());

        double r = rH / common;
        double s = sH / common;

        if (r >= 0 && r <= 1 && s >= 0 && s <= 1) {
            return true;
        } else {
            return false;
        }
    }

protected:
    bool are_crossed() {
        for (int i = 1; i < amount_of_dots - 1; i++) {
            for (int j = 0; j < i; j++) {
                if ((j + 1 != i) && is_crossed(dots[j], dots[j + 1], dots[i], dots[i + 1])) {
                    return true;
                }
            }
        }
        for (int i = 1; i < amount_of_dots - 2; i++) {
            if (is_crossed(dots[amount_of_dots - 1], dots[0], dots[i], dots[i + 1])) {
                return true;
            }
        }
        return false;
    }

public:
    polygon() {
        amount_of_dots = 0;
    }

    polygon(int amount, point input_dots[]) {
        amount_of_dots = amount;
        for (int i = 0; i < amount; ++i) {
            dots[i] = input_dots[i];
        }
        if (are_crossed()) {
            exit(3);
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
            sum1 += dots[i].x() * dots[i + 1].y();
            sum2 += dots[i + 1].x() * dots[i].y();
        }
        sum1 += dots[amount_of_dots - 1].x() * dots[0].y();
        sum2 += dots[0].x() * dots[amount_of_dots - 1].y();
        result = abs((sum1 - sum2)) / 2;
        return result;
    }
};

// Треугольник
class triangle : public polygon {
public:
    triangle() {
        amount_of_dots = 0;
    }

    triangle(point input_dots[]) {
        amount_of_dots = 3;
        dots[0] = input_dots[0];
        dots[1] = input_dots[1];
        dots[2] = input_dots[2];
    }

    triangle(triangle &copy) {
        amount_of_dots = copy.amount_of_dots;
        dots[0] = copy.dots[0];
        dots[1] = copy.dots[1];
        dots[2] = copy.dots[2];
    }

    triangle &operator=(triangle &copy) {
        amount_of_dots = copy.amount_of_dots;
        dots[0] = copy.dots[0];
        dots[1] = copy.dots[1];
        dots[2] = copy.dots[2];
        return *this;
    }
};

// Трапеция
class trapezoid : public polygon {
protected:
    static bool are_parallel(point a1, point a2, point b1, point b2) {
        double ax = a2.x() - a1.x();
        double ay = a2.y() - a1.y();
        double bx = b2.x() - b1.x();
        double by = b2.y() - b1.y();

        if (ay == 0) ay = 1;
        if (by == 0) by = 1;

        double a = ax / ay;
        double b = bx / by;

        if (a == b)
            return true;
        return false;
    }

public:
    trapezoid() {
        amount_of_dots = 0;
    }

    trapezoid(point input_dots[]) {
        amount_of_dots = 4;
        for (int i = 0; i < 4; ++i) {
            dots[i] = input_dots[i];
        }
        if (are_crossed()) {
            exit(3);
        }
        if (!are_parallel(dots[0], dots[1], dots[2], dots[3]) && !are_parallel(dots[1], dots[2], dots[0], dots[3])) {
            exit(4);
        }
    }

    trapezoid(trapezoid &copy) {
        amount_of_dots = copy.amount_of_dots;
        for (int i = 0; i < 4; ++i) {
            dots[i] = copy.dots[i];
        }
    }

    trapezoid &operator=(trapezoid &copy) {
        amount_of_dots = copy.amount_of_dots;
        for (int i = 0; i < 4; ++i) {
            dots[i] = copy.dots[i];
        }
        return *this;
    }
};

// Правильный многоугольник
class regular_polygon : public polygon {
public:
    regular_polygon() {
        amount_of_dots = 0;
    }

    regular_polygon(int amount, point input_dots[]) {
        amount_of_dots = amount;
        if (amount_of_dots < 3) {
            exit(2);
        }
        for (int i = 0; i < amount; ++i) {
            dots[i] = input_dots[i];
        }
        double side = dots[0].distance(dots[amount_of_dots - 1]);
        for (int i = 0; i < amount_of_dots - 1; ++i) {
            if (dots[i].distance(dots[i + 1]) != side) {
                exit(1);
            }
        }
        if (are_crossed()) {
            exit(3);
        }
    }

    regular_polygon(regular_polygon &copy) {
        amount_of_dots = copy.amount_of_dots;
        for (int i = 0; i < amount_of_dots; ++i) {
            dots[i] = copy.dots[i];
        }
    }

    regular_polygon &operator=(const regular_polygon &copy) {
        amount_of_dots = copy.amount_of_dots;
        for (int i = 0; i < amount_of_dots; ++i) {
            dots[i] = copy.dots[i];
        }
        return *this;
    }
};

// Полином
class polynomial {
private:
    vector<double> coefficients;

    static string indeterminate(unsigned long power) {
        switch (power) {
            case (0):
                return "";
            case (1):
                return "x";
            default:
                return "x^" + to_string(power);
        }
    }

    static char sign(double number) {
        if (number < 0) return '-';
        return '+';
    }

public:
    polynomial() {
        coefficients.push_back(0);
    }

    polynomial(const vector<int> &input_coefficients) {
        for (int input_coefficient: input_coefficients) {
            coefficients.push_back(input_coefficient);
        }
    }

    polynomial &operator=(const polynomial &copy) {
        coefficients = copy.coefficients;
        return *this;
    }

    ~polynomial() = default;

    bool operator==(polynomial &pol) {
        return coefficients == pol.coefficients;
    }

    bool operator!=(polynomial &pol) {
        return !(coefficients == pol.coefficients);
    }

    polynomial &operator+(const polynomial &pol) {
        for (int i = 0; i < pol.coefficients.size(); ++i) {
            if (i > coefficients.size() - 1) {
                coefficients.push_back(pol.coefficients[i]);
            } else {
                coefficients[i] += pol.coefficients[i];
            }
        }
        while (coefficients[coefficients.size() - 1] == 0) {
            coefficients.pop_back();
        }
        return *this;
    }

    polynomial &operator+=(const polynomial &pol) {
        for (int i = 0; i < pol.coefficients.size(); ++i) {
            if (i > coefficients.size() - 1) {
                coefficients.push_back(pol.coefficients[i]);
            } else {
                coefficients[i] += pol.coefficients[i];
            }
        }
        while (coefficients[coefficients.size() - 1] == 0) {
            coefficients.pop_back();
        }
        return *this;
    }

    polynomial &operator-() {
        for (double &coefficient: coefficients) {
            coefficient = -coefficient;
        }
        return *this;
    }

    polynomial &operator-(const polynomial &pol) {
        for (int i = 0; i < pol.coefficients.size(); ++i) {
            if (i > coefficients.size() - 1) {
                coefficients.push_back(-pol.coefficients[i]);
            } else {
                coefficients[i] -= pol.coefficients[i];
            }
        }
        while (coefficients[coefficients.size() - 1] == 0) {
            coefficients.pop_back();
        }
        return *this;
    }

    polynomial &operator-=(const polynomial &pol) {
        for (int i = 0; i < pol.coefficients.size(); ++i) {
            if (i > coefficients.size() - 1) {
                coefficients.push_back(-pol.coefficients[i]);
            } else {
                coefficients[i] -= pol.coefficients[i];
            }
        }
        while (coefficients[coefficients.size() - 1] == 0) {
            coefficients.pop_back();
        }
        return *this;
    }

    polynomial &operator*(int number) {
        for (double &coefficient: coefficients) {
            coefficient *= number;
        }
        return *this;
    };

    polynomial &operator*=(int number) {
        for (double &coefficient: coefficients) {
            coefficient *= number;
        }
        return *this;
    };

    polynomial &operator/(int number) {
        for (double &coefficient: coefficients) {
            coefficient *= number;
        }
        return *this;
    };

    polynomial &operator/=(int number) {
        for (double &coefficient: coefficients) {
            coefficient *= number;
        }
        return *this;
    };

    friend ostream &operator<<(ostream &os, polynomial &out) {
        if (out.coefficients[out.coefficients.size() - 1] < 0) {
            os << "- " << abs(out.coefficients[out.coefficients.size() - 1])
               << indeterminate(out.coefficients.size() - 1);
        } else {
            os << abs(out.coefficients[out.coefficients.size() - 1])
               << indeterminate(out.coefficients.size() - 1);
        }

        for (int i = (int) out.coefficients.size() - 2; i >= 0; --i) {
            if (out.coefficients[i] != 0) {
                os << " " << sign(out.coefficients[i]) << " " << abs(out.coefficients[i]) << indeterminate(i);
            }
        }
        return os;
    }

    // При чтении с консоли полином обязательно должен заканчиваться каким-либо коэффициентом 0 степени.
    friend istream &operator>>(istream &is, polynomial &in) {
        string element;
        in.coefficients.resize(0);
        bool positive = true;
        bool first = true;
        while (is >> element) {
            if (element == "-") {
                positive = false;
                continue;
            }
            if (element == "+") {
                positive = true;
                continue;
            }
            int coefficient = 0;
            int power = 0;
            int i = 0;
            while ((element[i] != 'x') and (element[i] != '\n')) {
                i++;
                if (element.size() < i + 1) {
                    element += '\n';
                    break;
                }
            }
            if (i == 0) {
                coefficient = 1;
            } else {
                for (int j = 0; j < i; j++) {
                    coefficient *= 10;
                    coefficient += element[j] - '0';
                }
            }
            if (element[i] != '\n') {
                if (element[i + 1] == '^') {
                    for (int j = i + 2; j < element.size(); ++j) {
                        power *= 10;
                        power += element[j] - '0';
                    }
                } else {
                    power = 1;
                }
            }
            int sign = 1;
            if (!positive) sign = -1;
            if (first) {
                in.coefficients.resize(power + 1);
                first = false;
            }
            in.coefficients[power] = sign * coefficient;
            if ((element[i] == '\n') or (power == 0)) {
                break;
            }
        }
        return is;
    }

    double &operator[](const int &index) {
        return coefficients[index];
    }
};

int main() {
    point d1, d2 = {1, 2};
    d1.print();
    d2.print();
    d1 = d2;
    d2 = {0, 0};
    d1.print();
    d2.print();
    point d[4];
    d[0] = {0, 0};
    d[1] = {0, 1};
    d[2] = {1, 1};
    d[3] = {1, 0};
    polyline pl1 = {4, d};
    cout << "polyline " << pl1.perimeter() << endl;
    closed_polyline cpl1 = {3, d}, cpl2;
    cpl2 = cpl1;
    cout << cpl2.perimeter() << endl;
    polygon pol1 = {4, d};
    cout << pol1.perimeter() << " " << pol1.area() << endl;
    triangle t1(d);
    cout << t1.area() << endl;
    regular_polygon rp1 = {4, d};
    vector<int> vec, vec2;
    vec.push_back(1);
    vec.push_back(-2);
    vec.push_back(-3);
    vec2.push_back(3);
    vec2.push_back(-5);
    polynomial poly1(vec), poly2(vec2);
    cout << poly1;
    poly2 += poly1;
    cout << endl << poly2;
    poly2 = -poly1;
    cout << endl << poly2;
    cout << endl << (poly2 == poly1);
    cout << endl << poly2[2] << endl;
    cin >> poly2;
    cout << poly2 << endl;
    polynomial pol3;
    cin >> pol3;
    cout << pol3[2];
    return 0;
}