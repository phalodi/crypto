#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 1001 // Assuming the maximum length of the string to be 1000 + space for null '\0' character

char caesar(char val, int key){
	if(islower(val))
		return (val+key-'a')%26 +'a';
	else if(isupper(val))
		return(val+key-'A')%26 +'A';
	return val;
}


int main(int argc, char* argv[]){
	int k;
	if(argc==2){
		k=atoi(argv[1])%26;
		char *a = (char*)malloc(MAX_LEN * sizeof(char));
		scanf(" %[^\n]s",a);
		int i=0;
		for(i;i<strlen(a);i++){
			a[i]=caesar(a[i],k);
		}
		printf("%s\n",a);

	}
	else{
		printf("not as per required arguments\n");
		return 1;
	}
}

