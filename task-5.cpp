#include <iostream>
#include <stdexcept>
#include <string>
 
using namespace std;

/*
* \brief пустой класс
*/
class except1 {};
 
/**
* \brief независимый класс с полями-параметрами функции
*/
class except2 {
    string msg;
public:
    except2(const string &s) : msg(s) {}
    const char *message() const { return msg.c_str(); }
};

/*
* \brief Класс наследник от стандартного исключения с полем
*/
class except3 : public invalid_argument {
    double num;
public:
    except3(const string msg, double n) : invalid_argument(msg), num(n) {}
    double arg() const { return num; }
};

/**
* \brief без спецификации исключений
*/
double root1(double a, double b, double c) {
    return a + b + c;
}
 
/**
* \brief со спецификацией throw()
*/
double root2(double a, double b, double c) throw() {
    return a + b + c;
}
 
/**
* \brief с конкретной спецификацией с подходящим стандартным исключением
*/
double root3(double a, double b, double c) throw(invalid_argument) {
    if (a <= 0.0 || b <= 0.0 || c <= 0.0)
        throw invalid_argument("Одна из длин меньше или равна 0");
    return a + b + c;
}
 
/**
* \brief Спецификация с собственным реализованным исключением
*/
double root4_1(double a, double b, double c) throw(except1) {
    if (a <= 0.0 || b <= 0.0 || c <= 0.0)
        throw except1();
    return a + b + c;
}

/**
* \brief Спецификация с собственным реализованным исключением
*/
double root4_2(double a, double b, double c) throw(except2) {
    if (a <= 0.0 || b <= 0.0 || c <= 0.0)
        throw except2("Одна из длин меньше или равна 0");
    return a + b + c;
}

/**
* \brief Спецификация с собственным реализованным исключением
*/
double root4_3(double a, double b, double c) throw(except3) {
    if (a <= 0.0)
        throw except3("Неверный аргумент", a);
    if (b <= 0.0)
        throw except3("Неверный аргумент", b);
    if (c <= 0.0)
        throw except3("Неверный аргумент", c);
    return a + b + c;
}
 
void helper(double (*func)(double, double, double)) {
    double a, b, c;
    cout << "Введите a= ";
    cin >> a;
    cout << "Введите b= ";
    cin >> b;
    cout << "Введите c= ";
    cin >> c;
    cout << "Периметр треугольника: " << func(a, b, c) << endl;
}
 
int main() {
    setlocale(LC_ALL, "rus");
    cout << "Программа считает периметр треугольника \n";
 
    try {
        helper(root1);
    }
    catch (...) {
        cout << "Произошло исключение в функции root1" << endl;
    }
 
    try {
        helper(root2);
    }
    catch (...) {
        cout << "Произошло исключение в функции root2" << endl;
    }
 
    try {
        helper(root3);
    }
    catch (invalid_argument &e) {
        cout << e.what() << endl;
    }
 
    try {
        helper(root4_1);
    }
    catch (except1) {
        cout << "Произошло исключение except1 в функции root4_1" << endl;
    }
 
    try {
        helper(root4_2);
    }
    catch (except2 &e) {
        cout << e.message() << endl;
    }
 
    try {
        helper(root4_3);
    }
    catch (except3 &e) {
        cout << e.what() << " " << e.arg() << endl;
    }
}