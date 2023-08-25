#include <malloc.h>
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include "cryptography.h"

char *reverse_encrypt(char *original_msg, int key)
{
    int i, j;
    int length = strlen(original_msg);
    char *encrypt_msg = calloc(1, length + 1);

    for (i = 0, j = length -1 ; i < length; i++, j--) {
        encrypt_msg[i] = original_msg[j];
    }

    return encrypt_msg;
}

char *reverse_decrypt(char *encrypt_msg, int key)
{
    return reverse_encrypt(encrypt_msg, 0);
}

char *caesar_encrypt(char *original_msg, int key)
{
    int i, ch;
    int length = strlen(original_msg);
    char *encrypt_msg = calloc(1, length + 1);

    for (i = 0; i < length; i++) {
        if (original_msg[i] == ' ') {
            encrypt_msg[i] = original_msg[i];
            continue;
        }
        ch = original_msg[i];
        if (ch >= 'a' && ch <= 'z') {
            ch += key;
            if (ch > 'z') {
                ch -= ('z' - 'a' + 1);
            }
            encrypt_msg[i] = ch;
        } else if (ch >= 'A' && ch <= 'Z') {
            ch += key;
            if (ch > 'Z') {
                ch -= ('Z' - 'A' + 1);
            }
            encrypt_msg[i] = ch;
        }
    }
    printf("%s\n", encrypt_msg);
    return encrypt_msg;
}

char *caesar_decrypt(char *encrypt_msg, int key)
{
    return caesar_encrypt(encrypt_msg, 0 - key);
}

char *transpose_encrypt(char *original_msg, int key)
{
    int row, col, row_plus, col_plus, length, cout = 0;

    length = strlen(original_msg);
    if (length <= key) {
        return "the key is too short";
    }

    row_plus = length / key + 1;  /* the rest objs of last row */
    col_plus = length % key;
    char *encrypt_msg = calloc(1, length + 1);
    if (encrypt_msg == NULL) {
        return "Failed to alloc mem for encrypt_msg";
    }

    char (*tmp)[key] = calloc(1, length + 1);

    for (cout = 0, row = 0; row < row_plus; row++) {
        for (col = 0; col < key; col++) {
            tmp[row][col] = original_msg[cout++];
            if (length == cout) {break;}
        }
    }
    for (cout = 0, col = 0; col < key; col++) {
        for (row = 0; row < row_plus; row++) {
            if ((row == row_plus - 1) && (col >= col_plus)) {continue;}
            encrypt_msg[cout++] = tmp[row][col];
        }
    }

    free(tmp);

    return encrypt_msg;
}

char *transpose_decrypt(char *encrypt_msg, int key)
{
    int row, col, row_plus, col_plus, length, cout = 0;

    length = strlen(encrypt_msg);
    if (length <= key) {
        return "the key is too short";
    }

    row_plus = length / key + 1;  /* the rest objs of last row */
    col_plus = length % key;
    char *decrypt_msg = calloc(1, length + 1);
    if (decrypt_msg == NULL) {
        return "Failed to alloc mem for encrypt_msg";
    }

    char (*tmp)[key] = calloc(1, length + 1);

    for (cout = 0, col = 0; col < key; col++) {
        for (row = 0; row < row_plus; row++) {
            if ((row == row_plus - 1) && (col >= col_plus)) {continue;}
            tmp[row][col] = encrypt_msg[cout++];
            if (length == cout) {break;}
        }
    }

    for (cout = 0, row = 0; row < row_plus; row++) {
        for (col = 0; col < key; col++) {
            decrypt_msg[cout++] = tmp[row][col];
        }
    }
    
    free(tmp);

    return decrypt_msg;
}

char *multiply_encrypt(char *original_msg, int key)
{
    int cout;
    int length = 0;

    length = strlen(original_msg);
    char *encrypt_msg = calloc(1, length + 1);
    if (encrypt_msg == NULL) {
        return "Failed to alloc mem for encrypt_msg";
    }

    for (cout = 0; cout < length; cout++) {
        if (original_msg[cout] == ' ') {
            encrypt_msg[cout] = original_msg[cout];
            continue;
        }

        encrypt_msg[cout] = (((key * original_msg[cout]) % 26) + 65);
    }

    return encrypt_msg;
}

char *multiply_decrypt(char *encrypt_msg, int key)
{
    int cout;
    int inv = 0;
    int length = 0;

    length = strlen(encrypt_msg);
    char *decrypt_msg = calloc(1, length + 1);
    if (decrypt_msg == NULL) {
        return "Failed to alloc mem for decrypt_msg";
    }

    for (cout = 0; cout < 26; cout++) {
        if (1 == (key * cout) % 26) {
            inv = cout;
            printf("inv:%d\n", inv);
        }
    }

    for (cout = 0; cout < length; cout++) {
        if (encrypt_msg[cout] == ' ') {
            decrypt_msg[cout] = encrypt_msg[cout];
            continue;
        }

        decrypt_msg[cout] = (((inv * encrypt_msg[cout]) % 26) + 65);
    }

    return decrypt_msg;
}

#define CAESAR_SUPPLY   5
char *affine_encrypt(char *original_msg, int key)
{
    int cout;
    int length = 0;

    length = strlen(original_msg);
    char *encrypt_msg = calloc(1, length + 1);
    if (encrypt_msg == NULL) {
        return "Failed to alloc mem for encrypt_msg";
    }

    for (cout = 0; cout < length; cout++) {
        if (original_msg[cout] == ' ') {
            encrypt_msg[cout] = original_msg[cout];
            continue;
        }

        encrypt_msg[cout] = (((key * original_msg[cout] + CAESAR_SUPPLY) % 26) + 65);
    }

    return encrypt_msg;
}

char *affine_decrypt(char *encrypt_msg, int key)
{
    int cout;
    int inv = 0;
    int length = 0;

    length = strlen(encrypt_msg);
    char *decrypt_msg = calloc(1, length + 1);
    if (decrypt_msg == NULL) {
        return "Failed to alloc mem for decrypt_msg";
    }

    for (cout = 0; cout < 26; cout++) {
        if (1 == (key * cout) % 26) {
            inv = cout;
            printf("inv:%d\n", inv);
        }
    }

    for (cout = 0; cout < length; cout++) {
        if (encrypt_msg[cout] == ' ') {
            decrypt_msg[cout] = encrypt_msg[cout];
            continue;
        }

        decrypt_msg[cout] = (((inv * (encrypt_msg[cout] - CAESAR_SUPPLY)) % 26) + 65);
    }

    return decrypt_msg;
}

static int encrypt_seq[26];
static int decrypt_seq[26];
void generate_key(int seed)
{
    int cout, i, val, tag;
    
    int rand_num;

    for (cout = 0; cout< 26; cout++) {
        encrypt_seq[cout] = -1;
        decrypt_seq[cout] = -1;
    }

    srand(seed);
    for (cout = 0; cout < 26; cout++) {
        rerun:
        rand_num = rand() % 26;
        for (i = 0; i < 26; i++) { /* repeated check */
            if (encrypt_seq[i] == rand_num) {
                goto rerun;
            }
        }

        encrypt_seq[cout] = rand_num; /* assignment */
        decrypt_seq[rand_num] = cout;
    }
}

char *replace_encrypt(char *original_msg, int key)
{
    int cout;
    int length = strlen(original_msg);
    char *encrypt_msg = (char *)calloc(1, length + 1);
    if (!encrypt_msg)
        return "Failed to alloc mem for encrypt_msg";

    generate_key(key);

    for (cout = 0; cout < length; cout++) {
        if (original_msg[cout] == ' ') {
            encrypt_msg[cout] = ' ';
            continue;
        }
        encrypt_msg[cout] = encrypt_seq[original_msg[cout] - 97] + 97;
    }

    return encrypt_msg;
}

char *replace_decrypt(char *encrypt_msg, int key)
{
    int cout;
    int length = strlen(encrypt_msg);
    char *decrypt_msg = (char *)calloc(1, length + 1);
    if (!decrypt_msg)
        return "Failed to alloc mem for decrypt_msg";
    
    for (cout = 0; cout < length; cout++) {
        if (encrypt_msg[cout] == ' ') {
            decrypt_msg[cout] = ' ';
            continue;
        }
        decrypt_msg[cout] = decrypt_seq[encrypt_msg[cout] - 97] + 97;
    }

    return decrypt_msg;
}

char *vigenere_encrypt(char *original_msg, int key)
{
    int cout;
    int length = strlen(original_msg);
    char *encrypt_msg = (char *)calloc(1, length + 1);
    if (!encrypt_msg)
        return "Failed to alloc mem for encrypt_msg";

    generate_key(key);

    for (cout = 0; cout < length; cout++) {
        if (original_msg[cout] == ' ') {
            encrypt_msg[cout] = ' ';
            continue;
        }
        encrypt_msg[cout] = original_msg[cout] - encrypt_seq[cout % 26];
    }

    return encrypt_msg;
}

char *vigenere_decrypt(char *encrypt_msg, int key)
{
    int cout;
    int length = strlen(encrypt_msg);
    char *decrypt_msg = (char *)calloc(1, length + 1);
    if (!decrypt_msg)
        return "Failed to alloc mem for decrypt_msg";
    
    for (cout = 0; cout < length; cout++) {
        if (encrypt_msg[cout] == ' ') {
            decrypt_msg[cout] = ' ';
            continue;
        }
        decrypt_msg[cout] = encrypt_msg[cout] + encrypt_seq[cout % 26];
    }

    return decrypt_msg;
}

int prime_check(int n)
{
    int cout;
    
    for (cout = 2; cout < n; cout++) {
        if (0 == n % cout)
            break;
    }

    return cout < n ? 0 : 1;
}

#define P 3
#define Q 11
int N;
int pub_key[100];
int pri_key[100];
int size;
int compute_rsa(void)
{
    int cout, i = 0;
    N = P * Q;
    int T = (P - 1) * (Q - 1);

    for (cout = 1; cout < T; cout++) { /* select public key */
        if (!prime_check(cout) || 0 == (T % cout))
            continue;

        pub_key[i++] = cout;
    }

    size = i;

    for (cout = 0, i = 0; i < size; i++) {
        do {
            if ((cout * T + 1) % pub_key[i] == 0) {
                pri_key[i] = (cout * T + 1) / pub_key[i];
                break;
            }
            cout++;
        } while (1 && cout < 50);
    }
}

char *rsa_encrypt(char *original_msg, int key)
{
    int cout, i, tmp;
    int length = strlen(original_msg);
    char *encrypt_msg = (char *)calloc(1, length + 1);
    if (!encrypt_msg)
        return "Failed to alloc mem for encrypt_msg";
    
    compute_rsa();
    key %= size; /* select specific key */

    for (cout = 0; cout < length; cout++) {
        if (original_msg[cout] == ' ') {
            encrypt_msg[cout] = ' ';
            continue;
        }
        tmp = original_msg[cout] - 97;
        for (i = 0; i < pub_key[key] - 1; i++) {
            tmp *= (original_msg[cout] - 97);
        }
        encrypt_msg[cout] = tmp % N + 97;
    }

    return encrypt_msg;
}

char *rsa_decrypt(char *encrypt_msg, int key)
{
    int cout, tmp, i;
    int length = strlen(encrypt_msg);
    char *decrypt_msg = (char *)calloc(1, length + 1);
    if (!decrypt_msg)
        return "Failed to alloc mem for decrypt_msg";
    
    key %= size;

    for (cout = 0; cout < length; cout++) {
        if (encrypt_msg[cout] == ' ') {
            decrypt_msg[cout] = ' ';
            continue;
        }
        tmp = encrypt_msg[cout] - 97;
        for (i = 0; i < pri_key[key] - 1; i++) {
            tmp *= (encrypt_msg[cout] - 97);
        }
        decrypt_msg[cout] = tmp % N + 97;
    }

    return decrypt_msg;
}