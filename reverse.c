#include <malloc.h>
#include "stdio.h"
#include "string.h"
#include "cryptography.h"

char *reverse_encrypt(char *orginal_msg, int key)
{
    int i, j;
    int length = strlen(orginal_msg);
    char *encrypt_msg = calloc(0, length + 1);

    for (i = 0, j = length -1 ; i < length; i++, j--) {
        encrypt_msg[i] = orginal_msg[j];
    }

    return encrypt_msg;
}


char *reverse_decrypt(char *encrypt_msg, int key)
{
    return reverse_encrypt(encrypt_msg, 0);
}

