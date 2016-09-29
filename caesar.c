#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>

#define ALPHABETS 26

int main(int argc, char *argv[])
{
	int shift, i, rc, ascii_code = 0;
	int arg = 0;
	size_t nbytes = 0, bytes_read = 0;
	char *data = NULL;

	/* Check the command line arguments */
	if (argc != 2) {
		printf("usage: %s <key>", argv[0]);
		rc = EINVAL;
		goto out;
	}

	/* Get the shift/rotate number */
	shift = atoi(argv[++arg]);
	if (!shift) {
		rc = EINVAL;
		printf("Enter valid shifting number");
		goto out;
	}

	/* Take the data to be encoded */
	puts("Enter data:");
	bytes_read = getline(&data, &nbytes, stdin);

	/* Encryption logic for Caesar cryptographic algorithm */
	for (i = 0; i < strlen(data); i++) {

		ascii_code = (data[i] + shift);
		if (data[i] >= 'A' && data[i] <= 'Z') {
			if (ascii_code <= 'Z')
				data[i] = ascii_code;
			else
				data[i] = 'A' + (ascii_code - 'A') % ALPHABETS;
		}
		else if (data[i] >= 'a' && data[i] <= 'z') {
			if (ascii_code <= 'z')
				data[i] = ascii_code;
			else
				data[i] = 'a' + (ascii_code - 'a') % ALPHABETS;
		}
	}

	printf("%s", data);
	free(data);
out:
	return rc;
}
