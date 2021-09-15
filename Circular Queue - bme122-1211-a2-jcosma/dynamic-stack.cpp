#include "dynamic-stack.h"
#include <iostream>

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack()//fine
{
    //items_ = nullptr;
    size_ = 0;
    init_capacity_ = 16;
    capacity_ = init_capacity_;
    items_ = new StackItem[capacity_];
}

DynamicStack::DynamicStack(unsigned int capacity)//fine
{
    init_capacity_ = capacity;
    capacity_ = capacity;
    size_ = 0;
    items_ = new StackItem[capacity_];
}

DynamicStack::~DynamicStack()//fine
{
    delete[] items_;
}

bool DynamicStack::empty() const //fine
{
    if (size_ == 0) return true;
    return false;
}

int DynamicStack::size() const//fine
{
    return size_;
}

void DynamicStack::push(StackItem value)
{
    //double array capacity
     if(size_ == capacity_)
     {
         StackItem *newArray;
         newArray = new StackItem[capacity_*2];
         for (int i = 0; i < size_; i++)
         {
             newArray[i] = items_[i];
         }
         delete[] items_;
         capacity_ = capacity_*2;
         items_ = newArray;
     }

    items_[size_] = value;
    size_++;
}

DynamicStack::StackItem DynamicStack::pop()
{
    if(empty()) return EMPTY_STACK;

    StackItem top = items_[size_-1];
    items_[size_-1] = NULL;
    size_ --;

    if(size_ <= capacity_/4 && capacity_/2 >= init_capacity_)
    {
        StackItem* newArray;
        newArray = new StackItem[capacity_/2];
        for (int i=0; i<size_; i++)
        {
            newArray[i] = items_[i];
        }
        delete[] items_;
        items_ = newArray;
        capacity_ = capacity_/2;

    }

    return top;
}

DynamicStack::StackItem DynamicStack::peek() const//fine
{
    if (empty()) return EMPTY_STACK;

    return items_[size_ - 1];
}

void DynamicStack::print() const//fine
{
    for (int i=0; i<size_; i++)
    {
        std::cout << items_[i];
    }
}
