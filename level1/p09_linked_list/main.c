#include <stddef.h>
#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct List {
    int data;
    struct List *next;
} List;


List *create_list(int size);

void set_list(List *list, int index, int data);

List *reverse_list(List *list);

//找不到返回-1 index从0开始
int find_list(List *list, int data);

//返回第count个data的索引 找不到返回-1
int multi_find_list(List *list, int data, int count);

int main() {
    List *list = create_list(3);
    set_list(list, 0, 1);
    set_list(list, 1, 5);
    set_list(list, 2, 5);
    list = reverse_list(list);
    int index_of_2 = find_list(list, 5);
    assert(index_of_2 == 0);
    int index_of_second_2 = multi_find_list(list, 5, 2);
    assert(index_of_second_2 == 1);
    return 0;
}

int multi_find_list(List *list, int data, int count) {
    List *now = list;
    int index = 0;
    while (now->next != NULL) {
        if (now->data == data) {
            --count;
            if (count == 0) return index;
        }
        ++index;
        now = now->next;
    }
    return -1;
}

int find_list(List *list, int data) {
    return multi_find_list(list, data, 1);
}

List *reverse_list(List *list) {
    List *prev = NULL;
    List *now = NULL;
    List *nxt = list;
    while (nxt->next != NULL) {
        prev = now;
        now = nxt;
        nxt = nxt->next;
        now->next = prev;
    }
    nxt->next = now;
    return nxt;
}

void set_list(List *list, int index, int data) {
    List *now = list;
    int cnt = 0;
    while (cnt < index) {
        assert(now->next != NULL);//无效的index 越界了
        now = now->next;
        ++cnt;
    }
    now->data = data;
}

List *create_list(int size) {
    List *new_list = malloc(size * sizeof(List));
    for (int i = 0; i < size - 1; ++i) {
        new_list[i].next = new_list + i + 1;
    }
    new_list[size - 1].next = NULL;
    return new_list;
}
