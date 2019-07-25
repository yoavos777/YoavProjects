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

void build_arr()
{
	for(i=0;i<16;i++)
	{
		strcpy(comm_oparr[i].name,comm_arr[i]);
		comm_oparr[i].opcode = i;
		for(j=0;j<4;j++)
			comm_oparr[i].des_addr[j] = -1;
			comm_oparr[i].orig_addr[j] = -1;
	}

	for(i=0;i<2;i++){
		for(j=1;j<4;j++)
			comm_oparr[i+4].des_addr[j] = j;
	}

	for(i=0;i<7;i++){
		if(i==2 || i==3 || i==6)
			for(j=1;j<4;j+=2)
				comm_oparr[i+7].des_addr[j] = j;
		else if(i == 5)
			for(j=0;j<4;j++)
				comm_oparr[i+7].des_addr[j] = j;
		else
			for(j=1;j<4;j++)
				comm_oparr[i+7].des_addr[j] = j;
	}

	for(i=0;i<4;i++){
		if(i == 1)
			for(j=0;j<4;j++)
				comm_oparr[i].des_addr[j] = j;
		else
			for(j=1;j<4;j++)
				comm_oparr[i].des_addr[j] = j;
	}

	for(j=1;j<4;j++)
		comm_oparr[6].des_addr[j] = j;
	
		
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
			comm_oparr[i].orig_addr[j] = j;
	}

	for(j=1;j<3;j++)
		comm_oparr[6].orig_addr[j] = j;
}


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


