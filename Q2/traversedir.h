struct stack{
	char* path;
	struct stack* next;
};


struct table{
	struct record** a;
	int size;
	struct record** max;
	int k;
};

struct record{
	char* word;
	int count;
	struct record* next;
	int rank;
};

