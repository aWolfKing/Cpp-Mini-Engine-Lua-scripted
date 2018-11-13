#include "texture.h"
#include <iostream>

namespace framework {



	texture::texture(unsigned int p_width, unsigned int p_heigth) : width{ p_width }, heigth{ p_heigth } {
		//this->bytes = new unsigned char[p_width * p_heigth * bytes_per_pixel];
		this->bytes = new COLORREF[p_width * p_heigth];
		std::cout << "colorref start init: " << this->bytes << std::endl;
	}

	texture::~texture() {
		delete[] this->bytes;
	}


	//unsigned char* texture::get_bytes_start() {
	COLORREF* texture::get_bytes_start(){
		return this->bytes;
	}

	unsigned long texture::number_of_bytes() {
		return this->width * this->heigth * bytes_per_pixel;
	}


	unsigned int texture::get_width() {
		return this->width;
	}

	unsigned int texture::get_height() {
		return this->heigth;
	}


}