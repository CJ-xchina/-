typedef int* IntPtr;
int fsub(int *a, int *b);
int fsub2(int *a, int *b);
int fsub3(int *a, int *b);
int main(void) {
    int sub = 0;
    int a = 1, b = 2;
    sub = fsub(&a, &b);
    sub += fsub2(&a, &b);
    sub += fsub3(&a, &b);
    return 0;
}

int fsub(int *a,  int *b) {
    int sub = 0;
    // 违背规则
    if (a > b) {
        sub = *a - *b;
    }
    // 违背规则
    else if (*a < b) {
        sub = 0;
    }
    return sub;
}

int fsub2(IntPtr a, IntPtr b) {
    int sub = 0;
    // 违背规则
    if (a >= b) {
        sub = *a - *b;
    }
    // 违背规则
    else if (a <= *b) {
        sub = 0;
    }
    return sub;
}

int fsub3(int *a, int *b) {
    int sub = 0;
    // 遵循规则
    if (*a > *b) {
        sub = *a - *b;
    }
    else if (*a < *b) {
        sub = *b - *a;
    }
    else {
        sub = 0;
    }
    return sub;
}