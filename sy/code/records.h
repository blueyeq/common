#ifndef RECORDS_H
#define RECORDS_H

#include "stdAfx.h"
#include "geometry.h"
#include <vector>

#define PB push_back

class Record{
public:
	int vehicle_id;
	int time;
	geo::Point2X point;
	int section_id;
public:
	Record(){
		vehicle_id=0;
		time=0;
		section_id=0;
	}
};

#endif