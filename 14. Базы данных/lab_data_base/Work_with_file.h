#pragma once
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <algorithm>
#include <vector>
#include "Student.h"


void copyFileContentToList(const std::string &filename, std::list<Student> &_list);
void copyListContentToFile(const std::string &filename, std::list<Student> &_list);
void copyListContentToFileWithoutSave(const std::string &filename, std::list<Student> &_list);
void viewGroupList();
void makeFile();
void printFileContent();
void addElementToFileBegin();
void addElementToFileEnd();
void addElementToFileAtPos();
void makeBackupFile(std::list<Student> &_list);
void doBackup();
void removeElementFromFile();
void changeElement();
void makeSharedFileSortedByName();
void makeSharedFileSortedByGroup();