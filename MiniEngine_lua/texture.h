#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include "stdafx.h"

namespace framework {


	constexpr unsigned char bytes_per_pixel = 3; //namely: r, g, b.



	class texture
	{
	public:
		texture() = delete;
		texture(unsigned int width, unsigned int height);
		~texture();

		/* Be carefull with what you do with this. */
		//unsigned char* get_bytes_start();
		COLORREF* get_bytes_start();
		/* Be carefull with what you do with this. */
		unsigned long number_of_bytes();

		unsigned int get_width();
		unsigned int get_height();

	private:
		unsigned int width;
		unsigned int heigth;
		//unsinged char* bytes;
		COLORREF* bytes;
	};


}


#endif // !TEXTURE_H
