#ifndef RSA_UTILITY_H
#define RSA_UTILITY_H

struct SecretKey {
    int p;
    int q;
    int e;
};

struct PrivateKey {
    int d;
    int e;
};

struct PublicKey {
    int n;
    int e;
};

struct SecretKey scan_secret_key(void);
struct PublicKey scan_public_key(void);
struct PrivateKey to_private_key(struct SecretKey key);
struct PublicKey to_public_key(struct SecretKey key);