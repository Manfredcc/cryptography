#ifndef __LIB_H__
#define __LIB_H__

typedef enum {
    FALSE,
    TRUE,
}BOOL;

typedef char *(*ENCRYPT)(char *original_msg, int key);
typedef char *(*DECRYPT)(char *encrypt_msg, int key);

typedef struct _OPS {
    ENCRYPT ego_encrypt;
    DECRYPT ego_decrypt;
}OPS;

typedef enum {
    REVERSE,
    CAESAR,
    TRANSPOSE,
    MULTIPLY,
    AFFINE,
    REPLACE,
    VIGENERE,
    ONE_OFF,
    RSA,
    ID_MAX,
}TRANSFER_ID;

typedef struct _crypt_ops {
    BOOL initialized;
    TRANSFER_ID ID;
    int key;
    OPS *FUNC;
    char name[20];
}crypt_ops, *pcrypt_ops;
extern crypt_ops operation;

void ops_init(void);
void menu(void);
char *get_line(void);

#endif /* __LIB_H__ */