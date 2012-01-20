#ifndef _FILEMAKER_H_INCLUDED
#define _FILEMAKER_H_INCLUDED


#include <iostream>
#include <string>
#include <fstream>
using namespace std;

extern int LogLevel;

int file_maker(int * size, double ** outtable, const string &filename);

#endif