#include <stdio.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#endif

/* Допуск при сравнении вещественных чисел */
#define EPS 1e-9

int main(void)
{
    double a, b, c;
    double xn, xk, dx;
    double x, F;
    long i, n;
    int is_defined;

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    printf("============================================================\n");
    printf("   Лабораторная работа №1. Компьютерное программирование    \n");
    printf("   Тема: Операторы условия и циклов. Вариант 7              \n");
    printf("============================================================\n\n");

    printf("Введите коэффициенты a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3)
    {
        printf("Ошибка: некорректный ввод коэффициентов a, b, c.\n");
        return 1;
    }

    printf("Введите начальное значение xn, конечное xk и шаг dx: ");
    if (scanf("%lf %lf %lf", &xn, &xk, &dx) != 3)
    {
        printf("Ошибка: некорректный ввод параметров интервала.\n");
        return 1;
    }

    if (dx <= 0.0 || xn > xk)
    {
        printf("Ошибка: некорректные параметры интервала "
               "(требуется dx > 0 и xn <= xk).\n");
        return 1;
    }

    /* Целые части коэффициентов (floor, как в методических указаниях) */
    long a_c = (long)floor(a);
    long b_c = (long)floor(b);
    long c_c = (long)floor(c);

    /* Проверка битового условия: (Ац ИЛИ Вц) МОД2 (Ац ИЛИ Сц) */
    long bitwise_cond = (a_c | b_c) ^ (a_c | c_c);
    int print_as_real = (bitwise_cond != 0);

    printf("\nАнализ исходных данных:\n");
    printf("Целые части: Ац = %ld, Вц = %ld, Сц = %ld\n", a_c, b_c, c_c);
    printf("Выражение (Ац | Вц) ^ (Ац | Сц) = %ld\n", bitwise_cond);
    printf("Формат вывода F(x): %s\n\n",
           print_as_real ? "действительное число (условие != 0)"
                         : "целое число (условие == 0)");

    printf("----------------------------------------\n");
    printf("     x                 F(x)             \n");
    printf("----------------------------------------\n");

    /* Количество шагов на интервале */
    n = (long)floor((xk - xn) / dx + EPS);

    /* Цикл табулирования: x считается по номеру шага,
       чтобы погрешность сложения не накапливалась */
    for (i = 0; i <= n; i++)
    {
        x = xn + i * dx;

        /* Ветвь 1: x < 5 и c != 0 */
        if (x < 5.0 - EPS && c != 0.0)
        {
            F = -a * x * x - b;
            is_defined = 1;
        }
        /* Ветвь 2: x > 5 и c == 0 */
        else if (x > 5.0 + EPS && c == 0.0)
        {
            F = (x - a) / x;
            is_defined = 1;
        }
        /* Ветвь 3: в остальных случаях */
        else
        {
            if (c != 0.0)
            {
                F = -x / c;
                is_defined = 1;
            }
            else
            {
                /* Деление на ноль при c == 0 */
                is_defined = 0;
            }
        }

        /* Вывод текущей строки таблицы */
        if (is_defined)
        {
            if (print_as_real)
                printf("%10.4f       %15.4f\n", x, F);
            else
                printf("%10.4f       %15.0f\n", x, F);
        }
        else
        {
            printf("%10.4f       Функция не определена\n", x);
        }
    }

    printf("----------------------------------------\n");

    return 0;
}
