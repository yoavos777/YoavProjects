#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "firstTransition.h"
#include "constTables.h"

extern tab comm_oparr[16];
extern ascii asc_arr[26]; 
int IC = 0;
int DC = 0;
int is_symbol = 0;
int reg_count = 0;
int memory_line[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char *comm_arr2[5] = {"mov","cmp","add","sub","lea"};
char *comm_arr1[9] = {"not","clr","inc","dec","jmp","bne","red","prn","jsr"};
char *comm_arr0[2] = {"rts","stop"};
char *reg_arr[8] = {"r0","r1","r2","r3","r4","r5","r6","r7"};

int * decToBinary(int,int);
void skip_spaces(char* , int *);
void read_word(char* , char* , int *);


int is_symbol_exists(char *sy_name, ptr *headp){
	ptr curr;
	curr = *headp;
	while(curr->next != NULL)/*runs untill gets to the end of the list*/
	{
		if(strcmp(curr->name,sy_name) == 0 && strcmp(curr->type,"macro") == 1)
			return 1;

		curr = curr->next;
	}
	return 0;
}

int is_macro(char *operand, ptr *headp){
	ptr curr;
	curr = *headp;
	
	while(curr!= NULL)/*runs untill gets to the end of the list*/
	{
		if(strcmp(curr->name,operand) == 0 && strcmp(curr->type,"macro") == 0)
			return curr->val;

		curr = curr->next;
	}
	return 0;
}

int is_symbol_arr_exists(char *operand, ptr *headp){
	int i;
	char symbol[MAX];
	char index[MAX];
	
	ptr curr;
	i=0;
	while(operand[i] !='['){
		if(operand[i] == '\0')
			return 0;
		symbol[i] = operand[i];
		i++;
	}
	/*printf("%d\n",i);*/	
	while(operand[i] !=']'){
		if(operand[i] == '\0')
			return 0;
		index[i] = operand[i];
		i++;
	}
	
	return 1;
}


int is_reg(char* operand)
{
	int i;
	for(i=0;i<8;i++)
		if(strcmp(operand,reg_arr[i]) == 0)
			return 1;
	return 0;
}

int is_addr(char* operand,int i,int num,int is_des)
{
	int j;
	printf("%s\n",operand);
	if(is_des == 1){
		for(j=0;j<4;j++)
			if(comm_oparr[i].des_addr[j] == num)
				return 1;
	}
	
	else{
		for(j=0;j<4;j++)
			if(comm_oparr[i].orig_addr[j] == num)
				return 1;
	}
	return 0;
}

int retrun_asc_code(char c)
{
	int i;
	for(i=0;i<26;i++){
		if(asc_arr[i].letter == c)
			return asc_arr[i].asc_code;
	}
	return 1;
	
}

void insert_data_memory(char* input,int *index, int place, FILE *fp2,ptr *headp)
{
	int i;
	int k;
	int num;
	int *num_arr;
	char operand[MAX];

	(*index) = place;

	
	while(input[*index] !='\n'){
			skip_spaces(input,index);
			read_word(input,operand,index);
			if(is_macro(operand,headp))
				num = is_macro(operand,headp);
			else
				num = atoi(operand);

			if(num < 0)
				num = 16384 + num;

			num_arr = decToBinary(num,4);
			k = 0;

			for(i=0;i<14;i++){
				memory_line[k] = num_arr[i];
				k++;
			}

			fprintf(fp2,"%d  ",IC+100);
			for(i = 0;i<14;i++)/*prints the memory line*/
				fprintf(fp2,"%d",memory_line[i]);
			fprintf(fp2,"\n");

			IC++;/*raise ic by one*/

			skip_spaces(input,index);
			if(input[*index] =='\n')
				break;
			(*index)++;
	}

	for(i = 0;i<14;i++)/*reset memory_line*/
		memory_line[i] = 0;
	
}




void insert_string_memory(char* input,int *index, int place, FILE *fp2)
{
	int i;
	int k;
	int num;
	int *num_arr;
	char operand[MAX];

	(*index) = place;

	
	while(input[*index] !='\n'){
			num = retrun_asc_code(input[*index]);
			if(num == 1){
				printf("Not a letter. Line %d",IC);
				return;
			}
			else{
				num_arr = decToBinary(num,4);
				k = 0;

				for(i=0;i<14;i++){
					memory_line[k] = num_arr[i];
					k++;
				}
			}
			fprintf(fp2,"%d  ",IC+100);
			for(i = 0;i<14;i++)/*prints the memory line*/
				fprintf(fp2,"%d",memory_line[i]);
			fprintf(fp2,"\n");
			IC++;/*raise ic by one*/
		
			(*index)++;
	}
	for(i = 0;i<14;i++)/*reset memory_line*/
		memory_line[i] = 0;

	fprintf(fp2,"%d  ",IC+100);
	for(i = 0;i<14;i++)/*prints the memory line*/
		fprintf(fp2,"%d",memory_line[i]);
	fprintf(fp2,"\n");
	IC++;/*raise ic by one*/
	
}


int insert_first_memory1(char* word,char* operand,int op_num,ptr *headp)
{
	int i;
	int j;
	int k;
	int num;
	int *num_arr;
			
	for(i=0;i<16;i++){
		if(strcmp(word,comm_oparr[i].name) == 0){
			num = comm_oparr[i].opcode;
			num_arr = decToBinary(num,1);
			k = 4;
			for(j=0;j<4;j++){
				memory_line[k] = num_arr[j];
				k++;
			}
			
			if(operand[0] == '#'){
				if(is_addr(operand,i,0,1))
					continue;
				else{
					printf("Illegal addresing method\n");
					return 1;
				}
			}

			else if(!is_macro(operand,headp) && !is_reg(operand) && !is_symbol_arr_exists(operand,headp)){
				if(is_addr(operand,i,1,1))
					memory_line[11] = 1;
				else{
					printf("Illegal addresing method\n");
					return 1;
				}
			}

			else if(is_symbol_arr_exists(operand,headp)){
				if(is_addr(operand,i,2,1))
					memory_line[10] = 1;
				else{
					printf("Illegal addresing method\n");
					return 1;
				}
			}
		

			else if(is_reg(operand)){
				if(is_addr(operand,i,3,1)){
					memory_line[11] = 1;
					memory_line[10] = 1;
				}
				else{
					printf("Illegal addresing method\n");
					return 1;
				}
			}
		}
	}
	return 0;
}

int insert_first_memory2(char* word,char* operand1,char* operand2,int op_num,ptr *headp)
{
	int i;
	int j;
	int k;
	int h;
	int num;
	int *num_arr;
		
	for(i=0;i<16;i++){
		if(strcmp(word,comm_oparr[i].name) == 0){
			num = comm_oparr[i].opcode;
			num_arr = decToBinary(num,1);
			k = 4;
			for(j=0;j<4;j++){
				memory_line[k] = num_arr[j];
				k++;
			}
			
			j = is_symbol_arr_exists(operand1,headp);
			printf("h1\n");
			h = is_symbol_arr_exists(operand2,headp);
			printf("h2\n");
			
			if(operand1[0] == '#'){
				
				if(is_addr(operand1,i,0,0)){
					goto sec_operand;
				}
				else{
					printf("Illegal addresing method\n");
					return 1;
				}
				
			}
			
			else if(!is_macro(operand1,headp) && !is_reg(operand1) && !j){
				if(is_addr(operand1,i,1,0))
					memory_line[9] = 1;
				else{
					printf("Illegal addresing method\n");
					return 1;
				}
			}

		
			else if(is_symbol_arr_exists(operand1,headp)){
				if(is_addr(operand1,i,2,1))
					memory_line[8] = 1;
				else{
					printf("Illegal addresing method\n");
					return 1;
				}
			}
		
			else if(is_reg(operand1)){
				if(is_addr(operand1,i,3,0)){
					reg_count += 1;
					memory_line[9] = 1;
					memory_line[8] = 1;
				}
				else{
					printf("Illegal addresing method\n");
					return 1;
				}
			}			
			
			/*-------------------*/
			sec_operand:do {
				/*printf("%s\n",operand2);*/
				if(operand2[0] == '#'){
					
					if(!is_addr(operand2,i,0,1)){
						/*k=1;
						continue;*/
						printf("Illegal addresing method\n");
						return 1;
						
					}
					else{
						/*printf("Illegal addresing method\n");
						return 1;*/
						k=1;
					}
				}

				else if(!is_macro(operand2,headp) && !is_reg(operand2) && !h){
					
					if(is_addr(operand2,i,1,1)){
						
						memory_line[11] = 1;
						k=1;
					}
					else{
						printf("Illegal addresing method\n");
						return 1;
					}
				}		

				else if(is_symbol_arr_exists(operand2,headp)){
					if(is_addr(operand2,i,2,1)){
						memory_line[10] = 1;
						k=1;
					}
					else{
						printf("Illegal addresing method\n");
						return 1;
					}
				}

				else if(is_reg(operand2)){
					if(is_addr(operand2,i,3,1)){
						reg_count += 1;
						memory_line[11] = 1;
						memory_line[10] = 1;
						k=1;
					}
					else{
						printf("Illegal addresing method\n");
						return 1;
					}
				}
				printf("%d\n",k);
			}while(k!=1);
		}
	}
	return 0;
}

int insert_operand_memory(char *operand, ptr *headp,int op_num,FILE *fp2)
{
	int i;
	int j;
	char index[MAX];
	char op[MAX];
	char symbol[MAX];
	
	int num;
	int *num_arr;
	int k;
	i = 1;

	if(operand[0] == '#'){
		while(operand[i] != ' ' && operand[i] != '\n' && operand[i] != ',' && operand[i] != '\0'){
			op[i-1] = operand[i];
			i++;
		}
		op[i] = '\0';
		/*printf("%s\n",op);*/
		if(is_macro(op,headp))
			num = is_macro(op,headp);
		else
			num = atoi(op);
		if(num < 0)
			num = 16384 + num;
		num_arr = decToBinary(num,2);
		k=0;		
		for(i=0;i<12;i++){
				memory_line[k] = num_arr[i];
				k++;
		}
		return 0;

	}	

	/*if the operand is a symbol prints the symbol for the second transition*/
	else if(!is_macro(operand,headp) && !is_reg(operand) && !is_symbol_arr_exists(operand,headp)){
		i = 0;
		while(operand[i] != '\0')
			i++;
		/*i += 5;
		fprintf("%d  ",IC+100);*/
		fprintf(fp2,"%s",operand);
		for(i=i;i<19;i++)
			fprintf(fp2," ");
		fprintf(fp2,"\n");
		IC++;
		return 1;
	}


	else if(is_symbol_arr_exists(operand,headp)){/*if the operand is a symbol prints the symbol for the second transition*/
		i = 0;
		k = 0;
		while(operand[i] !='['){
			if(operand[i] == '\0')
				return 1;
			symbol[i] = operand[i];
			i++;
		}
		symbol[i] = '\0';
		j=i;
		
		fprintf(fp2,"%s",symbol);
		for(i=i;i<19;i++)
			fprintf(fp2," ");
		fprintf(fp2,"\n");
		
		j++;
		IC++;
		
		while(operand[j] !=']'){
			if(operand[j] == '\0')
				return 1;
			
			index[k] = operand[j];
			j++;
			k++;
			
		}
		index[j] = '\0';
		
		if(is_macro(index,headp)){
			num = is_macro(index,headp);
		}
		else
			num = atoi(index);
		num_arr = decToBinary(num,2);
		k=0;
		for(i=0;i<12;i++){
				memory_line[k] = num_arr[i];
				k++;
		}
		
		return 0;
	}


	else if(is_reg(operand)){
		op[0] = operand[1]; 
		num = atoi(op);
		num_arr = decToBinary(num,3);
		if(op_num == 1)
			k=6;
		else
			k=9;

		for(i=0;i<3;i++){
				memory_line[k] = num_arr[i];
				k++;
		}
		return 0;
	}

}

void insert_2reg_memory(char* operand1, char* operand2)
{
	int i;
	char op1[MAX];
	char op2[MAX];
	int num;
	int *num_arr;
	int k;

	op1[0] = operand1[1]; 
	num = atoi(op1);
	num_arr = decToBinary(num,3);
	k = 6;
	for(i=0;i<3;i++){
			memory_line[k] = num_arr[i];
			k++;
	}

	op2[0] = operand2[1]; 
	num = atoi(op2);
	num_arr = decToBinary(num,3);
	k = 9;
	for(i=0;i<3;i++){
			memory_line[k] = num_arr[i];
			k++;
	}

}


void insert_memory_zero(char* input, char* word,int *index,FILE *fp2)
{
	int i;
	int j;
	int k;
	int num;
	int *num_arr;			
	for(i=0;i<16;i++){
		if(strcmp(word,comm_oparr[i].name) == 0){
			num = comm_oparr[i].opcode;
			num_arr = decToBinary(num,1);
			k = 4;
			for(j=0;j<4;j++){
				memory_line[k] = num_arr[j];
				k++;
			}
		}
	}
	fprintf(fp2,"%d  ",IC+100);
	for(i = 0;i<14;i++)
		fprintf(fp2,"%d",memory_line[i]);
	fprintf(fp2,"\n");
	IC++;
}

void insert_memory_one(char* input, char* word,char* operand,int *index,ptr *headp,FILE *fp2)
{
	int i;
	char op_cpy[MAX];
	strcpy(op_cpy,operand);

	if(insert_first_memory1(word,operand,1,headp)){/*memory of the command*/
		return;
	}		
	
	fprintf(fp2,"%d  ",IC+100);
	for(i = 0;i<14;i++)/*prints the memory line*/
		fprintf(fp2,"%d",memory_line[i]);
	fprintf(fp2,"\n");

	IC++;/*raise ic by one*/	

	for(i = 0;i<14;i++)/*reset memory_line*/
		memory_line[i] = 0;

	
	if(insert_operand_memory(op_cpy,headp,2,fp2)){/*memory of the operand*/
		
		for(i = 0;i<14;i++)/*reset memory_line*/
			memory_line[i] = 0;
		return;
	}
	else{
		fprintf(fp2,"%d  ",IC+100);
		for(i = 0;i<14;i++)/*prints the memory line*/
			fprintf(fp2,"%d",memory_line[i]);
		fprintf(fp2,"\n");
	
		IC++;/*raise ic by one*/
	}
	for(i = 0;i<14;i++)/*reset memory_line*/
		memory_line[i] = 0;	
}

void insert_memory_two(char* input, char* word,char* operand1, char* operand2,int *index,ptr *headp,FILE *fp2)
{
	int i;
	reg_count = 0;
	char op_cpy1[MAX];
	char op_cpy2[MAX];

	strcpy(op_cpy1,operand1);
	strcpy(op_cpy2,operand2);
	
	if(insert_first_memory2(word,operand1,operand2,1,headp))/*memory of the command*/
		return;	
	
	fprintf(fp2,"%d  ",IC+100);
	for(i = 0;i<14;i++)/*prints the memory line*/
		fprintf(fp2,"%d",memory_line[i]);
	fprintf(fp2,"\n");

	IC++;/*raise ic by one*/	
	
	for(i = 0;i<14;i++)/*reset memory_line*/
		memory_line[i] = 0;

	if(reg_count == 2){
		insert_2reg_memory(op_cpy1,op_cpy2);/*memory of the operand*/
		
		fprintf(fp2,"%d  ",IC+100);
		for(i = 0;i<14;i++)/*prints the memory line*/
			fprintf(fp2,"%d",memory_line[i]);
		fprintf(fp2,"\n");

		IC++;/*raise ic by one*/
		return;
	}
	
	if(insert_operand_memory(op_cpy1,headp,1,fp2)){
		for(i = 0;i<14;i++)/*reset memory_line*/
			memory_line[i] = 0;
	}	

	else{
		fprintf(fp2,"%d  ",IC+100);
		for(i = 0;i<14;i++)/*prints the memory line*/
			fprintf(fp2,"%d",memory_line[i]);
		fprintf(fp2,"\n");

		IC++;/*raise ic by one*/
	}
	for(i = 0;i<14;i++)/*reset memory_line*/
		memory_line[i] = 0;
	
	
	if(insert_operand_memory(op_cpy2,headp,2,fp2)){/*memory of the operand*/
		for(i = 0;i<14;i++)/*reset memory_line*/
			memory_line[i] = 0;
	}
	else{
		fprintf(fp2,"%d  ",IC+100);
		for(i = 0;i<14;i++)/*prints the memory line*/
			fprintf(fp2,"%d",memory_line[i]);
		fprintf(fp2,"\n");

		IC++;/*raise ic by one*/
	}
	for(i = 0;i<14;i++)/*reset memory_line*/
		memory_line[i] = 0;
	
}

int is_command(char* word)
{
	int i;
	for(i=0;i<2;i++)
		if(strcmp(word,comm_arr0[i]) == 0)
			return 0;
	
	for(i=0;i<9;i++)
		if(strcmp(word,comm_arr1[i]) == 0)
			return 1;

	for(i=0;i<5;i++)
		if(strcmp(word,comm_arr2[i]) == 0)
			return 2;

	return -1;	
}


/*Function that create a linked-list of the symbols*/
void insert(ptr *headp, int val, char *name, char *type)
{
	ptr temp = (ptr)malloc(sizeof(table));/*Creating a node dynamically.*/
	if(temp == NULL)
		exit(1);
	/*Assigning the data.*/
	strcpy(temp->name,name);
	temp->type = type;
	temp->val = val;

	/*if the head is null cre*/
	if(*headp == NULL){
		*headp = temp;
		temp->next = NULL;
	}

	ptr curr = *headp;/*a varible that used for running over the list*/
	while(curr->next != NULL)/*runs untill gets to the end of the list*/
	{
		if(strcmp(curr->name,name) == 0){
			printf("Symbol allready exist\n");
			return;
		}	
		curr = curr->next;
	}
	/*puts the new node in the end of the list*/
	curr->next = temp;
	temp->next = NULL;
}

void print_list(ptr headp)
{
	ptr curr;
	curr = headp;
	while(curr != NULL)/*runs untill gets to the end of the list*/
	{
		printf("%s:%s,%d\n",curr->name,curr->type,curr->val);
		curr = curr->next;
	}
}



void one_operand(char* input,char* operand,int *index)
{
	
	skip_spaces(input,index);

	if(input[*index] == '\n'){
		printf("Missing operand\n");
		return;
	}

	read_word(input,operand,index);
	skip_spaces(input,index);

	if(input[*index] != '\n' && input[*index] != ' ')/*if there is a char that is not enter or space after the parameters print the right exception and return 1*/
	{
	    printf("Extraneous text after end of command\n");
	    return;
	}
}


void two_operand(char* input, char* operand1, char* operand2,int *index)
{
	
	skip_spaces(input,index);

	if(input[*index] == '\n'){
		printf("Missing two operands\n");
		return;
	}

	read_word(input,operand1,index);
	skip_spaces(input,index);

	if(input[*index] != ',')
	{
		printf("Missing comma\n");
		return;
	}

	skip_spaces(input,index);
	if(input[*index] == '\n'){
		printf("Missing operand\n");
		return;
	}

	(*index)++;
	
	skip_spaces(input,index);
	read_word(input,operand2,index);
	skip_spaces(input,index);
	
	if(input[*index] != '\n' && input[*index] != ' ')/*if there is a char that is not enter or space after the parameters print the right exception and return 1*/
	{
	    printf("Extraneous text after end of command\n");
	    return;
	}
	
		
}


void macro_func(char* input, char* word, int *index, ptr *headp)
{
	char name[MAX];
	char num[MAX];
	
	skip_spaces(input,index);
	read_word(input,word,index);
	strcpy(name,word);
	skip_spaces(input,index);

	if(input[*index] != '=')
	{
		printf("Missing equal sign");
		return;
	}
	(*index)++;/**/

	skip_spaces(input,index);
	read_word(input,word,index);
	strcpy(num,word);

	int val = atoi(num);
	insert(headp,val,name,"macro");/*send the name and the value to a function that add a node to the linked list of flags*/
}

void data_func(char* input, char* word, int *index,ptr *headp)
{
	if(strcmp(word,".data") == 0){
		while(input[*index] !='\n')
		{
			skip_spaces(input,index);
			read_word(input,word,index);
			/*if(!isdigit(word) && !is_macro(word,headp)){
				printf("Not a number");
				return;
			}*/	
			skip_spaces(input,index);
			if(input[*index] == '\n')
				break;
			if(input[*index] != ',')
			{
				printf("Missing comma\n");
				return;
			}
			(*index)++;
			
		}
	}
	
	else{
		while(input[*index] !='\n')
			(*index)++;
	}
	
}

void symbol_func(FILE *fp2,char* input, char* word, char* operand1, char* operand2, int *index,ptr *headp)
{
	int operand_num;
	char symbol_name[MAX];
	int place;
	strcpy(symbol_name,word);
	skip_spaces(input,index);
	read_word(input,word,index);
	
	if(strcmp(word,".data") == 0){
		skip_spaces(input,index);
		place = *index;
		data_func(input,word,index,headp);
		insert(headp,IC+100,symbol_name,"data");
		insert_data_memory(input,index,place,fp2,headp);
		return;	
	}
	else if(strcmp(word,".string") == 0){
		skip_spaces(input,index);
		place = *index;
		data_func(input,word,index,headp);
		insert(headp,IC+100,symbol_name,"data");
		insert_string_memory(input,index,place,fp2);
		return;	
	}

	operand_num = is_command(word);

	if(operand_num == 0){
		insert(headp,IC+100,symbol_name,"code");
		insert_memory_zero(input,word,index,fp2);
	}

	else if(operand_num == 1){
		one_operand(input,operand1,index);
		insert(headp,IC+100,symbol_name,"code");
		insert_memory_one(input,word,operand1,index,headp,fp2);
	}

	else if(operand_num == 2){
		two_operand(input,operand1,operand2,index);
		insert(headp,IC+100,symbol_name,"code");
		insert_memory_two(input,word,operand1,operand2,index,headp,fp2);
		
	}

	else
		return;
}

void extern_func(char* input, char* word, char* operand, int *index,ptr *headp)
{
	skip_spaces(input,index);
	read_word(input,operand,index);
	if(strcmp(word,".extern") == 0){
		if(is_symbol_exists(word,headp)){
			printf("Symbol allready exist\n");
			return;
		}
		insert(headp,0,operand,"external");
	}	
}
