#ifndef MATRIX_H
#define MATRIX_H

#include "testBase.h"

namespace testBase{
	class Matrix : public Base{

		class Circle;
		public:
			Matrix(){
				type = 1;
				protect = 2;
			}
			virtual	void getType();
			~Matrix(){

			}
	};

}


#endif
