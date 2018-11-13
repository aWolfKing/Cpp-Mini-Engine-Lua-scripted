#include "mainwindow.h"
#include "rendering.h"
#include <iostream>



namespace mini_engine {


	namespace main_window {
		namespace default_functions {

			
			int reload_file_function::operator()() {
				mini_engine::main_window::sLua_manager.reload();
				return 0;
			}


			int draw_function::operator()(HWND window) {
				framework::texture& drawing_texture = mini_engine::rendering::draw_texture;

				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(window, &ps);
				
				https://stackoverflow.com/questions/26005744/how-to-display-pixels-on-screen-directly-from-a-raw-array-of-rgb-values-faster-t
				{
					HBITMAP bmp = CreateBitmap(drawing_texture.get_width(), drawing_texture.get_height(), 1, 8 * sizeof(COLORREF), (void*)drawing_texture.get_bytes_start());

					HDC source = CreateCompatibleDC(hdc);

					SelectObject(source, bmp);
					BitBlt(hdc, 0, 0, window_size_x, window_size_y, source, 0, 0, SRCCOPY);

					DeleteDC(source);
					DeleteObject(bmp);
				}			

				EndPaint(window, &ps);

				return 0;
			}
			

			int cleanup_function::operator()() {
				mini_engine::main_window::sLua_manager.cleanup();
				return 0;
			}


		}
	}


}