#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define EPS 1e-9

int main(void)
{
    double a, b, c;
    double x_start, x_end, dx;

    printf("Enter parameters a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("Error: Invalid input for a, b, c.\n");
        return 1;
    }

    printf("Enter x_start, x_end, dx: ");
    if (scanf("%lf %lf %lf", &x_start, &x_end, &dx) != 3) {
        printf("Error: Invalid input for interval.\n");
        return 1;
    }

    if (dx <= 0.0) {
        printf("Error: Step dx must be greater than zero.\n");
        return 1;
    }

    if (x_start > x_end) {
        printf("Error: x_start cannot be greater than x_end.\n");
        return 1;
    }

    /* Bitwise condition: (Ac | Bc) ^ (Ac | Cc) */
    long a_c = (long)trunc(a);
    long b_c = (long)trunc(b);
    long c_c = (long)trunc(c);

    bool is_real = (((a_c | b_c) ^ (a_c | c_c)) != 0);

    printf("\nBitwise condition value: %ld (Output: %s)\n",
           ((a_c | b_c) ^ (a_c | c_c)),
           is_real ? "Real" : "Integer");

    printf("\n%-12s %-18s\n", "x", "F(x)");
    printf("------------------------------------\n");

    for (double x = x_start; x <= x_end + EPS; x += dx) {
        double F = 0.0;
        bool undefined = false;

        /* Branch 1: x < 5 and c != 0 */
        if (x < 5.0 - EPS && fabs(c) > EPS) {
            F = -a * x * x - b;
        }
        /* Branch 2: x > 5 and c == 0 */
        else if (x > 5.0 + EPS && fabs(c) < EPS) {
            if (fabs(x) < EPS) {
                undefined = true;
            } else {
                F = (x - a) / x;
            }
        }
        /* Branch 3: Otherwise */
        else {
            if (fabs(c) < EPS) {
                undefined = true; /* Division by zero */
            } else {
                F = -x / c;
            }
        }

        if (undefined) {
            printf("%-12.4f %-18s\n", x, "undefined");
        } else {
            if (is_real) {
                printf("%-12.4f %-18.4f\n", x, F);
            } else {
                printf("%-12.4f %-18.0f\n", x, F);
            }
        }
    }

    printf("------------------------------------\n");

    return 0;
}
