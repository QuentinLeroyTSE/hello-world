//Declaration classe T2D

#ifndef _T2D_
#define _T2D_

#include <string>

using namespace std;

class T2D {

	int X_;
	int Y_;
	float **tab_;

public:

	T2D(int resX, int resY);
	void fillTab(float* tabF, int sizeTF);
	void exportobj(string name, float pos1, float pos2);
	void exportT2D(string name); //pour le d�veloppement
	void pantalon(float alpha);
	//Ajouter vos d�claration de m�thode ici (les d�finitions dans le .cpp et utilisation dans le main)

};

#endif // !_T2D_