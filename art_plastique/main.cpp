#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>

#include "Image.h"

bool img_ok = false;
bool quit = false;

int main(int argc,char *argv[])
{

	//chargement de l'image
	ColorImage* img;
	while(!img_ok && !quit){

		std::cout<<"Entrez le nom de l'image : ('q' pour annuler)"<<std::endl;
		std::string name;
		std::cin>>name;

		if(name == "q")
			quit = true; // si q on quitte

		else{ //sinon on lis le fichier
			std::ifstream s(name.c_str(), std::ios::binary);
			img = ColorImage::readTGA(s);
			if(img == NULL){
				std::cerr<<"Erreur : impossible d'ouvrir l'image"<<std::endl;
			}
			else
				img_ok = true;
		}
		
	}
	//....................

	//traitement de l'image

	if(!quit){ //si l'action de quitter n'a pas été appelé





	}

	//....................

	if(img != NULL && !quit) delete img; //si il y a une image dans img on libere la memoire
	return 0;
}

