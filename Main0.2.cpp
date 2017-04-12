//Programme Traitement d'image 3D format obj

/*
Ajoutez vos méthodes dans le header et le source de l'objet T2D
Tester vos méthodes sur l'objet t2d crée plus bas, après la borne "ICI APPLIQUEZ VOS METHODES T2D A L'OBJET t2d"
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Include\T2D.h"

using namespace std;

void main()
{

	string nom_fichier = "";
	cout << "nom du fichier : " << endl;
	cin >> nom_fichier;
	//ouverture du fichier en mode texte
	ifstream fichier(nom_fichier); 
	string mot = "";
	string pos1, pos2;
	if (!fichier.is_open()) { cout << "Erreur d'ouverture" << endl; }
	else {
		//Gestion entête
		while (mot != "pos1:") {
			fichier >> mot;
		}
		fichier >> pos1;
		while (mot != "pos2:") {
			fichier >> mot;
		}
		fichier >> pos2
		fichier.close();
	}
	//ouverture du fichier en mode bianaire
	ifstream frapide(nom_fichier, ios::in | ios::binary); 
	if (!frapide.is_open()) { cout << "Erreur d'ouverture" << endl; }
	else {
		//calcul taille du fichier
		
		long pos = frapide.tellg();
		frapide.seekg(0, ios_base::end);
		long sizeFichier = frapide.tellg();
		frapide.seekg(pos, ios_base::beg);
		
		//lecture du fichier en mode binaire
		char* tabC = new char[sizeFichier];
		frapide.read((char *)&tabC[0], sizeFichier*sizeof(char));
		if (!frapide.good()) { cout << "Erreur de lecture" << endl; }
		else { cout << "Lecture terminee" << endl; }
		frapide.close();

		//compte du nombre de ligne
		char* v = "v";
		int nbr_ligne = 0;
		int i = 0;
		for (i; i < sizeFichier; i++) {
			if (tabC[i] == *v) {
				nbr_ligne++;
				i = i + 20; //histoire de gagner du temps
			}
		}
		int sizeTF = nbr_ligne * 3;
		float* TabF = new float[sizeTF];
		cout << "sizeTF : " << sizeTF << endl;
		//recherche du 1er "v"
		i = 0;
		while (tabC[i] != *v) {
			i++;
		}
		//tabC[i] = v ici
		i = i + 2;
		char *esc = " ";
		char *n = "\n";
		string valeur = "";
		float fvaleur = 0;
		int f = 0;
		while (i < sizeFichier) {
			if (tabC[i] == *v) {
				i = i + 2;
			}
			while (tabC[i] != *esc && tabC[i] != *n) {
				valeur += tabC[i]; //très long --> à optimiser
				i++;
			}
			fvaleur = stof(valeur);
			TabF[f] = fvaleur;
			valeur = "";
			f++;
			i++;
		}
		cout << "tableau float rempli " << endl;
		
		//Iniatialisation matrice 2D contenant les altitudes
		int resX = 1437; //nombre de ligne
		int resY = 1280; //nombre de colonne
		T2D t2d(resX, resY);
		
		t2d.fillTab(TabF, sizeTF, resX);
		
		/**********************************************/
		/*ICI APPLIQUEZ VOS METHODES T2D A L'OBJET t2d*/
		/**********************************************/
		cout << "debut traitement " << endl;
		float alpha = 0;
		cout << "alpha : " << endl;
		cin >> alpha;
		t2d.pantalon(alpha);
		
		
		
		
		cout << "traitement termine " << endl;
		//exportation en obj
		float p1, p2;
		p1 = stof(pos1);
		p2 = stof(pos2);
		t2d.exportobj("newfile.obj", p1, p2, resX, resY);

	}//else ouverture

	system("pause");
}


