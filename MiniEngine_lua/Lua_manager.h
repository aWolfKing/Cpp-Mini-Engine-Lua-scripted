#pragma once
#ifndef LUA_MANAGER_H
#define LUA_MANAGER_H

#include <string>
#include "framework_Lua.h"

extern "C" {
#include "Lua/lua.h"
#include "Lua/lauxlib.h"
#include "Lua/lualib.h"
}


namespace framework {


	class Lua_manager
	{
	public:
		Lua_manager();
		~Lua_manager();

		lua_State* Get_Lua_state();

		void initialize(); //Initialize manager and aqquire resources then load_file().
		void cleanup(); //If alive, unload_file() then release resources.
		void reload(); //unload_file() (if alive) then load_file().

		void set_file_path(std::string);
		void update_input(int x, int y, bool space);

		void call_lua_defined_function(std::string); //Calls the function defined in lua that has the name provided as argument. (for example: update30 or draw.)

	private:
		void unload_file();
		void load_file();
		void load_framework_libs();

		::lua_State* Lua_state;
		std::string file_name;
		bool alive;

		struct {
			std::string input_table_name = "input";
			std::string input_name_horizontal = "x";
			std::string input_name_vertical = "y";
			std::string input_name_space = "space";
		};

	};


}


#endif // !LUA_MANAGER_H


