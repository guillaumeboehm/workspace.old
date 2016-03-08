#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <iostream>
#include <fstream>

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char ubyte;

/********************************
	classe GrayImage
*****************************/

class GrayImage{
private:
	ushort width;	// Largeur
	ushort height;	//	Hauteur
	ubyte* array;	// Pointeur sur char(ubyte), alloue par la suite un tableau dynamique

public:
	GrayImage(ushort width, ushort height);	// Constructeur
	GrayImage(); 	// Constructeur par défaut
	GrayImage(const GrayImage& source);		// Constructeur par copie
	inline ~GrayImage() { delete [] array; }	// Destructeur
	
	// Différents accesseurs et mutateurs + surcharge opérateur () (foncteur)
	inline const ubyte& pixel(ushort x, ushort y) const { return array[y*width + x]; }	
	inline ubyte& pixel(ushort x, ushort y) { return array[y*width + x]; }
	inline const ubyte& operator() (ushort x, ushort y) const { return array[y*width + x]; }
	inline ubyte& operator () (ushort x, ushort y) { return array[y*width + x]; }
	
	void clear(ubyte =0);	// Tous les pixels de l'image prennent la valeur ubyte donnée
	void rectangle(ushort x, ushort y, ushort w, ushort h, ubyte color=0);
	void fillRectangle(ushort x, ushort y, ushort w, ushort h, ubyte color=0);

	void writeRAW(std::ostream& );	// Ecriture RAW 'brute'
	void writePGM(std::ostream& );	// Ecriture dans un fichier PGM

	static void skip_line(std::istream&);
	static void skip_comments(std::istream&);

	static GrayImage* readPGM(std::istream&); //lecture du PGM

	GrayImage* simpleScale(ushort, ushort) const; //redimmensionnement simple
	GrayImage* bilinearScale(ushort, ushort) const; // redimmensionnement bilinéaire


};

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

};

/********************************
	classe ColorImage
*****************************/

class ColorImage{
private:
	ushort width; //largeur
	ushort height; //hauteur
	Color* array; //tableau de pixels couleur
public:
	ColorImage(ushort w, ushort h); // Constructeur
	ColorImage(); 	// Constructeur par défaut
	ColorImage(const ColorImage& source);		// Constructeur par copie
	inline ~ColorImage(){ delete [] array;} //destructeur

	inline const Color& pixel(ushort x, ushort y) const { return array[y*width + x]; } //meme utilisation que ()
	inline Color& pixel(ushort x, ushort y) { return array[y*width + x]; } //meme utilisation que ()
	inline const Color& operator() (ushort x, ushort y) const { return array[y*width + x]; } //surcharge de () en R value
	inline Color& operator () (ushort x, ushort y) { return array[y*width + x]; } //surcharge de () en L value

	void clear(Color); //fonction pour mettre toute l'image a la même couleur
	void rectangle(ushort x, ushort y, ushort w, ushort h, Color color); //fonction pour créer les bordures d'un rectangle
	void fillRectangle(ushort x, ushort y, ushort w, ushort h, Color color); //fonction pour créer un rectangle rempli

	void writePPM(std::ostream& );	// Ecriture dans un fichier PPM
	static ColorImage* readPPM(std::istream&); //Lecture d'une image depuis un fichier PPM

	ColorImage* simpleScale(ushort w, ushort h) const; //Redimenssionnement simpliste
	ColorImage* bilinearScale(ushort w, ushort h) const; //Redimmensionnement bilinéaire

	void writeJPEG(const char* fname, unsigned int quality = 75) const; // Ecriture dans un fichier JPEG

	void writeTGA(std::ofstream& f) const; //Ecriture dans un fichier TGA
	static ColorImage* readTGA(std::ifstream& f); //Lecture dans un fichier TGA
};

#endif //IMAGE_HPP
