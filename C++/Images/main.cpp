#include "Image.hpp"
#include <iomanip>
#include <sstream>

int main(){
	Color color(255,0,0);

	std::ifstream g("chat.tga", std::ios::binary);
	std::ofstream f("chat2.tga", std::ios::binary);

	ColorImage* i = ColorImage::readTGA(g);

	//i = i->bilinearScale(823,400);

	i->writeTGA(f);

/*
	for(unsigned int quality=0;quality<=100;quality+=5)  {
		std::ostringstream oss; // Variable pour former le nom de chaque fichier.
		oss << "out_" << std::setfill('0') << std::setw(3) << quality << ".jpg";
		i->writeJPEG(oss.str().c_str(),quality);
	}
*/

	f.close();
	g.close();

	return 0;
}