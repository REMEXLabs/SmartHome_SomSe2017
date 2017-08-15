/*
Author: Eric Schmidt
Update: 22. April 2017
//--------------------------------------------------------------------------
*/

#ifndef __LIST_H__
#define __LIST_H__

#include <stdint.h>

// Provides a class for a basic chained list with a few extra functions for data
// access.
//
class List
{
  private:
    int16_t *buffer;

    uint8_t bufferSize;
    uint8_t head;
  public:
    List(uint8_t size);

    void push_front(int16_t value);
    int16_t pop_back();
    int16_t pop_front();
    int16_t read_back();
    int16_t read_front();
    int16_t read(uint8_t pos);

    void clear();

    uint8_t size();
    uint8_t max_size();

    int16_t sum();
    int16_t mean();
    int16_t standardDeviation();

};

#endif // __LIST_H__
