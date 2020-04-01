#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>

double *mas, eps = 0.000000001;
int cmp, mov, n;

void out(int n){
    printf("\n");
    for (int i = 0; i < n; ++i){
        printf("%f ", mas[i]);
    }
}

void out2(int n){
    printf("\n");
    for (int i = 1; i <= n; ++i){
        printf("%f ", mas[i]);
    }
}

bool comp (double a, double b){
    return abs(a) > abs(b);
}

void generate_straight (int sz){
    for (int i = 0; i < sz; ++i){
        mas[i] = i + 1;
    }
}

void generate_reversed (int sz){
    for (int i = 0; i < sz; ++i){
        mas[i] = sz - i;
    }
}

void generate_random (int sz){
    for (int i = 0; i < sz; ++i){
        mas[i] = rand() * rand() / 10000.0;
    }
}

void simple_choice (double *mas, int sz){
    double vsp;
    for (int i = 0; i < sz - 1; ++i){
        int mn = i;
        for (int j = i + 1; j < sz; ++j){
            if (comp(mas[mn], mas[j])) mn = j;
            cmp++;
        }
        if (mn == i) continue;
        vsp = mas[mn];
        mas[mn] = mas[i];
        mas[i] = vsp;
        mov++;
    }
}

void sift (int num, int n){
    double vsp;
    bool ok = 0;
    while (num * 2 <= n && !ok){
        int mx;
        if (num * 2 == n){
            mx = num * 2;
        }
        else if (comp(mas[num * 2], mas[num * 2 + 1])){
            mx = num * 2;
        }
        else mx = num * 2 + 1;
        cmp++;
        if (comp(mas[mx], mas[num])){
            vsp = mas[mx];
            mas[mx] = mas[num];
            mas[num] = vsp;
            mov++;
            num = mx;
        }
        else ok = 1;
    }
}

void heap_sort (double *mas, int n){
    for (int i = n; i > 0; --i){
        mas[i] = mas[i - 1];
    }

    for (int i = n / 2; i > 0; --i){
        sift(i, n);
    }
    double vsp;
    for (int i = n; i > 1; --i){
        vsp = mas[i];
        mas[i] = mas[1];
        mas[1] = vsp;
        mov++;
        sift(1, i - 1);
    }
}

int main(void)
{

    srand(time(0));
    scanf("%d", &n);
    mas = malloc((n + 1) * sizeof(double));

    generate_straight(n);
    simple_choice(mas, n);
    out(n);
    printf("\nComparisons: %d\nSwaps: %d\n", cmp, mov);
    cmp = mov = 0;

    generate_reversed(n);
    simple_choice(mas, n);
    out(n);
    printf("\nComparisons: %d\nSwaps: %d\n", cmp, mov);
    cmp = mov = 0;

    generate_random(n);
    simple_choice(mas, n);
    out(n);
    printf("\nComparisons: %d\nSwaps: %d\n", cmp, mov);
    cmp = mov = 0;

    generate_random(n);
    simple_choice(mas, n);
    out(n);
    printf("\nComparisons: %d\nSwaps: %d\n", cmp, mov);
    cmp = mov = 0;


    printf("\n\n");


    generate_straight(n);
    heap_sort(mas, n);
    out2(n);
    printf("\nComparisons: %d\nSwaps: %d\n", cmp, mov);
    cmp = mov = 0;

    generate_reversed(n);
    heap_sort(mas, n);
    out2(n);
    printf("\nComparisons: %d\nSwaps: %d\n", cmp, mov);
    cmp = mov = 0;

    generate_random(n);
    heap_sort(mas, n);
    out2(n);
    printf("\nComparisons: %d\nSwaps: %d\n", cmp, mov);
    cmp = mov = 0;

    generate_random(n);
    heap_sort(mas, n);
    out2(n);
    printf("\nComparisons: %d\nSwaps: %d\n", cmp, mov);
    cmp = mov = 0;

    free(mas);

    return 0;
}