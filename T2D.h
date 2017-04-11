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
	void fillTab(float* tabF, int sizeTF, int resX);
	void exportobj(string name, float pos1, float pos2, int resX, int resY);
	void exportT2D(string name, int resY); //pour le développement
	//Ajouter vos déclaration de méthode ici (les définitions dans le .cpp et utilisation dans le main)

};

#endif // !_T2D_