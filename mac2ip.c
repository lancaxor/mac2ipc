#include "defs.h"

/******************************************************/
/*******	Inner_addr & MAC=Outer_Addr;	*******/
/******************************************************/
/*******	using: mac2ip ip.addr mac.addr	*******/
/******************************************************/
/*******	XXXX.XXXX.XXXX or xx-xx-xx-xx,	*******/
/*******	where X and x -- hex
/******************************************************/

int main(int args,char*argv[]){
	if(args<2){
		printf("MAC & IP required!\n");
		OutHelp();
		return 1;}
	else if(args<3){
		for(int i=0;i<firstParamLen;i++)
			argv[1][i]=toupper(argv[1][i]);
		if(strcmp(argv[1],"HELP/0")){
			OutHelp();
			return 5;}
		printf("IP required!\n");
		return 2;}

	l_mac=inet_addr(argv[1]);
	l_out=inet_addr(argv[2]);
	dbg(l_mac);
	dbg(l_out);
	sin_mac.s_addr=l_mac;
	sin_outIP.s_addr=l_out;
	printf("MAC: %s\nOuter IP:%s\n",argv[1],argv[2]);
	printf("-----------------------------------------\nInner IPs:\n");

	for(long l=0;l<4294967295;l++){
		if((l&l_mac)==l_out){
			noFound=0;
			sin_inIP.s_addr=l;
			printf("%s\n",inet_ntoa(sin_inIP));}}
	printf("%s\n",noFound==1?"No Addresses found!":"");
	return 0;}
	
void OutHelp(){
	printf("Ussage: mac2ip [MAC] [Subnet IP]\nParams format: xx-xx-xx-xx-xx-xx\nxx -- number from 0 to 255\njoin!\n");}

void dbg(long ch){
	printf(">> >%d<\n", ch);
}