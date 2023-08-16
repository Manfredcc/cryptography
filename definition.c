#include <malloc.h>
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