#ifndef SON_HPP
#define SON_HPP

struct Header{ //44 octets
	char        RIFF[4];          // "RIFF"
	int     total_size;    // data_size + header (44 bits) - 8 octets(RIFF et total_size)
	char        WAVE[4];     // "WAVE"
	char        fmt[4];     // "fmt"
	int     block_size;         // 16 for PCM format
	short     format;            // 1 for PCM format
	short     channels;       // channels
	int     frequency;      // sampling frequency
	int     bytes_per_second;
	short     bytes_per_block;
	short     bits_per_sample;
	char        data[4];        // "data"
	int     data_size; // en octets
};

class Son {

private:
	unsigned char* DATA;
	Header header;

public:
	Son(unsigned int);
	inline ~Son(){};

	inline void setDATA(unsigned char* lum){ DATA = lum; }

	void ecrire_wav(std::string);


};

#endif
