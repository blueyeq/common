#ifndef TIME_H
#define TIME_H

#include "stdafx.h"
#include <iostream>

using namespace std;

class Mytime{
public:
	int seconds;
	int getSeconds(char cdataTime[50]);
};

void readTime(char* timefile1);


#endif