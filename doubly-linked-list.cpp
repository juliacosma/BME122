#include "doubly-linked-list.h"
#include <iostream>
#include <new>
using namespace std;

DoublyLinkedList::Node::Node(DataType data)
        :value(data), next(NULL), prev(NULL)
{
}
DoublyLinkedList::DoublyLinkedList()
        :head_(NULL), tail_(NULL), size_(0)
{
}

/*DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& list)
:size_(list.size_)
{
}*/

DoublyLinkedList::~DoublyLinkedList()
{
    Node* temp;
    while (head_ != NULL)
    {
        temp = head_ -> next;
        delete head_;
        head_ = temp;
    }
}

bool DoublyLinkedList::empty() const
{
    if(size() == 0) return true;
    else return false;
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    return CAPACITY;
}

void DoublyLinkedList::print() const
{
    for(int i = 0; i < size(); i++) {
        cout << select(i) << " ";
    }
}

bool DoublyLinkedList::insert_front(DataType value)
{
    return insert(value, 0);
}

bool DoublyLinkedList::remove_front()
{
    return remove(0);
}

bool DoublyLinkedList::insert_back(DataType value)
{
    return insert(value, size());
}

bool DoublyLinkedList::remove_back()
{
    return remove(size()-1);
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    if(index > size() || full()) return false;

    Node* newNode = new Node(value);

    if(empty()) {
        head_ = newNode;
        tail_ = newNode;
    //add to front
    } else if(index == 0) {
        newNode -> next = head_;
        head_ -> prev = newNode;
        head_ = newNode;
    //add to back
    } else if(index == size()) {
        Node* last = getNode(size()-1);
        last -> next = newNode;
        newNode -> prev = last;
        tail_ = newNode;
    //add to index
    } else {
        Node* nodePtr = getNode(index-1);
        newNode -> next = nodePtr -> next;
        nodePtr -> next = newNode;
        newNode -> prev = nodePtr;
        if(newNode -> next != NULL) newNode -> next -> prev = newNode;
    }
    size_++;
    return true;
}

bool DoublyLinkedList::remove(unsigned int index)
{
    if(index >= size()) return false;

    Node* nodePtr = getNode(index);
    if(index == 0) {
        //empties list
        if(size() == 1) {
            head_ = NULL;
            tail_ = NULL;
        }
        //delete front node
        else {
            head_ = head_ -> next;
            head_ -> prev = NULL;
        }
    //delete last node
    } else if (index == size()-1) {
        tail_ = tail_ -> prev;
        tail_ -> next = NULL;
    //delete at index
    } else {
        Node* prev = nodePtr -> prev;
        Node* next = nodePtr -> next;
        prev -> next = next;
        next -> prev = prev;
    }
    size_--;
    delete nodePtr;
    return true;
}

unsigned int DoublyLinkedList::search(DataType value) const
{
    Node* nodePtr = head_;
    for(int i = 0; i < size(); i++) {
        if(nodePtr -> value == value) {
            return i;
        }
        nodePtr = nodePtr -> next;
    }
    return size();
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    if(index >= size()) {
        return getNode(size()-1) -> value;
    } else {
        return getNode(index) -> value;
    }
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    if(index >= size()) return false;

    Node* nodePtr = getNode(index);
    nodePtr -> value = value;
    return true;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    Node* nodePtr = head_;
    for(int i = 0; i < index; i++) {
        nodePtr = nodePtr -> next;
    }
    return nodePtr;
}

bool DoublyLinkedList::full() const
{
    if(size() == capacity()) return true;
    else return false;
}
