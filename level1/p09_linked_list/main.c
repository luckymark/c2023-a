#include <stddef.h>
#include <assert.h>

typedef struct {

} List;


List *create_list(int size);

void set_list(int index, int data);

void reverse_list(List *list);

int find_list(List *list, int data);

int multi_find_list(List *list, int data, int index);

int main() {
    List *list = create_list(3);
    set_list(1, 1);
    set_list(2, 2);
    set_list(3, 2);
    reverse_list(list);
    int index_of_2 = find_list(list, 2);
    assert(index_of_2 == 0);
    int index_of_second_2 = multi_find_list(list, 2, 2);
    assert(index_of_second_2==1);
}

int multi_find_list(List *list, int data, int index) {
    return 0;
}

int find_list(List *list, int data) {
    return 0;
}

void reverse_list(List *list) {

}

void set_list(int index, int data) {

}

List *create_list(int size) {
    return NULL;
}
