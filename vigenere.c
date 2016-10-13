#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 1001 // Assuming the maximum length of the string to be 1000 + space for null '\0' character

char caesar(char val, char k){
	int key;
	key = (isupper(k)) ? (k-'A') : (k-'a');
	if(islower(val))
		return (val+key-'a')%26 +'a';
	return(val+key-'A')%26 +'A';
}


int main(int argc, char* argv[]){
	int k,i,j;
	bool b=true;

	// check if the arguments are as required in the question
	if(argc==2){
		int ctr;
		for(ctr=0;argv[1][ctr]!='\0';ctr++)
			if (!isalpha(argv[1][ctr])){
				b=false;
				break;
			}
	}
	else b=false;

	if(b){
		char *a = (char*)malloc(MAX_LEN * sizeof(char));
		scanf(" %[^\n]s",a);
		int keylen = strlen(argv[1]);
		i=j=0;
		for(i=0;i<strlen(a);i++){
			if(isalpha(a[i])){
				a[i]=caesar(a[i],argv[1][j]);
				j++;
			}
			if(j==keylen)j=0;
		}
		printf("%s\n",a);

	}
	else{
		printf("not as per required arguments\n");
		return 1;
	}
}

