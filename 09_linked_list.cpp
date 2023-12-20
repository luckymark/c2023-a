#include <iostream>

// 定义链表节点类
class Node{
public:
    int data;
    Node* next;

    Node(int data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

// 定义链表类
class LinkedList {
public:
    Node* head;

    LinkedList() {
        head = nullptr;
    }

    // 插入一个新节点到链表末尾
    void insert(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // 打印链表
    void display() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};

int main() {
    LinkedList myList;
    myList.insert(1);
    myList.insert(2);
    myList.insert(3);

    myList.display();

    return 0;
}