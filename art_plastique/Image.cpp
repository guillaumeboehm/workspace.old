#include "Image.h"
#include <stdexcept>
#include <string>

/**********************************************************************
	fonctions de ColorImage
*****************************/

ColorImage::ColorImage(ushort w, ushort h)
	:width(w), height(h), array(0)
{
	array = new Color[width*height];
}

ColorImage::ColorImage()
	:array(0)
{ throw std::runtime_error("It's ilegal to create a ColorImage's instance without parameters."); }

ColorImage::ColorImage(const ColorImage& source)
	:width(source.width), height(source.height), array(new Color[width*height])
{ for(uint i=0; i<uint(width*height); ++i) array[i]=source.array[i]; }


void ColorImage::clear(Color color){
	for(uint i=0; i<uint(width*height);++i)
		array[i] = color;
}

ColorImage* ColorImage::readTGA(std::ifstream& f){

	if(!f)
		return NULL;

	ubyte header[18];
	f.read((char*)header,18);

	ubyte Image_id_field = header[0]; //la taille en octets du champ image identification field

	ubyte TGA_type = header[2]; //le sous format de l'image TGA

	short cm_length = header[5] + (header[6]*256); //le nombre de couleurs dans la palette
	ubyte cm_size = header[7]; //la taille en bits de chaque couleur

	short _width = header[12] + (header[13]*256); //la largeur de l'image
	short _height = header[14] + (header[15]*256); //la hauteur de l'image
	ubyte img_desc = header[17];

	ColorImage* img = new ColorImage(_width, _height);
	f.read(NULL, Image_id_field); //enleve le champ Image identification field
	if(TGA_type == 2){ //Image RGB non compessée
		ubyte pixels[3];
		if((img_desc & 0x20) == 32) //si l'image est à l'endroit
			for(int i=0; i<_height; ++i)
				for(int j=0; j<_width; ++j){
					/*les pixels etant ecrits BGR et de bas en haut sur l'image
					je trouvais judicieux d'utiliser cette boucle*/
					f.read((char*)pixels, 3);
					img->pixel(j,i).setColor((ubyte)pixels[2],(ubyte)pixels[1],(ubyte)pixels[0]);
				}			
		else
			for(int i=_height-1; i>=0; --i)
				for(int j=0; j<_width; ++j){
					/*les pixels etant ecrits BGR et de bas en haut sur l'image
					je trouvais judicieux d'utiliser cette boucle*/
					f.read((char*)pixels, 3);
					img->pixel(j,i).setColor((ubyte)pixels[2],(ubyte)pixels[1],(ubyte)pixels[0]);
				}
	}
	else if(TGA_type == 1){ //Image RGB non compessée avec palette de couleur
		ubyte* cm = new ubyte[cm_length*3];
		if(cm_size==24){ // si la palette est codé sur 24bits
			f.read((char*)cm, cm_length*3);
		}
		else if(cm_size==32){ // si la palette est codé sur 32bits
			ubyte tmp[3];
			for(int i=0; i<cm_length*3; ++i){
				f.read((char*)tmp, 3); //recupere les 3 octets RGB
				cm[i] = tmp[0];
				cm[i+1] = tmp[1];
				cm[i+2] = tmp[2];
				f.read(NULL, 1); //sers a enlever l'octet attribut
				i+=2;
			}
		}
		/* on ne se préocupe pas du codage de la palette sur 15 et 16 bits
		car notre image n'est pas en niveau de gris*/
		ubyte pixels[1];
		if((img_desc & 0x20) == 32) //si l'image est à l'endroit
			for(int i=0; i<_height; ++i)
				for(int j=0; j<_width; ++j){
					f.read((char*)pixels, 1);
					/*on recupere l'index du la couleur du pixel dans la palette dans pixels
					puis on colore les pixels grace à cm*/
					img->pixel(j,i).setColor((ubyte)cm[(pixels[0]*3)+2],(ubyte)cm[(pixels[0]*3)+1],(ubyte)cm[pixels[0]*3]);
				}
		else
			for(int i=_height-1; i>=0; --i)
				for(int j=0; j<_width; ++j){
					f.read((char*)pixels, 1);
					/*on recupere l'index du la couleur du pixel dans la palette dans pixels
					puis on colore les pixels grace à cm*/
					img->pixel(j,i).setColor((ubyte)cm[(pixels[0]*3)+2],(ubyte)cm[(pixels[0]*3)+1],(ubyte)cm[pixels[0]*3]);
				}
		delete cm;
	}
	else if(TGA_type == 10){ //sous-format 10 TGA couleur compréssé rle
		int comp = 0;
		ubyte head[1]; //stocke le header du packet
		ubyte color[3];
		ubyte cl_count; //stocke le nombre d'elements apres le packet

		if((img_desc & 0x20) == 32) //si l'image est à l'endroit
			while(comp < _width*_height){ //on parcours l'image
				f.read((char*)head, 1);
				cl_count = (head[0] & 0x7F) + 1;
				if((head[0] & 0x80) == 128){ //si le packet est un run length packet
					f.read((char*)color, 3);
					for(int i=0; i<cl_count; ++i){
						img->pixel(comp%_width, comp/_width).setColor(color[2], color[1], color[0]);
						comp++;
					}
					cl_count=0;
				}
				else{ //si le packet est un raw packet
					for(int i=0; i<cl_count; ++i){
						f.read((char*)color, 3);
						img->pixel(comp%_width, comp/_width).setColor(color[2], color[1], color[0]);
						comp++;
					}
					cl_count=0;
				}
			}
		else //si l'image est à l'envers idem à à l'endroit sauf pour la copie de la couleur dans img
			while(comp < _width*_height){
				f.read((char*)head, 1);
				cl_count = (head[0] & 0x7F) + 1;
				if((head[0] & 0x80) == 128){
					f.read((char*)color, 3);
					for(int i=0; i<cl_count; ++i){
						/*_height-(comp/_width)-1 au lieu de comp/width afin de commencer par la fin de l'image*/
						img->pixel(comp%_width, _height-(comp/_width)-1).setColor(color[2], color[1], color[0]);
						comp++;
					}
					cl_count=0;
				}
				else{
					for(int i=0; i<cl_count; ++i){
						f.read((char*)color, 3);
						img->pixel(comp%_width, _height-(comp/_width)-1).setColor(color[2], color[1], color[0]);
						comp++;
					}
					cl_count=0;
				}
			}
	}
	else{
		delete img;
		return NULL;
	}
	return img;
}