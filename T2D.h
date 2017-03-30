//Declaration classe T2D

#ifndef _T2D_
#define _T2D_

#include <string>

using namespace std;

class T2D {

	int tailleTab_;
	float **tab_;

public:

	T2D(int resX, int resY);
	void fillTab(float* tabF, int sizeTF);

};

#endif // !_T2D_