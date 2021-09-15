#include "sequential-list.h"
#include <iostream>
using namespace std;

//Constructor
SequentialList::SequentialList(unsigned int cap)
{
    capacity_ = cap;
    size_ = 0;
    data_ = new DataType[capacity_];
}
//Destructor
SequentialList::~SequentialList()
{
    delete [] data_;
    data_ = nullptr;
}

unsigned int SequentialList::size() const
{
    return size_;
}

unsigned int SequentialList::capacity() const
{
    return capacity_;
}

bool SequentialList::empty() const
{
    if(size() == 0) {
        return true;
    } else {
        return false;
    }
}

bool SequentialList::full() const
{
    if(size() == capacity()) {
        return true;
    } else {
        return false;
    }
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
    if(index >= 0 && index < size()) {
        return data_[index];
    } else {
        return data_[size()-1];
    }
}

unsigned int SequentialList::search(DataType val) const
{
    for(int i = 0; i < size(); i++) {
        if(data_[i] == val) {
            return i;
        }
    }
    return size();
}

void SequentialList::print() const
{
    cout << "All elements in list: ";
    for(int i = 0; i < size(); i++) {
        cout << data_[i] << " ";
    }
}

bool SequentialList::insert(DataType val, unsigned int index)
{
    //out of bounds or list is full
    if(index > size() || full()) return false;

    //move data items back by one
    for(int i = size(); i > index; i--) {
        data_[i] = data_[i-1];
    }
    data_[index] = val;
    size_++;
    return true;
}

bool SequentialList::insert_front(DataType val)
{
    return insert(val, 0);
}

bool SequentialList::insert_back(DataType val)
{
    return insert(val, size());
}

bool SequentialList::remove(unsigned int index)
{
    //out of bounds
    if(index >= size()) return false;

    //move data items forward by one
    for(int i = index; i < size()-1; i++) {
        data_[i] = data_[i+1];
    }
    data_[size()-1] = NULL;
    size_--;

    return true;
}

bool SequentialList::remove_front()
{
   return remove(0);
}

bool SequentialList::remove_back()
{
    return remove(size()-1);
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    //out of bounds
    if(index >= size()) return false;

    data_[index] = val;
    return true;
}

