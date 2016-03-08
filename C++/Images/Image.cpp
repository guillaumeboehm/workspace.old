#include "Image.hpp"
#include <stdexcept>
#include <string>
#include "jpeglib.h"

/**********************************************************************
	fonctions de GrayImage
*****************************/

GrayImage::GrayImage(ushort w, ushort h)
	:width(w), height(h), array(0)
{ array = new ubyte[width*height]; }

GrayImage::GrayImage()
	:array(0)
{ throw std::runtime_error("It's ilegal to create a GrayImage's instance without parameters."); }

GrayImage::GrayImage(const GrayImage& source)
	:width(source.width), height(source.height), array(new ubyte[width*height])
{ for(uint i=0; i<uint(width*height); ++i) array[i]=source.array[i]; }

void GrayImage::clear(ubyte gray){ //colore toute l'image du niveau de gris donné
	for(uint i=0; i<uint(width*height);++i) 
		array[i]=gray; 
}

void GrayImage::rectangle(ushort x, ushort y, ushort w, ushort h, ubyte color){ //dessine un rectangle non plein
	for(uint i=x; i<uint(x+w+1); ++i){
		pixel(i,y) = color;
		pixel(i,y+h) = color;
	}
	for(uint i=y+1; i<y+h; ++i){
		pixel(x,i) = color;
		pixel(x+w,i) = color;
	}
}

void GrayImage::fillRectangle(ushort x, ushort y, ushort w, ushort h, ubyte color){//dessine un rectangle plein
	for(uint i=y; i<y+w; ++i)
		for(uint j=x; j<x+h; ++j){
			pixel(i,j) = color;
		}
}

void GrayImage::writeRAW(std::ostream& f){
	ubyte tmp[4];
	// poids faibles  |  poids forts
	tmp[0]=width%256;	tmp[1]=width>>8;
	tmp[2]=height%256;	tmp[3]=height>>8;
	f.write((const char*)tmp, 4);
	f.write((const char*)array, width*height);
}

void GrayImage::writePGM(std::ostream& f){
	f<<"P5\n"; // Magic Number
	f<<"# Commentaire \n";
	f<<width<<" "<<height<<std::endl; // Utilisation de l'operateur injection car il s'agit de texte
	f<<"# Commentaire 2 \n";
	f<<"255\n"; // Valeur max des niveaux de gris
	//> No more comments here
	f.write((const char*)array, width*height);
}

// skip_line(is) permet de sauter toute une série d'octets de "is" jusqu'à trouver un '\n'
void GrayImage::skip_line(std::istream& is)
{
 char c;
 do {
  is.get(c);      // Lire un caractère
 } while(c!='\n'); // tant qu'on n'atteint pas la fin de ligne.
}

// skip_comments(is) utilise la fonction précédente pour sauter zéro, une ou plusieurs lignes
// de commentaires débutées par '#' et allant jusqu'à '\n'.
void GrayImage::skip_comments(std::istream& is)
{
 char c;
 is.get(c);       // Lire un caractère.
 while(c=='#')    // Tant que c'est un '#'.
  {
   skip_line(is); // On élimine les caractères jusqu'à la fin de ligne,
   is.get(c);     // Et on lit un nouveau caractère.
  }
 is.putback(c);   // On remet le caractère lu puisqu'il n'est pas un '#'.
}

GrayImage* GrayImage::readPGM(std::istream& f){
	//en connaissant le format de l'image on peut isoler les informations utiles
	std::string s;
	ushort width, height;
	ubyte gray_level;
	f>>s;
	GrayImage::skip_line(f);
	GrayImage::skip_comments(f);
	f>>width;
	f>>height;
	GrayImage::skip_line(f);
	GrayImage::skip_comments(f);
	f>>gray_level;
	GrayImage::skip_line(f);

	if(s == "P5"){ //si l'image est du sous-format P5 on crée une nouvelle image et on remplit le tableau de pixels
		GrayImage* temp = new GrayImage(width, height);
		f.read((char*)temp->array, width*height);
		return temp;
	}
	else if(s == "P2"){//sinon si elle est du sous-format P2 on crée une nouvelle image et on remplit le tableau de pixels
		GrayImage* temp = new GrayImage(width, height);
		for(ushort j=0; j<height; ++j)
			for(ushort k=0; k<width; ++k){
				int u;
				f >> u;
				temp->pixel(k,j) = ubyte(u);
			}
		return temp;
	}
	else throw std::runtime_error("Wrong Format !");//si elle n'est ni du sous-format P5, ni P2 alors on lance une exception
	
}

GrayImage* GrayImage::simpleScale(ushort w, ushort h) const{ //redimensionne l'image simplement
	GrayImage* i_prime = new GrayImage(w,h);
	for(ushort y_prime=0; y_prime<h; ++y_prime)
		for(ushort x_prime=0; x_prime<w; ++x_prime){
			double x = ((double)x_prime)/w*width;
			double y = ((double)y_prime)/h*height;
			ushort xi = (ushort)x;
			ushort yi = (ushort)y;
			i_prime->pixel(x_prime, y_prime) = pixel(xi,yi);
		}
		return i_prime;
}

GrayImage* GrayImage::bilinearScale(ushort w, ushort h) const{ //redimensionne l'image en faisant un croisement de
	GrayImage* i_prime = new GrayImage(w,h);				   //toutes les couleurs environantes
	for(ushort y_prime=0; y_prime<h; ++y_prime)
		for(ushort x_prime=0; x_prime<w; ++x_prime){
			double x = ((double)x_prime)/w*width;
			double y = ((double)y_prime)/h*height;
			ushort xi = (ushort)x;
			ushort yi = (ushort)y;
			ushort xip1 = (xi +1 >= width ? xi : xi+1);
			ushort yip1 = (yi +1 >= height ? yi : yi+1);
			double lambda = x - xi;
			double mu = y - yi;
			//calcul bilinéaire
			i_prime->pixel(x_prime,y_prime) = (1-lambda)*(1-mu)*pixel(xi,yi)+
											  (1-lambda)*mu*pixel(xi,yip1)+
											  lambda*(1-mu)*pixel(xip1,yi)+
											  lambda*mu*pixel(xip1,yip1);
		}
		return i_prime;
}

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

void ColorImage::rectangle(ushort x, ushort y, ushort w, ushort h, Color color){
	for(uint i=x; i<uint(x+w+1); ++i){
		pixel(i,y) = color;
		pixel(i,y+h) = color;
	}
	for(uint i=y+1; i<y+h; ++i){
		pixel(x,i) = color;
		pixel(x+w,i) = color;
	}
}

void ColorImage::fillRectangle(ushort x, ushort y, ushort w, ushort h, Color color){
	for(uint i=y; i<y+w; ++i)
		for(uint j=x; j<x+h; ++j){
			pixel(i,j) = color;
		}
}

void ColorImage::writePPM(std::ostream& f){
	f<<"P6\n"; // Magic Number
	f<<"# Commentaire \n";
	f<<width<<" "<<height<<std::endl; // Utilisation de l'operateur d'injectiob car il s'agit de texte
	f<<"# Commentaire 2 \n";
	f<<"255\n"; // Valeur max des niveaux de couleur
	//> No more comments here
	for(int i=0; i<height; ++i)
		for(int j=0; j<width; ++j)
			f<<pixel(j,i).getRed()<<pixel(j,i).getGreen()<<pixel(j,i).getBlue();
}

ColorImage* ColorImage::readPPM(std::istream& f){
	std::string s;
	ushort width, height;
	ubyte color_level;
	f>>s;
	GrayImage::skip_line(f);
	GrayImage::skip_comments(f);
	f>>width;
	f>>height;
	GrayImage::skip_line(f);
	GrayImage::skip_comments(f);
	f>>color_level;
	GrayImage::skip_line(f);

	if(s == "P6"){//si l'image est du sous-format P6
		ColorImage* temp = new ColorImage(width, height);
		for(ushort j=0; j<height; ++j)
			for(ushort k=0; k<width; ++k){
				ubyte r,g,b;
				r = f.get();
				g = f.get();
				b = f.get();
				temp->pixel(k,j).setColor(r,g,b);
			}
		return temp;
	}
	else if(s == "P3"){//sinon si l'image est du sous-format P3
		ColorImage* temp = new ColorImage(width, height);
		for(ushort j=0; j<height; ++j)
			for(ushort k=0; k<width; ++k){
				int r,g,b;
				f >> r >> g >> b;
				temp->pixel(k,j).setColor((ubyte)r,(ubyte)g,(ubyte)b);
			}
		return temp;
	}
	else throw std::runtime_error("Wrong Format !");//si l'image n'est ni P6 ni P3, lance une exception
}

ColorImage* ColorImage::simpleScale(ushort w, ushort h) const{
	ColorImage* i_prime = new ColorImage(w,h);
	for(ushort y_prime=0; y_prime<h; ++y_prime)
		for(ushort x_prime=0; x_prime<w; ++x_prime){
			double x = ((double)x_prime)/w*width;
			double y = ((double)y_prime)/h*height;
			ushort xi = (ushort)x;
			ushort yi = (ushort)y;
			i_prime->pixel(x_prime, y_prime) = pixel(xi,yi);
		}
		return i_prime;
}

ColorImage* ColorImage::bilinearScale(ushort w, ushort h) const{
	ColorImage* i_prime = new ColorImage(w,h);
	for(ushort y_prime=0; y_prime<h; ++y_prime)
		for(ushort x_prime=0; x_prime<w; ++x_prime){
			double x = ((((double)x_prime)+0.5)/w*width)-0.5;
			double y = ((((double)y_prime)+0.5)/h*height)-0.5;
			ushort xi = (ushort)x;
			ushort yi = (ushort)y;
			ushort xip1 = (xi +1 >= width ? xi : xi+1);
			ushort yip1 = (yi +1 >= height ? yi : yi+1);
			double lambda = x - xi;
			double mu = y - yi;
			if(lambda < 0)
				std::cerr<<lambda<<std::endl;
			//calcul bilinéaire pour chaque composantes d'une couleur
			i_prime->pixel(x_prime,y_prime).setColor((1-lambda)*(1-mu)*pixel(xi,yi).getRed()+
													  (1-lambda)*mu*pixel(xi,yip1).getRed()+
													  lambda*(1-mu)*pixel(xip1,yi).getRed()+
													  lambda*mu*pixel(xip1,yip1).getRed(),
													  (1-lambda)*(1-mu)*pixel(xi,yi).getGreen()+
													  (1-lambda)*mu*pixel(xi,yip1).getGreen()+
													  lambda*(1-mu)*pixel(xip1,yi).getGreen()+
													  lambda*mu*pixel(xip1,yip1).getGreen(),
													  (1-lambda)*(1-mu)*pixel(xi,yi).getBlue()+
													  (1-lambda)*mu*pixel(xi,yip1).getBlue()+
													  lambda*(1-mu)*pixel(xip1,yi).getBlue()+
													  lambda*mu*pixel(xip1,yip1).getBlue());
		}
		return i_prime;
}

void ColorImage::writeJPEG(const char* fname, unsigned int quality) const{

	struct jpeg_compress_struct jcomp;

	FILE * outfile;
	JSAMPROW row_pointer[1];

	jpeg_create_compress(&jcomp);

	if ((outfile = fopen(fname, "wb")) == NULL) {
		throw std::runtime_error( "echec ouverture du fichier destination d'ecriture de l'image JPEG" );
	}

	jpeg_stdio_dest(&jcomp, outfile);

	jcomp.image_width = width;
	jcomp.image_height = height;
	jcomp.input_components = 3;
	jcomp.in_color_space = JCS_RGB;

	jpeg_set_defaults(&jcomp);
	jpeg_set_quality(&jcomp,quality,TRUE);

	int row_stride = width;

	struct jpeg_error_mgr jerr;
	jcomp.err = jpeg_std_error(&jerr);

	jpeg_start_compress(&jcomp, TRUE);	

	while (jcomp.next_scanline < jcomp.image_height) {
		row_pointer[0] = (JSAMPROW)& array[jcomp.next_scanline * row_stride];
		(void) jpeg_write_scanlines(&jcomp, row_pointer, 1);
	}

	jpeg_finish_compress(&jcomp);

	fclose(outfile);
	jpeg_destroy_compress(&jcomp);
}

void ColorImage::writeTGA(std::ofstream& f) const{
	//le tableau header comporte toutes les données du header de l'image
	ubyte header[18] = {0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	header[12] = width & 0xFF;
	header[13] = (width >> 8) & 0xFF; //je n'ai pas totalement compris l'operateur >> mais je sais qu'il me permet
	header[14] = height & 0xFF;		  //d'avoir width%256
	header[15] = (height >> 8) & 0xFF;
	header[16] = 24;
	f.write((char*)header, 18);

	// le tableau pixels permet d'ecrire avec f.write() les composantes d'une Color
	ubyte pixels[3];
	for(int i=height-1; i>=0; --i) //cette boucle se fait dans l'autre sens car l'image se dessine de bas en haut pendant
								  //la lecture du fichier je commence donc par ecrire le bas de l'image
		for(int j=0; j<width; ++j){
			pixels[2] = pixel(j,i).getRed(); // l'ecriture semble se faire de la fin du tableau vers le debut, je n'ai
			pixels[1] = pixel(j,i).getGreen();// pas cerné pourquoi
			pixels[0] = pixel(j,i).getBlue();
			f.write((char*)pixels, 3);
		}
}

ColorImage* ColorImage::readTGA(std::ifstream& f){
	ubyte header[18];
	f.read((char*)header,18);
	ubyte Image_id_field = header[0];
	//char mapped = header[1];
	ubyte TGA_type = header[2];
	short _width = header[12] + (header[13]*256);
	short _height = header[14] + (header[15]*256);
	ColorImage* img = new ColorImage(_width, _height);
	//ubyte bits_per_pix = header[16];
	f.read(NULL, Image_id_field);
	if(TGA_type == 2){
		ubyte pixels[3];
		for(int i=_height-1; i>=0; --i)
			for(int j=0; j<_width; ++j){
				f.read((char*)pixels, 3);
				img->pixel(j,i).setColor((ubyte)pixels[2],(ubyte)pixels[1],(ubyte)pixels[0]);
			}
	}
	return img;
}