#include "Image.h"
#include <stdexcept>
#include <string>
#include "jpeglib.h"

const char *identifier="boehm_g";
const char *informations=
 "Je rajoute ici que j'ai également corrigé le décalage occasionné par le redimmensionnement bilinéaire.\n\n"
 "J'ai cru remarquer en codant l'ecriture du sous-format avec compression rle des images TGA que "
 "votre image chat_rle change de raw packet si la ligne est dépassé, de la même façon que pour les "
 "run_lenght packets, seulement il me semble,\nd'après se que j'ai compris de la doc, que les raw packets "
 "n'ont pas a etre changés à un changement de ligne, c'est peut-être une erreur de ma part, mais cela "
 "dis, je ne vois pas de difference à l'oeil entre mon image et la votre, alors que la mienne est moins "
 "lourde... je pensais interressant de vous en informer.\n"
 "De plus, je n'ai pas vraiment compris pourquoi un petit bout de l'image manquait en bas à droite, mais "
 "étant donné qu'il en est de même pour votre image, je n'ai pas vraiment cherché plus, j'ai tout de même aperçu que"
 "la lecture de l'image rle redonnait ensuite la bonne image en la réécrivant sous un format autre que tga compréssé rle.\n"
 "erreur de segmentation dans la fonction readMaison";

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
	for(uint i=x; i<uint(x+w); ++i){
		pixel(i,y) = color;
		if(h>1) pixel(i,y+h-1) = color;
	}
	for(uint i=y; i<y+h; ++i){
		pixel(x,i) = color;
		if(w>1) pixel(x+w-1,i) = color;
	}
}

void GrayImage::fillRectangle(ushort x, ushort y, ushort w, ushort h, ubyte color){//dessine un rectangle plein
	for(uint i=y; i<y+w; ++i)
		for(uint j=x; j<x+h; ++j){
			pixel(i,j) = color;
		}
}

void GrayImage::writeRAW(std::ostream& f){

	if(!f)
		throw std::runtime_error("erreur à l'ouverture du fichier destination");

	ubyte tmp[4];
	// poids faibles  |  poids forts
	tmp[0]=width%256;	tmp[1]=width>>8;
	tmp[2]=height%256;	tmp[3]=height>>8;
	f.write((const char*)tmp, 4);
	f.write((const char*)array, width*height);
}

void GrayImage::writePGM(std::ostream& f){

	if(!f)
		throw std::runtime_error("erreur à l'ouverture du fichier destination");

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

	if(!f)
		throw std::runtime_error("erreur à l'ouverture du fichier source");

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

GrayImage* GrayImage::bilinearScale(ushort w, ushort h) const{
	GrayImage* iprime = new GrayImage(w,h);

	for(ushort yprime=0; yprime<h; ++yprime)
		for(ushort xprime=0; xprime<w; ++xprime){
			double x = ((double(xprime+0.5)/w)* width)-0.5;
			double y = ((double(yprime+0.5)/h)* height)-0.5;
			ushort xi=ushort(x);
			ushort yi=ushort(y);
			ushort xiPone = (xi+1 >= width ? xi : xi+1);
			ushort yiPone = (yi+1 >= height ? yi : yi+1);
			double lambdA = x - xi;
			double mU = y - yi;

            if(mU < 0) mU *= -1; //corrige le décalage
            if(lambdA < 0) lambdA *= -1;

			iprime->pixel(xprime, yprime)=(1-lambdA)*(1-mU)*pixel(xi, yi)
										 +(1-lambdA)*mU*pixel(xi, yiPone)
										 +lambdA*(1-mU)*pixel(xiPone, yi)
										 +lambdA*mU*pixel(xiPone, yiPone);
		}

	return iprime;
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
	for(uint i=x; i<uint(x+w); ++i){
		pixel(i,y) = color;
		if(h>1) pixel(i,y+h-1) = color;
	}
	for(uint i=y; i<y+h; ++i){
		pixel(x,i) = color;
		if(w>1) pixel(x+w-1,i) = color;
	}
}

void ColorImage::fillRectangle(ushort x, ushort y, ushort w, ushort h, Color color){
	for(uint i=y; i<y+w; ++i)
		for(uint j=x; j<x+h; ++j){
			pixel(i,j) = color;
		}
}

void ColorImage::writePPM(std::ostream& f){

	if(!f)
		throw std::runtime_error("erreur à l'ouverture du fichier destination");

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
	ColorImage* iprime = new ColorImage(w,h);

	for(ushort yprime=0; yprime<h; ++yprime)
		for(ushort xprime=0; xprime<w; ++xprime){
			double x = ((double(xprime+0.5)/w)* width)-0.5;
			double y = ((double(yprime+0.5)/h)* height)-0.5;
			ushort xi=ushort(x);
			ushort yi=ushort(y);
			ushort xiPone = (xi+1 >= width ? xi : xi+1);
			ushort yiPone = (yi+1 >= height ? yi : yi+1);
			double lambdA = x - xi;
			double mU = y - yi;

			if(lambdA < 0) lambdA *= -1; //corrige le décalage
			if(mU < 0) mU *= -1;

            iprime->pixel(xprime, yprime) = (1-lambdA)*(1-mU)*pixel(xi, yi)
									        + (1-lambdA)*mU*pixel(xi, yiPone)
									        + lambdA*(1-mU)*pixel(xiPone, yi)
        								    + lambdA*mU*pixel(xiPone, yiPone);
        }

	return iprime;
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

ColorImage* ColorImage::readJPEG(const char* fname){
    struct jpeg_decompress_struct jcomp;
    struct jpeg_error_mgr jerr;

    FILE * file;

    jcomp.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&jcomp);

    if ((file = fopen(fname, "rb")) == NULL)
        throw std::runtime_error("echec ouverture du fichier source de lecture de l'image JPEG");

    jpeg_stdio_src(&jcomp, file);
    jpeg_read_header(&jcomp, TRUE);
    jpeg_start_decompress(&jcomp);

    ushort width = jcomp.output_width;
    ushort height = jcomp.output_height;

    unsigned int row_stride = jcomp.output_width * jcomp.output_components;
    JSAMPARRAY buffer = (*jcomp.mem->alloc_sarray)
		((j_common_ptr) &jcomp, JPOOL_IMAGE, row_stride, 1);

    ColorImage* imgout = new ColorImage(width, height);

    while (jcomp.output_scanline < jcomp.output_height){
        (void) jpeg_read_scanlines(&jcomp, buffer, 1);
        for(ushort x=0; x < width; ++x)
        	//jcomp.output_scanline-1 à cause d'un décalage de l'image
        	imgout->pixel(x,jcomp.output_scanline-1).setColor(buffer[0][jcomp.output_components * x],
        													  buffer[0][jcomp.output_components * x+1],
        													  buffer[0][jcomp.output_components * x+2]);
    }

    jpeg_finish_decompress(&jcomp);
    jpeg_destroy_decompress(&jcomp);
    fclose(file);

    return imgout;
}

struct tab_rle{ // sert pour l'ecriture tga avec compression
	bool rl;
	Color color;
};

void ColorImage::writeTGA(std::ofstream& f,bool rle) const{

	if(!f)
		throw std::runtime_error("echec à l'ouverture du fichier de destination");

	//le tableau header comporte toutes les données du header de l'image
	ubyte header[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	header[12] = width & 0xFF; //ET logique pour recupérer le premier octet du ushort
	header[13] = (width >> 8) & 0xFF; //décalage binaire puis ET logique afin de récupérer le deuxieme octet du ushort
	header[14] = height & 0xFF;
	header[15] = (height >> 8) & 0xFF; //idem
	header[16] = 24;
	header[17] = 32; //permet de définir le début de l'image comme étant le coin haut-gauche de l'ecran
	/*SANS COMPRESSION RLE*/
	if(!rle){
		header[2] = 2; //sous format 2
		f.write((char*)header, 18);
		// le tableau pixels permet d'ecrire avec f.write() les composantes d'une Color
		ubyte pixels[3];
		for(int i=0; i<height; ++i) /*cette boucle se fait dans l'autre sens car l'image se dessine de bas en haut pendant
										la lecture du fichier je commence donc par ecrire le bas de l'image*/
			for(int j=0; j<width; ++j){
				pixels[2] = pixel(j,i).getRed(); // les composantes des couleurs sont sous le format BGR
				pixels[1] = pixel(j,i).getGreen();
				pixels[0] = pixel(j,i).getBlue();
				f.write((char*)pixels, 3);
			}
	}
	/*AVEC COMPRESSION RLE*/
	else{
		header[2] = 10; //sous format 10
		f.write((char*)header, 18);

		/**********cette partie sert à savoir à l'avance quel pixel sera a mettre dans un run length*********
		packet ou un raw packet*********/
		tab_rle* tab = new tab_rle[width*height]; //tableau qui stockera l'image

		for(int i=0; i<height; ++i)
			for(int j=0; j<width; ++j)
				tab[i*width + j].color = pixel(j,i); //recopie de l'image

		for(int i=0; i<width*height; ++i) //on parcours l'image
			tab[i].rl = false; //on met rl a faut dans un premier temps
			//si rl est a true, le pixel devra aller dans un run length packet, ou un raw packet sinon
		
		for(int i=0; i<width*height; ++i){
			while(i<width*height-1 && tab[i].color.getRed() == tab[i+1].color.getRed() &&
				  tab[i].color.getGreen() == tab[i+1].color.getGreen() &&
				  tab[i].color.getBlue() == tab[i+1].color.getBlue())
				tab[i++].rl = true; //rl du pixel i = true si le pixel i+1 a la même couleur

			if(i>0) //sert a mettre le rl du dernier pixel de la suite a true, ou non s'il est isolé au debut
					//d'une ligne
				if(tab[i-1].color.getRed() == tab[i].color.getRed() &&
				   tab[i-1].color.getGreen() == tab[i].color.getGreen() &&
				   tab[i-1].color.getBlue() == tab[i].color.getBlue() && i%width != 0)
					tab[i].rl = true;
		}
		/******************************/

		int count = 0;
		bool spec = false; /*spec sert à dire si un packet a été changé suite a un changement de ligne ou un
							packet plein, afin d'éviter deréécrire un packet*/
		for(int i=0; i<width*height; ++i){ //on parcours toute l'image
			spec = false;
			if(tab[i].rl){ //si le pixel doit etre ecrit dans un run length packet
				while(i<width*height-1 && tab[i].rl && tab[i+1].rl && tab[i].color.getRed() == tab[i+1].color.getRed() &&
			   				tab[i].color.getGreen() == tab[i+1].color.getGreen() &&
			   				tab[i].color.getBlue() == tab[i+1].color.getBlue()){
					spec = false;

					count++; //si la couleur est identique est qu'elle doit etre dans un run length packet on
					i++;	 //incremente un compteur

					if(count==128){ //si le packet est plein on change de packet
						char header_package[1] = {0};
						header_package[0] = count-1 + 128; //+ 128 afin de mettre le dernier bit a 1
						f.write(header_package, 1);
						char color_tmp[3] = {(char)tab[i].color.getBlue(), (char)tab[i].color.getGreen(), (char)tab[i].color.getRed()};
						f.write(color_tmp, 3);
						count=0;
						spec = true;
					}
					else if(i%width == 0){ //si la ligne est finie, il faut changer de packet
						char header_package[1] = {0};
						header_package[0] = count-1 + 128;
						f.write(header_package, 1);
						char color_tmp[3] = {(char)tab[i].color.getBlue(), (char)tab[i].color.getGreen(), (char)tab[i].color.getRed()};
						f.write(color_tmp, 3);
						count=0;
						spec = true;
					}
				}
				if(!spec){ //s'il n'y a pas eu de changement de ligne ou de packet plein
					char header_package[1] = {0};
					header_package[0] = count + 128;
					f.write(header_package, 1);
					char color_tmp[3] = {(char)tab[i].color.getBlue(), (char)tab[i].color.getGreen(), (char)tab[i].color.getRed()};
					f.write(color_tmp, 3);
					count=0;
				}
			}
			else{ //si le pixel doit aller dans un raw packet
				while(i<width*height && !tab[i].rl){
					spec = false;
					count++; //on incremente un compteur tant qu'il y a des pixels a mettre dans le raw packet
					i++;
					if(count==128){ //si le packet est plein on change de packet
						count--;
						char header_package[1] = {0};
						header_package[0] = count-1;
						f.write(header_package, 1);
						for(int j=i-count-1; j<i-1; ++j){
							char color_tmp[3] = {(char)tab[j].color.getBlue(), (char)tab[j].color.getGreen(), (char)tab[j].color.getRed()};
							f.write(color_tmp, 3);
						}
						count=0;
						--i;
						spec = true;
					}
				}
				if(!spec){//s'il n'y a pas eu de changement suite a un packet plein, on change de packet
					char header_package[1] = {0};
					header_package[0] = count-1;
					f.write(header_package, 1);
					for(int j=i-count; j<i; ++j){
						char color_tmp[3] = {(char)tab[j].color.getBlue(), (char)tab[j].color.getGreen(), (char)tab[j].color.getRed()};
						f.write(color_tmp, 3);
					}
					count=0;
					--i;
				}
			}
		}
		delete[] tab;
	}
}

ColorImage* ColorImage::readTGA(std::ifstream& f){

	if(!f)
		throw std::runtime_error("erreur à l'ouverture du fichier source");

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
		throw std::runtime_error( "wrong file format, please use RGB uncompressed or RGB colormapped uncompressed TGA images" ); //si le sous format n'est ni 1 ni 2
		delete img;
	}
	return img;
}

ColorImage* ColorImage::readMaison(std::istream& f){
	ubyte header[10];
	f.read((char*)header, 10);
	char* commentaire;
	f.read(commentaire, (int)header[6]);
	ushort _width = header[7];
	ushort _height = header[9];
	if(header[0] == 'M' && header[1] == 'a' && header[2] == 'i' && header[3] == 's' && header[4] == 'o' && header[5] == 'n'){
		ColorImage* img = new ColorImage(_width, _height);
		ubyte array_tmp[1];
		for(int i=0; i<_height; ++i){
			for(int j=0; j<_width-3; ++j){
				f.read((char*)array_tmp, 1);
				img->array[i*_width + j*3] = array_tmp[0];
			}
			for(int j=0; j<_width; ++j){
				f.read((char*)array_tmp, 1);
				img->array[i*_width + (j+1)*3] = array_tmp[0];
			}
			for(int j=0; j<_width; ++j){
				f.read((char*)array_tmp, 1);
				img->array[i*_width + (j+2)*3] = array_tmp[0];
			}
		}
		return img;
	}
	else
		throw std::runtime_error("Wrong Format");
}

ColorImage* ColorImage::anaglyphe() const{
	ColorImage* img = new ColorImage(width/2, height);
	for(int i=0; i<height; ++i){
		for(int j=0; j<width/2; ++j){
			img->pixel(j,i).setColor(pixel(j+width/2,i).getRed(), pixel(j,i).getGreen(), pixel(j,i).getBlue());
		}
	}
	return img;
}