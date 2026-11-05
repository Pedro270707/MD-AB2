#ifndef RSA_MATH_H
#define RSA_MATH_H
#include <stdint.h>

int get_character_code(char c);
char get_character(int i);
void string_to_int_array(char str[], int arr[], int size);
void int_array_to_string(int arr[], char str[], int size);
uint64_t mod_pow(uint64_t a, uint64_t b, uint64_t n);
uint64_t gcd(uint64_t a, uint64_t b, int64_t coefficients[2]);
uint64_t inverse_mod(uint64_t a, uint64_t m);

#endif
