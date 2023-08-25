#ifndef __DEFINITION_H__
#define __DEFINITION_H__

char *reverse_encrypt(char *original_msg, int key);
char *reverse_decrypt(char *encrypt_msg, int key);

char *caesar_encrypt(char *original_msg, int key);
char *caesar_decrypt(char *encrypt_msg, int key);

char *transpose_encrypt(char *original_msg, int key);
char *transpose_decrypt(char *encrypt_msg, int key);

char *multiply_encrypt(char *original_msg, int key);
char *multiply_decrypt(char *encrypt_msg, int key);

char *affine_encrypt(char *original_msg, int key);
char *affine_decrypt(char *encrypt_msg, int key);

char *replace_encrypt(char *original_msg, int key);
char *replace_decrypt(char *encrypt_msg, int key);

char *vigenere_encrypt(char *original_msg, int key);
char *vigenere_decrypt(char *encrypt_msg, int key);

char *rsa_encrypt(char *original_msg, int key);
char *rsa_decrypt(char *encrypt_msg, int key);
#endif /* __DEFINITION_H__ */