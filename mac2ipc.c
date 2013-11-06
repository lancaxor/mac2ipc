/*
 ============================================================================
 Name        : test_c_cross.c
 Author      : lex
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include "defs.h"

int main(void) {
	char *mac=(char*)malloc(100*sizeof(char));
	char *outip=(char*)malloc(100*sizeof(char));
	long lmac=0,loutip=0;
	puts("Enter MAC");
	scanf("%s",mac);
	//puts("Enter outer IP");
	//scanf("%s",&outip);

	printdbg("Unsplitting...");
	char*unsplitted=removeSeparators(mac);
	if(strcmp(unsplitted,"ERROR_WHILE_COUNTING_OKTET_SIZE")!=0)
		printf("Afret splitting: %s\n",unsplitted);
	else{
		printdbg("bad MAC format!");
		return -1;}
	lmac=atohex(unsplitted);
	printf("Result: %12x\n",lmac);
	free(outip);
	free(mac);
	return EXIT_SUCCESS;
}

int powr(const int arg,int power){
	int result=1;
	for(int i=1;i<=power;i++){
		result*=arg;
	}
	return result;
}

char* removeSeparators(char*param){
	int oksize=0;
	int oknum=0;
	int length=0;
	int hexindex=0;
	char*result;
	
	if(param[2]=='-'||param[2]==':'||param[2]=='.'){
		oksize=2;
		length=17;}
	else if(param[4]=='-'||param[4]==':'||param[4]=='.'){
		oksize=4;
		length=14;}
	else
		return  "ERROR_WHILE_COUNTING_OKTET_SIZE";
	
	result=(char*)malloc(12*sizeof(char));			//12 symbols in MAC48 (except separators)
	
	for(int i=0;i<length-1;i++){
		if((i+1)%(oksize+1)!=0){
		*(result+hexindex)=*(param+i);
		++hexindex;
		}
	}
	*(result+11)=*(param+length-1);
	return result;
	
}

long atohex(const char*param){
	long res=0;
	res=strtol(param,NULL,16);
	return res;
}

void printdbg(char*str){
	printf("\n\t>>> %s\n",str);
}
