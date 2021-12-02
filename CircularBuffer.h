// Copyright [2021] <Nuno Mestre>

#ifndef _HOME_NUNO_PS4B_CIRCULARBUFFER_H_
#define _HOME_NUNO_PS4B_CIRCULARBUFFER_H_
#include <stdint.h>
#include <iostream>
class CircularBuffer {
 public:
        explicit CircularBuffer(int capacity);
        ~CircularBuffer();
        int get_size();
        bool isEmpty();
        bool isFull();
        void enqueue(int16_t x);
        int16_t dequeue();
        int16_t peek();
 private:
        int16_t* data;
        int size;
        int capacity;
};
#endif  // _HOME_NUNO_PS4B_CIRCULARBUFFER_H_
