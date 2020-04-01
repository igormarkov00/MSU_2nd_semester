#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
extern double f1 (double x);
extern double f2 (double x);
extern double f3 (double x);
int num_of_it, num_out, points_out; //num_of_it - количество итераций при поиске корня
//num_out - индекатор надобности вывода количества итераций, points_out - индекатор надобности вывода абсцисс точек пересечения

double root (double (*f)(double), double (*g)(double), double a, double b, double eps1){
    while(1){
        num_of_it++;
        double x0 = a - (b - a) * (f(a) - g(a)) / (f(b) - f(a) + g(a) - g(b)), y0 = f(x0) - g(x0), d = b - a;
        //x0 - абсцисса точки пересечения, y0 - ордината точки пересечения, d - длина переданного отрезка
        if ((f(a) - g(a)) * y0 >= 0) a = x0;
        else b = x0; //смещение границ отрезка
        if (d - b + a <= eps1) return x0; //сравнение текущей точности с требуемой
    }
}

double integral (double (*f)(double), double a, double b, double eps2){
    double s0 = 0, s1 = 0, s = f(a) + f(b), d = (b - a) / 228;//s0 - переменная, хранящая интегральную сумму, полученную на предыдущем шаге
    //s1 - интегральная сумма на текущем щаге, d - длина интегральных отрезков, s - вспомогательная переменная
    for (double x = a + d; x < b; x += d){
        s += 2 * f(x);
    }
    s1 = s * 0,5 * d;//"нулевой" щаг цикла
    do{
        s0 = s1;
        for (double x = a + 0.5 * d; x < b; x += d){
            s += 2 * f(x);
        }
        d *= 0.5;
        s1 = 0.5 * d * s;
    } while (fabs(s1 - s0) > eps2);//цикл продолжается, пока не будет достигнута требуемая точность
    return s1;
}

void root_test (void){
    printf("You are now testing the root function\nPut your input data here in format f1 f2 a b eps:\n");
    int g1, g2;
    double a, b, eps;
    scanf("%d%d%lf%lf%lf", &g1, &g2, &a, &b, &eps);
    double (*f)(double), (*g)(double); //f и g - указатели на функции, передаваемые в root
    if (g1 == 1) f = f1;
    if (g1 == 2) f = f2;
    if (g1 == 3) f = f3;
    if (g2 == 1) g = f1;
    if (g2 == 2) g = f2;
    if (g2 == 3) g = f3;
    printf("The answer is %lf\n", root(f, g, a, b, eps));
    printf("Type 1 to continue, or 0 to quit\n");
    scanf("%d", &g1);
    if (g1) root_test();
    return;
}

void integral_test (void){
    printf("You are now testing the integral function\nPut your input data here in format f a b eps:\n");
    int f;
    double a, b, eps;
    scanf("%d%lf%lf%lf", &f, &a, &b, &eps);
    double (*g)(double); //g - указатель на функцию, передаваемую в integral
    if (f == 1) g = f1;
    if (f == 2) g = f2;
    if (f == 3) g = f3;
    printf("The answer is %lf\n", integral(g, a, b, eps));
    printf("Type 1 to continue, or 0 to quit\n");
    scanf("%d", &f);
    if (f) integral_test();
    return;
}

int main(int argc, char *argv[])
{
    //цикл ниже обрабатывает опции командной строки
    for (int i = 1; i < argc; ++i){
        if (!strcmp("-iterations", argv[i])) num_out++;
        if (!strcmp("-crosspoints", argv[i])) points_out++;
        if (!strcmp("-help", argv[i])){
            printf("Keys:\n");
            printf("  -iterations     Prints number of iterations for cross-points searching\n");
            printf("  -crosspoints    Prints abscissa coordinates of cross-points\n");
            printf("  -root_test      Root function testing mode\n");
            printf("  -integral_test  Integral function testing mode\n");
        }
        if (!strcmp("-root_test", argv[i])){
            root_test();
            return 0;
        }
        if (!strcmp("-integral_test", argv[i])){
            integral_test();
            return 0;
        }
    }
    //ниже представлен непосредственно алгоритм решения задачи
    if (num_out) printf("Number of iterations needed:\n");
    double eps = 0.000001, p12 = root(f1, f2, 5, 7, eps);
    if (num_out) printf("1x2: %d\n", num_of_it);
    num_of_it = 0;
    double p13 = root(f1, f3, 2.01, 3, eps);
    if (num_out) printf("1x3: %d\n", num_of_it);
    num_of_it = 0;
    double p23 = root(f3, f2, 3, 5, eps);
    if (num_out) printf("2x3: %d\n", num_of_it);
    if (points_out) printf("Cross-points are:\n1x2: %lf\n1x3: %lf\n2x3: %lf\n", p12, p13, p23);
    double i1 = integral(f1, (p12 < p13? p12 : p13), (p12 > p13? p12 : p13), eps);
    double i2 = integral(f2, (p12 < p23? p12 : p23), (p12 > p23? p12 : p23), eps);
    double i3 = integral(f3, (p23 < p13? p23 : p13), (p23 > p13? p23 : p13), eps);
    //printf("%lf %lf %lf\n", i1, i2, i3);
    double ans = i2 + i3 - i1;
    printf("\nS = %lf\n", ans);

    system("pause"); //систем пауз
    return 0;
}
