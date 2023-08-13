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
