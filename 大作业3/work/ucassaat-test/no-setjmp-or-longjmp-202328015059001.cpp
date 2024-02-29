#include <math.h>
#include <setjmp.h>
jmp_buf mark;
double fdiv (double a, double b);
int main(void) {
    int jmpret;
    double r, nl = 1.0, n2 = 0.0;
    jmpret = setjmp(mark);
    if (jmpret == 0) {
        r = fdiv(nl, n2);
    }
    else {
        return -1;
    }

    int testJ = setjmp(mark);
    longjmp(mark, -2);
    return 0;
}
double fdiv(double a, double b) {
    double div = a / b;
    if (fobs(b) < 1e-10) {
        longjmp(mark, -1);
    }
    return div;
}