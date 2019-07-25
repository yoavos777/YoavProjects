#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * decToBinary(int n,int word_num) 
{ 
	int a[16],i,j;
	int k,h;
	static int b[16];
	k = 0;
       
	for(i=0;n>0;i++)    
	{    
		a[i]=n%2;    
		n=n/2;
		k++;  
	}   
	
	if(word_num == 1){
		if(k<4){
			for(h=k;h<4;h++)
				a[h]=0;
			i=h;
		}
	}

	if(word_num == 2){
		if(k<12){
			for(h=k;h<12;h++)
				a[h]=0;
			i=h;
		}
	}

	if(word_num == 3){
		if(k<3){
			for(h=k;h<3;h++)
				a[h]=0;
			i=h;
		}
	}

	if(word_num == 4){
		if(k<14){
			for(h=k;h<14;h++)
				a[h]=0;
			i=h;
		}
	}

	j = i-1;
	for(i=i-1;i>=0;i--)    
	{    
		b[j-i] = a[i]; 
	}
	return b;    
}

/*Function that skip space charachters and tabs*/
void skip_spaces(char* input, int *index)
{
	/*int nextTabStop;*/

	while(input[*index] == ' ' || input[*index] == '\t')
	    (*index)++;
}

void read_word(char* input, char* word, int *index)
{
	int i = 0;
	while(input[*index] != ' ' && input[*index] != '\n' && input[*index] != '\t' && input[*index] != '=' && input[*index] != ',')/*runs until the current character is space, enter*/
	{
	    word[i] = input[*index];/*puts the current character of input in the character of functionType*/
	    (*index)++;/*raise the place index of input by 1*/
	    i++;/*raise the place index of functionType by 1*/
	}
	word[i] = '\0';/*puts null in the end of functionType to make it a string*/
}




void get_symbol_name(char* operand)
{
	int i;
	i = 0;
	while(operand[i] != '[')
		i++;
	operand[i] = '\0';
}





