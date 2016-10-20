#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 128

int main(int argc, char **argv)
{
	int k;
	char *s = (char *)malloc(MAX_LEN);

	/* check for args */
	if(argc!=2)
	{
		printf("not as per required arguments\n");
		exit(EXIT_FAILURE);
	}

	k=atoi(argv[1]);
	s=gets(s);
	for(int i=0,n=strlen(s);i<n;i++)
	{
		int c=(s[i]+k);
		if(s[i]>='A' && s[i]<='Z')
		{
			if(c<='Z')
				s[i]=c;
			else
				s[i]='A'+(c-65)%26;
		}
		else if(s[i]>='a' && s[i]<='z')
		{
			if(c<='z')
				s[i]=c;
			else
				s[i]='a'+(c-97)%26;
		}
	}
	for(int i=0,n=strlen(s);i<n;i++)
		printf("%c",s[i]);
	printf("\n");
	free(s);
	return 0;
}
