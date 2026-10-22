#include <stdio.h>
#include "rsa_math.h"

int get_character_code(char c) {
    
}

char get_character(int i) {
    
}

void string_to_int_array(char str[], int arr[], int size) {
    
}

void int_array_to_string(int arr[], char str[], int size) {
    
}

// Exponenciacao modular rapida
int mod_pow(int a, int b, int n) {
    
}

// Calcula os coeficientes x e y tais que xa + yb = mdc(a, b). Retorna: mdc(a, b).
int gcd(int a, int b, int quotient_amount, int quotients[], int coefficients[2]) {
    
}

// Primeiro, calcula MDC entre a e m.
// Os coeficientes geram uma equacao na forma xa + ym = 1 (pois mdc(a, m) = 1, ja que a e m sao coprimos).
// Calculando o modulo: xa + ym = 1 (mod m). Como ym (mod m) = 0: xa = 1 (mod m). Assim, x e o inverso multiplicativo modular de a.
int inverse_mod(int a, int m) {
    
}