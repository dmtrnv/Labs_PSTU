#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "HashTable.h"


HashTable makeAndFill();
void add(HashTable &table);
void remove(HashTable &table);
void find(HashTable &table);
void changeData(HashTable &table);
void showNumberOfCollisions(HashTable &table);