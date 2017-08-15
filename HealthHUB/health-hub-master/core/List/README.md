# List
The List class implements the ring buffer data structure. It is able to store as many `int16` values as defined during initialization. 

The class provides various functions to access and store data as well as a few arithmetical functions over all values within the list.

## Store Data
To store new values into the list use the `push_front(int16_t value)` function. This also takes care if the value exceeds the maximum amount of values the list is able to store. Once the maximum limit is reached, the the oldest value is deleted and every value moves a position backwards. 

## Access Data
To access stored data you can either use the `pop_*` functions, which returns **and** deletes the value (similar as a stack) or the `read_*` functions, which only returns the value without deleting it. 
If you want a value given a specific position with the list, you can use the `read(uint8_t pos)` function. 

## Arithmetical functions
The List class also provides functions to calculate statistic measures over all values within the list. You can either calculate the `sum()` the `mean()` or the `standardDeviation()`. These functions are mainly used to determine if a sensor scan is finished.

Based on the standard deviation, the code below demonstrate how to use the list class:

```
int16_t List::standardDeviation(){
  int16_t sd = 0;
  int16_t m = mean();

  for(int i=0; i < size(); i++){
    sd += pow(read(i) - m, 2);
  }

  sd /= size();

  return(sqrt(sd));
}
```