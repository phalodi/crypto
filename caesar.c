#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int k;

	if(argc==2)
	{
		k=atoi(argv[1]);
		char *s=GetString();
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
		return 0;
	}
	else
	{
		printf("not as per required arguments");
		return 1;
	}
}


