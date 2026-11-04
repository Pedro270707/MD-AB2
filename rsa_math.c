#include <stdio.h>
#include "rsa_list.h"
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

static int gcd_internal(int a, int b, struct IntList **quotients, int coefficients[2]) {
    if (b == 0) {
        int quotient_amount = (*quotients)->size - 1;
        int last_result = 0;
        int result = 1;
        int temp;
        for (int i = quotient_amount - 1; i >= 0; i--) {
            temp = result;
            result = il_get(*quotients, i) * result + last_result;
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
    il_add(quotients, a / b);
    return gcd_internal(b, a % b, quotients, coefficients);
}

// Calcula os coeficientes x e y tais que xa + yb = mdc(a, b). Retorna: mdc(a, b).
int gcd(int a, int b, int coefficients[2]) {
    struct IntList *quotients = il_create();

    int gcd_value = gcd_internal(a, b, &quotients, coefficients);

    free(quotients);

    return gcd_value;
}

// Primeiro, calcula MDC entre a e m.
// Os coeficientes geram uma equacao na forma xa + ym = 1 (pois mdc(a, m) = 1, ja que a e m sao coprimos).
// Calculando o modulo: xa + ym = 1 (mod m). Como ym (mod m) = 0: xa = 1 (mod m). Assim, x e o inverso multiplicativo modular de a.
// Calcula o inverso multiplicativo modular de a modulo m.
// Retorna -1 caso o inverso nao exista.
int inverse_mod(int a, int m) {
    if (m <= 1) {
        return -1;
    }

    // Calcula os coeficientes da identidade de Bezout:
    // ax + my = mdc(a, m).
    int coefficients[2];
    int result = gcd(a, m, coefficients);

    // O inverso modular so existe se mdc(a, m) = 1.
    if (result != 1) {
        return -1;
    }

    // O coeficiente x e o inverso modular de a.
    int inverse = coefficients[0] % m;

    // Ajusta o resultado para um valor nao negativo.
    if (inverse < 0) {
        inverse += m;
    }

    return inverse;
}
