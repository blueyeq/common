#include "Circle.h"

namespace testBase{
	Circle::Circle(){
		base_member = new Matrix();
	}
	Circle::~Circle(){
		if(base_member != NULL){
			delete base_member;
		}
	}
	void Circle::BaseGetType(){
		printf("in circlen\n");
		base_member->getType();
	}
}
