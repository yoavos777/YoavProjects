#define MAX 200

typedef struct tab * ptr;
typedef struct tab{
	char name[MAX];
	char *type;
	int val;
	ptr next;
}table;
