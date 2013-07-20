#ifndef TEST_BASH_H
#define TEST_BASH_H

#include <stdio.h>

namespace testBase{
	typedef unsigned int uint32_t;
	class Base{

		protected:
			uint32_t type;
			uint32_t protect;
		public:
			Base(){}
		    virtual	~Base(){}
			virtual	void getType() = 0;

	};

}

#endif

