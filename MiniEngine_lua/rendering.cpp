#include "rendering.h"
#include <iostream>

namespace mini_engine {
	namespace rendering {

		framework::texture draw_texture = framework::texture{ unsigned int{window_size_x }, unsigned int{window_size_y } };


		void draw_background(unsigned char r, unsigned char g, unsigned char b) {
			framework::texture& drawing_texture = mini_engine::rendering::draw_texture;

			COLORREF* pixels_start = drawing_texture.get_bytes_start();			
			if (pixels_start) {
				for (int i = 0; i < (drawing_texture.get_width()*drawing_texture.get_height()); ++i) {
					//new (&((i * 3)[pixels_start])) unsigned char[3]{ r, g, b};
					*(pixels_start + i) = RGB(b, g, r);
				}
			}

		}


		void draw_sprite(int x, int y, int id) {
			//check if id is valid
		}


		void draw_square(int x, int y, int width, int height, unsigned char r, unsigned char g, unsigned char b) {
			framework::texture& drawing_texture = mini_engine::rendering::draw_texture;

			COLORREF* pixels_start = drawing_texture.get_bytes_start();
			if (pixels_start) {
				int x_end = x + width, y_end = y + height;
				if (x < x_end && y < y_end && 0 < x_end && 0 < y_end) {
					if (x < 0) {
						x = 0;
					}
					if (y < 0) {
						y = 0;
					}
					if (!(x_end < drawing_texture.get_width())) {
						x_end = drawing_texture.get_width();
					}
					if (!(y_end < drawing_texture.get_height())) {
						y_end = drawing_texture.get_height();
					}
					int num_x = x_end - x, num_y = y_end - y;
					if (0 < num_x && 0 < num_y) {
						for (int cy{ 0 }; cy < num_y; ++cy)
							for (int cx{ 0 }; cx < num_x; ++cx) {
								*(pixels_start + (x + cx) + ((y + cy) * drawing_texture.get_width())) = RGB(b, g, r);
							}
					}
				}
			}

		}


	}
}