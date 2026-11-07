#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "rsa_bigint.h"
#include "rsa_list.h"
#include "rsa_math.h"
#include "rsa_utility.h"

#define OPTION_COUNT 3

// Imprime uma chave publica (n, e) a partir de (p, q, e).
void generate_public_key() {
    struct SecretKey secret_key = scan_secret_key();
    struct PublicKey public_key = to_public_key(secret_key);
}

// Descriptografa uma mensagem usando a chave privada.
void decrypt() {
    struct SecretKey secret_key = scan_secret_key();
    struct PrivateKey private_key = to_private_key(secret_key);
}

// Criptografa uma mensagem usando a chave publica.
void encrypt() {
    struct PublicKey public_key = scan_public_key();
}

void debug() {
    printf("Depuracao\n");
    printf("MDC\n");
    printf("Escreva dois numeros inteiros nao negativos: ");

    uint64_t a, b;

    if (scanf("%" SCNu64 "%" SCNu64, &a, &b) != 2) {
        return;
    }

    int64_t coefficients[2];
    uint64_t gcd_value = gcd(a, b, coefficients);

    printf("%" PRIu64 " * %" PRId64 " + %" PRIu64 " * %" PRId64 " = %" PRIu64 "\n", a, coefficients[0], b, coefficients[1], gcd_value);

    printf("BigInt\n");
    printf("Calculos com BigInt:\n");
    
    printf("Escreva dois numeros inteiros: ");
    
    int64_t c, d;

    if (scanf("%" SCNd64 "%" SCNd64, &c, &d) != 2) {
        return;
    }

    struct BigInt *bigint_first = bigint_create_from_number(c);
    struct BigInt *bigint_second = bigint_create_from_number(d);

    struct BigInt *bigint_added = bigint_add(bigint_first, bigint_second);
    printf("%" PRId64 " + %" PRId64 " = 0x", c, d);
    bigint_print_as_hex(bigint_added);
    
    struct BigInt *bigint_multiplied = bigint_multiply(bigint_first, bigint_second);
    printf("%" PRId64 " * %" PRId64 " = 0x", c, d);
    bigint_print_as_hex(bigint_multiplied);

    printf("\n");

    free(bigint_first);
    free(bigint_second);
    free(bigint_added);
    free(bigint_multiplied);
}

int main() {
    int key = 0;

    do {
        printf("Escolha uma opcao:\n");
        printf("-1 - Depuracao\n");
        printf("1 - Gerar chave publica\n");
        printf("2 - Criptografar\n");
        printf("3 - Descriptografar\n");

        scanf("%d", &key);

        if (key != -1 && (key < 1 || key > OPTION_COUNT)) {
            printf("Codigo invalido: %d.\n", key);
            printf("\n");
        } else {
            break;
        }
    } while (1);

    switch (key) {
        case -1:
            debug();
            break;
        case 1:
            generate_public_key();
            break;
        case 2:
            encrypt();
            break;
        case 3:
            decrypt();
            break;
    }

    return 0;
}