#include <iostream>
#include "hash.h"

unsigned int hashFunction(unsigned int key, unsigned int capacity) { //Função hash
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = (key >> 16) ^ key;
    return key % capacity;
}