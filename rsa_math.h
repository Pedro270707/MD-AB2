#ifndef RSA_MATH_H
#define RSA_MATH_H

int get_character_code(char c);
char get_character(int i);
void string_to_int_array(char str[], int arr[], int size);
void int_array_to_string(int arr[], char str[], int size);
int mod_pow(int a, int b, int n);
int gcd(int a, int b, int coefficients[2]);
int inverse_mod(int a, int m);

#endif