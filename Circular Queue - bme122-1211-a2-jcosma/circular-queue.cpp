#include "circular-queue.h"
#include <iostream>

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue()
{
    head_ = 0;
    tail_ = 0;
    capacity_ = 16;
    size_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity)
{
    head_ = 0;
    tail_ = 0;
    capacity_ = capacity;
    size_ = 0;
    items_ = new QueueItem[capacity];
}

CircularQueue::~CircularQueue()
{
    delete[] items_;
}

bool CircularQueue::empty() const
{
    if (size_ == 0) return true;
    return false;
}

bool CircularQueue::full() const
{
    if (size_ == capacity_) return true;
    return false;
}

int CircularQueue::size() const
{
    return size_;
}

bool CircularQueue::enqueue(QueueItem value)
{
    if (full()) return false;

    items_[tail_] = value;

    if (tail_ == capacity_ - 1)
    {
        tail_ = 0;
    }
    else
    {
        tail_++;
    }
    size_++;

    return true;
}

CircularQueue::QueueItem CircularQueue::dequeue()
{
    if(empty()) return EMPTY_QUEUE;

    QueueItem returnMe = items_[head_];

    if (head_ == capacity_ -1)
    {
        head_ = 0;
    }
    else
    {
        head_++;
    }
    size_--;

    return returnMe;
}

CircularQueue::QueueItem CircularQueue::peek() const
{
    if (empty()) return EMPTY_QUEUE;

    return items_[head_];
}

void CircularQueue::print() const
{
    for (int i=0; i<capacity_; i++) std::cout << items_[i];
}
