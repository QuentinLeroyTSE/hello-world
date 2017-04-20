//Programme Traitement d'image 3D format obj
//Méthodes à ajouter vers la fin du programme, à l'emplacement indiqué.

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

	ifstream fichier(nom_fichier); //ouverture du fichier en mode texte
	
	string mot = "";
	string pos1, pos2;

	if (!fichier.is_open()) {
		cout << "Erreur d'ouverture" << endl;
	}
	else {
		
		//Gestion entête
		while (mot != "pos1:") {
			fichier >> mot;
		}
		fichier >> pos1;
		while (mot != "pos2:") {
			fichier >> mot;
		}
		fichier >> pos2;

		cout << "pos1: " << pos1 << endl;
		cout << "pos2: " << pos2 << endl;

		fichier.close();
	}

	ifstream frapide(nom_fichier, ios::in | ios::binary); //ouverture du fichier en mode bianaire

	if (!frapide.is_open()) {
		cout << "Erreur d'ouverture" << endl;
	}
	else {
		
		//calcul taille du fichier
		
		// sauvegarder la position courante 
		long pos = frapide.tellg();
		// se placer en fin de fichier 
		frapide.seekg(0, ios_base::end);
		// récupérer la nouvelle position = la taille du fichier 
		long sizeFichier = frapide.tellg();
		// restaurer la position initiale du fichier 
		frapide.seekg(pos, ios_base::beg);
		cout << "size fichier : " << sizeFichier << endl;
		
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

		cout << "nbr_ligne fichier, nombre de point : " << nbr_ligne << endl; // = nombre de point enfaite

		int sizeTF = nbr_ligne * 3;
		float* TabF = new float[sizeTF];
		cout << "sizeTF : " << sizeTF << endl;
		//recherche du 1er "v"
		i = 0;
		while (tabC[i] != *v) {
			i++;
		}
		//tabC[i] = v ici
		//Remplissage Tableau de float; interprétation en float
		i = i + 2;
		char *esc = " ";
		char *n = "\n";
		char cval[9];
		int c = 0;
		string svaleur = "123456789"; //9 char -234.6789
		float fvaleur = 0;
		int f = 0;
		while (i < sizeFichier) {
			if (tabC[i] == *v) {
				i = i + 2;
			}
			while (tabC[i] != *esc && tabC[i] != *n) {
				if (c < 9) {//limitation à 9 char
					cval[c] = tabC[i];
					c++;
				}
				i++;
				
			}
			svaleur = cval;
			fvaleur = stof(svaleur);
			TabF[f] = fvaleur;
			c = 0;
			f++;
			i++;
		}
		cout << "tableau float rempli " << endl;
		
		//Iniatialisation matrice 2D contenant les altitudes
		int resX = 1437;
		int resY = 1280;
		T2D t2d(resX, resY);
		
		t2d.fillTab(TabF, sizeTF);

		string choix;
		cout << "exporter T2D o/n : " << endl;
		cin >> choix;
		if (choix == "o") {
			t2d.exportT2D("T2D.txt");
		}

		cout << "debut traitement " << endl;
		cout << "traitement pantalon o/n : " << endl;
		cin >> choix;
		if (choix == "o") {
			float alpha = 0;
			cout << "alpha : " << endl;
			cin >> alpha;
			t2d.pantalon(alpha);
		}
		cout << "traitement ouverture o/n : " << endl;
		cin >> choix;
		if (choix == "o") {
			t2d.ouverture();
		}
		cout << "traitement contour o/n : " << endl;
		cin >> choix;
		if (choix == "o") {
			t2d.contour();
		}
		/*****************************/
		/*AJOUTER VOS TRAITEMENTS ICI*/
		/*****************************/
		
		/* << "traitement ton_traitement o/n : " << endl;
		cin >> choix;
		if (choix == "o") {
			t2d.ta_methode();
		}
		*/
		
		
		cout << "traitement termine " << endl;

		float p1, p2;
		p1 = stof(pos1);
		p2 = stof(pos2);
		t2d.exportobj("new.obj", p1, p2);
		//t2d.exportT2D("T2D.txt");
		
	}//else ouverture

	system("pause");
}


