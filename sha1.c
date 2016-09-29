#include <stdio.h>
#include <stdlib.h>
#include <openssl/hmac.h>
#include <errno.h>
#include <string.h>

/*
 * Creats a keyed-hash message authentication code (HMAC) using sha1 engine
 */
int hmac_sha1_encryption(char *key, char *data, unsigned char **digest)
{
	int rc = 0;

	/* sha1 hash engine here. */
	*digest = HMAC(EVP_sha1(), key, strlen(key), (unsigned char *)data,
		       strlen(data), NULL, NULL);
	if (NULL == digest)
		rc = EINVAL;
	return rc;
}

int main(int argc, char *argv[])
{
	int rc = 0, i = 0, arg = 0;
	size_t nbytes = 0, bytes_read = 0;
	char *key = NULL, *data = NULL;
	unsigned char *digest = NULL;
	char mdString[40];

	/* Check the number of arguments and take the key*/
	if (argc != 2) {
		printf("usage: %s <key>", argv[0]);
		goto out;
	}
	key = argv[++arg];

	/* Take the data from stdin. getline() function allocates the
	 * memory for buffer (reallocates if full). */
	puts("Enter data:");
	bytes_read = getline(&data, &nbytes, stdin);

	/* Call the hmac sha1 encrytion */
	rc = hmac_sha1_encryption(key, data, &digest);
	if (rc) {
		errno = rc;
		perror("Enter valid input");
		goto out;
	}

	/* SHA1 produces a 20-byte hash value which rendered as 40 characters. */
	for(i = 0; i < 20; i++)
		sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);

	printf("HMAC digest: %s\n", mdString);
	free(data);
 out:
	return rc;
}
