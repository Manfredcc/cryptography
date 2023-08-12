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

=================================================================*/

pcryptographyoc egoist;

int main(int argc, char *argv[])
{
    char *man;

    do {
        egoist = calloc(1, sizeof(*egoist));
        if (egoist == NULL) {
            printf("failed to alloc mem for egoist\n");
            break;
        }
        menu();
        man = get_line();
        printf("original message:%s\n", man);

        // egoist->original_msg = get_line();
        // if (egoist->original_msg == NULL) {
        //     printf("failed to alloc mem for original message\n");
        //     break;
        // }
        // printf("original message:%s\n", egoist->original_msg);

        ops_init();
    } while (0);

    return 0;
}