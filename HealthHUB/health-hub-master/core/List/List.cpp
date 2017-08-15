/*
Author: Eric Schmidt
Update: 24. April 2017
//--------------------------------------------------------------------------
*/

#include "List.h"
#include <math.h>

// Constructor for List class. Creates a Array with given size
//
// uint8_t size: Size of the List
//
List::List(uint8_t size){
  bufferSize = size;
  head = -1;
  buffer = new int16_t[bufferSize];
}

// Insert a given value into the next index of the List. If the index
// exceeds bufferSize the last entry is removed with @see List#pop_back.
//
// int16_t value: Value to insert
//
void List::push_front(int16_t value){
  head += 1;
  if (head == bufferSize){
    pop_back();
    buffer[head] = value;
  }else{
    buffer[head] = value;
  }
}

// Read the last entry of the List
//
// Return: Last entry of the List
//
int16_t List::read_back(){
  return buffer[0];
}

// Read the first entry of the List
//
// Return: First entry of the List
//
int16_t List::read_front(){
  return buffer[head];
}

// Read the entry of a given index of the List.
//
// uint8_t pos: Index of the entry
//
// Return: Entry of the List at given position
//
int16_t List::read(uint8_t pos){
  return buffer[pos];
}

// Reads and Removes the last Entry of the List
//
// Return: The last Entry of the List
//
int16_t List::pop_back(){
  int16_t value = buffer[0];

  for (uint8_t i=1; i < bufferSize; i++){
    buffer[i-1] = buffer[i];
  }
  head -= 1;

  return value;
}

// Reads and Removes the first Entry of the List
//
// Return: The first Entry of the List
//
int16_t List::pop_front(){
  int16_t value = buffer[head];
  head -= 1;

  return value;
}

// Clear the List.
//
void List::clear(){
  head = -1;
}

// Calculate the sum over all entries of the List
//
// Return: The sum over all entries of the List
//
int16_t List::sum(){
  int16_t sum = 0;

  for(int i=0; i < size(); i++){
    sum += read(i);
  }

  return sum;
}

// Calculate the mean over all entries of the List
//
// Return: The mean over all entries of the List
//
int16_t List::mean(){
  return sum() / size();
}

// Calculate the standard deviation over all entries of the List
//
// Return: The standard deviation over all entries of the List
//
int16_t List::standardDeviation(){
  int16_t sd = 0;
  int16_t m = mean();

  for(int i=0; i < size(); i++){
    sd += pow(read(i) - m, 2);
  }

  sd /= size();

  return(sqrt(sd));
}

// Returns the current size of the List
//
// Return: The size of the List
//
uint8_t List::size(){
  return head + 1;
}

// Returns the maximum size of the List
//
// Return: The maximum size of the List
//
uint8_t List::max_size(){
  return bufferSize;
}
