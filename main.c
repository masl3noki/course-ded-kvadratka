#include "usepackage.h"

//#define TESTMODE
/*!Как переключаться между квадраткой и Юнит-тестированием:
 * Чтобы переключиться на UNIT TEST, раскомментируйте строку #define TESTMODE
 * Чтобы переключиться на солвер квадратного уравнения, закомментируйте строку #define TESTMODE
 */

//! Для работы с return
enum RootCount
    {
        InfRoot = -1,
        NoRoot,
        OneRoot,
        TwoRoots,
        ComplexRoots
    };

//! Хаб, в котором происходит перераспределение коэффициентов в SolveLinear или SolveSquare
void SolveEq (double, double, double);

//! Солвер линейного уравнения вида b*y+c=0
enum RootCount SolveLinear (double, double, double complex * x1);

//! Солвер квадратного уравнения вида a*y^2+b*y+c=0
enum RootCount SolveSquare (double, double, double, double complex * x1, double complex * x2);

//! Сравнение double с нулем
bool cmpDouble (double, double);

//! AKA kvadratka.c: главная функция программы, на вход берет коэффициенты и выводит ответ
void kvadratka (void);

//! AKA UnitTest.c: Юнит-тестирование
void UnitTest (void);

int main(void)
{
#ifndef TESTMODE
    kvadratka();
    return 0;
#else
    UnitTest();
    return 0;
#endif
}

void kvadratka(void)
{
    SetConsoleOutputCP(CP_UTF8); //Русский язык в консоли
    double a = NAN, b = NAN, c = NAN;

    printf("Решаем квадратное уравнение с вещественными коэффициентами вида ax^2+bx+c=0 с точностью до %g\n", MAXPREC);
    printf("Введите коэффициенты уравнения a, b, c:\n");

    if (scanf("%lf %lf %lf", &a, &b, &c) < 3)
    {
        printf("ERROR: Введено недостаточное количество коэффициентов\n");
    }

    //assert (isfinite(a) && isfinite(b) && isfinite(c));
    assert (isfinite(a) && "ERROR: Coefficient a = NaN or inf.");
    assert (isfinite(b) && "ERROR: Coefficient b = NaN or inf.");
    assert (isfinite(c) && "ERROR: Coefficient c = NaN or inf.");

    SolveEq(a, b, c);
}

void SolveEq (double a, double b, double c)
{
    double complex x1 = NAN,
                   x2 = NAN;

    if (cmpDouble(a, MAXPREC))
        {
            printf("Введено уравнение %g*x%+g=0\n", b, c);
            switch (SolveLinear(b, c, &x1))
            {
                case InfRoot:
                    //printf("SolveLinear: b == 0, c == 0: любой корень\n");
                    printf("Любой корень из множества комплексных чисел С\n");
                    break;
                case NoRoot:
                    //printf("SolveLinear: b == 0, c != 0: нет корней\n");
                    printf("Нет корней");
                    break;
                case OneRoot:
                    //printf("SolveLinear: RE корень единственный: x=%g\n", creal(x1));
                    printf("Единственный корень: x=%g\n", creal(x1));
                    break;
                case TwoRoots:
                    printf("ERROR: SolveLinear: case TwoRoots: что-то пошло не так!");
                    break;
                case ComplexRoots:
                    printf("ERROR: SolveLinear: case ComplexRoots: что-то пошло не так!");
                    break;
            }
        }
    else
    {
        printf("Введено уравнение %g*x^2%+g*x%+g=0\n", a, b, c);
        switch (SolveSquare(a, b, c, &x1, &x2))
        {
            case InfRoot:
                //printf("SolveSquare: Бесконечное количество корней");
                printf("Любой корень из множества комплексных чисел С\n");
                break;
            case NoRoot:
                //printf("SolveSquare: Нет корней");
                printf("Нет корней");
                break;
            case OneRoot:
                //printf("SolveSquare: D = 0, RE корень 1 кратности два: x = %g\n", creal(x1));
                printf("Единственный корень кратности два: x = %g\n", creal(x1));
                break;
            case TwoRoots:
                //printf("SolveSquare: D > 0, RE корней 2: x1 = %g; x2 = %g\n", creal(x1), creal(x2));
                printf("Два вещественых корня единичной кратности: x1 = %g; x2 = %g\n", creal(x1), creal(x2));
                break;
            case ComplexRoots:
                //printf("SolveSquare: D < 0, IM корней 2: x1 = %g%+gi; x2 = %g%+gi\n", creal(x1), cimag(x1), creal(x2), cimag(x2));
                printf("Два комплекснозначных корня единичной кратности: x1 = %g%+gi; x2 = %g%+gi\n", creal(x1), cimag(x1), creal(x2), cimag(x2));
                break;
        }
    }
}

enum RootCount SolveLinear (double b, double c, double complex * x1)
{
    if (cmpDouble(b, MAXPREC))
    {
        if (cmpDouble(c, MAXPREC))
        {
            //printf("SolveLinear: b == 0, c == 0: любой корень\n");
            return InfRoot;
        } else
        {
            //printf("SolveLinear: b == 0, c != 0: нет корней\n");
            return NoRoot;
        }
    } else
    {
        *x1 = -c / b;
        if (*x1 == 0)
            *x1 = 0;
        assert (isfinite(creal(*x1)) && "ERROR: Root x1 = NaN or inf.");
        //printf("SolveLinear: RE корень единственный: x=%g\n", creal(*x1));
        return OneRoot;
    }
}

enum RootCount SolveSquare (double a,double b, double c, double complex * x1, double complex * x2) //Главное нахождение корней
{
    double D = b*b -4*a*c;

    if (D >= 0)
    {
        *x1 = (-b+sqrt(D))/(2*a);
        *x2 = (-b-sqrt(D))/(2*a);
        assert(isfinite(creal(*x1)) && "Root x1: Re(x1) = NAN of INF");
        assert(isfinite(cimag(*x1)) && "Root x1: Im(x1) = NAN of INF");
        assert(isfinite(creal(*x2)) && "Root x1: Re(x2) = NAN of INF");
        assert(isfinite(cimag(*x2)) && "Root x1: Im(x2) = NAN of INF");

        if ((creal(*x1) == creal(*x2)) && (cimag(*x1) == cimag(*x2)))
        {
            //printf("SolveSquare: D = 0, RE корень 1: x = %g\n", creal(*x1));
            return OneRoot;
        } else
        {
            //printf("SolveSquare: D > 0, RE корней 2: x1 = %g; x2 = %g\n", creal(*x1), creal(*x2));
            return TwoRoots;
        }
    } else
    if (D < 0)
    {
        *x1 = (-b+ sqrt(fabs(D)) * I)/(2*a);
        *x2 = (-b- sqrt(fabs(D)) * I)/(2*a);
        assert(isfinite(creal(*x1)) && "Root x1: Re(x1) = NAN of INF");
        assert(isfinite(cimag(*x1)) && "Root x1: Im(x1) = NAN of INF");
        assert(isfinite(creal(*x2)) && "Root x1: Re(x2) = NAN of INF");
        assert(isfinite(cimag(*x2)) && "Root x1: Im(x2) = NAN of INF");

        //printf("SolveSquare: D < 0, IM корней 2: x1 = %g%+gi; x2 = %g%+gi\n", creal(*x1), cimag(*x1), creal(*x2), cimag(*x2));
        return ComplexRoots;
    }
}

bool cmpDouble (double a, double b)
{
    if (fabs(fabs(a) - fabs(b)) <= MAXPREC)
        return TRUE;
    return FALSE;
}

void UnitTest(void)
{
    /*
    struct test
    {
        double a, b, c;
        double complex x1, x2;
    };
    //! Unit Test 1 //
    struct test UT1 = {
            1.365, 28.1476, 3.39476,
            NAN, NAN
    };
    count++;
    printf("Test %d:\n", count);
    SolveSquare(UT1.a, UT1.b, UT1.c, &UT1.x1, &UT1.x2);
    if (((creal(UT1.x1) == -20.4996) && (creal(UT1.x2) == -0.121319)) ||
        ((creal(UT1.x2) == -20.4996) && (creal(UT1.x1) == -0.121319)))
    {
        printf("PASSED\n");
    } else printf("FAILED\n");
    */
    
    printf("Идет Юнит-тестирование\n");
    int count = 0;
    enum RootCount RootCount;
    double complex x1 = 0,
                   x2 = 0;

    //! Unit Test 1 //

    count++;
    printf("Test %d:\n", count);
    SolveSquare(1, -4, 13,&x1, &x2);
    if (((x1 == 2 + 3*I) && (x2 == 2 - 3*I)) ||
        ((x2 == 2 + 3*I) && (x1 == 2 - 3*I)))
    {
        printf("PASSED\n");
    } else printf("FAILED\n");

    //! Unit Test 2 //

    count++;
    printf("Test %d:\n", count);
    SolveLinear(2, 4,&x1);
    if (creal(x1) == -2)
    {
        printf("PASSED\n");
    } else printf("FAILED\n");

    //! Unit Test 3 //

    count++;
    printf("Test %d:\n", count);
    RootCount = SolveLinear(0, 4,&x1);
    if (RootCount == 0)
    {
        printf("PASSED\n");
    } else printf("FAILED\n");

    //! Unit Test 4 //

    count++;
    printf("Test %d:\n", count);
    RootCount = SolveLinear(0, 0,&x1);
    if (RootCount == -1)
    {
        printf("PASSED\n");
    } else printf("FAILED\n");

    //! Unit Test 5 //

    count++;
    printf("Test %d:\n", count);
    SolveSquare(1, -4, 4,&x1, &x2);
    if (((x1 == 2 + 0*I) && (x2 == 2 + 0*I)) ||
        ((x2 == 2 + 0*I) && (x1 == 2 + 0*I)))
    {
        printf("PASSED\n");
    } else printf("FAILED\n");
}
