#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constTables.h"

char *comm_arr[16] = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};
tab comm_oparr[16];
ascii asc_arr[26];
int i;
int j;
char c;

/*function that build the command array*/
void build_command_arr()
{
	for(i=0;i<16;i++)
	{
		strcpy(comm_oparr[i].name,comm_arr[i]);
		comm_oparr[i].opcode = i;
		for(j=0;j<4;j++)
			comm_oparr[i].des_addr[j] = -1;
			comm_oparr[i].orig_addr[j] = -1;
	}

	for(i=0;i<2;i++){/*legal destnation method for the commands not,clr*/
		for(j=1;j<4;j++)
			comm_oparr[i+4].des_addr[j] = j;
	}

	for(i=0;i<7;i++){
		if(i==2 || i==3 || i==6)/*legal destnation method for the commands inc,dec,red*/
			for(j=1;j<4;j+=2)

				comm_oparr[i+7].des_addr[j] = j;
		else if(i == 5)/*legal destnation method for the commands prn*/
			for(j=0;j<4;j++)
				comm_oparr[i+7].des_addr[j] = j;

		else/*legal destnation method for the commands jmp,bne,jsr*/
			for(j=1;j<4;j++)
				comm_oparr[i+7].des_addr[j] = j;
	}

	for(i=0;i<4;i++){
		if(i == 1)/*legal destnation method for the commands cmp*/
			for(j=0;j<4;j++)
				comm_oparr[i].des_addr[j] = j;
		else/*legal destnation method for the commands mov,add,sub*/
			for(j=1;j<4;j++)
				comm_oparr[i].des_addr[j] = j;
	}

	for(j=1;j<4;j++)/*legal destnation method for the commands lea*/
		comm_oparr[6].des_addr[j] = j;
	
		
	for(i=0;i<4;i++){/*legal origin method for the commands mov,cmp,add,sub*/
		for(j=0;j<4;j++)
			comm_oparr[i].orig_addr[j] = j;
	}

	for(j=1;j<3;j++)/*legal origin method for the commands lea*/
		comm_oparr[6].orig_addr[j] = j;
}

/*build the ascii code array*/
void build_ascii()
{
	i = 0;
	j = 97;
	for(c='a';c<='z';c++){
		asc_arr[i].letter = c;
		asc_arr[i].asc_code = j;
		i++;
		j++;
	}	
		
}


