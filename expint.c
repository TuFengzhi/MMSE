//
// Created by Tu Fengzhi on 2018/10/22.
//

#include "expint.h"
#include "const.h"

#include <math.h>

#define MAXIT 100
#define EULER 0.5772156649
#define FPMIN 1.0e-30
#define EPS 1.0e-7

float expint(int n, float x)
{
    void nrerror(char error_text[]);
    int i, ii, nm1;
    float a, b, c, d, del, fact, h, psi, ans;

    nm1 = n - 1;
    if (n < 0 || x < 0.0 || (x == 0.0 && (n == 0 || n == 1)))
        printf("bad arguments in expint");
    else
    {
        if (n == 0)
            ans = exp(-x) / x;
        else
        {
            if (x == 0.0)
                ans = 1.0 / nm1;

            else
            {
                if (x > 1.0)
                {
                    b = x + n;
                    c = 1.0 / FPMIN;
                    d = 1.0 / b;
                    h = d;
                    for (i = 1; i <= MAXIT; i++)
                    {
                        a = -i * (nm1 + i);
                        b += 2.0;
                        d = 1.0 / (a * d + b);
                        c = b + a / c;
                        del = c * d;
                        h *= del;
                        if (fabs(del - 1.0) < EPS)
                        {
                            ans = h * exp(-x);
                            return ans;
                        }
                    }
                    printf("continued fraction failed in expint");
                }
                else
                {
                    ans = (nm1 != 0 ? 1.0 / nm1 : -log(x) - EULER);
                    fact = 1.0;
                    for (i = 1; i <= MAXIT; i++)
                    {
                        fact *= -x / i;
                        if (i != nm1)
                            del = -fact / (i - nm1);
                        else
                        {
                            psi = -EULER;
                            for (ii = 1; ii <= nm1; ii++)
                                psi += 1.0 / ii;
                            del = fact * (-log(x) + psi);
                        }
                        ans += del;
                        if (fabs(del) < fabs(ans) * EPS)
                            return ans;
                    }
                    printf("series failed in expint");
                }
            }
        }
    }
    return ans;
}

#undef MAXIT
#undef EPS
#undef FPMIN
#undef EULER

/* (C) Copr. 1986-92 Numerical Recipes Software ?421.1-9. */
float linear_value(float Start, float Step, float Input, float *Space)
{
    int Index = (int)((Input - Start) / Step);
    float X1 = Start + Step * Index;
    float X2 = Start + Step * (Index + 1);
    float Y1 = Space[Index];
    float Y2 = Space[Index + 1];

    float Ans = Y1 + (Y2 - Y1) / (X2 - X1) * (Input - X1);
    printf("%f %f %f %f %f %f\n", X1, Input, X2, Y1, Ans, Y2);
    return Ans;
}

float expint_interpolation(float x)
{
    float ans = 0;
    if (x < 0.001F)
    {
        ans = 6.33153936413615F;
    }
    else if (x < 0.5F)
    {
        // 0.001:0.001:0.5
        linear_value(0.001, 0.001, x, ExpintTable1);
    }
    else if (x < 1.5F)
    {
        // 0.5:0.004:1.5
        linear_value(0.5, 0.004, x, ExpintTable2);
    }
    else if (x < 3.5F)
    {
        // 1.5:0.016:3.5
        linear_value(1.5, 0.016, x, ExpintTable3);
    }
    else if (x < 11.436F)
    {
        // 3.5:0.128:11.5
        linear_value(3.5, 0.128, x, ExpintTable4);
    }
    else
    {
        ans = 8.73366540296160e-07F;
    }

    return  ans;
}
