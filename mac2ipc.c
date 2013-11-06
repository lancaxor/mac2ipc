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
	
	printf("Afret splitting: %s",removeSeparators(mac));

/*	long*__l_addr=splitIP(mac,'m');

	printdbg("Splitting...");

	if(*__l_addr==SPLIT_BAD_OKSIZE)
		printf("SPLIT_BAD_OKSIZE!");
	else if((*__l_addr)==SPLIT_BAD_ATTRIB)
		printf("SPLIT_BAD_ATTRIB!");
	else
		printf("Nothing of this...");

	for(int i=0;i<macoksize;i++){
		//printf("%x",__l_addr[i]);
	}
*/
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

long* splitIP(const char*arg,const char attrib){
	printdbg("Start splitting...");


	int oksize=3;
	long *res;

	/*
	 * finding oktet size
	 */
	if(arg[2]=='-'||arg[2]==':'||arg[2]=='.')
		oksize=2;
	else if(arg[4]=='-'||arg[4]==':'||arg[4]=='.')
		oksize=4;
	else{
		res=(long*)malloc(sizeof(long));
		*res=SPLIT_BAD_OKSIZE;
		return  res;
	}


	/*
	 * finding current address (arg) type (MAC or IP)
	 */
	if(attrib=='m')
		macoksize=oksize;
	else if (attrib=='i')
		ipoksize=oksize;
	else{
			res=(long*)malloc(sizeof(long));
			*res=SPLIT_BAD_ATTRIB;
			return  res;
		}

	printdbg("Allocating...");

	res=(long*)malloc(oksize*sizeof(long));

	int oknum=12/oksize;

	printf("oksize: %d\toknum:%d\n",oksize,oknum);

	for(int i=0;i<oknum;i++){			//for every oktet
		res[i]=0;
		for(int j=0;j<oksize;j++){		//for every symbol in oktet
			const int p=(oksize-j-1);
			int dec=powr(10,p);

			printdbg(arg[j]);

			long l=(long) (intptr_t) atoi(&arg[j]);
			*(res+i)=l;
			res[i]*=dec;
		}
	}
	free(res);
	printdbg("end splitting");

	return res;
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

void printdbg(char*str){
	printf("\n\t>>> %s\n",str);
}
