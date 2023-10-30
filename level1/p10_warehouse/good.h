typedef struct Good Good;
struct Good{
    char name[30];
    char model[50];
    int num;
    Good* last;
    Good* next;
};

typedef struct Good Good;
Good* pop(Good* good);
void push(Good* good);
void showlist(Good good);


