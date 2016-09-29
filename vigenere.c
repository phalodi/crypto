#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ALPHABETS 26

int main(int argc, char *argv[])
{
        int rc = 0, i = 0, arg = 0, j = 0, c = 0;
        int ascii_code;
        size_t key_len = 0;
        size_t nbytes = 0, bytes_read = 0;
        char *key = NULL, *data = NULL;

	/* Check the command line arguments */
        if (argc != 2) {
                printf("usage: %s <key>", argv[0]);
                goto out;
        }
        key = argv[++arg];
        key_len = strlen(key);

        /* Check the key */
        for (i = 0; i < key_len; i++) {
                if (!((key[i] >= 'a' && key[i] <= 'z') ||
		      (key[i] >= 'A' && key[i] <= 'Z'))) {
                        printf("invalid key\n");
                        rc = EINVAL;
                        goto out;
                }
        }

	/* Take the data to be encoded */
        puts("Enter data:");
        bytes_read = getline(&data, &nbytes, stdin);

	/* Encryption logic for Vigenere cryptographic algorithm */
        for(i = 0; i < strlen(data); i++) {

                ascii_code = data[j];
                if (ascii_code >= 'a')
                        c = (ascii_code - 'a');
                else
                        c = (ascii_code - 'A');

                if (data[i] >= 'A' && data[i] <= 'Z') {
                        data[i] = 'A'+ ((data[i] - 'A') + c) % ALPHABETS;
                        j++;
                }
                else if (data[i] >= 'a' && data[i] <= 'z') {
                        data[i] = 'a' + ((data[i] - 'a') + c) % ALPHABETS;
                        j++;
                }

                if (j >= key_len)
                        j = 0;
        }

        printf("%s", data);
        free(data);
out:
        return rc;
        
}
