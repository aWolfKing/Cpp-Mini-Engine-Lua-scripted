#pragma once
#ifndef RENDERING_H
#define RENDERING_H

#include "mainwindow.h"
#include "texture.h"



namespace mini_engine {
	namespace rendering{


		extern framework::texture draw_texture;

		void draw_background(unsigned char r, unsigned char g, unsigned char b);

		void draw_sprite(int x, int y, int id);

		void draw_square(int x, int y, int width, int height, unsigned char r, unsigned char g, unsigned char b);


	}
}



#endif // !RENDERING_H
