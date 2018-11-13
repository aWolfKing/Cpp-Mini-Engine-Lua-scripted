#include "Lua_manager.h"
#include "framework_Lua.h"

#include "lua_allowed_libs.h"


namespace framework {



	Lua_manager::Lua_manager() : file_name{"Game/test_game.Lua"} {
		this->alive = false;
	}

	Lua_manager::~Lua_manager() {
		this->cleanup();
	}


	lua_State* Lua_manager::Get_Lua_state() {
		if (this->alive) {
			return this->Lua_state;
		}
		return nullptr;
	}


	void Lua_manager::initialize() {
		this->alive = true;
		this->load_file();
	}

	void Lua_manager::cleanup() {
		this->unload_file();
		this->alive = false;
	}

	void Lua_manager::reload() {
		this->unload_file();
		this->load_file();
	}

	void Lua_manager::set_file_path(std::string path) {
		this->unload_file();
		this->file_name = path;
		this->load_file();
	}

	void Lua_manager::update_input(int x, int y, bool space) {
		if (this->alive) {
			/*
			lua_getglobal(this->Lua_state, this->input_table_name.c_str());
			lua_pushstring(this->Lua_state, this->input_name_horizontal.c_str());
			lua_gettable(this->Lua_state, -2);
			lua_pushnumber(this->Lua_state, x);
			lua_setfield(this->Lua_state, -3, this->input_name_horizontal.c_str());

			lua_getglobal(this->Lua_state, this->input_table_name.c_str());
			lua_pushstring(this->Lua_state, this->input_name_vertical.c_str());
			lua_gettable(this->Lua_state, -2);
			lua_pushnumber(this->Lua_state, y);
			lua_setfield(this->Lua_state, -3, this->input_name_vertical.c_str());

			lua_getglobal(this->Lua_state, this->input_table_name.c_str());
			lua_pushstring(this->Lua_state, this->input_name_space.c_str());
			lua_gettable(this->Lua_state, -2);
			lua_pushnumber(this->Lua_state, int{space});
			lua_setfield(this->Lua_state, -3, this->input_name_space.c_str());
			*/
			//Error?

			//ugly "solution"
			std::string ls = "input={};input.x=" + std::to_string(x) + ";input.y=" + std::to_string(y) + ";input.space=" + std::to_string(space) + ";";
			luaL_loadstring(this->Lua_state, ls.c_str());
			lua_pcall(this->Lua_state, 0, 0, 0);
			

		}
	}

	void Lua_manager::call_lua_defined_function(std::string function_name) {
		if (this->alive) {
			lua_getglobal(this->Lua_state, function_name.c_str());
			if (lua_isfunction(this->Lua_state, -1)) {
				lua_pcall(this->Lua_state, 0, 0, 0);
			}
		}
	}

	void Lua_manager::unload_file() {
		if (this->alive) {
			lua_close(this->Lua_state);
		}
	}

	void Lua_manager::load_file() {
		this->Lua_state = luaL_newstate();
		luaL_open_allowed_libs(this->Lua_state);
		this->load_framework_libs();
		luaL_loadfile(this->Lua_state, this->file_name.c_str());
		lua_pcall(this->Lua_state, 0, 0, 0);
	}

	void Lua_manager::load_framework_libs() {
		if (this->alive) {

			lua_pushcfunction(this->Lua_state, framework::Lua::Lua_background);
			lua_setglobal(this->Lua_state, std::string{"background"}.c_str());
			lua_pcall(this->Lua_state, 0, 0, 0);

			lua_pushcfunction(this->Lua_state, framework::Lua::Lua_drawsprite);
			lua_setglobal(this->Lua_state, std::string{"drawsprite"}.c_str());
			lua_pcall(this->Lua_state, 0, 0, 0);

			lua_pushcfunction(this->Lua_state, framework::Lua::Lua_drawsquare);
			lua_setglobal(this->Lua_state, std::string{"drawsquare"}.c_str());
			lua_pcall(this->Lua_state, 0, 0, 0);

			lua_pushcfunction(this->Lua_state, framework::Lua::Lua_print);
			lua_setglobal(this->Lua_state, std::string{"print"}.c_str());
			lua_pcall(this->Lua_state, 0, 0, 0);

			
			lua_createtable(this->Lua_state, 0, 3);

			lua_pushnumber(this->Lua_state, 0);
			lua_setfield(this->Lua_state, -2, this->input_name_horizontal.c_str());
			
			lua_pushnumber(this->Lua_state, 0);
			lua_setfield(this->Lua_state, -2, this->input_name_vertical.c_str());

			lua_pushnumber(this->Lua_state, 0);
			lua_setfield(this->Lua_state, -2, this->input_name_space.c_str());

		}
	}



}