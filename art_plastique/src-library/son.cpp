#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include "son.hpp"

Son::Son(unsigned int _l)
	:DATA(NULL)
{
	//initialise la structure

	header.RIFF[0] = 'R';
	header.RIFF[1] = 'I';
	header.RIFF[2] = 'F';
	header.RIFF[3] = 'F';

	header.WAVE[0] = 'W';
	header.WAVE[1] = 'A';
	header.WAVE[2] = 'V';
	header.WAVE[3] = 'E';

	header.fmt[0] = 'f';
	header.fmt[1] = 'm';
	header.fmt[2] = 't';
	header.fmt[3] = ' ';

	header.block_size = 0x10;
	header.format = 0x01;
	header.channels = 0x01;
	header.frequency = 0xac44;
	header.bits_per_sample = 0x8/*8*/;
	header.bytes_per_block = header.channels * (header.bits_per_sample / 8);
	header.bytes_per_second = header.frequency * (int)header.bytes_per_block;

	header.data[0] = 'd';
	header.data[1] = 'a';
	header.data[2] = 't';
	header.data[3] = 'a';

	header.data_size = _l;
	header.total_size = header.data_size + 44 - 8;
/*
	DATA = new unsigned char[header.data_size];
	for(unsigned int i=0; i<header.data_size; i+=10){
		DATA[i] = 0x01;
		DATA[i+1] = 0x02;
		DATA[i+2] = 0x03;
		DATA[i+3] = 0x04;
		DATA[i+4] = 0x05;
		DATA[i+5] = 0x06;
		DATA[i+6] = 0x05;
		DATA[i+7] = 0x04;
		DATA[i+8] = 0x03;
		DATA[i+9] = 0x02;
	}*/
}

void Son::ecrire_wav(std::string nameofwave){
	FILE * w = NULL;
	std::string name = nameofwave + ".wav";
	w = fopen(name.c_str(), "wb");

	fwrite(header.RIFF, 1, 4, w);
	fwrite(&header.total_size, 4, 1, w);
	fwrite(header.WAVE, 1, 4, w);
	fwrite(header.fmt, 1, 4, w);
	fwrite(&header.block_size, 4, 1, w);
	fwrite(&header.format, 2, 1, w);
	fwrite(&header.channels, 2, 1, w);
	fwrite(&header.frequency, 4, 1, w);
	fwrite(&header.bytes_per_second, 4, 1, w);
	fwrite(&header.bytes_per_block, 2, 1, w);
	fwrite(&header.bits_per_sample, 2, 1, w);
	fwrite(header.data, 1, 4, w);
	fwrite(&header.data_size, 4, 1, w);

	//std::cerr<<header.data_size<<" pixels"<<std::endl;

	fwrite(DATA, 1, header.data_size, w);

	fclose(w);
}
