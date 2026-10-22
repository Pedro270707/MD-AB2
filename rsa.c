#include <stdio.h>
#include <string.h>
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

int main() {
    int key = 0;

    do {
        printf("Escolha uma opcao:\n");
        printf("1 - Gerar chave publica\n");
        printf("2 - Criptografar\n");
        printf("3 - Descriptografar\n");

        scanf("%d", &key);

        if (key < 1 || key > OPTION_COUNT) {
            printf("Codigo invalido.\n");
            printf("\n");
        }
    } while (key < 1 || key > OPTION_COUNT);

    switch (key) {
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