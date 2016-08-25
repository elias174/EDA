#include<iostream>
using namespace std;

template <class T>
class Node {
public:
    T data;
    Node<T> * next;
    Node(T data){
        this->data = data;
        this->next = NULL;
    }
};

template <class T>
class List {

public:
    Node<T> * head;
    List(){
        this->head = NULL;
    }
    void insert(T data){
        if(!head){
            head = new Node<T>(data);
            return;
        }
        Node<T> *tmp = this->head;
        Node<T> *prev = NULL;
        while(tmp){
            prev = tmp;
            tmp = tmp->next;
        }
        tmp = new Node<T>(data);
        prev->next = tmp;
    }

    void print(){
        Node<T> *tmp = this->head;
        while(tmp){
            cout << tmp->data << endl;
            tmp = tmp->next;
        }
    }

    void reverse(){
        Node<T> *tmp = this->head;
        Node<T> *prev = NULL;
        Node<T> *next = NULL;
        while(tmp){
            next = tmp->next;
            tmp->next = prev;
            prev = tmp;
            tmp = next;
        }
        this->head = prev;
    }

};


int main (int argc, char *argv[]) {
    List<int> a;
    a.insert(2);
    a.insert(3);
    a.insert(24);
    a.insert(31);
    a.insert(21);
//  a.print();
    a.reverse();
    a.print();
    //cout << a.head->data << endl;
    return 0;
}
