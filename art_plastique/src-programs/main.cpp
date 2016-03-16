#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cmath>
#include <time.h>
#include <iomanip>
#include <cstdlib>

#define MAX_VALUE 97392

#include "MidiFile.h"

#include "Image.h"
#include "son.hpp"

bool img_ok = false;
bool quit = false;
std::string name;

int max_value = MAX_VALUE;

void createMelody(ColorImage* img, std::string name){

	int melody_size = img->getWidth() * img->getHeight();
	if(max_value < melody_size)
		max_value = melody_size;

	vector<uchar> midievent;     // temporary storage for MIDI events

	srand(time(NULL));
	// data to write to MIDI file: (60 = middle C)
	int melody[melody_size];
	int mrhythm[melody_size];
	int mvolumer[melody_size];
	int mvolumeg[melody_size];
	int mvolumeb[melody_size];
	for(int i=0; i<melody_size-1; ++i){
		mrhythm[i] = 1;
		melody[i] = ((img->getLum()[i])/3)+50;
		mvolumer[i] = img->pixel(i).getRed()/4;
		mvolumeg[i] = img->pixel(i).getGreen()/2;
		mvolumeb[i] = img->pixel(i).getBlue();
	}
	melody[melody_size] = -1;
	mrhythm[melody_size] = -1;
	mvolumer[melody_size] = -1;
	mvolumeg[melody_size] = -1;
	mvolumeb[melody_size] = -1;



	MidiFile outputfile;        // create an empty MIDI file with one track
	outputfile.absoluteTicks();  // time information stored as absolute time
	                       // (will be coverted to delta time when written)
	outputfile.addTrack(3);     // Add another two tracks to the MIDI file
	
	midievent.resize(3);        // set the size of the array to 3 bytes
	int tpq = 120;              // default value in MIDI file is 48
	outputfile.setTicksPerQuarterNote(tpq);

	// store a melody line in track 1 (track 0 left empty for conductor info)
	int i=0;
	int actiontime = 0;      // temporary storage for MIDI event time
	while (melody[i] >= 0) {
		midievent[2] = mvolumer[i];

		midievent[0] = 0x91;     // store a note on command (MIDI channel 1)
		if(i<=82)
		midievent[1] = 38;// drums 31 -> 82 45!!!!!
		outputfile.addEvent(1, actiontime, midievent);
		actiontime += tpq * mrhythm[i];
		midievent[0] = 0x81;     // store a note off command (MIDI channel 1)
		outputfile.addEvent(1, actiontime, midievent);
		i++;
	}

	// store a melody line in track 2 (track 0 left empty for conductor info)
	int j=0;
	int actiontime2 = 0;      // temporary storage for MIDI event time
	midievent[1] = 31; //bass grave
	while (melody[j] >= 0) {
		midievent[2] = mvolumeg[j];

		midievent[0] = 0x99;     // store a note on command (MIDI channel 1)
		outputfile.addEvent(2, actiontime2, midievent);
		actiontime2 += tpq * mrhythm[j];
		midievent[0] = 0x89;     // store a note off command (MIDI channel 1)
		outputfile.addEvent(2, actiontime2, midievent);
		j++;
	}

	// store a melody line in track 2 (track 0 left empty for conductor info)
	int k=0;
	int actiontime3 = 0;      // temporary storage for MIDI event time
	midievent[1] = 45; //bass grave
	while (melody[k] >= 0) {
		midievent[2] = mvolumeb[k];

		midievent[0] = 0x99;     // store a note on command (MIDI channel 1)
		outputfile.addEvent(2, actiontime3, midievent);
		actiontime3 += tpq * mrhythm[k];
		midievent[0] = 0x89;     // store a note off command (MIDI channel 1)
		outputfile.addEvent(2, actiontime3, midievent);
		k++;
	}

	

	outputfile.sortTracks();         // make sure data is in correct order
	std::string name_midi = "../" + name + ".mid";
	outputfile.write(name_midi); // write Standard MIDI File twinkle.mid














}

int main(int argc,char *argv[])
{

	std::cout<<argv[1];

	//chargement de l'image
	ColorImage* img = NULL;
	while(!img_ok && !quit){

		std::cout<<"Entrez le nom de l'image : ('q' pour annuler)"<<std::endl;
		std::cin>>name;

		//name = "test_big.tga";
		if(name == "q")
			quit = true; // si q on quitte

		else{ //sinon on lis le fichier
			std::string tempName = "../" + name + ".jpg";
			//std::ifstream s(tempName/*.c_str()*/, std::ios::binary);
			//img = ColorImage::readTGA(s);
			img = ColorImage::readJPEG(tempName.c_str());
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

		ColorImage* img_temp = img->simpleScale(50, 50);
		delete img;
		img = img_temp;
		img->makeLuminance();
/*
		ushort w = img->getWidth();
		ushort h = img->getHeight();
		Son son(uint(w * h));
		son.setDATA((unsigned char*)img->getLum());
		son.ecrire_wav(name);*/
	

	//....................

	createMelody(img, name);

	if(img != NULL && !quit) delete img; //si il y a une image dans img on libere la memoire
}

	return 0;
}
