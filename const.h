typedef struct constTab{
	char name[10];
	int opcode;
	int orig_addr[4];
	int des_addr[4];		
}tab;

typedef struct constAsc{
	char letter;
	int asc_code;		
}ascii;
