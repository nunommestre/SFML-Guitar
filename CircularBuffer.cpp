// Copyright [2021] <Nuno Mestre>
#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(int cap) {
        size = 0;
        capacity = cap;
        if (cap < 1) {
                throw std::invalid_argument
                ("constructor: capacity must be greater than zero.");
        }
        data = new int16_t[cap];
        for (int i = 0; i < capacity; ++i) {
                data[i] = 0;
        }
}
int CircularBuffer::get_size() {
        return size;
}
bool CircularBuffer::isEmpty() {
        if (size == 0) {
                return true;
        }
        return false;
}
bool CircularBuffer::isFull() {
        if (size >= capacity) {
                return true;
        }
        return false;
}
void CircularBuffer::enqueue(int16_t x) {
        if (!isFull()) {
                data[size] = x;
                size++;
        } else {
                throw std::runtime_error
                ("enqueue: can't enqueue to a full ring");
        }
}
int16_t CircularBuffer::dequeue() {
        if (isEmpty()) {
                throw std::runtime_error
                ("dequeue: cannot remove the last item in an empty queue");
        }
        int16_t arr = [this]() { return data[0];} ();
        for (int i = 0; i < capacity - 1; ++i) {
                data[i] = data[i+1];
        }
        size--;
        return arr;
}
int16_t CircularBuffer::peek() {
        if (isEmpty()) {
                throw std::runtime_error
                        ("peek: there are no items to see in this queue");
        }
        return data[0];
}
CircularBuffer::~CircularBuffer() {
        delete data;
        data = nullptr;
}
