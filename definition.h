#ifndef __DEFINITION_H__
#define __DEFINITION_H__

char *reverse_encrypt(char *original_msg, int key);
char *reverse_decrypt(char *encrypt_msg, int key);

char *caesar_encrypt(char *original_msg, int key);
char *caesar_decrypt(char *encrypt_msg, int key);

char *transpose_encrypt(char *original_msg, int key);
char *transpose_decrypt(char *encrypt_msg, int key);
#endif /* __DEFINITION_H__ */