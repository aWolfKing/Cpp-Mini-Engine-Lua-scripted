#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <functional>
#include "nfunction.h"
#include "stdafx.h"
#include "Lua_manager.h"
#include <string>




constexpr int window_size_x = 512;
constexpr int window_size_y = 512;

constexpr int window_framerate = 50;




namespace mini_engine {	
	namespace main_window {


		namespace default_functions {

			struct reload_file_function 
			{
				int operator () ();
			};

			struct draw_function
			{
				int operator () (HWND);
			};

			struct cleanup_function 
			{
				int operator () ();
			};

		}



		using window_function = framework::non_nullable_function<int>;
		

		static ::framework::Lua_manager sLua_manager = ::framework::Lua_manager{};

		static main_window::window_function reload_file = main_window::window_function{ main_window::default_functions::reload_file_function{} };

		static ::framework::non_nullable_function<int, HWND> paint = ::framework::non_nullable_function<int, HWND>{ main_window::default_functions::draw_function{} };

		static main_window::window_function on_destroy = main_window::window_function{ main_window::default_functions::cleanup_function{} };


	}
}



#endif // !MAINWINDOW_H