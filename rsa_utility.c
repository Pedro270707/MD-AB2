#include "rsa_math.h"
#include "rsa_utility.h"

// Escaneia uma chave secreta: (p, q, e).
struct SecretKey scan_secret_key() {

}

// Escaneia uma chave publica: (n, e).
struct PublicKey scan_public_key() {
    
}

// Retorna uma chave privada (d, e) a partir de (p, q, e).
struct PrivateKey to_private_key(struct SecretKey key) {
    // Calcular d: d = inverso multiplicativo modular de e (mod (p - 1)(q - 1)).
    int d = inverse_mod(e, (key.p - 1) * (key.q - 1));

    return (struct PrivateKey){ .d = d, .e = key.e };
}

// Retorna uma chave publica (n, e) a partir de (p, q, e).
struct PublicKey to_public_key(struct SecretKey key) {
    return (struct PublicKey){ .n = key.p * key.q, .e = key.e };
}