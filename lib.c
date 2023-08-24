#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "lib.h"
#include "definition.h"

crypt_ops operation;
static OPS ops_lib[ID_MAX] = {
    { /* reverse */
        .ego_encrypt = reverse_encrypt,
        .ego_decrypt = reverse_decrypt,
    },

    { /* caesar */
        .ego_encrypt = caesar_encrypt,
        .ego_decrypt = caesar_decrypt,
    },

    { /* transpose */
        .ego_encrypt = transpose_encrypt,
        .ego_decrypt = transpose_decrypt,
    },

    { /* multiply */
        .ego_encrypt = multiply_encrypt,
        .ego_decrypt = multiply_decrypt,
    },

    { /* affine */
        .ego_encrypt = affine_encrypt,
        .ego_decrypt = affine_decrypt,
    },
};

static char *names[ID_MAX] = {
    "reverse",
    "caesar",
    "tramspose",
    "multiply",
    "affine",
    "replace",
    "vigenere",
    "one_off",
    "rsa",
};

void ops_init(void)
{
    if (operation.initialized) {
        printf("Already initialized\n");
        return;
    }

    switch (operation.ID) {
    case REVERSE:
        operation.FUNC = &ops_lib[REVERSE];
        strcpy(operation.name, names[REVERSE]);
        break;
    case CAESAR:
        operation.FUNC = &ops_lib[CAESAR];
        strcpy(operation.name, names[CAESAR]);
        break;
    case TRANSPOSE:
        operation.FUNC = &ops_lib[TRANSPOSE];
        strcpy(operation.name, names[TRANSPOSE]);
        break;
    case MULTIPLY:
        operation.FUNC = &ops_lib[MULTIPLY];
        strcpy(operation.name, names[MULTIPLY]);
        break;
    case AFFINE:
        operation.FUNC = &ops_lib[AFFINE];
        strcpy(operation.name, names[AFFINE]);
        break;
    case REPLACE:
        operation.FUNC = &ops_lib[REPLACE];
        strcpy(operation.name, names[REPLACE]);
        break;
    case VIGENERE:
        operation.FUNC = &ops_lib[VIGENERE];
        strcpy(operation.name, names[VIGENERE]);
        break;
    case ONE_OFF:
        operation.FUNC = &ops_lib[ONE_OFF];
        strcpy(operation.name, names[ONE_OFF]);
        break;
    case RSA:
        operation.FUNC = &ops_lib[RSA];
        strcpy(operation.name, names[RSA]);
        break;
    default:
        operation.initialized = FALSE;
        strcpy(operation.name, "Invalid cryption");
        printf("Invalid cryption\n");
        return;
    }

    operation.initialized = TRUE;
    printf("%s: cryption method:%s\n", __func__, operation.name);

    return;
}

char *get_line(void)
{
    const size_t size_step = 10;
    char *buffer = malloc(size_step);
    char *cur_poistion = buffer;
    size_t max_length = size_step;
    size_t length = 0;
    int ch;

    if (cur_poistion == NULL) { return NULL; }

    while ((ch = getchar()) != '\n' && ch != EOF); /* clear buffer */
    while (1) {
        ch = fgetc(stdin);
        if (ch == '\n')
            break;
        if (++length >= max_length) {
            char *new_buff = realloc(buffer, max_length += size_step);

            if (new_buff == NULL) {
                free(buffer);
                return NULL;
            }

            cur_poistion = new_buff + (cur_poistion - buffer);
            buffer = new_buff;
        }

        *cur_poistion++ = ch;
    }

    *cur_poistion = '\0';
    return buffer;
}

void menu(void)
{
    int cout;
    char id;
    int key;

    printf("Welcome to use cryptography system from Manfred\n");
    printf("Now make a choice of method\n");
    for (cout = 0; cout < ID_MAX; cout++) {
        printf("> %d : %s\n", cout, names[cout]);
    }
    id = fgetc(stdin);
    id -= 48;
    if (id < ID_MAX) {
        operation.ID = id;
        printf("U chose %d:%s\n", id, names[id]);
    }
    
    switch (id) {
    case CAESAR:
        printf("Please input the key: \n");
        scanf("%d", &key);
        operation.key = key % 26;
        break;
    case TRANSPOSE:
        printf("Please input the key(column): \n");
        scanf("%d", &key);
        operation.key = key;
        break;
    case MULTIPLY:
    case AFFINE:
        printf("Please input the key: \n");
        scanf("%d", &key);
        operation.key = key;
        break;
    }
}