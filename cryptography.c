#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "cryptography.h"
#include "lib.h"

/*================================================================

                    CRYPTOGRAPHY SYSTEM
    This code implements some basic crypotgraphy algorithm

    Date            Author          Description
    ----            ------          ------
    2023/08/12      Manfred         First release
    2023/08/13      Manfred         Add caesar method

=================================================================*/

pcryptographyoc egoist;

void show(void);

int main(int argc, char *argv[])
{

    do {
        egoist = calloc(1, sizeof(*egoist));
        if (egoist == NULL) {
            printf("failed to alloc mem for egoist\n");
            break;
        }
        menu();
        ops_init();

        egoist->original_msg = get_line(); /* -1- Get original input */
        if (egoist->original_msg == NULL) {
            printf("failed to alloc mem for original message\n");
            break;
        }

        egoist->encrypt_msg = operation.FUNC->ego_encrypt(egoist->original_msg, operation.key); /* -2- Encrypt */
        egoist->decrypt_msg = operation.FUNC->ego_decrypt(egoist->encrypt_msg, operation.key); /* -3- Decrypt */

    } while (0);
 
    show();

    return 0;
}

void show(void)
{
    printf("[Original:%s]\n", egoist->original_msg);
    printf("[Encrypt:%s]\n", egoist->encrypt_msg);
    printf("[Decrypt:%s]\n", egoist->decrypt_msg);
}