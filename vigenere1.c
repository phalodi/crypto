#include<stdio.h>
#include<cs50.h>
#include<string.h>

int main(int argc,string argv[])
{
if(argc==2)
{
string k=argv[1];
int d=strlen(k);
for(int i=0;i<d;i++)
{
if(!((k[i]>='a' && k[i]<='z')||(k[i]>='A' && k[i]<='Z')))
{
printf("invalid key\n");
return 1;
}
}

string p=GetString();
int j=0,c;
for(int i=0;i<strlen(p);i++)
{
int k1=k[j];
if(k1>=97)
c=(k1-97);
else
c=(k1-65);
if(p[i]>='A' && p[i]<='Z')
{
p[i]='A'+((p[i]-65)+c)%26;
j++;
}
else if(p[i]>='a' && p[i]<='z')
{
p[i]='a'+((p[i]-97)+c)%26;
j++;
}

if(j>=d)
j=0;
}
for(int i=0;i<strlen(p);i++)
printf("%c",p[i]);
printf("\n");
return 0;
}
else
{
printf("Number of agruments are less or more");
return 1;
}
}
