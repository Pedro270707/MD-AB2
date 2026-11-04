#include <stdio.h>
#include "rsa_math.h"
#include <stdint.h>

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
uint64_t mod_pow(uint64_t a, uint64_t b, uint64_t n) {

}

// Calcula os coeficientes de Bezout pelo Algoritmo de Euclides Estendido.
static uint64_t gcd_internal(uint64_t a, uint64_t b, int quotient_amount,
                             int64_t quotients[], int64_t coefficients[2]) {
    if (b == 0) {
        // Trata o caso em que nao houve nenhuma divisao.
        if (quotient_amount == 0) {
            coefficients[0] = 1;
            coefficients[1] = 0;
            return a;
        }

        quotient_amount--;
        int64_t last_result = 0;
        int64_t result = 1;
        int64_t temp;

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

    quotients[quotient_amount] = (int64_t)(a / b);

    return gcd_internal(b, a % b, quotient_amount + 1,
                        quotients, coefficients);
}

// Calcula os coeficientes x e y tais que xa + yb = mdc(a, b).
// Retorna o MDC de a e b.
uint64_t gcd(uint64_t a, uint64_t b, int64_t coefficients[2]) {
    int64_t quotients[1024];

    return gcd_internal(a, b, 0, quotients, coefficients);
}

// Calcula o inverso multiplicativo modular de a modulo m.
// Retorna 0 caso o inverso nao exista.
uint64_t inverse_mod(uint64_t a, uint64_t m) {
    if (m <= 1) {
        return 0;
    }

    // Reduz a ao modulo m.
    a %= m;

    // Calcula os coeficientes da identidade de Bezout:
    // ax + my = mdc(a, m).
    int64_t coefficients[2];
    uint64_t result = gcd(a, m, coefficients);

    // O inverso modular so existe se mdc(a, m) = 1.
    if (result != 1) {
        return 0;
    }

    // O coeficiente x e o inverso modular de a.
    int64_t inverse = coefficients[0] % (int64_t)m;

    // Ajusta o resultado para um valor nao negativo.
    if (inverse < 0) {
        inverse += (int64_t)m;
    }

    return (uint64_t)inverse;
}
