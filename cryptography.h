#ifndef __CRYPTOGRAPHY_H_
#define __CRYPTOGRAPHY_H_

#include "lib.h"

typedef enum {
    IN_ORI_EVENT,
    ENCRYPT_EVENT,
    DECRYPT_EVENT,
    OUT_RESULT_EVENT,
    EVENT_MAX,
}EVENT;

typedef struct _cryptographyoc {
    char *name;
    char *original_msg;
    char *encrypt_msg;
    char *decrypt_msg;
    pcrypt_ops ops;
    EVENT event; 
} cryptographyoc, *pcryptographyoc;

#endif /* __CRYPTOGRAPHY_H_ */