#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int main() {
    int a = 5, b = 10, c = 0, d = 3, e = 1, f = 7;
    int g = 2, h = 9, i, j, k, l, m, n, p, q, r, s, t;
    int arr1[SIZE], arr2[SIZE], arr3[SIZE];

    // Initialize arrays
    for(i = 0; i < SIZE; i++) {
        arr1[i] = i * 2;
        arr2[i] = i + 5;
        arr3[i] = i * i;
    }

    printf("Initial values: a=%d, b=%d, c=%d, d=%d, e=%d, f=%d, g=%d, h=%d\n", a, b, c, d, e, f, g, h);

    // Loop 1
    for(i = 0; i < SIZE; i++) {
        a = a + i;
        b = b - i;
        c = a + b;
        d = c % 5;
        e = e + d;
        f = f + i * 2;
        g = g + a - b;
        h = h - c + d;

        if(a % 2 == 0) {
            arr1[i] = arr1[i] + a;
        } 
        else {
            arr2[i] = arr2[i] - b;
        }

        printf("Loop1 i=%d -> a=%d b=%d c=%d d=%d e=%d f=%d g=%d h=%d\n", i,a,b,c,d,e,f,g,h);
    }

    // Loop 2: nested loop with conditions
    for(j = 0; j < SIZE; j++) {
        for(k = 0; k < SIZE; k++) {
            a = a + j - k;
            b = b - j + k;
            c = c + a - b;
            d = (d + k) % 7;
            e = e + d;
            f = f - j;

            if((a + b + c) % 3 == 0) {
                g = g + k;
                h = h - j;
            } 
            else if((d + e + f) % 2 == 0) {
                g = g - k;
                h = h + j;
            } 
            else {
                g = g + j - k;
                h = h + k - j;
            }

            arr3[k] = arr1[k] + arr2[k] + a - b;

            printf("Loop2 j=%d k=%d -> a=%d b=%d c=%d d=%d e=%d f=%d g=%d h=%d arr3[%d]=%d\n", j,k,a,b,c,d,e,f,g,h,k,arr3[k]);
        }
    }

    // Loop 3: array manipulation
    for(l = 0; l < SIZE; l++) {
        arr1[l] = arr1[l] + a - b + c;
        arr2[l] = arr2[l] - c + d;
        arr3[l] = arr3[l] + e - f;
        a = a + arr1[l];
        b = b - arr2[l];
        c = c + arr3[l];

        if(a % 2 == 0) {
            d = d + l;
        } 
        else {
            e = e - l;
        }

        if(b % 3 == 0) {
            f = f + l;
        } 
        else {
            g = g - l;
        }

        printf("Loop3 l=%d -> a=%d b=%d c=%d d=%d e=%d f=%d g=%d\n", l,a,b,c,d,e,f,g);
    }

    // Conditional block
    if(a % 2 == 0 && b % 3 == 0) {
        d = a + b + c;
        e = d / 2;
        f = d - e;
        g = e + f;
        h = g - d;
    } 
    else if(a % 3 == 0 || b % 2 == 0) {
        d = a * b;
        e = d % 7;
        f = e + c;
        g = f - a;
        h = g + b;
    } 
    else {
        d = a - b;
        e = d + f;
        f = a + b + c;
        g = f - e;
        h = g + d;
    }

    printf("After conditional -> a=%d b=%d c=%d d=%d e=%d f=%d g=%d h=%d\n", a,b,c,d,e,f,g,h);

    // Loop4: complex nested conditionals
    for(m = 0; m < SIZE; m++) {
        for(n = 0; n < SIZE; n++) {
            a = a + m - n;
            b = b - m + n;
            c = c + a - b;

            if(a % 2 == 0) {
                d = d + m;
                if(d % 3 == 0) {
                    e = e + n;
                    f = f - n;
                } 
                else {
                    e = e - n;
                    f = f + n;
                }
            } 
            else {
                d = d - m;
                if(d % 2 == 0) {
                    e = e - n;
                    f = f + n;
                } 
                else {
                    e = e + n;
                    f = f - n;
                }
            }

            arr1[n] = arr1[n] + a - b + c;
            arr2[n] = arr2[n] + b - a + d;
            arr3[n] = arr3[n] + c - d + e;

            printf("Loop4 m=%d n=%d -> a=%d b=%d c=%d d=%d e=%d f=%d arr1[%d]=%d arr2[%d]=%d arr3[%d]=%d\n",
                m,n,a,b,c,d,e,f,n,arr1[n],n,arr2[n],n,arr3[n]);
        }
    }

    // Loop5: triple nested
    for(p = 0; p < SIZE; p++) {
        for(q = 0; q < SIZE; q++) {
            for(r = 0; r < SIZE; r++) {
                a = a + p - q + r;
                b = b - p + q - r;
                c = c + a - b;
                d = (d + p + q + r) % 10;
                e = e + c - d;
                f = f - b + a;
                g = g + e - f;
                h = h + d - e;

                arr1[r] = arr1[r] + a - b;
                arr2[r] = arr2[r] - c + d;
                arr3[r] = arr3[r] + e - f;

                printf("Loop5 p=%d q=%d r=%d -> a=%d b=%d c=%d d=%d e=%d f=%d g=%d h=%d\n", p,q,r,a,b,c,d,e,f,g,h);
            }
        }
    }

    // Extra loops to extend code
    for(s = 0; s < SIZE; s++) {
        a = a + s;
        b = b - s;
        c = c + s;
        d = d + a - b;
        e = e - c + d;
        f = f + e - d;
        g = g - a + b;
        h = h + c - e;

        if(a % 2 == 0) { 
            f = f + s;
        }
        else {
            g = g - s;
        }

        if(b % 3 == 0) {
            e = e + s;
        } 
        else {
            d = d - s;
        }

        printf("Extra loop1 s=%d -> a=%d b=%d c=%d d=%d e=%d f=%d g=%d h=%d\n", s,a,b,c,d,e,f,g,h);
    }

    for(t = 0; t < SIZE; t++) {
        a = a - t;
        b = b + t;
        c = c - t;
        d = d + t;
        e = e - t;
        f = f + t;
        g = g - t;
        h = h + t;

        arr1[t] = arr1[t] + a - b;
        arr2[t] = arr2[t] + c - d;
        arr3[t] = arr3[t] - e + f;

        printf("Extra loop2 t=%d -> a=%d b=%d c=%d d=%d e=%d f=%d g=%d h=%d arr1[%d]=%d arr2[%d]=%d arr3[%d]=%d\n",
            t,a,b,c,d,e,f,g,h,t,arr1[t],t,arr2[t],t,arr3[t]);
    }

    // Final calculations
    a = a + b + c + d + e + f + g + h;
    b = a - b - c;
    c = a + b - d;
    d = (a + b + c) % 10;
    e = d * 2;
    f = e + a - b;
    g = f - c + d;
    h = g + e - f;

    printf("Final values -> a=%d b=%d c=%d d=%d e=%d f=%d g=%d h=%d\n", a,b,c,d,e,f,g,h);

    // Print arrays
    printf("Array1: ");
    for(i = 0; i < SIZE; i++) printf("%d ", arr1[i]);
    printf("\nArray2: ");
    for(i = 0; i < SIZE; i++) printf("%d ", arr2[i]);
    printf("\nArray3: ");
    for(i = 0; i < SIZE; i++) printf("%d ", arr3[i]);
    printf("\n");

    return 0;
}
