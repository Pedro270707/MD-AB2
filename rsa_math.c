#include <stdio.h>
#include "rsa_math.h"

int get_character_code(char c) {
    if (c == ' ') return 28;
    return c - 'A' + 2;
}

char get_character(int i) {
    if (i == 28) return ' ';
    return (char) (i - 2 + 'A');
}

void string_to_int_array(char str[], int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = get_character_code(str[i]);
    }
}

void int_array_to_string(int arr[], char str[], int size) {
    for (int i = 0; i < size; i++) {
        str[i] = get_character(arr[i]);
    }
    str[size] = '\0';
}

// Exponenciacao modular rapida
int mod_pow(int a, int b, int n) {
    
}

static int gcd_internal(int a, int b, int quotient_amount, int quotients[], int coefficients[2]) {
    if (b == 0) {
        quotient_amount--;
        int last_result = 0;
        int result = 1;
        int temp;
        for (int i = quotient_amount - 1; i >= 0; i--) {
            temp = result;
            result = quotients[i] * result + last_result;
            last_result = temp;
        }

        if (quotient_amount % 2 == 0) {
            last_result *= -1;
        } else {
            result *= -1;
        }

        coefficients[0] = last_result;
        coefficients[1] = result;

        return a;
    }
    quotients[quotient_amount] = a / b;
    return gcd_internal(b, a % b, quotient_amount + 1, quotients, coefficients);
}

// Calcula os coeficientes x e y tais que xa + yb = mdc(a, b). Retorna: mdc(a, b).
int gcd(int a, int b, int coefficients[2]) {
    int quotients[1024];

    return gcd_internal(a, b, 0, quotients, coefficients);
}

// Primeiro, calcula MDC entre a e m.
// Os coeficientes geram uma equacao na forma xa + ym = 1 (pois mdc(a, m) = 1, ja que a e m sao coprimos).
// Calculando o modulo: xa + ym = 1 (mod m). Como ym (mod m) = 0: xa = 1 (mod m). Assim, x e o inverso multiplicativo modular de a.
int inverse_mod(int a, int m) {
    
}