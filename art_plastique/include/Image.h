#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include "son.hpp"

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char ubyte;

/********************************
	classe Color
*****************************/

class Color{
private:
	ubyte red; //composante rouge
	ubyte green; //composante verte
	ubyte blue; //composante bleue
public:
	inline Color(ubyte _r = 255, ubyte _g = 255, ubyte _b = 255)	:red(_r), green(_g), blue(_b){} //constructeur
	inline ~Color(){}; //destructeur
	inline ubyte getRed() const{return red;} //getteur de la composante rouge
	inline ubyte getGreen() const{return green;} //getteur de la composante verte
	inline ubyte getBlue() const{return blue;} //getteur de la composante bleue
	inline void setColor(const ubyte& _r,const ubyte& _g,const ubyte& _b){red = _r; green = _g; blue = _b;} //setteur de la couleur
	friend inline Color operator* (const float& f, const Color& color) { return Color(color.red*f, color.green*f, color.blue*f); }
	friend inline Color operator+ (const Color& c1, const Color& c2) { return Color(c1.red+c2.red, c1.green+c2.green, c1.blue+c2.blue); }
	inline void fromCMY(ubyte c, ubyte m, ubyte y) { this->red = 1-c; this->green = 1-m; this->blue = 1-y;};
	inline ubyte getLuminance() { return (red + green + blue)/3; }
};

/********************************
	classe ColorImage
*****************************/

class ColorImage{
private:
	ushort width; //largeur
	ushort height; //hauteur
	Color* array; //tableau de pixels couleur


	//membres utiles au traitement de l'image
	ubyte* lum; // le tableau qui associe a chaque pixel ça luminescence



	//................................

public:
	ColorImage(ushort w, ushort h); // Constructeur
	ColorImage(); 	// Constructeur par défaut
	ColorImage(const ColorImage& source);		// Constructeur par copie
	inline ~ColorImage(){ //destructeur
		delete [] array;
		delete [] lum;
	}
	inline const Color& pixel(ushort x, ushort y) const { return array[y*width + x]; } //meme utilisation que ()
	inline Color& pixel(ushort x, ushort y) { return array[y*width + x]; } //meme utilisation que ()
	inline Color& pixel(int x) { return array[x]; } //meme utilisation que ()
	inline const Color& operator() (ushort x, ushort y) const { return array[y*width + x]; } //surcharge de () en R value
	inline Color& operator () (ushort x, ushort y) { return array[y*width + x]; } //surcharge de () en L value

	inline ubyte* getLum() const{ return lum; }
	inline ushort getWidth() const{ return width; }
	inline ushort getHeight() const{ return height; }

	ColorImage* simpleScale(ushort w, ushort h) const;

	void clear(Color); //fonction pour mettre toute l'image a la même couleur

	static ColorImage* readTGA(std::ifstream& f); //Lecture dans un fichier TGA
	static ColorImage* readJPEG(const char* );
	void makeLuminance();
};

#endif //IMAGE_HPP
